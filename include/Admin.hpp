#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "Usuario.hpp"

class Admin {
private:
    bool autorizacao;
    Usuario admin;

public:
    // Usuário 
    void verListaDeUsuarios();
    void filtrarListaDeUsuarios();
    void editarUsuario(Usuario usuario);
    void deletarUsuario(Usuario usuario);
    void promoverUsuario(Usuario usuario);
    void cadastrarUsuario();

    // Produtos
    void verListaDeProdutos();
    void filtrarListaDeProdutos();
    void editarProduto(Usuario usuario);
    void deletarProduto(int idProduto);

    // Pedidos
    void verListaDePedido();
    void filtrarListaDePedidos();
    void editarPedido(Usuario usuario);
    void deletarPedido(int idPedido);

    // Resumo estatístico
    void verResumoEstatistico(); // Mostra total de usuários, produtos e pedidos
};

#endif
