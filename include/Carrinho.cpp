#include "Carrinho.hpp"
#include "Produto.hpp"

void Carrinho::inserir(Produto &produto, int quantidade)
{
  carrinhoProdutos[produto] = quantidade;
}

std::string Carrinho::exibir()
{
  std::string result;
  for (const auto &item : carrinhoProdutos)
  {
    result += "Produto: " + item.first.nome + " Quantidade: " + std::to_string(item.second) + "\n";
  }
  return result;
}

void Carrinho::excluir(int id)
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
  // TODO: carrinho -> pedido
}