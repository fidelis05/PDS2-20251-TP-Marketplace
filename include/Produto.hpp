#ifndef PRODUTO_HPP
#define PRODUTO_HPP
#include <iostream>
#include <string>

class Produto
{
public:
  int id;
  std::string nome;
  std::string marca;
  double valor;
  double avaliacao;
  int quantidade;
  std::string descricao;
  std::string endereco;

  Produto(int id, const std::string &nome, const std::string &marca, double valor,
    double avaliacao, int quantidade, const std::string &descricao, const std::string &endereco);
};

#endif