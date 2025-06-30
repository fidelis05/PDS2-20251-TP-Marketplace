#ifndef CARRINHO_HPP
#define CARRINHO_HPP

#include "Produto.hpp"
#include <map>

class Carrinho {
private:
  int id_usuario, id_vendedor;

public:
  std::map<Produto, int> carrinhoProdutos;
  Carrinho() = default;
  void inserir(const Produto &produto, int quantidade);
  std::string exibir();
  void excluir(int id); // exclui um produto especifico
  void excluir();       // exclui todo o carrinho
  void finalizarCompra();
};

#endif
