#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include "Produto.hpp"
#include "Usuario.hpp"
#include "Carrinho.hpp"
#include <iostream>
#include <string>

class Pedido
{
public:
  int id;
  std::string createdAt;
  std::string codigoRastreio;
    Carrinho Compra

  Pedido(Usuario x, Carrinho y);
<<<<<<< Updated upstream

  void cancelarPedido();
=======
    void statusdoPedido();
    void devolverPedido();
    void pagamentoConcluido();
    void prazodeEntrega();
    void cancelarpedido
>>>>>>> Stashed changes
};

#endif
