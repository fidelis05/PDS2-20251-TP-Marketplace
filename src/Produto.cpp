#include "Produto.hpp"
#include <iostream>
#include <string>
#include "exceptions/MarketPlaceException.hpp"

Produto::Produto(unsigned int id, const std::string &nome, const std::string &marca, double valor,
                 double avaliacao, unsigned int quantidade, const std::string &descricao, const std::string &endereco)
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

void Produto::reduzirEstoque(unsigned int quantidade)
{
  if (quantidade > this->quantidade)
  {
    throw ProdutoException("Estoque insuficiente para reduzir a quantidade solicitada.");
  }
  this->quantidade -= quantidade;
}

bool Produto::operator<(const Produto &other) const
{
  return this->id < other.id;
}
