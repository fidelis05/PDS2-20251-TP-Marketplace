/**
 * @file Admin.hpp
 * @brief Declaração da classe Admin
 * @author Sistema Marketplace PDS2
 * @version 1.0
 * @date 2025
 */

#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "Usuario.hpp"
#include "Pedido.hpp"
#include <vector>
#include <string>

/**
 * @brief Classe que representa um administrador do sistema
 * 
 * Esta classe fornece funcionalidades administrativas para gerenciar
 * usuários, produtos e pedidos no marketplace.
 */
class Admin
{
private:
    bool autorizacao;    ///< Flag de autorização do administrador
    Usuario admin;       ///< Dados do usuário administrador

public:
    // Gerenciamento de Usuários
    
    /**
     * @brief Obtém a lista de todos os usuários cadastrados
     * @return Vetor com strings formatadas contendo informações dos usuários
     */
    std::vector<std::string> obterListaDeUsuarios();
    
    /**
     * @brief Edita as informações de um usuário
     * @param email Email do usuário a ser editado
     * @param novoNome Novo nome do usuário
     * @param novoTelefone Novo telefone do usuário
     * @param novoEndereco Novo endereço do usuário
     */
    void editarUsuario(const std::string &email, const std::string &novoNome, const std::string &novoTelefone, const std::string &novoEndereco);
    
    /**
     * @brief Remove um usuário do sistema
     * @param email Email do usuário a ser removido
     */
    void deletarUsuario(const std::string &email);
    
    /**
     * @brief Cadastra um novo usuário no sistema
     * @param nome Nome do usuário
     * @param email Email único do usuário
     * @param senha Senha do usuário
     * @param telefone Telefone do usuário
     * @param cpf CPF do usuário
     * @param endereco Endereço do usuário
     */
    void cadastrarUsuario(const std::string &nome, const std::string &email, const std::string &senha,
                          const std::string &telefone, const std::string &cpf, const std::string &endereco);

    // Gerenciamento de Produtos
    
    /**
     * @brief Obtém a lista de todos os produtos cadastrados
     * @return Vetor com strings formatadas contendo informações dos produtos
     */
    std::vector<std::string> obterListaDeProdutos();
    
    /**
     * @brief Edita as informações de um produto
     * @param idProduto ID do produto a ser editado
     * @param novoNome Novo nome do produto
     * @param novaMarca Nova marca do produto
     * @param novoValor Novo preço do produto
     * @param novaDescricao Nova descrição do produto
     */
    void editarProduto(unsigned int idProduto, const std::string &novoNome, const std::string &novaMarca,
                       double novoValor, const std::string &novaDescricao);
    
    /**
     * @brief Remove um produto do sistema
     * @param idProduto ID do produto a ser removido
     */
    void deletarProduto(unsigned int idProduto);

    // Gerenciamento de Pedidos
    
    /**
     * @brief Obtém a lista de todos os pedidos
     * @return Vetor com strings formatadas contendo informações dos pedidos
     */
    std::vector<std::string> obterListaDePedidos();
    
    /**
     * @brief Edita o status de um pedido
     * @param idPedido ID do pedido a ser editado
     * @param novoStatus Novo status do pedido
     */
    void editarPedido(unsigned int idPedido, const std::string &novoStatus);
    
    /**
     * @brief Remove um pedido do sistema
     * @param idPedido ID do pedido a ser removido
     */
    void deletarPedido(unsigned int idPedido);

    // Estatísticas do Sistema
    
    /**
     * @brief Estrutura para resumo de estatísticas do sistema
     */
    struct EstatisticasResumo
    {
        int totalUsuarios;   ///< Total de usuários cadastrados
        int totalProdutos;   ///< Total de produtos disponíveis
        int totalPedidos;    ///< Total de pedidos realizados
    };
    
    /**
     * @brief Obtém um resumo estatístico do sistema
     * @return Estrutura com as estatísticas do sistema
     */
    EstatisticasResumo obterResumoEstatistico();
};

#endif
