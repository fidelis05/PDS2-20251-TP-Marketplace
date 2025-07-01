#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "Usuario.hpp"
#include "Admin.hpp"
#include "Correios.hpp"
#include "Produto.hpp"
#include <ncurses.h>
#include <string>
#include <vector>
#include <algorithm>

class Interface
{
private:
  Usuario usuarioLogado;
  Admin admin;
  Correios correios;
  bool isLoggedIn;
  bool isAdmin;
  bool isCorreios;

  // Tiling window state
  std::vector<Produto> allProducts;
  std::vector<Produto> displayedProducts;
  std::string searchTerm;
  int highlight;
  bool searching;

  // NCurses helper methods
  void inicializarNCurses();
  void finalizarNCurses();
  void desenharTitulo(WINDOW *win, const std::string &titulo);
  void desenharMoldura(WINDOW *win);
  void mostrarMensagem(const std::string &mensagem);
  void esperarTecla();
  int obterOpcaoMenu(WINDOW *win, int numOpcoes);
  std::string obterInput(WINDOW *win, int y, int x, const std::string &prompt, bool senha = false);
  void limparTela();

  // Tiling window methods
  void carregarProdutos();
  std::vector<Produto> filtrarProdutos(const std::vector<Produto> &produtos, const std::string &termo);
  void desenharPerfilInfo(WINDOW *win, const std::string &userName, const std::string &userEmail, int pedidosCount);
  void desenharListaProdutos(WINDOW *win);
  void desenharDetalhesProduto(WINDOW *win, const Produto &produto);
  void mostrarInterfaceTiling();
  void mostrarDetalhesView(const Produto &produto);
  bool mostrarTelaLogin();

  // Admin window management methods
  void mostrarJanelaListaUsuarios();
  void mostrarJanelaFiltrarUsuarios();
  void mostrarJanelaCadastrarUsuario();
  void mostrarJanelaListaProdutos();
  void mostrarJanelaFiltrarProdutos();
  void mostrarJanelaListaPedidos();
  void mostrarJanelaResumoEstatistico();

  // Correios window management methods
  void mostrarJanelaConsultarPedido();
  void mostrarJanelaListarEntregas();
  void mostrarJanelaConfirmarEntrega();
  void mostrarJanelaReportarProblema();
  void mostrarJanelaAtualizarStatus();
  void mostrarJanelaCodigoRastreio();
  void mostrarJanelaAlterarSenha();

  // User function windows
  void mostrarJanelaCarrinho();
  void mostrarJanelaPedidos();
  void mostrarJanelaEditarPerfil();
  void mostrarJanelaNovoProduto();

public:
  Interface();
  ~Interface();
  void mostrarMenuPrincipal();
  void mostrarMenuUsuario();
  void mostrarMenuAdmin();
  void mostrarMenuCorreios();
  void executarLogin();
  void executarLoginCorreios();
  void executarCadastro();
  void executar();
};

#endif
