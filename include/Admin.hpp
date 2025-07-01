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
    void editarUsuario(const std::string &email, const std::string &novoNome, const std::string &novoTelefone, const std::string &novoEndereco);
    void deletarUsuario(const std::string &email);
    void cadastrarUsuario(const std::string &nome, const std::string &email, const std::string &senha,
                          const std::string &telefone, const std::string &cpf, const std::string &endereco);

    // Produtos
    std::vector<std::string> obterListaDeProdutos();
    void editarProduto(unsigned int idProduto, const std::string &novoNome, const std::string &novaMarca,
                       double novoValor, const std::string &novaDescricao);
    void deletarProduto(unsigned int idProduto);

    // Pedidos
    std::vector<std::string> obterListaDePedidos();
    void editarPedido(unsigned int idPedido, const std::string &novoStatus);
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
