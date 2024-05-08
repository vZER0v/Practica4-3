#include "CuentaCorriente.h"
#include <iostream>

CuentaCorriente::CuentaCorriente() : saldo(0.0), clave("12345") {}

CuentaCorriente::CuentaCorriente(const std::string& nom, const std::string& apel, const std::string& dir, const std::string& tel, double sal, const std::string& numId, const std::string& clav)
    : nombre(nom), apellidos(apel), direccion(dir), telefono(tel), saldo(sal), numeroIdentificacion(numId), clave(clav.empty() ? "12345" : clav) {}

std::string CuentaCorriente::getNumeroIdentificacion() const {
    return numeroIdentificacion;
}

std::string CuentaCorriente::getClave() const {
    return clave;
}

void CuentaCorriente::setNombre(const std::string& nom) {
    nombre = nom;
}

void CuentaCorriente::setNumeroIdentificacion(const std::string& numId) {
    numeroIdentificacion = numId;
}

void CuentaCorriente::setClave(const std::string& clav) {
    clave = clav;
}

void CuentaCorriente::cambiarClave(const std::string& nuevaClave) {
    clave = nuevaClave;
}

bool CuentaCorriente::validarClave(const std::string& clav) const {
    return clave == clav;
}

bool CuentaCorriente::retirarDinero(double cantidad, const std::string& clav) {
    if (validarClave(clav) && cantidad > 0 && saldo >= cantidad) {
        saldo -= cantidad;
        std::cout << "Retiro exitoso. Saldo actual: $" << saldo << std::endl;
        return true;
    } else {
        std::cout << "Retiro fallido: Clave incorrecta o saldo insuficiente." << std::endl;
        return false;
    }
}

bool CuentaCorriente::ingresarDinero(double cantidad, const std::string& clav) {
    if (validarClave(clav) && cantidad > 0) {
        saldo += cantidad;
        std::cout << "Deposito exitoso. Saldo actual: $" << saldo << std::endl;
        return true;
    } else {
        std::cout << "Deposito fallido: Clave incorrecta." << std::endl;
        return false;
    }
}

void CuentaCorriente::consultarCuenta() const {
    std::cout << "Nombre: " << nombre << "\nApellidos: " << apellidos << "\nDirección: " << direccion << "\nTeléfono: " << telefono << "\nSaldo: $" << saldo << std::endl;
}

bool CuentaCorriente::saldoNegativo() const {
    return saldo < 0;
}
