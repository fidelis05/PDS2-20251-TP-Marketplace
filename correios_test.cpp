#include "include/Correios.hpp"
#include <iostream>

int main()
{
  std::cout << "=== TESTE DO SISTEMA DE LOGIN DOS CORREIOS ===" << std::endl;

  // Create a Correios user
  Correios funcionario(123, "correios_user", "senha123");

  std::cout << "\n1. Tentativa de acesso sem login:" << std::endl;
  try
  {
    funcionario.setStatus(3);
  }
  catch (const std::exception &e)
  {
    std::cout << "Erro esperado: " << e.what() << std::endl;
  }

  std::cout << "\n2. Login com credenciais incorretas:" << std::endl;
  bool loginResult = funcionario.login("correios_user", "senha_errada");
  std::cout << "Login resultado: " << (loginResult ? "Sucesso" : "Falhou") << std::endl;

  std::cout << "\n3. Login com credenciais corretas:" << std::endl;
  loginResult = funcionario.login("correios_user", "senha123");
  std::cout << "Login resultado: " << (loginResult ? "Sucesso" : "Falhou") << std::endl;
  std::cout << "Autenticado: " << (funcionario.isAuthenticated() ? "Sim" : "Não") << std::endl;

  std::cout << "\n4. Testando funcionalidades após login:" << std::endl;
  try
  {
    funcionario.setcodigoRastreio(987654321);
    std::cout << "Código de rastreio definido com sucesso!" << std::endl;

    funcionario.listarPedidosParaEntrega();

    funcionario.consultarPedido(1);
  }
  catch (const std::exception &e)
  {
    std::cout << "Erro: " << e.what() << std::endl;
  }

  std::cout << "\n5. Teste de alteração de senha:" << std::endl;
  try
  {
    funcionario.alterarSenha("senha123", "nova_senha_segura");
    std::cout << "Senha alterada com sucesso!" << std::endl;
  }
  catch (const std::exception &e)
  {
    std::cout << "Erro: " << e.what() << std::endl;
  }

  std::cout << "\n6. Logout:" << std::endl;
  funcionario.logout();
  std::cout << "Autenticado após logout: " << (funcionario.isAuthenticated() ? "Sim" : "Não") << std::endl;

  std::cout << "\n7. Tentativa de acesso após logout:" << std::endl;
  try
  {
    funcionario.setStatus(4);
  }
  catch (const std::exception &e)
  {
    std::cout << "Erro esperado: " << e.what() << std::endl;
  }

  std::cout << "\n=== TESTE DE MÚLTIPLAS TENTATIVAS DE LOGIN ===" << std::endl;
  Correios funcionario2(456, "admin_correios", "admin123");

  // Simulate multiple failed login attempts
  for (int i = 1; i <= 4; i++)
  {
    std::cout << "\nTentativa " << i << " com senha errada:" << std::endl;
    funcionario2.login("admin_correios", "senha_errada");
  }

  std::cout << "\n=== FIM DOS TESTES ===" << std::endl;
  return 0;
}
