#include "Correios.hpp"
#include <ctime>

int Correios::setStatus(int n) {
    if (n < 8) {
        if (n <= 3) {
            if (this->codigoRastreio == 0) {
                throw std::runtime_error("Favor informe o Código de Rastreio antes de Prosseguir");
                return -1;
            } else {
                this->statusInfo = this->status.status_map[n];
            }
        } else {
            this->statusInfo = this->status.status_map[n];
        }
    } else {
        throw std::runtime_error("Defina um número válido");
        return -1;
    }

    if (n == 7) {
        this->dataEntrega = std::time(nullptr);
    }
    return 0;
}

int Correios::setcodigoRastreio(int x) { 
    this->codigoRastreio = x; 
    return 0;
}

int Correios::getLista() {
    return 0;
}
