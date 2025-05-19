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

void Produto::exibirInformacoes()
{
  std::cout << "ID: " << id << "\n";
  std::cout << "Nome: " << nome << "\n";
  std::cout << "Marca: " << marca << "\n";
  std::cout << "Valor: " << valor << "\n";
  std::cout << "Avaliação: " << avaliacao << "\n";
  std::cout << "Quantidade: " << quantidade << "\n";
  std::cout << "Descrição: " << descricao << "\n";
  std::cout << "Endereço: " << endereco << "\n";
}
void Produto::reduzirEstoque(int quantidade)
{
  if (quantidade > this->quantidade)
  {
    std::cout << "Quantidade insuficiente em estoque.\n";
  }
  else
  {
    this->quantidade <= quantidade;
    std::cout << "Estoque reduzido. Nova quantidade: " << this->quantidade << "\n";
  }
}
