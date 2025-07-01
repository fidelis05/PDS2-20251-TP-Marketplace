#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "Usuario.hpp"
#include "Pedido.hpp"
#include <vector>
#include <string>

class Admin
{
private:
    bool autorizacao;
    Usuario admin;

public:
    // Usuário
    std::vector<std::string> obterListaDeUsuarios();
    std::vector<std::string> filtrarListaDeUsuarios(const std::string &filtro);
    void editarUsuario(Usuario usuario);
    void deletarUsuario(Usuario usuario);
    void promoverUsuario(Usuario usuario);
    void cadastrarUsuario(const std::string &nome, const std::string &email, const std::string &senha,
                          const std::string &telefone, const std::string &cpf, const std::string &endereco);

    // Produtos
    std::vector<std::string> obterListaDeProdutos();
    std::vector<std::string> filtrarListaDeProdutos(const std::string &filtro);
    void editarProduto(Usuario usuario);
    void deletarProduto(unsigned int idProduto);

    // Pedidos
    std::vector<std::string> obterListaDePedidos();
    std::vector<std::string> filtrarListaDePedidos();
    void editarPedido(Usuario usuario);
    void deletarPedido(unsigned int idPedido);

    // Resumo estatístico
    struct EstatisticasResumo
    {
        int totalUsuarios;
        int totalProdutos;
        int totalPedidos;
    };
    EstatisticasResumo obterResumoEstatistico();
};

#endif
