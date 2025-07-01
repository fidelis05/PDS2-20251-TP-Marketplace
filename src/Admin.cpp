#include "Admin.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

void Admin::verListaDeUsuarios()
{
  std::ifstream file("usuarios.txt");
  std::string line;

  std::cout << "\n===== LISTA DE USUÁRIOS =====" << std::endl;
  while (std::getline(file, line))
  {
    std::stringstream ss(line);
    std::string email, senha, nome, telefone, cpf, endereco;

    std::getline(ss, email, '|');
    std::getline(ss, senha, '|');
    std::getline(ss, nome, '|');
    std::getline(ss, telefone, '|');
    std::getline(ss, cpf, '|');
    std::getline(ss, endereco, '|');

    std::cout << "Nome: " << nome << " | Email: " << email << " | Telefone: " << telefone << std::endl;
  }
  file.close();
}

void Admin::filtrarListaDeUsuarios()
{
  std::string filtro;
  std::cout << "Filtrar por nome: ";
  std::cin.ignore();
  std::getline(std::cin, filtro);

  std::ifstream file("usuarios.txt");
  std::string line;
  bool encontrou = false;

  std::cout << "\n===== USUÁRIOS ENCONTRADOS =====" << std::endl;
  while (std::getline(file, line))
  {
    std::stringstream ss(line);
    std::string email, senha, nome, telefone, cpf, endereco;

    std::getline(ss, email, '|');
    std::getline(ss, senha, '|');
    std::getline(ss, nome, '|');
    std::getline(ss, telefone, '|');
    std::getline(ss, cpf, '|');
    std::getline(ss, endereco, '|');

    if (nome.find(filtro) != std::string::npos)
    {
      std::cout << "Nome: " << nome << " | Email: " << email << " | Telefone: " << telefone << std::endl;
      encontrou = true;
    }
  }

  if (!encontrou)
  {
    std::cout << "Nenhum usuário encontrado." << std::endl;
  }
  file.close();
}

void Admin::editarUsuario(Usuario usuario)
{
  std::cout << "Funcionalidade de editar usuário não implementada completamente." << std::endl;
  std::cout << "Usuário: " << usuario.getNome() << std::endl;
}

void Admin::deletarUsuario(Usuario usuario)
{
  std::cout << "Funcionalidade de deletar usuário não implementada completamente." << std::endl;
  std::cout << "Usuário: " << usuario.getNome() << std::endl;
}

void Admin::promoverUsuario(Usuario usuario)
{
  std::cout << "Promovendo usuário: " << usuario.getNome() << " para administrador." << std::endl;
}

void Admin::cadastrarUsuario()
{
  Usuario novoUsuario;
  std::string nome, email, senha, telefone, cpf, endereco;

  std::cout << "\n===== CADASTRAR USUÁRIO =====" << std::endl;
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

  novoUsuario.cadastrar(nome, email, senha, telefone, cpf, endereco);
}

void Admin::verListaDeProdutos()
{
  std::ifstream file("produtos.txt");
  std::string line;

  std::cout << "\n===== LISTA DE PRODUTOS =====" << std::endl;
  while (std::getline(file, line))
  {
    std::stringstream ss(line);
    std::string id, nome, marca, valor, avaliacao, quantidade, descricao, endereco;

    std::getline(ss, id, '|');
    std::getline(ss, nome, '|');
    std::getline(ss, marca, '|');
    std::getline(ss, valor, '|');
    std::getline(ss, avaliacao, '|');
    std::getline(ss, quantidade, '|');
    std::getline(ss, descricao, '|');
    std::getline(ss, endereco, '|');

    std::cout << "ID: " << id << " | Nome: " << nome << " | Marca: " << marca
              << " | Valor: R$" << valor << " | Quantidade: " << quantidade << std::endl;
  }
  file.close();
}

void Admin::filtrarListaDeProdutos()
{
  std::string filtro;
  std::cout << "Filtrar por nome: ";
  std::cin.ignore();
  std::getline(std::cin, filtro);

  std::ifstream file("produtos.txt");
  std::string line;
  bool encontrou = false;

  std::cout << "\n===== PRODUTOS ENCONTRADOS =====" << std::endl;
  while (std::getline(file, line))
  {
    std::stringstream ss(line);
    std::string id, nome, marca, valor, avaliacao, quantidade, descricao, endereco;

    std::getline(ss, id, '|');
    std::getline(ss, nome, '|');
    std::getline(ss, marca, '|');
    std::getline(ss, valor, '|');
    std::getline(ss, avaliacao, '|');
    std::getline(ss, quantidade, '|');
    std::getline(ss, descricao, '|');
    std::getline(ss, endereco, '|');

    if (nome.find(filtro) != std::string::npos)
    {
      std::cout << "ID: " << id << " | Nome: " << nome << " | Valor: R$" << valor << std::endl;
      encontrou = true;
    }
  }

  if (!encontrou)
  {
    std::cout << "Nenhum produto encontrado." << std::endl;
  }
  file.close();
}

void Admin::editarProduto(Usuario usuario)
{
  std::cout << "Funcionalidade de editar produto não implementada completamente." << std::endl;
  std::cout << "Usuário: " << usuario.getNome() << std::endl;
}

void Admin::deletarProduto(unsigned int idProduto)
{
  std::cout << "Funcionalidade de deletar produto não implementada completamente." << std::endl;
  std::cout << "ID do produto: " << idProduto << std::endl;
}

void Admin::verListaDePedido()
{
  try
  {
    auto pedidos = Pedido::lerTodosPedidos("pedidos.csv");

    std::cout << "\n===== LISTA DE PEDIDOS =====" << std::endl;
    for (const auto &pedido : pedidos)
    {
      std::cout << "Pedido ID: " << pedido.getId()
                << " | Comprador: " << pedido.getIdComprador()
                << " | Vendedor: " << pedido.getIdVendedor()
                << " | Status: " << pedido.getStatus() << std::endl;
    }
    std::cout << "============================" << std::endl;
  }
  catch (const std::exception &e)
  {
    std::cout << "Nenhum pedido encontrado." << std::endl;
  }
}

void Admin::filtrarListaDePedidos()
{
  std::cout << "Funcionalidade de filtrar pedidos não implementada completamente." << std::endl;
}

void Admin::editarPedido(Usuario usuario)
{
  std::cout << "Funcionalidade de editar pedido não implementada completamente." << std::endl;
  std::cout << "Usuário: " << usuario.getNome() << std::endl;
}

void Admin::deletarPedido(unsigned int idPedido)
{
  std::cout << "Funcionalidade de deletar pedido não implementada completamente." << std::endl;
  std::cout << "ID do pedido: " << idPedido << std::endl;
}

void Admin::verResumoEstatistico()
{
  int totalUsuarios = 0, totalProdutos = 0, totalPedidos = 0;

  // Count users
  std::ifstream userFile("usuarios.txt");
  std::string line;
  while (std::getline(userFile, line))
  {
    totalUsuarios++;
  }
  userFile.close();

  // Count products
  std::ifstream productFile("produtos.txt");
  while (std::getline(productFile, line))
  {
    totalProdutos++;
  }
  productFile.close();

  // Count orders
  try
  {
    auto pedidos = Pedido::lerTodosPedidos("pedidos.csv");
    totalPedidos = pedidos.size();
  }
  catch (const std::exception &e)
  {
    totalPedidos = 0;
  }

  std::cout << "\n===== RESUMO ESTATÍSTICO =====" << std::endl;
  std::cout << "Total de usuários: " << totalUsuarios << std::endl;
  std::cout << "Total de produtos: " << totalProdutos << std::endl;
  std::cout << "Total de pedidos: " << totalPedidos << std::endl;
  std::cout << "==============================" << std::endl;
}
