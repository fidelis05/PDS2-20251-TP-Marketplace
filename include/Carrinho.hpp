#ifndef CARRINHO_HPP
#define CARRINHO_HPP

#include "Produto.hpp"
#include <map>

class Carrinho
{
private:
  unsigned int id_usuario, id_vendedor;

public:
  std::map<Produto, unsigned int> carrinhoProdutos;
  Carrinho() = default;
  void inserir(const Produto &produto, unsigned int quantidade);
  std::string exibir();
  void excluir(unsigned int id); // exclui um produto especifico
  void excluir();                // exclui todo o carrinho
  void finalizarCompra();
};

#endif
