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

  Pedido(Usuario x, Carrinho y);

  void cancelarPedido();
};

#endif
