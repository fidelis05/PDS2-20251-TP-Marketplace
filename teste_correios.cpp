#include "include/Interface.hpp"
#include <iostream>

int main()
{
  std::cout << "=== TESTE DO SISTEMA DE LOGIN CORREIOS ===" << std::endl;

  Interface interface;

  std::cout << "Sistema inicializado com sucesso!" << std::endl;
  std::cout << "Agora você pode testar o login do Correios." << std::endl;
  std::cout << "Credenciais padrão:" << std::endl;
  std::cout << "Usuário: correios" << std::endl;
  std::cout << "Senha: correios123" << std::endl;
  std::cout << "===========================================" << std::endl;

  // Executar a interface principal
  interface.executar();

  return 0;
}
