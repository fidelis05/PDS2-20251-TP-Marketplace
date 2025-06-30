#include "Produto.hpp"
#include <iostream>
#include <string>

Produto::Produto(int id, const std::string &nome, const std::string &marca, double valor,
                 double avaliacao, int quantidade, const std::string &descricao, const std::string &endereco)
    : id(id),
      nome(nome),
      marca(marca),
      valor(valor),
      avaliacao(avaliacao),
      quantidade(quantidade),
      descricao(descricao),
      endereco(endereco)
{
}

std::string Produto::exibirInformacoes()
{
  std::string info;
  info += "ID: ";
  id;
  "\n";
  info += "Nome: ";
  nome;
  "\n";
  info += "Marca: ";
  marca;
  "\n";
  info += "Valor: ";
  valor;
  "\n";
  info += "Avaliação: ";
  avaliacao;
  "\n";
  info += "Quantidade: ";
  quantidade;
  "\n";
  info += "Descrição: ";
  descricao;
  "\n";
  info += "Endereço: ";
  endereco;
  "\n";

  return info;
}
void Produto::reduzirEstoque(int quantidade)
{
  if (quantidade > this->quantidade)
  {
    std::cout << "Quantidade insuficiente em estoque.\n";
  }
  else if (this->quantidade <= quantidade)
  {
    this->quantidade -= quantidade;
    std::cout << "Estoque reduzido. Nova quantidade: " << this->quantidade << "\n";
  }
}
