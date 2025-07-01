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

void Admin::editarUsuario(const std::string &email, const std::string &novoNome, const std::string &novoTelefone, const std::string &novoEndereco)
{
  std::ifstream file("data/usuarios.txt");
  std::vector<std::string> lines;
  std::string line;
  bool encontrado = false;

  while (std::getline(file, line))
  {
    std::stringstream ss(line);
    std::string fileEmail, senha, nome, telefone, cpf, endereco;

    std::getline(ss, fileEmail, '|');
    std::getline(ss, senha, '|');
    std::getline(ss, nome, '|');
    std::getline(ss, telefone, '|');
    std::getline(ss, cpf, '|');
    std::getline(ss, endereco, '|');

    if (fileEmail == email)
    {
      line = fileEmail + "|" + senha + "|" + novoNome + "|" + novoTelefone + "|" + cpf + "|" + novoEndereco;
      encontrado = true;
    }
    lines.push_back(line);
  }
  file.close();

  if (encontrado)
  {
    std::ofstream outFile("data/usuarios.txt");
    for (const auto &l : lines)
    {
      outFile << l << std::endl;
    }
    outFile.close();
  }
}

void Admin::deletarUsuario(const std::string &email)
{
  std::ifstream file("data/usuarios.txt");
  std::vector<std::string> lines;
  std::string line;

  while (std::getline(file, line))
  {
    std::stringstream ss(line);
    std::string fileEmail;
    std::getline(ss, fileEmail, '|');

    if (fileEmail != email)
    {
      lines.push_back(line);
    }
  }
  file.close();

  std::ofstream outFile("data/usuarios.txt");
  for (const auto &l : lines)
  {
    outFile << l << std::endl;
  }
  outFile.close();
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

void Admin::editarProduto(unsigned int idProduto, const std::string &novoNome, const std::string &novaMarca,
                          double novoValor, const std::string &novaDescricao)
{
  std::ifstream file("data/produtos.txt");
  std::vector<std::string> lines;
  std::string line;
  bool encontrado = false;

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

    if (std::stoi(id) == idProduto)
    {
      line = id + "|" + novoNome + "|" + novaMarca + "|" + std::to_string(novoValor) + "|" +
             avaliacao + "|" + quantidade + "|" + novaDescricao + "|" + endereco;
      encontrado = true;
    }
    lines.push_back(line);
  }
  file.close();

  if (encontrado)
  {
    std::ofstream outFile("data/produtos.txt");
    for (const auto &l : lines)
    {
      outFile << l << std::endl;
    }
    outFile.close();
  }
}

void Admin::deletarProduto(unsigned int idProduto)
{
  std::ifstream file("data/produtos.txt");
  std::vector<std::string> lines;
  std::string line;

  while (std::getline(file, line))
  {
    std::stringstream ss(line);
    std::string id;
    std::getline(ss, id, '|');

    if (std::stoi(id) != idProduto)
    {
      lines.push_back(line);
    }
  }
  file.close();

  std::ofstream outFile("data/produtos.txt");
  for (const auto &l : lines)
  {
    outFile << l << std::endl;
  }
  outFile.close();
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
  {}

  return pedidos;
}

void Admin::editarPedido(unsigned int idPedido, const std::string &novoStatus)
{
  try
  {
    auto pedidos = Pedido::lerTodosPedidos("data/pedidos.txt");
    bool encontrado = false;

    for (auto &pedido : pedidos)
    {
      if (pedido.getId() == idPedido)
      {
        encontrado = true;
        break;
      }
    }

    if (encontrado)
    {
      std::ifstream file("data/pedidos.txt");
      std::vector<std::string> lines;
      std::string line;

      if (std::getline(file, line))
      {
        lines.push_back(line);
      }

      while (std::getline(file, line))
      {
        std::stringstream ss(line);
        std::string id, compradorId, vendedorId, status, codigoRastreio, dataCriacao, previsaoEntrega, dataEntrega, pagamento;

        std::getline(ss, id, ',');
        std::getline(ss, compradorId, ',');
        std::getline(ss, vendedorId, ',');
        std::getline(ss, status, ',');
        std::getline(ss, codigoRastreio, ',');
        std::getline(ss, dataCriacao, ',');
        std::getline(ss, previsaoEntrega, ',');
        std::getline(ss, dataEntrega, ',');
        std::getline(ss, pagamento, ',');

        if (std::stoi(id) == idPedido)
        {
          status = novoStatus;
        }

        line = id + "," + compradorId + "," + vendedorId + "," + status + "," +
               codigoRastreio + "," + dataCriacao + "," + previsaoEntrega + "," + dataEntrega + "," + pagamento;
        lines.push_back(line);
      }
      file.close();

      std::ofstream outFile("data/pedidos.txt");
      for (const auto &l : lines)
      {
        outFile << l << std::endl;
      }
      outFile.close();
    }
  }
  catch (const std::exception &e)
  {}
}

void Admin::deletarPedido(unsigned int idPedido)
{
  std::ifstream file("data/pedidos.txt");
  std::vector<std::string> lines;
  std::string line;

  if (std::getline(file, line))
  {
    lines.push_back(line);
  }

  while (std::getline(file, line))
  {
    std::stringstream ss(line);
    std::string id;
    std::getline(ss, id, ',');

    if (std::stoi(id) != idPedido)
    {
      lines.push_back(line);
    }
  }
  file.close();

  std::ofstream outFile("data/pedidos.txt");
  for (const auto &l : lines)
  {
    outFile << l << std::endl;
  }
  outFile.close();
}

Admin::EstatisticasResumo Admin::obterResumoEstatistico()
{
  EstatisticasResumo resumo = {0, 0, 0};

  std::ifstream userFile("data/usuarios.txt");
  std::string line;
  while (std::getline(userFile, line))
  {
    resumo.totalUsuarios++;
  }
  userFile.close();

  std::ifstream productFile("data/produtos.txt");
  while (std::getline(productFile, line))
  {
    resumo.totalProdutos++;
  }
  productFile.close();

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
