#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "Usuario.hpp"

class Admin {
  bool autorização;
  Usuario Admin;

  void verListadePedidos();
  void verListadeUsuarios();
  void verListadeProduto();

  void gerenciarUsuario(verListadeUsuario);
  void deletarUsuario();
  void promoverUsuario();

  void gerenciarProduto();
  void deletarProduto();
};

#endif