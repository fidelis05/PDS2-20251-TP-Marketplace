#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>
#include <vector>

#include "Produto.hpp"
#include "Pedido.hpp"
#include "Carrinho.hpp"

class Usuario{
private:
  std::string id_usuario;
  std::string nome;
  std::string email;
  std::string senha;
  std::string telefone;
  std::string cpf_cnpj;
  std::string endereco_u;

  std::vector<Produto> meusProdutos;
  std::vector<Pedido> meusPedidos;

  Carrinho carrinho; 

public:
  Usuario();
  Usuario(std::string nome, std::string email, std::string senha);

  void cadastrar(); 
  bool login(std::string email, std::string senha);
  void visualizarPerfil();
  void editarPerfil();

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
  std::string getId();
};


#endif