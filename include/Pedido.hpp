#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include "Carrinho.hpp"
#include "Produto.hpp"
#include "Usuario.hpp"
<<<<<<< Updated upstream
#include <istream>

struct Pedido {
  int = ID std::string = created_at std::string = codigo_rastreio
=======
#include <iostream>
#include <string>

class Pedido {
public:
  int id;
  std::string createdAt;
  std::string codigoRastreio;
  Carrinho compra
>>>>>>> Stashed changes

  Pedido(Usuario x, Carrinho y);

  void cancelarPedido();
};

#endif
