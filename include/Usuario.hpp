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

  std::vector<Produto> obterProdutos();
  void adicionarProdutoAoCarrinho(unsigned int idProduto);
  void removerProdutoDoCarrinho(unsigned int idProduto);
  std::vector<std::shared_ptr<Pedido>> obterPedidos();
  bool finalizarCompraBusiness();
  void atualizarPerfil(const std::string &novoNome, const std::string &novoEmail,
                       const std::string &novoTelefone, const std::string &novoEndereco);
  void atualizarSenha(const std::string &novaSenha);
  bool adicionarNovoProduto(const Produto &produto);

  // Getters
  std::string getEmail() const { return email; }
  std::string getNome() const { return nome; }
  std::string getTelefone() const { return telefone; }
  std::string getCpfCnpj() const { return cpf_cnpj; }
  std::string getEndereco() const { return endereco; }
  unsigned int getId() const { return id_usuario; }
};

#endif
