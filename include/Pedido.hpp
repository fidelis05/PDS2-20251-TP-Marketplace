#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include "Produto.hpp"
#include "Usuario.hpp"
#include "Carrinho.hpp"
#include <iostream>
#include <string>
#include <map>

struct Status
{
  std::map<int, std::string> status_map;

  Status()
  {
    status_map[0] = "Esperando aprovação do pagamento";
    status_map[1] = "Enviado";
    status_map[2] = "Vendedor ciente";
    status_map[3] = "Despachado";
    status_map[4] = "A caminho";
    status_map[5] = "Saiu para Entrega";
    status_map[6] = "Entregue";
  }
};

class Pedido
{
private:
  int id;
  std::string createdAt;
  std::string codigoRastreio;
  Carrinho Compra;

protected:
  Status status; // so pra ter uma métrica
  std::string Status;

public:
  void getId();
  void getcreatedAt();
  void getcodigoRastreio();

  Pedido(Usuario x, Carrinho y);

  void cancelarPedido();
  void statusDoPedido();
  void devolverPedido();
  void pagamentoConcluido();
  void prazoDeEntrega();
};

#endif
