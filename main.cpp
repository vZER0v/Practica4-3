#include "Producto.h"
#include "CuentaCorriente.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Declaraciones de funciones
vector<Producto*> cargarDatos();
void mostrarProductos(const vector<Producto*>& productos);
void modificarProductos(vector<Producto*>& productos);
void realizarCompra(vector<Producto*>& productos, vector<CuentaCorriente>& cuentas);
vector<CuentaCorriente> cargarCuentas();
CuentaCorriente crearCuenta();
void cambiarClaveCuenta(vector<CuentaCorriente>& cuentas);
void ingresarDineroCuenta(vector<CuentaCorriente>& cuentas);
void retirarDineroCuenta(vector<CuentaCorriente>& cuentas);

int main() {
    vector<Producto*> productos = cargarDatos();
    vector<CuentaCorriente> cuentas = cargarCuentas();

    int opcion;
    do {
        cout << "Menu Principal:\n1. Agregar Productos\n2. Modificar Productos\n3. Realizar Compra\n4. Agregar Cuenta\n5. Cambiar Clave de Cuenta\n6. Ingresar Dinero a Cuenta\n7. Retirar Dinero de Cuenta\n0. Salir\nIngrese una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                productos = cargarDatos();
                break;
            case 2:
                modificarProductos(productos);
                break;
            case 3:
                realizarCompra(productos, cuentas);
                break;
            case 4:
                cuentas.push_back(crearCuenta());
                break;
            case 5:
                cambiarClaveCuenta(cuentas);
                break;
            case 6:
                ingresarDineroCuenta(cuentas);
                break;
            case 7:
                retirarDineroCuenta(cuentas);
                break;
            case 0:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion no valida, intente de nuevo.\n";
        }
    } while (opcion != 0);

    // Limpiar memoria de productos
    for (Producto* producto : productos) {
        delete producto;
    }
    productos.clear();

    return 0;
}

// Implementaciones de funciones
vector<Producto*> cargarDatos() {
    vector<Producto*> productos;
    int opcion;
    string nombre, marca, fechaVencimiento, material;
    int precio, descuento, cantidad, garantia;
    do {
        cout << "Seleccione el tipo de producto a agregar (1-Comestible, 2-Electronico, 3-Aseo, 0-Terminar): ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 0) break;

        cout << "Ingrese el nombre del producto: ";
        getline(cin, nombre);
        cout << "Ingrese la marca: ";
        getline(cin, marca);
        cout << "Ingrese el precio: ";
        cin >> precio;
        cout << "Ingrese el descuento (%): ";
        cin >> descuento;
        cout << "Ingrese la cantidad en inventario: ";
        cin >> cantidad;
        cin.ignore();

        switch (opcion) {
            case 1:
                cout << "Ingrese la fecha de vencimiento (MM/AAAA): ";
                getline(cin, fechaVencimiento);
                productos.push_back(new Comestible(nombre, marca, precio, descuento, cantidad, fechaVencimiento));
                break;
            case 2:
                cout << "Ingrese la garantía (meses): ";
                cin >> garantia;
                cin.ignore();
                productos.push_back(new Electronico(nombre, marca, precio, descuento, cantidad, garantia));
                break;
            case 3:
                cout << "Ingrese el material: ";
                getline(cin, material);
                productos.push_back(new Aseo(nombre, marca, precio, descuento, cantidad, material));
                break;
        }
    } while (opcion != 0);

    return productos;
}

void mostrarProductos(const vector<Producto*>& productos) {
    for (const Producto* producto : productos) {
        producto->mostrarInformacion();
    }
}

void modificarProductos(vector<Producto*>& productos) {
    if (productos.empty()) {
        cout << "No hay productos para modificar." << endl;
        return;
    }
    mostrarProductos(productos);
    cout << "Ingrese el nombre del producto a modificar: ";
    string nombre;
    getline(cin, nombre);
    for (auto& producto : productos) {
        if (producto->getNombre() == nombre) {
            producto->modificarProducto();
            return;
        }
    }
    cout << "Producto no encontrado." << endl;
}

void realizarCompra(vector<Producto*>& productos, vector<CuentaCorriente>& cuentas) {
    if (productos.empty()) {
        cout << "No hay productos disponibles para la compra." << endl;
        return;
    }

    string numId, clave;
    cout << "Ingrese numero de identificacion para la cuenta: ";
    cin >> numId;
    cout << "Ingrese clave de la cuenta: ";
    cin >> clave;

    auto cuenta = find_if(cuentas.begin(), cuentas.end(), [&numId](const CuentaCorriente& cc) { return cc.getNumeroIdentificacion() == numId; });
    if (cuenta == cuentas.end() || !cuenta->validarClave(clave)) {
        cout << "Identificacion o clave incorrecta." << endl;
        return;
    }

    vector<pair<Producto*, int>> carrito;
    int total = 0;
    while (true) {
        mostrarProductos(productos);
        cout << "Ingrese el nombre del producto a comprar o 'finalizar' para terminar: ";
        string nombre;
        getline(cin, nombre);
        if (nombre == "finalizar") {
            break;
        }

        auto producto = find_if(productos.begin(), productos.end(), [&nombre](Producto* p) { return p->getNombre() == nombre; });
        if (producto == productos.end()) {
            cout << "Producto no encontrado." << endl;
            continue;
        }

        cout << "Ingrese la cantidad: ";
        int cantidad;
        cin >> cantidad;
        cin.ignore();

        if (cantidad > (*producto)->getCantidadInventario()) {
            cout << "Cantidad solicitada no disponible. Solo hay " << (*producto)->getCantidadInventario() << " unidades en inventario." << endl;
            continue;
        }

        int subtotal = (*producto)->getPrecio() * cantidad * (100 - (*producto)->getDescuento()) / 100;
        total += subtotal;
        carrito.push_back(make_pair(*producto, cantidad));
        (*producto)->venderProducto(cantidad);
        cout << "Producto aniadido al carrito. Subtotal: $" << subtotal << endl;
    }

    if (cuenta->getSaldo() < total) {
        cout << "Saldo insuficiente para realizar la compra. Total necesario: $" << total << ", Saldo disponible: $" << cuenta->getSaldo() << endl;
            } else {
                cuenta->retirarDinero(total, clave);
                cout << "Compra realizada exitosamente. Total: $" << total << ", Saldo restante: $" << cuenta->getSaldo() << endl;
            }
        }

        vector<CuentaCorriente> cargarCuentas() {
            vector<CuentaCorriente> cuentas;
            // Aqui se cargarian las cuentas desde una base de datos o archivo, por simplicidad se asume que ya hay cuentas.
            return cuentas;
        }

        CuentaCorriente crearCuenta() {
            string nombre, apellidos, direccion, telefono, numId, clave;
            double saldo;
            cout << "Ingrese nombre: "; getline(cin, nombre);
            cout << "Ingrese apellidos: "; getline(cin, apellidos);
            cout << "Ingrese direccion: "; getline(cin, direccion);
            cout << "Ingrese telefono: "; getline(cin, telefono);
            cout << "Ingrese saldo inicial: "; cin >> saldo; cin.ignore();
            cout << "Ingrese numero de identificacion: "; getline(cin, numId);
            cout << "Ingrese clave (dejar en blanco para clave por defecto): "; getline(cin, clave);
            return CuentaCorriente(nombre, apellidos, direccion, telefono, saldo, numId, clave.empty() ? "12345" : clave);
        }

        void cambiarClaveCuenta(vector<CuentaCorriente>& cuentas) {
            string numId, oldClave, newClave;
            cout << "Ingrese numero de identificacion: "; cin >> numId;
            cout << "Ingrese clave actual: "; cin >> oldClave;
            auto it = find_if(cuentas.begin(), cuentas.end(), [&numId](const CuentaCorriente& cc) { return cc.getNumeroIdentificacion() == numId; });
            if (it != cuentas.end() && it->validarClave(oldClave)) {
                cout << "Ingrese nueva clave: "; cin >> newClave;
                it->cambiarClave(newClave);
                cout << "Clave cambiada exitosamente." << endl;
            } else {
                cout << "Cuenta no encontrada o clave incorrecta." << endl;
            }
        }

        void ingresarDineroCuenta(vector<CuentaCorriente>& cuentas) {
            string numId, clave;
            double cantidad;
            cout << "Ingrese numero de identificación: "; cin >> numId;
            cout << "Ingrese clave: "; cin >> clave;
            auto it = find_if(cuentas.begin(), cuentas.end(), [&numId](const CuentaCorriente& cc) { return cc.getNumeroIdentificacion() == numId; });
            if (it != cuentas.end()) {
                cout << "Ingrese cantidad a ingresar: $"; cin >> cantidad;
                it->ingresarDinero(cantidad, clave);
                cout << "Dinero ingresado exitosamente. Nuevo saldo: $" << it->getSaldo() << endl;
            } else {
                cout << "Cuenta no encontrada." << endl;
            }
        }

        void retirarDineroCuenta(vector<CuentaCorriente>& cuentas) {
            string numId, clave;
            double cantidad;
            cout << "Ingrese numero de identificación: "; cin >> numId;
            cout << "Ingrese clave: "; cin >> clave;
            auto it = find_if(cuentas.begin(), cuentas.end(), [&numId, &clave](const CuentaCorriente& cc) { return cc.getNumeroIdentificacion() == numId && cc.validarClave(clave); });
            if (it != cuentas.end()) {
                cout << "Ingrese cantidad a retirar: $"; cin >> cantidad;
                if (it->getSaldo() >= cantidad) {
                    it->retirarDinero(cantidad, clave);
                    cout << "Dinero retirado exitosamente. Nuevo saldo: $" << it->getSaldo() << endl;
                } else {
                    cout << "Saldo insuficiente." << endl;
                }
            } else {
                cout << "Cuenta no encontrada o clave incorrecta." << endl;
            }
        }
