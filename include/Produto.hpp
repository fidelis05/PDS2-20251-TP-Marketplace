/**
 * @file Produto.hpp
 * @brief Declaração da classe Produto
 * @author Sistema Marketplace PDS2
 * @version 1.0
 * @date 2025
 */

#ifndef PRODUTO_HPP
#define PRODUTO_HPP
#include <iostream>
#include <string>

/**
 * @brief Classe que representa um produto no marketplace
 * 
 * Esta classe gerencia todas as informações relacionadas aos produtos
 * disponíveis no sistema, incluindo preço, estoque, avaliações e localização.
 */
class Produto
{
public:
  unsigned int id;          ///< Identificador único do produto
  std::string nome;         ///< Nome do produto
  std::string marca;        ///< Marca do produto
  double valor;             ///< Preço do produto
  double avaliacao;         ///< Avaliação média do produto (0-5)
  unsigned int quantidade;  ///< Quantidade em estoque
  std::string descricao;    ///< Descrição detalhada do produto
  std::string endereco;     ///< Localização do produto/vendedor

  /**
   * @brief Exibe as informações do produto
   */
  void exibirInformacoes();
  
  /**
   * @brief Reduz o estoque do produto
   * @param quantidade Quantidade a ser reduzida do estoque
   * @throws ProdutoException Se a quantidade for maior que o estoque disponível
   */
  void reduzirEstoque(unsigned int quantidade);

  /**
   * @brief Construtor do produto
   * @param id Identificador único do produto
   * @param nome Nome do produto
   * @param marca Marca do produto
   * @param valor Preço do produto
   * @param avaliacao Avaliação inicial do produto
   * @param quantidade Quantidade inicial em estoque
   * @param descricao Descrição do produto
   * @param endereco Localização do produto
   */
  Produto(unsigned int id, const std::string &nome, const std::string &marca, double valor,
          double avaliacao, unsigned int quantidade, const std::string &descricao, const std::string &endereco);

  /**
   * @brief Operador de comparação para ordenação
   * @param other Outro produto para comparação
   * @return true se este produto tem ID menor que o outro
   */
  bool operator<(const Produto &other) const;
};

#endif