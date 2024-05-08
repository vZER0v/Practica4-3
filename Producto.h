#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <iostream>
#include <string>

class Producto {
protected:
    std::string nombre;
    std::string marca;
    int precio;
    int descuento;
    int cantidadInventario;

public:
    Producto(std::string _nombre, std::string _marca, int _precio, int _descuento, int _cantidad);
    virtual ~Producto() {}
    virtual void mostrarInformacion() const = 0;
    void modificarProducto();
    int getPrecio() const;
    int getCantidadInventario() const;
    void venderProducto(int cantidad);
    std::string getNombre() const;
    int getDescuento() const;
};

class Comestible : public Producto {
private:
    std::string fechaVencimiento;

public:
    Comestible(std::string _nombre, std::string _marca, int _precio, int _descuento, int _cantidad, std::string _fecha);
    void mostrarInformacion() const override;
};

class Electronico : public Producto {
private:
    int garantiaMeses;

public:
    Electronico(std::string _nombre, std::string _marca, int _precio, int _descuento, int _cantidad, int _garantia);
    void mostrarInformacion() const override;
};

class Aseo : public Producto {
private:
    std::string material;

public:
    Aseo(std::string _nombre, std::string _marca, int _precio, int _descuento, int _cantidad, std::string _material);
    void mostrarInformacion() const override;
};

#endif // PRODUCTO_H
