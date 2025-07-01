#ifndef PRODUTO_HPP
#define PRODUTO_HPP
#include <iostream>
#include <string>

class Produto
{
public:
  unsigned int id;
  std::string nome;
  std::string marca;
  double valor;
  double avaliacao;
  unsigned int quantidade;
  std::string descricao;
  std::string endereco;

  void exibirInformacoes();
  void reduzirEstoque(unsigned int quantidade);

  Produto(unsigned int id, const std::string &nome, const std::string &marca, double valor,
          double avaliacao, unsigned int quantidade, const std::string &descricao, const std::string &endereco);

  bool operator<(const Produto &other) const;
};

#endif