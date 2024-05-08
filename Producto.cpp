#include "Producto.h"

Producto::Producto(std::string _nombre, std::string _marca, int _precio, int _descuento, int _cantidad)
    : nombre(_nombre), marca(_marca), precio(_precio), descuento(_descuento), cantidadInventario(_cantidad) {}

void Producto::modificarProducto() {
    std::cout << "Modificar nombre (" << nombre << "): ";
    std::getline(std::cin, nombre);
    std::cout << "Modificar precio (" << precio << "): ";
    std::cin >> precio;
    std::cin.ignore();
    std::cout << "Modificar descuento (" << descuento << "%): ";
    std::cin >> descuento;
    std::cin.ignore();
}

int Producto::getPrecio() const {
    return precio;
}

int Producto::getCantidadInventario() const {
    return cantidadInventario;
}

void Producto::venderProducto(int cantidad) {
    if (cantidad <= cantidadInventario) {
        cantidadInventario -= cantidad;
    } else {
        std::cout << "No hay suficiente inventario." << std::endl;
    }
}

std::string Producto::getNombre() const {
    return nombre;
}

int Producto::getDescuento() const {
    return descuento;
}

Comestible::Comestible(std::string _nombre, std::string _marca, int _precio, int _descuento, int _cantidad, std::string _fecha)
    : Producto(_nombre, _marca, _precio, _descuento, _cantidad), fechaVencimiento(_fecha) {}

void Comestible::mostrarInformacion() const {
    std::cout << "Comestible - Nombre: " << nombre << ", Marca: " << marca
              << ", Precio: $" << precio << ", Descuento: " << descuento
              << "%, Inventario: " << cantidadInventario << ", Fecha de vencimiento: " << fechaVencimiento << std::endl;
}

Electronico::Electronico(std::string _nombre, std::string _marca, int _precio, int _descuento, int _cantidad, int _garantia)
    : Producto(_nombre, _marca, _precio, _descuento, _cantidad), garantiaMeses(_garantia) {}

void Electronico::mostrarInformacion() const {
    std::cout << "Electronico - Nombre: " << nombre << ", Marca: " << marca
              << ", Precio: $" << precio << ", Descuento: " << descuento
              << "%, Inventario: " << cantidadInventario << ", Garantia: " << garantiaMeses << " meses" << std::endl;
}

Aseo::Aseo(std::string _nombre, std::string _marca, int _precio, int _descuento, int _cantidad, std::string _material)
    : Producto(_nombre, _marca, _precio, _descuento, _cantidad), material(_material) {}

void Aseo::mostrarInformacion() const {
    std::cout << "Aseo - Nombre: " << nombre << ", Marca: " << marca
              << ", Precio: $" << precio << ", Descuento: " << descuento
              << "%, Inventario: " << cantidadInventario << ", Material: " << material << std::endl;
}
