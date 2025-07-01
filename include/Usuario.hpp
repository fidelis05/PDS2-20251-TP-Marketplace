/**
 * @file Usuario.hpp
 * @brief Declaração da classe Usuario
 * @author Sistema Marketplace PDS2
 * @version 1.0
 * @date 2025
 */

#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>
#include <vector>
#include <memory>

#include "Produto.hpp"
#include "Carrinho.hpp"

// Forward declarations to avoid circular dependency
class Pedido;

/**
 * @brief Classe que representa um usuário do marketplace
 * 
 * Esta classe gerencia todas as informações e operações relacionadas
 * aos usuários do sistema, incluindo cadastro, login, gerenciamento
 * de produtos e pedidos.
 */
class Usuario
{
private:
  unsigned int id_usuario;    ///< Identificador único do usuário
  std::string nome;          ///< Nome completo do usuário
  std::string email;         ///< Email do usuário (usado para login)
  std::string senha;         ///< Senha do usuário
  std::string telefone;      ///< Número de telefone do usuário
  std::string cpf_cnpj;      ///< CPF ou CNPJ do usuário
  std::string endereco;      ///< Endereço completo do usuário

  std::vector<Produto> meusProdutos;                    ///< Lista de produtos que o usuário vende
  std::vector<std::shared_ptr<Pedido>> meusPedidos;    ///< Lista de pedidos do usuário

public:
  Carrinho carrinho;         ///< Carrinho de compras do usuário

  /** @brief Construtor padrão */
  Usuario();
  
  /** 
   * @brief Construtor parametrizado
   * @param nome Nome do usuário
   * @param email Email do usuário
   * @param senha Senha do usuário
   */
  Usuario(std::string nome, std::string email, std::string senha);

  /**
   * @brief Cadastra um novo usuário no sistema
   * @param nome Nome completo do usuário
   * @param email Email único do usuário
   * @param senha Senha para acesso
   * @param telefone Número de telefone
   * @param cpf_cnpj CPF ou CNPJ do usuário
   * @param endereco Endereço completo
   */
  void cadastrar(std::string nome, std::string email, std::string senha, std::string telefone, std::string cpf_cnpj, std::string endereco);
  
  /**
   * @brief Realiza login no sistema
   * @param email Email do usuário
   * @param senha Senha do usuário
   * @return true se o login for bem-sucedido, false caso contrário
   */
  bool login(std::string email, std::string senha);

  /**
   * @brief Obtém a lista de produtos do usuário
   * @return Vetor com os produtos do usuário
   */
  std::vector<Produto> obterProdutos();
  
  /**
   * @brief Adiciona um produto ao carrinho
   * @param idProduto ID do produto a ser adicionado
   */
  void adicionarProdutoAoCarrinho(unsigned int idProduto);
  
  /**
   * @brief Remove um produto do carrinho
   * @param idProduto ID do produto a ser removido
   */
  void removerProdutoDoCarrinho(unsigned int idProduto);
  
  /**
   * @brief Obtém a lista de pedidos do usuário
   * @return Vetor com os pedidos do usuário
   */
  std::vector<std::shared_ptr<Pedido>> obterPedidos();
  
  /**
   * @brief Finaliza uma compra
   * @return true se a compra for finalizada com sucesso, false caso contrário
   */
  bool finalizarCompraBusiness();
  
  /**
   * @brief Atualiza as informações do perfil do usuário
   * @param novoNome Novo nome do usuário
   * @param novoEmail Novo email do usuário
   * @param novoTelefone Novo telefone do usuário
   * @param novoEndereco Novo endereço do usuário
   */
  void atualizarPerfil(const std::string &novoNome, const std::string &novoEmail,
                       const std::string &novoTelefone, const std::string &novoEndereco);
  
  /**
   * @brief Atualiza a senha do usuário
   * @param novaSenha Nova senha a ser definida
   */
  void atualizarSenha(const std::string &novaSenha);
  
  /**
   * @brief Adiciona um novo produto à lista do usuário
   * @param produto Produto a ser adicionado
   * @return true se o produto foi adicionado com sucesso, false caso contrário
   */
  bool adicionarNovoProduto(const Produto &produto);

  // Getters
  /** @brief Obtém o email do usuário @return Email do usuário */
  std::string getEmail() const { return email; }
  
  /** @brief Obtém o nome do usuário @return Nome do usuário */
  std::string getNome() const { return nome; }
  
  /** @brief Obtém o telefone do usuário @return Telefone do usuário */
  std::string getTelefone() const { return telefone; }
  
  /** @brief Obtém o CPF/CNPJ do usuário @return CPF/CNPJ do usuário */
  std::string getCpfCnpj() const { return cpf_cnpj; }
  
  /** @brief Obtém o endereço do usuário @return Endereço do usuário */
  std::string getEndereco() const { return endereco; }
  
  /** @brief Obtém o ID do usuário @return ID único do usuário */
  unsigned int getId() const { return id_usuario; }
};

#endif
