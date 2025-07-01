#include "Carrinho.hpp"
#include "Produto.hpp"

void Carrinho::inserir(const Produto &produto, unsigned int quantidade)
{
  carrinhoProdutos[produto] = quantidade;
}

std::string Carrinho::exibir()
{
  int i = 1;
  double total = 0.0;
  std::string result;
  for (auto const &map : carrinhoProdutos)
  {
    const Produto &produto = map.first;
    unsigned int quantidade = map.second;
    result += std::to_string(i++) + ". " + produto.nome + " -  R$" + std::to_string(produto.valor) + " x " + std::to_string(quantidade) + "\n";
    total += produto.valor * quantidade;
  }
  result += "Total: R$" + std::to_string(total) + "\n";
  return result;
}

void Carrinho::excluir(unsigned int id)
{
  for (auto it = carrinhoProdutos.begin(); it != carrinhoProdutos.end(); ++it)
  {
    if (it->first.id == id)
    {
      carrinhoProdutos.erase(it);
      break;
    }
  }
}

void Carrinho::excluir()
{
  carrinhoProdutos.clear();
}

void Carrinho::finalizarCompra()
{
  carrinhoProdutos.clear();
}
