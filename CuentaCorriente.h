#ifndef CUENTACORRIENTE_H
#define CUENTACORRIENTE_H
#include <string>

class CuentaCorriente {
private:
    std::string nombre;
    std::string apellidos;
    std::string direccion;
    std::string telefono;
    double saldo;
    std::string numeroIdentificacion;
    std::string clave;

public:
    CuentaCorriente();
    CuentaCorriente(const std::string& nom, const std::string& apel, const std::string& dir, const std::string& tel, double sal, const std::string& numId, const std::string& clav = "12345");

    std::string getNumeroIdentificacion() const;
    std::string getClave() const;
    double getSaldo() const { return saldo; } // Implementación directa en el header.

    void setNombre(const std::string& nom);
    void setNumeroIdentificacion(const std::string& numId);
    void setClave(const std::string& clav);

    void cambiarClave(const std::string& nuevaClave);
    bool validarClave(const std::string& clav) const;

    bool retirarDinero(double cantidad, const std::string& clav);
    bool ingresarDinero(double cantidad, const std::string& clav);
    void consultarCuenta() const;
    bool saldoNegativo() const;
};

#endif // CUENTACORRIENTE_H
