#include "Admin.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

std::vector<std::string> Admin::obterListaDeUsuarios()
{
  std::vector<std::string> usuarios;
  std::ifstream file("data/usuarios.txt");
  std::string line;

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

    usuarios.push_back("Nome: " + nome + " | Email: " + email + " | Telefone: " + telefone);
  }
  file.close();
  return usuarios;
}

std::vector<std::string> Admin::filtrarListaDeUsuarios(const std::string &filtro)
{
  std::vector<std::string> usuarios;
  std::ifstream file("data/usuarios.txt");
  std::string line;

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
      usuarios.push_back("Nome: " + nome + " | Email: " + email + " | Telefone: " + telefone);
    }
  }
  file.close();
  return usuarios;
}

void Admin::editarUsuario(Usuario usuario)
{
  // Placeholder - functionality not fully implemented
}

void Admin::deletarUsuario(Usuario usuario)
{
  // Placeholder - functionality not fully implemented
}

void Admin::promoverUsuario(Usuario usuario)
{
  // Placeholder - functionality not fully implemented
}

void Admin::cadastrarUsuario(const std::string &nome, const std::string &email, const std::string &senha,
                             const std::string &telefone, const std::string &cpf, const std::string &endereco)
{
  Usuario novoUsuario;
  novoUsuario.cadastrar(nome, email, senha, telefone, cpf, endereco);
}

std::vector<std::string> Admin::obterListaDeProdutos()
{
  std::vector<std::string> produtos;
  std::ifstream file("data/produtos.txt");
  std::string line;

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

    produtos.push_back("ID: " + id + " | Nome: " + nome + " | Marca: " + marca +
                       " | Valor: R$" + valor + " | Quantidade: " + quantidade);
  }
  file.close();
  return produtos;
}

std::vector<std::string> Admin::filtrarListaDeProdutos(const std::string &filtro)
{
  std::vector<std::string> produtos;
  std::ifstream file("data/produtos.txt");
  std::string line;

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
      produtos.push_back("ID: " + id + " | Nome: " + nome + " | Valor: R$" + valor);
    }
  }
  file.close();
  return produtos;
}

void Admin::editarProduto(Usuario usuario)
{
  // Placeholder - functionality not fully implemented
}

void Admin::deletarProduto(unsigned int idProduto)
{
  // Placeholder - functionality not fully implemented
}

std::vector<std::string> Admin::obterListaDePedidos()
{
  std::vector<std::string> pedidos;

  try
  {
    auto pedidosList = Pedido::lerTodosPedidos("data/pedidos.txt");

    for (const auto &pedido : pedidosList)
    {
      pedidos.push_back("Pedido ID: " + std::to_string(pedido.getId()) +
                        " | Comprador: " + std::to_string(pedido.getIdComprador()) +
                        " | Vendedor: " + std::to_string(pedido.getIdVendedor()) +
                        " | Status: " + pedido.getStatus());
    }
  }
  catch (const std::exception &e)
  {
    // Return empty list if no orders found
  }

  return pedidos;
}

std::vector<std::string> Admin::filtrarListaDePedidos()
{
  // Placeholder - return empty for now
  return std::vector<std::string>();
}

void Admin::editarPedido(Usuario usuario)
{
  // Placeholder - functionality not fully implemented
}

void Admin::deletarPedido(unsigned int idPedido)
{
  // Placeholder - functionality not fully implemented
}

Admin::EstatisticasResumo Admin::obterResumoEstatistico()
{
  EstatisticasResumo resumo = {0, 0, 0};

  // Count users
  std::ifstream userFile("data/usuarios.txt");
  std::string line;
  while (std::getline(userFile, line))
  {
    resumo.totalUsuarios++;
  }
  userFile.close();

  // Count products
  std::ifstream productFile("data/produtos.txt");
  while (std::getline(productFile, line))
  {
    resumo.totalProdutos++;
  }
  productFile.close();

  // Count orders
  try
  {
    auto pedidos = Pedido::lerTodosPedidos("data/pedidos.txt");
    resumo.totalPedidos = pedidos.size();
  }
  catch (const std::exception &e)
  {
    resumo.totalPedidos = 0;
  }

  return resumo;
}
