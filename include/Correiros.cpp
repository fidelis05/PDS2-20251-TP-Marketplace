#include "Correios.hpp"

int Correios::setStatus(int n) {
  if (n < 8) {
    if (n <= 3) {
      if (this->codigoRastreio == 0) {
        std::cout << "Favor informe o Código de Rastreio antes de Prosseguir"
      } else {
        this->statusInfo = this->Status[n];
      }
    } else {
      this->statusInfo = this->Status[n];
    }
  } else {
    std::cout << "Defina um número válido"}
  

  if (n == 7) {
    // seta o time now
  }
}
int setcodigoRastreio(int x) { this->codigoRastreio = x; }
int getLista() {
    :
}
