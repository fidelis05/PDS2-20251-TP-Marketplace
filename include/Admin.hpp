<<<<<<< Updated upstream
#ifndef ADMIN_HPP
#define ADMIN_HPP

=======
>>>>>>> Stashed changes
#include "Usuario.hpp"

class Admin {
  bool autorização;
  Usuario Admin;

<<<<<<< Updated upstream
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
=======
  // Usuário 
  void verListadeUsuarios();
  void filtrarListadeUsuarios();
  void editarUsuario(Usuario usuario.ID);{
        void deletarUsuario(); // RESTRINGIR ESSA FUNÇÃO AO ESCOPA DE EDITAR USUARIO
        void promoverUsuario();
    }
  void cadastrarUsuario();

// Produtos
void verListadeProdutos();
  void filtrarListadeUsuarios();
  void editarProduto(Usuario usuario.ID);{
        void deletarProduto();
    }

// Pedidos    
void verListadePedido();
  void filtrarListadePedidos();
  void editarPedido(Usuario usuario.ID);{
        void deletarPedido();
    }

// Resumo de Historia de usuario

void verlistaresumoestártico(); //usar para contar o total de usuario, produto e pedido, faz isso acessando o escopo de lista e contando quanto cada um tem




>>>>>>> Stashed changes
