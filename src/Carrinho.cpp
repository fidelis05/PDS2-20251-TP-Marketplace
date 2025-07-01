#include "Carrinho.hpp"
#include "Produto.hpp"

void Carrinho::inserir(const Produto &produto, unsigned int quantidade)
{
  carrinhoProdutos[produto] = quantidade;
}

std::string Carrinho::exibir()
{
  std::string result;
  for (auto const &map : carrinhoProdutos)
  {
    const Produto &produto = map.first;
    unsigned int quantidade = map.second;
    result += "Produto: " + produto.nome + " Quantidade: " + std::to_string(quantidade) + "\n";
  }
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
  std::cout << "Finalizando compra..." << std::endl;
  std::cout << "Itens no carrinho:" << std::endl;
  std::cout << exibir() << std::endl;
  std::cout << "Compra finalizada! O carrinho será limpo." << std::endl;
  excluir(); // Clear the cart
}