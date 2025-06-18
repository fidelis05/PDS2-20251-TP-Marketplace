#include "Pedido.hpp"

Pedido::Pedido(Usuario x, Carrinho y) {
  this->id = Carrinho.getId;
  this->createdAt = t; // time now;
  this->previsaoEntrega =
      0; // so pra iniciar, já que estára à cargo da empresa de entrega
  this->compra = y;
  this->entregue = 0;
  this->status(); // so pra ter uma métrica 
  this->statusInfo = status.s[0];
  this->codigoRastreio = 0;
}

int Pedido::getId() { return this->id; }

int getcodigoRastreio() { return this->codigoRastreio; }
Data Pedido::getcreatedAt() { return createdAt; }
Data Pedido::getprevisaoEntrega() { return previsaoEntrega; }
std::string Pedido::getStatus() { return statusInfo; }

void Pedido::cancelarPedido() {
  statusInfo = status.s[7]; // dps reverter processo
};
void Pedido::devolverPedido() {
  if (entregue - pedidoEntregue < 7) {
    // reverte :
  } else {
    std::cout << "O tempo de devolução foi excedido";
  }
}
void Pedido::pagamentoConcluido() {
  if (pago = 1) {
    statusInfo = status.s[1]
  }
}
