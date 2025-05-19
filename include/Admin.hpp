#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "Usuario.hpp"

class Admin {
  bool autorização;
  Usuario Admin;

  // Usuário 
  void verListadeUsuarios();
  void filtrarListadeUsuarios();
  void editarUsuario(Usuario usuario.ID);
  {
    void deletarUsuario(); // RESTRINGIR ESSA FUNÇÃO AO ESCOPA DE EDITAR USUARIO
    void promoverUsuario();
  }
  void cadastrarUsuario();

  // Produtos
  void verListadeProdutos();
  void filtrarListadeUsuarios();
  void editarProduto(Usuario usuario.ID);
  {
    void deletarProduto();
  }

  // Pedidos
  void verListadePedido();
  void filtrarListadePedidos();
  void editarPedido(Usuario usuario.ID);
  {
    void deletarPedido();
  }

  // Resumo de Historia de usuario

  void
  verlistaresumoestártico(); //u sar para contar o total de usuario, produto e 
                             // edido, faz isso acessando o escopo de lista e 
                             // ontando quanto cada um tem

#endif
