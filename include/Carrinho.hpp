#ifndef CARRINHO_HPP
#define CARRINHO_HPP

#include "Produto.hpp"
#include <map>

class Carrinho
{
  public:
  std::map<Produto, int> carrinhoProdutos;

  Carrinho() = default;
  void inserir(Produto &produto, int quantidade);
  std::string exibir();
  void excluir(int id); // exclui um produto especifico
  void excluir();       // exclui todo o carrinho
  void finalizarCompra();

};

#endif