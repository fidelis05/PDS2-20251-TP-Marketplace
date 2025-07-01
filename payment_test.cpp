#include "include/Pedido.hpp"
#include "include/Carrinho.hpp"
#include <iostream>

int main()
{
  // Test 1: New Pedido always has payment true
  Carrinho carrinho;
  Pedido pedido(123, 456, carrinho);
  std::cout << "Test 1 - New Pedido payment: " << (pedido.getPagamento() ? "true" : "false") << std::endl;

  // Test 2: Reading from CSV also has payment true (regardless of CSV content)
  try
  {
    auto pedidos = Pedido::lerTodosPedidos("pedidos.csv");
    if (!pedidos.empty())
    {
      std::cout << "Test 2 - CSV Pedido payment: " << (pedidos[0].getPagamento() ? "true" : "false") << std::endl;
    }
  }
  catch (const std::exception &e)
  {
    std::cout << "Test 2 - Could not read CSV, but that's ok for this test" << std::endl;
  }

  // Test 3: pagamentoConcluido should work without checking payment
  try
  {
    pedido.pagamentoConcluido();
    std::cout << "Test 3 - pagamentoConcluido executed successfully" << std::endl;
  }
  catch (const std::exception &e)
  {
    std::cout << "Test 3 - Error: " << e.what() << std::endl;
  }

  return 0;
}
