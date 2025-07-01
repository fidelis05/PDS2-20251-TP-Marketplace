#include "Interface.hpp"
#include <iostream>
#include <limits>

Interface::Interface() : correios(1, "correios", "correios123"), isLoggedIn(false), isAdmin(false), isCorreios(false) {}

void Interface::mostrarMenuPrincipal()
{
  std::cout << "\n======= MARKETPLACE MINAS =======" << std::endl;
  std::cout << "1. Login" << std::endl;
  std::cout << "2. Cadastro" << std::endl;
  std::cout << "3. Login Administrador" << std::endl;
  std::cout << "4. Login Correios" << std::endl;
  std::cout << "0. Sair" << std::endl;
  std::cout << "=================================" << std::endl;
  std::cout << "Escolha uma opção: ";
}

void Interface::mostrarMenuUsuario()
{
  std::cout << "\n======= MENU USUÁRIO =======" << std::endl;
  std::cout << "1. Ver Perfil" << std::endl;
  std::cout << "2. Editar Perfil" << std::endl;
  std::cout << "3. Ver Produtos" << std::endl;
  std::cout << "4. Buscar Produtos" << std::endl;
  std::cout << "5. Detalhes do Produto" << std::endl;
  std::cout << "6. Adicionar ao Carrinho" << std::endl;
  std::cout << "7. Ver Carrinho" << std::endl;
  std::cout << "8. Remover do Carrinho" << std::endl;
  std::cout << "9. Finalizar Compra" << std::endl;
  std::cout << "10. Cadastrar Produto" << std::endl;
  std::cout << "11. Meus Pedidos" << std::endl;
  std::cout << "0. Logout" << std::endl;
  std::cout << "==============================" << std::endl;
  std::cout << "Escolha uma opção: ";
}

void Interface::mostrarMenuAdmin()
{
  std::cout << "\n======= MENU ADMINISTRADOR =======" << std::endl;
  std::cout << "1. Listar Usuários" << std::endl;
  std::cout << "2. Filtrar Usuários" << std::endl;
  std::cout << "3. Cadastrar Usuário" << std::endl;
  std::cout << "4. Listar Produtos" << std::endl;
  std::cout << "5. Filtrar Produtos" << std::endl;
  std::cout << "6. Listar Pedidos" << std::endl;
  std::cout << "7. Resumo Estatístico" << std::endl;
  std::cout << "0. Logout" << std::endl;
  std::cout << "==================================" << std::endl;
  std::cout << "Escolha uma opção: ";
}

void Interface::mostrarMenuCorreios()
{
  std::cout << "\n======= MENU CORREIOS =======" << std::endl;
  std::cout << "1. Consultar Pedido" << std::endl;
  std::cout << "2. Listar Pedidos para Entrega" << std::endl;
  std::cout << "3. Confirmar Entrega" << std::endl;
  std::cout << "4. Reportar Problema na Entrega" << std::endl;
  std::cout << "5. Atualizar Status do Pedido" << std::endl;
  std::cout << "6. Definir Código de Rastreio" << std::endl;
  std::cout << "7. Alterar Senha" << std::endl;
  std::cout << "0. Logout" << std::endl;
  std::cout << "=============================" << std::endl;
  std::cout << "Escolha uma opção: ";
}

void Interface::executarLogin()
{
  std::string email, senha;

  std::cout << "\n===== LOGIN =====" << std::endl;
  std::cout << "Email: ";
  std::cin >> email;
  std::cout << "Senha: ";
  std::cin >> senha;

  if (usuarioLogado.login(email, senha))
  {
    isLoggedIn = true;
    std::cout << "Login realizado com sucesso!" << std::endl;
    std::cout << "Bem-vindo, " << usuarioLogado.getNome() << "!" << std::endl;
  }
  else
  {
    std::cout << "Email ou senha incorretos!" << std::endl;
  }
}

void Interface::executarCadastro()
{
  std::string nome, email, senha, telefone, cpf, endereco;

  std::cout << "\n===== CADASTRO =====" << std::endl;
  std::cout << "Nome: ";
  std::cin.ignore();
  std::getline(std::cin, nome);
  std::cout << "Email: ";
  std::getline(std::cin, email);
  std::cout << "Senha: ";
  std::getline(std::cin, senha);
  std::cout << "Telefone: ";
  std::getline(std::cin, telefone);
  std::cout << "CPF/CNPJ: ";
  std::getline(std::cin, cpf);
  std::cout << "Endereço: ";
  std::getline(std::cin, endereco);

  usuarioLogado.cadastrar(nome, email, senha, telefone, cpf, endereco);
}

void Interface::executarLoginCorreios()
{
  std::string usuario, senha;

  std::cout << "\n===== LOGIN CORREIOS =====" << std::endl;
  std::cout << "Usuário: ";
  std::cin >> usuario;
  std::cout << "Senha: ";
  std::cin >> senha;

  if (correios.login(usuario, senha))
  {
    isCorreios = true;
    std::cout << "Login do Correios realizado com sucesso!" << std::endl;
    std::cout << "Bem-vindo, " << correios.getUsuario() << "!" << std::endl;
  }
  else
  {
    std::cout << "Usuário ou senha incorretos, ou conta bloqueada!" << std::endl;
  }
}

void Interface::executar()
{
  int opcao;

  while (true)
  {
    if (!isLoggedIn && !isAdmin && !isCorreios)
    {
      mostrarMenuPrincipal();
      std::cin >> opcao;

      switch (opcao)
      {
      case 1:
        executarLogin();
        break;
      case 2:
        executarCadastro();
        break;
      case 3:
        // Admin login (simplified)
        {
          std::string adminPass;
          std::cout << "Senha de administrador: ";
          std::cin >> adminPass;
          if (adminPass == "admin123")
          {
            isAdmin = true;
            std::cout << "Login de administrador realizado!" << std::endl;
          }
          else
          {
            std::cout << "Senha incorreta!" << std::endl;
          }
        }
        break;
      case 4:
        executarLoginCorreios();
        break;
      case 0:
        std::cout << "Saindo do sistema..." << std::endl;
        return;
      default:
        std::cout << "Opção inválida!" << std::endl;
      }
    }
    else if (isLoggedIn)
    {
      mostrarMenuUsuario();
      std::cin >> opcao;

      switch (opcao)
      {
      case 1:
        usuarioLogado.visualizarPerfil();
        break;
      case 2:
        usuarioLogado.editarPerfil();
        break;
      case 3:
        usuarioLogado.visualizarProdutos();
        break;
      case 4:
      {
        int filtroOpcao;
        std::cout << "1. Filtrar por nome" << std::endl;
        std::cout << "2. Filtrar por categoria" << std::endl;
        std::cout << "3. Filtrar por preço" << std::endl;
        std::cout << "Escolha: ";
        std::cin >> filtroOpcao;

        switch (filtroOpcao)
        {
        case 1:
          usuarioLogado.aplicarFiltroNome();
          break;
        case 2:
          usuarioLogado.aplicarFiltroCategoria();
          break;
        case 3:
          usuarioLogado.aplicarFiltroPreco();
          break;
        default:
          std::cout << "Opção inválida!" << std::endl;
        }
      }
      break;
      case 5:
        usuarioLogado.detalhesProduto();
        break;
      case 6:
        usuarioLogado.adicionarAoCarrinho();
        break;
      case 7:
        usuarioLogado.visualizarCarrinho();
        break;
      case 8:
        usuarioLogado.removerDoCarrinho();
        break;
      case 9:
        usuarioLogado.finalizarCompra();
        break;
      case 10:
        usuarioLogado.cadastrarProduto();
        break;
      case 11:
        usuarioLogado.visualizarPedidos();
        break;
      case 0:
        isLoggedIn = false;
        std::cout << "Logout realizado!" << std::endl;
        break;
      default:
        std::cout << "Opção inválida!" << std::endl;
      }
    }
    else if (isAdmin)
    {
      mostrarMenuAdmin();
      std::cin >> opcao;

      switch (opcao)
      {
      case 1:
        admin.verListaDeUsuarios();
        break;
      case 2:
        admin.filtrarListaDeUsuarios();
        break;
      case 3:
        admin.cadastrarUsuario();
        break;
      case 4:
        admin.verListaDeProdutos();
        break;
      case 5:
        admin.filtrarListaDeProdutos();
        break;
      case 6:
        admin.verListaDePedido();
        break;
      case 7:
        admin.verResumoEstatistico();
        break;
      case 0:
        isAdmin = false;
        std::cout << "Logout de administrador realizado!" << std::endl;
        break;
      default:
        std::cout << "Opção inválida!" << std::endl;
      }
    }
    else if (isCorreios)
    {
      mostrarMenuCorreios();
      std::cin >> opcao;

      switch (opcao)
      {
      case 1:
      {
        unsigned int idPedido;
        std::cout << "Digite o ID do pedido: ";
        std::cin >> idPedido;
        correios.consultarPedido(idPedido);
      }
      break;
      case 2:
        correios.listarPedidosParaEntrega();
        break;
      case 3:
      {
        unsigned int idPedido;
        std::cout << "Digite o ID do pedido para confirmar entrega: ";
        std::cin >> idPedido;
        correios.confirmarEntrega(idPedido);
      }
      break;
      case 4:
      {
        unsigned int idPedido;
        std::string problema;
        std::cout << "Digite o ID do pedido: ";
        std::cin >> idPedido;
        std::cout << "Descreva o problema: ";
        std::cin.ignore();
        std::getline(std::cin, problema);
        correios.reportarProblemaEntrega(idPedido, problema);
      }
      break;
      case 5:
      {
        unsigned int statusNum;
        std::cout << "Digite o novo status (0-7): ";
        std::cin >> statusNum;
        correios.setStatus(statusNum);
      }
      break;
      case 6:
      {
        unsigned int codigoRastreio;
        std::cout << "Digite o código de rastreio: ";
        std::cin >> codigoRastreio;
        correios.setcodigoRastreio(codigoRastreio);
      }
      break;
      case 7:
      {
        std::string senhaAtual, novaSenha;
        std::cout << "Senha atual: ";
        std::cin >> senhaAtual;
        std::cout << "Nova senha: ";
        std::cin >> novaSenha;
        correios.alterarSenha(senhaAtual, novaSenha);
      }
      break;
      case 0:
        correios.logout();
        isCorreios = false;
        std::cout << "Logout de correios realizado!" << std::endl;
        break;
      default:
        std::cout << "Opção inválida!" << std::endl;
      }
    }

    // Clear input buffer
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}
