#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>
#include <vector>
#include <memory>

#include "Produto.hpp"
#include "Carrinho.hpp"

// Forward declarations to avoid circular dependency
class Pedido;

class Usuario
{
private:
  unsigned int id_usuario;
  std::string nome;
  std::string email;
  std::string senha;
  std::string telefone;
  std::string cpf_cnpj;
  std::string endereco;

  std::vector<Produto> meusProdutos;
  std::vector<std::shared_ptr<Pedido>> meusPedidos;

public:
  Carrinho carrinho;

  Usuario();
  Usuario(std::string nome, std::string email, std::string senha);

  void cadastrar(std::string nome, std::string email, std::string senha, std::string telefone, std::string cpf_cnpj, std::string endereco);
  bool login(std::string email, std::string senha);
  void visualizarPerfil();
  void editarPerfil();
  void editarEmail();
  void editarSenha();
  void editarEndereco();
  void editarTelefone();

  // funções de produto
  void visualizarProdutos();
  void detalhesProduto();
  void aplicarFiltroNome();
  void aplicarFiltroCategoria();
  void aplicarFiltroPreco();
  void cadastrarProduto();
  void editarProduto();
  void excluirProduto();

  // funções do carrinho
  void adicionarAoCarrinho();
  void removerDoCarrinho();
  void visualizarCarrinho();

  // funções de pedido
  void finalizarCompra();
  void visualizarPedidos();
  void cancelarPedido();

  bool confirmarAcao();

  std::string getEmail();
  std::string getNome();
  unsigned int getId() const { return id_usuario; }
};

#endif
