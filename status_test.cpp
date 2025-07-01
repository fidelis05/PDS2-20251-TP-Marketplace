#include "include/Pedido.hpp"
#include "include/Carrinho.hpp"
#include <iostream>

int main()
{
  // Test: New Pedido should not have "Esperando aprovação do pagamento" status
  Carrinho carrinho;
  Pedido pedido(123, 456, carrinho);

  std::cout << "Payment status: " << (pedido.getPagamento() ? "true" : "false") << std::endl;
  std::cout << "Order status: " << pedido.getStatus() << std::endl;

  // Should not be waiting for payment anymore
  if (pedido.getStatus() == "Esperando aprovação do pagamento")
  {
    std::cout << "ERROR: Still waiting for payment!" << std::endl;
    return 1;
  }
  else
  {
    std::cout << "SUCCESS: Not waiting for payment anymore!" << std::endl;
    return 0;
  }
}
