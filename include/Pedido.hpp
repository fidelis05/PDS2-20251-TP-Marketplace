#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include "Carrinho.hpp"
#include "Produto.hpp"
#include "Usuario.hpp"
#include <iostream>
#include <map>
#include <string>
#include <time.h>

struct Status {
  std::map<int, std::string> s;

  Status() {
    status_map[0] = "Esperando aprovação do pagamento";
    status_map[1] = "Enviado";
    status_map[2] = "Vendedor ciente";
    status_map[3] = "Despachado";
    status_map[4] = "A caminho";
    status_map[5] = "Saiu para Entrega";
    status_map[6] = "Entregue";
    status_map[7] = "Cancelado";
  }
};

class Pedido {
private:
  int idVendedor, idComprador;
  int id;
  std::chrono::year_month_day createdAt;
  std::chrono::year_month_day previsaoEntrega;
  std::chrono::year_month_day dataEntrega;
  Carrinho compra;

protected:
  Status status; // so pra ter uma métrica 
  std::string statusInfo;
  int codigoRastreio;

public:
  // constructor
  Pedido(Usuario x, Carrinho y);

  // getters
  int getId();
  std::chrono::year_month_day getcreatedAt();
  std::chrono::year_month_day getprevisaoEntrega();
  std::chrono::year_month_day getDataEntrega();

  std::string getStatus();
  int getcodigoRastreio();

  // Ações
  void pagamentoConcluido();
  void cancelarPedido();
};
class Comprador : public Pedido {

  void devolverPedido();
} class Vendedor : pulbic Pedido {
  void enviarPedido();
}

#endif
