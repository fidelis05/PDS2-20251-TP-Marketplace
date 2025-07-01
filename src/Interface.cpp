#include "Interface.hpp"
#include <iostream>
#include <limits>
#include <cstring>
#include <fstream>
#include <sstream>
#include <cctype>

Interface::Interface() : correios(1, "correios", "correios123"), isLoggedIn(false), isAdmin(false), isCorreios(false),
                         highlight(0), searching(false)
{
  inicializarNCurses();
  carregarProdutos();
}

Interface::~Interface()
{
  finalizarNCurses();
}

void Interface::inicializarNCurses()
{
  initscr();
  noecho();
  cbreak();
  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_WHITE, COLOR_BLUE);
  init_pair(3, COLOR_RED, COLOR_BLACK);
  init_pair(4, COLOR_YELLOW, COLOR_BLACK);
  keypad(stdscr, TRUE);
}

void Interface::finalizarNCurses()
{
  endwin();
}

void Interface::carregarProdutos()
{
  allProducts.clear();
  std::ifstream file("data/produtos.txt");
  std::string line;

  while (std::getline(file, line))
  {
    if (line.empty())
      continue;

    std::stringstream ss(line);
    std::string item;
    std::vector<std::string> tokens;

    while (std::getline(ss, item, '|'))
    {
      tokens.push_back(item);
    }

    if (tokens.size() >= 8)
    {
      try
      {
        unsigned int id = std::stoi(tokens[0]);
        std::string nome = tokens[1];
        std::string marca = tokens[2];
        double valor = std::stod(tokens[3]);
        double avaliacao = std::stod(tokens[4]);
        unsigned int quantidade = std::stoi(tokens[5]);
        std::string descricao = tokens[6];
        std::string endereco = tokens[7];

        allProducts.emplace_back(id, nome, marca, valor, avaliacao, quantidade, descricao, endereco);
      }
      catch (const std::exception &e)
      {
        // Skip malformed lines
        continue;
      }
    }
  }

  displayedProducts = allProducts;
}

std::vector<Produto> Interface::filtrarProdutos(const std::vector<Produto> &produtos, const std::string &termo)
{
  if (termo.empty())
  {
    return produtos;
  }

  std::vector<Produto> filtered;
  std::string lowerTermo = termo;
  std::transform(lowerTermo.begin(), lowerTermo.end(), lowerTermo.begin(), ::tolower);

  for (const auto &produto : produtos)
  {
    std::string lowerNome = produto.nome;
    std::transform(lowerNome.begin(), lowerNome.end(), lowerNome.begin(), ::tolower);

    std::string lowerMarca = produto.marca;
    std::transform(lowerMarca.begin(), lowerMarca.end(), lowerMarca.begin(), ::tolower);

    if (lowerNome.find(lowerTermo) != std::string::npos ||
        lowerMarca.find(lowerTermo) != std::string::npos)
    {
      filtered.push_back(produto);
    }
  }

  return filtered;
}

void Interface::desenharPerfilInfo(WINDOW *win, const std::string &userName, const std::string &userEmail, int pedidosCount)
{
  werase(win);
  wbkgd(win, COLOR_PAIR(1));
  box(win, 0, 0);
  wattron(win, A_BOLD);
  mvwprintw(win, 0, 2, " Perfil ");
  wattroff(win, A_BOLD);

  int info_start_y = 3;
  mvwprintw(win, info_start_y, 2, "Nome: %.*s", getmaxx(win) - 8, userName.c_str());
  mvwprintw(win, info_start_y + 1, 2, "Email: %.*s", getmaxx(win) - 9, userEmail.c_str());
  mvwprintw(win, info_start_y + 2, 2, "Pedidos: %d", pedidosCount);

  // Menu actions
  mvwprintw(win, info_start_y + 5, 2, "Acoes:");
  mvwprintw(win, info_start_y + 6, 2, "c - Carrinho");
  mvwprintw(win, info_start_y + 7, 2, "p - Pedidos");
  mvwprintw(win, info_start_y + 8, 2, "e - Editar Perfil");
  mvwprintw(win, info_start_y + 9, 2, "n - Novo Produto");
  mvwprintw(win, info_start_y + 10, 2, "q - Sair");
}

void Interface::desenharListaProdutos(WINDOW *win)
{
  werase(win);
  wbkgd(win, COLOR_PAIR(1));
  box(win, 0, 0);
  wattron(win, A_BOLD);
  mvwprintw(win, 0, 2, " Marketplace ");
  wattroff(win, A_BOLD);

  mvwprintw(win, 2, 2, "Pesquisa: %s", searchTerm.c_str());

  if (displayedProducts.empty() && !searchTerm.empty())
  {
    mvwprintw(win, 4, 2, "Nenhum produto encontrado.");
  }
  else if (displayedProducts.empty() && searchTerm.empty() && !allProducts.empty())
  {
    mvwprintw(win, 4, 2, "Nenhum produto disponivel.");
  }

  int product_win_width = getmaxx(win);
  int max_display = LINES - 8; // Leave space for header and footer

  for (int i = 0; i < std::min((int)displayedProducts.size(), max_display); ++i)
  {
    if (i == highlight)
    {
      wattron(win, A_REVERSE);
    }

    std::string product_line = displayedProducts[i].nome + " - R$" +
                               std::to_string(displayedProducts[i].valor).substr(0, std::to_string(displayedProducts[i].valor).find(".") + 3);
    mvwprintw(win, i + 4, 2, "%.*s", product_win_width - 4, product_line.c_str());

    if (i == highlight)
    {
      wattroff(win, A_REVERSE);
    }
  }

  // Footer instructions
  int footer_y = LINES - 4;
  if (searching)
  {
    mvwprintw(win, footer_y, 2, "Digite para pesquisar...");
    mvwprintw(win, footer_y + 1, 2, "Esc - limpar | Enter - finalizar");
  }
  else
  {
    mvwprintw(win, footer_y, 2, "Setas - navegar | Enter - detalhes");
    mvwprintw(win, footer_y + 1, 2, "/ - pesquisar | a - adicionar ao carrinho");
  }
}

void Interface::desenharDetalhesProduto(WINDOW *win, const Produto &produto)
{
  werase(win);
  wbkgd(win, COLOR_PAIR(1));
  box(win, 0, 0);

  wattron(win, A_BOLD);
  std::string title = " " + produto.nome + " ";
  mvwprintw(win, 0, 2, "%.*s", getmaxx(win) - 4, title.c_str());
  wattroff(win, A_BOLD);

  mvwprintw(win, 2, 2, "Nome: %.*s", getmaxx(win) - 8, produto.nome.c_str());
  mvwprintw(win, 3, 2, "Marca: %.*s", getmaxx(win) - 9, produto.marca.c_str());
  mvwprintw(win, 4, 2, "Preco: R$%.2f", produto.valor);
  mvwprintw(win, 5, 2, "Avaliacao: %.1f/5", produto.avaliacao);
  mvwprintw(win, 6, 2, "Estoque: %u", produto.quantidade);
  mvwprintw(win, 7, 2, "Local: %.*s", getmaxx(win) - 9, produto.endereco.c_str());

  // Description (wrap text)
  mvwprintw(win, 9, 2, "Descricao:");
  int desc_width = getmaxx(win) - 4;
  std::string desc = produto.descricao;
  int y = 10;
  for (size_t i = 0; i < desc.length(); i += desc_width)
  {
    std::string line = desc.substr(i, desc_width);
    mvwprintw(win, y++, 2, "%s", line.c_str());
    if (y >= LINES - 3)
      break; // Don't overflow window
  }

  mvwprintw(win, LINES - 3, 2, "a - Adicionar ao carrinho");
  mvwprintw(win, LINES - 2, 2, "Qualquer tecla para voltar");
}

void Interface::mostrarDetalhesView(const Produto &produto)
{
  clear();
  refresh();

  int profile_w = COLS / 4;
  int product_w = COLS / 3;
  int details_w = COLS - profile_w - product_w;

  WINDOW *profile_win = newwin(LINES, profile_w, 0, 0);
  WINDOW *product_win = newwin(LINES, product_w, 0, profile_w);
  WINDOW *details_win = newwin(LINES, details_w, 0, profile_w + product_w);
  keypad(details_win, TRUE);

  desenharPerfilInfo(profile_win, usuarioLogado.getNome(), usuarioLogado.getEmail(), 0);
  desenharListaProdutos(product_win);
  desenharDetalhesProduto(details_win, produto);

  wrefresh(profile_win);
  wrefresh(product_win);
  wrefresh(details_win);

  int ch = wgetch(details_win);

  if (ch == 'a' || ch == 'A')
  {
    // Add to cart functionality
    usuarioLogado.carrinho.inserir(produto, 1); // Add 1 unit by default
    mostrarMensagem("Produto adicionado ao carrinho!");
  }

  delwin(profile_win);
  delwin(product_win);
  delwin(details_win);

  clear();
  refresh();
}

void Interface::mostrarInterfaceTiling()
{
  clear();
  refresh();

  int profile_win_width = COLS / 4;
  int product_win_width = COLS - profile_win_width;

  WINDOW *profile_win = newwin(LINES, profile_win_width, 0, 0);
  WINDOW *product_win = newwin(LINES, product_win_width, 0, profile_win_width);

  keypad(product_win, TRUE);

  int c;

  while (true)
  {
    desenharPerfilInfo(profile_win, usuarioLogado.getNome(), usuarioLogado.getEmail(), 0);
    desenharListaProdutos(product_win);

    wrefresh(profile_win);
    wrefresh(product_win);

    wmove(product_win, 2, 12 + searchTerm.length());

    c = wgetch(product_win);

    if (searching)
    {
      if (c == 10) // Enter key - finish searching
      {
        searching = false;
        if (static_cast<size_t>(highlight) >= displayedProducts.size() && !displayedProducts.empty())
        {
          highlight = displayedProducts.size() - 1;
        }
        else if (displayedProducts.empty())
        {
          highlight = 0;
        }
      }
      else if (c == 27) // Escape key - clear search
      {
        searchTerm = "";
        displayedProducts = filtrarProdutos(allProducts, searchTerm);
        highlight = 0;
        searching = false;
      }
      else if (c == KEY_BACKSPACE || c == 127 || c == 8)
      {
        if (!searchTerm.empty())
        {
          searchTerm.pop_back();
          displayedProducts = filtrarProdutos(allProducts, searchTerm);
          highlight = 0;
        }
      }
      else if (isprint(c))
      {
        searchTerm += c;
        displayedProducts = filtrarProdutos(allProducts, searchTerm);
        highlight = 0;
      }
    }
    else
    {
      switch (c)
      {
      case KEY_UP:
        if (!displayedProducts.empty())
        {
          if (highlight == 0)
          {
            highlight = displayedProducts.size() - 1;
          }
          else
          {
            highlight--;
          }
        }
        break;
      case KEY_DOWN:
        if (!displayedProducts.empty())
        {
          if (static_cast<size_t>(highlight) == displayedProducts.size() - 1)
          {
            highlight = 0;
          }
          else
          {
            highlight++;
          }
        }
        break;
      case 10: // Enter key
        if (!displayedProducts.empty() && static_cast<size_t>(highlight) < displayedProducts.size())
        {
          mostrarDetalhesView(displayedProducts[highlight]);
          touchwin(stdscr);
          refresh();
        }
        break;
      case '/':
        searching = true;
        break;
      case 'a':
      case 'A':
        if (!displayedProducts.empty() && static_cast<size_t>(highlight) < displayedProducts.size())
        {
          // Add to cart
          usuarioLogado.carrinho.inserir(displayedProducts[highlight], 1);
          mostrarMensagem("Produto adicionado ao carrinho!");
        }
        break;
      case 'c':
      case 'C':
        mostrarJanelaCarrinho();
        break;
      case 'p':
      case 'P':
        mostrarJanelaPedidos();
        break;
      case 'e':
      case 'E':
        mostrarJanelaEditarPerfil();
        break;
      case 'n':
      case 'N':
        mostrarJanelaNovoProduto();
        carregarProdutos(); // Reload products after adding new one
        displayedProducts = filtrarProdutos(allProducts, searchTerm);
        break;
      case 'q':
      case 'Q':
        delwin(product_win);
        delwin(profile_win);
        isLoggedIn = false;
        return;
      }
    }
  }

  delwin(product_win);
  delwin(profile_win);
}

bool Interface::mostrarTelaLogin()
{
  WINDOW *login_win = newwin(10, 40, (LINES - 10) / 2, (COLS - 40) / 2);
  keypad(login_win, TRUE);
  wbkgd(login_win, COLOR_PAIR(1));
  box(login_win, 0, 0);

  mvwprintw(login_win, 1, (40 - 5) / 2, "LOGIN");

  char username_c[51] = {0};
  char password_c[51] = {0};
  int user_len = 0;
  int pass_len = 0;

  enum class State
  {
    USERNAME,
    PASSWORD,
    DONE
  };
  State state = State::USERNAME;

  mvwprintw(login_win, 3, 2, "Email: ");
  mvwprintw(login_win, 4, 2, "Senha: ");
  wmove(login_win, 3, 9); // Start at email field
  wrefresh(login_win);

  int ch;
  while (state != State::DONE)
  {
    ch = wgetch(login_win);

    if (ch == KEY_RESIZE)
    {
      clear();
      refresh();
      mvwin(login_win, (LINES - 10) / 2, (COLS - 40) / 2);
      werase(login_win);
      box(login_win, 0, 0);
      mvwprintw(login_win, 1, (40 - 5) / 2, "LOGIN");
      mvwprintw(login_win, 3, 2, "Email: %s", username_c);
      std::string pass_mask(pass_len, '*');
      mvwprintw(login_win, 4, 2, "Senha: %s", pass_mask.c_str());
      if (state == State::USERNAME)
      {
        wmove(login_win, 3, 9 + user_len);
      }
      else
      {
        wmove(login_win, 4, 9 + pass_len);
      }
      wrefresh(login_win);
      continue;
    }

    switch (state)
    {
    case State::USERNAME:
      if (ch == '\n')
      {
        state = State::PASSWORD;
        wmove(login_win, 4, 9);
      }
      else if (ch == KEY_BACKSPACE || ch == 127 || ch == 8)
      {
        if (user_len > 0)
        {
          user_len--;
          username_c[user_len] = '\0';
          mvwaddch(login_win, 3, 9 + user_len, ' ');
          wmove(login_win, 3, 9 + user_len);
        }
      }
      else if (isprint(ch) && user_len < 50)
      {
        username_c[user_len++] = ch;
        waddch(login_win, ch);
      }
      break;
    case State::PASSWORD:
      if (ch == '\n')
      {
        state = State::DONE;
      }
      else if (ch == KEY_BACKSPACE || ch == 127 || ch == 8)
      {
        if (pass_len > 0)
        {
          pass_len--;
          password_c[pass_len] = '\0';
          mvwaddch(login_win, 4, 9 + pass_len, ' ');
          wmove(login_win, 4, 9 + pass_len);
        }
      }
      else if (isprint(ch) && pass_len < 50)
      {
        password_c[pass_len++] = ch;
        waddch(login_win, '*');
      }
      break;
    case State::DONE:
      break;
    }
    wrefresh(login_win);
  }

  // Try to login with the credentials
  std::string email(username_c);
  std::string senha(password_c);

  bool loginSuccess = usuarioLogado.login(email, senha);

  if (loginSuccess)
  {
    delwin(login_win);
    return true;
  }
  else
  {
    mvwprintw(login_win, 6, 2, "Email ou senha incorretos!");
    mvwprintw(login_win, 7, 2, "Pressione qualquer tecla...");
    wrefresh(login_win);
    wgetch(login_win);
    delwin(login_win);
    return false;
  }
}

void Interface::desenharTitulo(WINDOW *win, const std::string &titulo)
{
  wattron(win, A_BOLD);
  std::string titulo_formatado = " " + titulo + " ";
  mvwprintw(win, 0, 2, "%.*s", getmaxx(win) - 4, titulo_formatado.c_str());
  wattroff(win, A_BOLD);
}

void Interface::desenharMoldura(WINDOW *win)
{
  wbkgd(win, COLOR_PAIR(1));
  box(win, 0, 0);
}

void Interface::mostrarMensagem(const std::string &mensagem)
{
  int height = 5;
  int width = std::min(60, (int)mensagem.length() + 10);
  WINDOW *msg_win = newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
  desenharMoldura(msg_win);
  mvwprintw(msg_win, 2, 2, "%.*s", width - 4, mensagem.c_str());
  mvwprintw(msg_win, 3, 2, "Pressione qualquer tecla...");
  wrefresh(msg_win);
  wgetch(msg_win);
  delwin(msg_win);
  clear();
  refresh();
}

void Interface::esperarTecla()
{
  mvprintw(LINES - 2, 2, "Pressione qualquer tecla para continuar...");
  refresh();
  getch();
}

int Interface::obterOpcaoMenu(WINDOW *win, int numOpcoes)
{
  int ch;
  while (true)
  {
    ch = wgetch(win);
    if (ch >= '0' && ch <= '9')
    {
      int opcao = ch - '0';
      if (opcao >= 0 && opcao <= numOpcoes)
      {
        return opcao;
      }
    }
  }
}

std::string Interface::obterInput(WINDOW *win, int y, int x, const std::string &prompt, bool senha)
{
  mvwprintw(win, y, x, "%s", prompt.c_str());
  wrefresh(win);

  char buffer[256] = {0};
  int pos = 0;
  int ch;

  wmove(win, y, x + prompt.length());

  while ((ch = wgetch(win)) != '\n' && pos < 255)
  {
    if (ch == KEY_BACKSPACE || ch == 127 || ch == 8)
    {
      if (pos > 0)
      {
        pos--;
        buffer[pos] = '\0';
        mvwaddch(win, y, x + prompt.length() + pos, ' ');
        wmove(win, y, x + prompt.length() + pos);
      }
    }
    else if (isprint(ch))
    {
      buffer[pos++] = ch;
      if (senha)
      {
        waddch(win, '*');
      }
      else
      {
        waddch(win, ch);
      }
    }
    wrefresh(win);
  }

  return std::string(buffer);
}

void Interface::limparTela()
{
  clear();
  refresh();
}

void Interface::mostrarMenuPrincipal()
{
  int height = 12;
  int width = 40;
  WINDOW *menu_win = newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
  keypad(menu_win, TRUE);

  desenharMoldura(menu_win);
  desenharTitulo(menu_win, "MARKETPLACE MINAS");

  mvwprintw(menu_win, 2, 2, "1. Login");
  mvwprintw(menu_win, 3, 2, "2. Cadastro");
  mvwprintw(menu_win, 4, 2, "3. Login Administrador");
  mvwprintw(menu_win, 5, 2, "4. Login Correios");
  mvwprintw(menu_win, 6, 2, "0. Sair");

  mvwprintw(menu_win, 8, 2, "Escolha uma opcao: ");
  wrefresh(menu_win);

  int opcao = obterOpcaoMenu(menu_win, 4);
  delwin(menu_win);
  limparTela();

  switch (opcao)
  {
  case 1:
    executarLogin();
    break;
  case 2:
    executarCadastro();
    break;
  case 3:
  {
    int login_height = 8;
    int login_width = 40;
    WINDOW *login_win = newwin(login_height, login_width, (LINES - login_height) / 2, (COLS - login_width) / 2);
    keypad(login_win, TRUE);
    desenharMoldura(login_win);
    desenharTitulo(login_win, "LOGIN ADMIN");

    std::string adminPass = obterInput(login_win, 3, 2, "Senha: ", true);

    if (adminPass == "admin123")
    {
      isAdmin = true;
      mostrarMensagem("Login de administrador realizado!");
    }
    else
    {
      mostrarMensagem("Senha incorreta!");
    }
    delwin(login_win);
    limparTela();
  }
  break;
  case 4:
    executarLoginCorreios();
    break;
  case 0:
    finalizarNCurses();
    exit(0);
    break;
  }
}

void Interface::mostrarMenuUsuario()
{
  // Use the new tiling interface instead of the old menu
  mostrarInterfaceTiling();
}

void Interface::mostrarMenuAdmin()
{
  int height = 12;
  int width = 40;
  WINDOW *menu_win = newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
  keypad(menu_win, TRUE);

  desenharMoldura(menu_win);
  desenharTitulo(menu_win, "MENU ADMINISTRADOR");

  mvwprintw(menu_win, 2, 2, "1. Listar Usuarios");
  mvwprintw(menu_win, 3, 2, "2. Cadastrar Usuario");
  mvwprintw(menu_win, 4, 2, "3. Listar Produtos");
  mvwprintw(menu_win, 5, 2, "4. Listar Pedidos");
  mvwprintw(menu_win, 6, 2, "5. Resumo Estatistico");
  mvwprintw(menu_win, 7, 2, "0. Logout");

  mvwprintw(menu_win, 8, 2, "Escolha: ");
  wrefresh(menu_win);

  int opcao = obterOpcaoMenu(menu_win, 7);
  delwin(menu_win);
  limparTela();

  switch (opcao)
  {
  case 1:
    mostrarJanelaListaUsuarios();
    break;
  case 2:
    mostrarJanelaCadastrarUsuario();
    break;
  case 3:
    mostrarJanelaListaProdutos();
    break;
  case 4:
    mostrarJanelaListaPedidos();
    break;
  case 5:
    mostrarJanelaResumoEstatistico();
    break;
  case 0:
    isAdmin = false;
    mostrarMensagem("Logout de administrador realizado!");
    break;
  }
}

void Interface::mostrarMenuCorreios()
{
  int height = 14;
  int width = 45;
  WINDOW *menu_win = newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
  keypad(menu_win, TRUE);

  desenharMoldura(menu_win);
  desenharTitulo(menu_win, "MENU CORREIOS");

  mvwprintw(menu_win, 2, 2, "1. Consultar Pedido");
  mvwprintw(menu_win, 3, 2, "2. Listar Pedidos para Entrega");
  mvwprintw(menu_win, 4, 2, "3. Confirmar Entrega");
  mvwprintw(menu_win, 5, 2, "4. Reportar Problema na Entrega");
  mvwprintw(menu_win, 6, 2, "5. Atualizar Status do Pedido");
  mvwprintw(menu_win, 7, 2, "6. Definir Codigo de Rastreio");
  mvwprintw(menu_win, 8, 2, "7. Alterar Senha");
  mvwprintw(menu_win, 9, 2, "0. Logout");

  mvwprintw(menu_win, 11, 2, "Escolha: ");
  wrefresh(menu_win);

  int opcao = obterOpcaoMenu(menu_win, 7);
  delwin(menu_win);
  limparTela();

  switch (opcao)
  {
  case 1:
    mostrarJanelaConsultarPedido();
    break;
  case 2:
    mostrarJanelaListarEntregas();
    break;
  case 3:
    mostrarJanelaConfirmarEntrega();
    break;
  case 4:
    mostrarJanelaReportarProblema();
    break;
  case 5:
    mostrarJanelaAtualizarStatus();
    break;
  case 6:
    mostrarJanelaCodigoRastreio();
    break;
  case 7:
    mostrarJanelaAlterarSenha();
    break;
  case 0:
    correios.logout();
    isCorreios = false;
    mostrarMensagem("Logout de correios realizado!");
    break;
  }
}

void Interface::executarLogin()
{
  if (mostrarTelaLogin())
  {
    isLoggedIn = true;
    std::string mensagem = "Login realizado com sucesso!\nBem-vindo, " + usuarioLogado.getNome() + "!";
    mostrarMensagem(mensagem);
  }
}

void Interface::executarCadastro()
{
  int height = 18;
  int width = 60;
  WINDOW *cadastro_win = newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
  keypad(cadastro_win, TRUE);

  desenharMoldura(cadastro_win);
  desenharTitulo(cadastro_win, "CADASTRO");

  std::string nome = obterInput(cadastro_win, 3, 2, "Nome: ");
  std::string email = obterInput(cadastro_win, 5, 2, "Email: ");
  std::string senha = obterInput(cadastro_win, 7, 2, "Senha: ", true);
  std::string telefone = obterInput(cadastro_win, 9, 2, "Telefone: ");
  std::string cpf = obterInput(cadastro_win, 11, 2, "CPF/CNPJ: ");
  std::string endereco = obterInput(cadastro_win, 13, 2, "Endereco: ");

  usuarioLogado.cadastrar(nome, email, senha, telefone, cpf, endereco);

  delwin(cadastro_win);
  mostrarMensagem("Cadastro realizado com sucesso!");
}

void Interface::executarLoginCorreios()
{
  int height = 10;
  int width = 50;
  WINDOW *login_win = newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
  keypad(login_win, TRUE);

  desenharMoldura(login_win);
  desenharTitulo(login_win, "LOGIN CORREIOS");

  std::string usuario = obterInput(login_win, 3, 2, "Usuario: ");
  std::string senha = obterInput(login_win, 5, 2, "Senha: ", true);

  if (correios.login(usuario, senha))
  {
    isCorreios = true;
    std::string mensagem = "Login do Correios realizado com sucesso!\nBem-vindo, " + correios.getUsuario() + "!";
    delwin(login_win);
    mostrarMensagem(mensagem);
  }
  else
  {
    delwin(login_win);
    mostrarMensagem("Usuario ou senha incorretos, ou conta bloqueada!");
  }
}

void Interface::mostrarJanelaCarrinho()
{
  int height = 20;
  int width = 80;
  WINDOW *carrinho_win = newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
  keypad(carrinho_win, TRUE);

  desenharMoldura(carrinho_win);
  desenharTitulo(carrinho_win, "CARRINHO DE COMPRAS");

  // Display cart items
  mvwprintw(carrinho_win, 3, 2, "Itens no carrinho:");
  std::string carrinhoInfo = usuarioLogado.carrinho.exibir();

  // Display cart contents
  std::stringstream ss(carrinhoInfo);
  std::string line;
  int lineNum = 5;
  while (std::getline(ss, line) && lineNum < height - 8)
  {
    mvwprintw(carrinho_win, lineNum++, 2, "%.*s", width - 4, line.c_str());
  }

  mvwprintw(carrinho_win, height - 7, 2, "Opcoes:");
  mvwprintw(carrinho_win, height - 6, 2, "r - Remover item");
  mvwprintw(carrinho_win, height - 5, 2, "R - Remover todos os itens");
  mvwprintw(carrinho_win, height - 4, 2, "f - Finalizar compra");
  mvwprintw(carrinho_win, height - 3, 2, "Qualquer outra tecla - Voltar");

  wrefresh(carrinho_win);

  int ch = wgetch(carrinho_win);

  switch (ch)
  {
  case 'r':
  case 'R':
    if (ch == 'r')
    {
      // Remove specific item
      std::string idStr = obterInput(carrinho_win, height - 2, 2, "ID do produto: ");
      try
      {
        unsigned int id = std::stoi(idStr);
        usuarioLogado.carrinho.excluir(id);
        mostrarMensagem("Produto removido do carrinho!");
      }
      catch (const std::exception &e)
      {
        mostrarMensagem("ID invalido!");
      }
    }
    else
    {
      // Remove all items
      usuarioLogado.carrinho.excluir();
      mostrarMensagem("Carrinho limpo!");
    }
    break;
  case 'f':
  case 'F':
    // Finalize purchase
    if (usuarioLogado.carrinho.carrinhoProdutos.empty())
    {
      mostrarMensagem("Carrinho vazio!");
    }
    else
    {
      if (usuarioLogado.finalizarCompraBusiness())
      {
        usuarioLogado.carrinho.finalizarCompra();
        mostrarMensagem("Compra finalizada com sucesso!");
      }
      else
      {
        mostrarMensagem("Erro ao finalizar compra!");
      }
    }
    break;
  default:
    break;
  }

  delwin(carrinho_win);
  clear();
  refresh();
}

void Interface::mostrarJanelaPedidos()
{
  int height = 20;
  int width = 80;
  WINDOW *pedidos_win = newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
  keypad(pedidos_win, TRUE);

  desenharMoldura(pedidos_win);
  desenharTitulo(pedidos_win, "MEUS PEDIDOS");

  // Get user's orders
  auto pedidos = usuarioLogado.obterPedidos();

  mvwprintw(pedidos_win, 3, 2, "Pedidos realizados:");

  if (pedidos.empty())
  {
    mvwprintw(pedidos_win, 5, 2, "Nenhum pedido encontrado.");
  }
  else
  {
    int lineNum = 5;
    for (size_t i = 0; i < pedidos.size() && lineNum < height - 6; ++i)
    {
      auto pedido = pedidos[i];
      mvwprintw(pedidos_win, lineNum++, 2, "Pedido #%u - Status: %s",
                pedido->getId(), pedido->getStatus().c_str());
      mvwprintw(pedidos_win, lineNum++, 2, "  Data: %s",
                Pedido::timeToString(pedido->getCreatedAt()).c_str());
      lineNum++;
    }
  }

  mvwprintw(pedidos_win, height - 4, 2, "c - Cancelar pedido");
  mvwprintw(pedidos_win, height - 3, 2, "Qualquer outra tecla - Voltar");

  wrefresh(pedidos_win);

  int ch = wgetch(pedidos_win);

  if (ch == 'c' || ch == 'C')
  {
    std::string idStr = obterInput(pedidos_win, height - 2, 2, "ID do pedido: ");
    try
    {
      unsigned int id = std::stoi(idStr);
      // Find and cancel the order
      bool found = false;
      for (auto pedido : pedidos)
      {
        if (pedido->getId() == id)
        {
          try
          {
            pedido->cancelarPedido();
            mostrarMensagem("Pedido cancelado com sucesso!");
            found = true;
            break;
          }
          catch (const std::runtime_error &e)
          {
            mostrarMensagem("Erro: " + std::string(e.what()));
            found = true;
            break;
          }
        }
      }
      if (!found)
      {
        mostrarMensagem("Pedido nao encontrado!");
      }
    }
    catch (const std::exception &e)
    {
      mostrarMensagem("ID de pedido invalido!");
    }
  }

  delwin(pedidos_win);
  clear();
  refresh();
}

void Interface::mostrarJanelaEditarPerfil()
{
  int height = 18;
  int width = 60;
  WINDOW *perfil_win = newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
  keypad(perfil_win, TRUE);

  desenharMoldura(perfil_win);
  desenharTitulo(perfil_win, "EDITAR PERFIL");

  // Show current profile info
  mvwprintw(perfil_win, 3, 2, "Dados atuais:");
  mvwprintw(perfil_win, 4, 2, "Nome: %.*s", width - 8, usuarioLogado.getNome().c_str());
  mvwprintw(perfil_win, 5, 2, "Email: %.*s", width - 9, usuarioLogado.getEmail().c_str());
  mvwprintw(perfil_win, 6, 2, "Telefone: %.*s", width - 12, usuarioLogado.getTelefone().c_str());
  mvwprintw(perfil_win, 7, 2, "Endereco: %.*s", width - 12, usuarioLogado.getEndereco().c_str());

  mvwprintw(perfil_win, 9, 2, "Opcoes:");
  mvwprintw(perfil_win, 10, 2, "1 - Editar perfil");
  mvwprintw(perfil_win, 15, 2, "0 - Voltar");

  wrefresh(perfil_win);

  int opcao = obterOpcaoMenu(perfil_win, 5);

  switch (opcao)
  {
  case 1:
  {
    std::string novoNome = obterInput(perfil_win, 16, 2, "Novo nome: ");
    std::string novoEmail = obterInput(perfil_win, 16, 2, "Novo email: ");
    std::string novoTelefone = obterInput(perfil_win, 16, 2, "Novo telefone: ");
    std::string novoEndereco = obterInput(perfil_win, 16, 2, "Novo endereco: ");
    usuarioLogado.atualizarPerfil(novoNome, novoEmail, novoTelefone, novoEndereco);
    mostrarMensagem("Nome atualizado com sucesso!");
  }
  break;
  case 0:
    break;
  }

  delwin(perfil_win);
  clear();
  refresh();
}

void Interface::mostrarJanelaNovoProduto()
{
  int height = 18;
  int width = 70;
  WINDOW *produto_win = newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
  keypad(produto_win, TRUE);

  desenharMoldura(produto_win);
  desenharTitulo(produto_win, "CADASTRAR PRODUTO");

  std::string nome = obterInput(produto_win, 3, 2, "Nome: ");
  std::string marca = obterInput(produto_win, 5, 2, "Marca: ");
  std::string valorStr = obterInput(produto_win, 7, 2, "Valor (R$): ");
  std::string quantidadeStr = obterInput(produto_win, 9, 2, "Quantidade: ");
  std::string descricao = obterInput(produto_win, 11, 2, "Descricao: ");
  std::string endereco = obterInput(produto_win, 13, 2, "Local: ");

  try
  {
    double valor = std::stod(valorStr);
    unsigned int quantidade = std::stoi(quantidadeStr);

    static unsigned int nextId = allProducts.size() + 1000 + 1; // Ids comecem em 1000

    Produto novoProduto(nextId, nome, marca, valor, 0.0, quantidade, descricao, endereco);

    std::ofstream file("data/produtos.txt", std::ios::app);
    file << novoProduto.id << "|" << novoProduto.nome << "|" << novoProduto.marca << "|"
         << novoProduto.valor << "|" << novoProduto.avaliacao << "|" << novoProduto.quantidade
         << "|" << novoProduto.descricao << "|" << novoProduto.endereco << std::endl;
    file.close();

    mostrarMensagem("Produto cadastrado com sucesso!");
  }
  catch (const std::exception &e)
  {
    mostrarMensagem("Erro nos dados informados!");
  }

  delwin(produto_win);
  clear();
  refresh();
}

void Interface::mostrarJanelaListaUsuarios()
{
  auto usuarios = admin.obterListaDeUsuarios();

  int height = std::min(20, (int)usuarios.size() + 5);
  int width = 80;
  WINDOW *win = newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
  keypad(win, TRUE);

  desenharMoldura(win);
  desenharTitulo(win, "LISTA DE USUARIOS");

  for (size_t i = 0; i < usuarios.size() && static_cast<int>(i) < height - 4; ++i)
  {
    mvwprintw(win, i + 2, 2, "%.*s", width - 4, usuarios[i].c_str());
  }

  mvwprintw(win, height - 2, 2, "Pressione qualquer tecla...");
  wrefresh(win);
  wgetch(win);
  delwin(win);
  clear();
  refresh();
}

void Interface::mostrarJanelaCadastrarUsuario()
{
  int height = 16;
  int width = 60;
  WINDOW *win = newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
  keypad(win, TRUE);

  desenharMoldura(win);
  desenharTitulo(win, "CADASTRAR USUARIO");

  std::string nome = obterInput(win, 3, 2, "Nome: ");
  std::string email = obterInput(win, 5, 2, "Email: ");
  std::string senha = obterInput(win, 7, 2, "Senha: ", true);
  std::string telefone = obterInput(win, 9, 2, "Telefone: ");
  std::string cpf = obterInput(win, 11, 2, "CPF/CNPJ: ");
  std::string endereco = obterInput(win, 13, 2, "Endereco: ");

  admin.cadastrarUsuario(nome, email, senha, telefone, cpf, endereco);

  delwin(win);
  mostrarMensagem("Usuario cadastrado com sucesso!");
}

void Interface::mostrarJanelaListaProdutos()
{
  auto produtos = admin.obterListaDeProdutos();

  int height = std::min(20, (int)produtos.size() + 5);
  int width = 80;
  WINDOW *win = newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
  keypad(win, TRUE);

  desenharMoldura(win);
  desenharTitulo(win, "LISTA DE PRODUTOS");

  for (size_t i = 0; i < produtos.size() && static_cast<int>(i) < height - 4; ++i)
  {
    mvwprintw(win, i + 2, 2, "%.*s", width - 4, produtos[i].c_str());
  }

  mvwprintw(win, height - 2, 2, "Pressione qualquer tecla...");
  wrefresh(win);
  wgetch(win);
  delwin(win);
  clear();
  refresh();
}

void Interface::mostrarJanelaListaPedidos()
{
  auto pedidos = admin.obterListaDePedidos();

  int height = std::min(20, (int)pedidos.size() + 5);
  int width = 80;
  WINDOW *win = newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
  keypad(win, TRUE);

  desenharMoldura(win);
  desenharTitulo(win, "LISTA DE PEDIDOS");

  if (pedidos.empty())
  {
    mvwprintw(win, 2, 2, "Nenhum pedido encontrado.");
  }
  else
  {
    for (size_t i = 0; i < pedidos.size() && static_cast<int>(i) < height - 4; ++i)
    {
      mvwprintw(win, i + 2, 2, "%.*s", width - 4, pedidos[i].c_str());
    }
  }

  mvwprintw(win, height - 2, 2, "Pressione qualquer tecla...");
  wrefresh(win);
  wgetch(win);
  delwin(win);
  clear();
  refresh();
}

void Interface::mostrarJanelaResumoEstatistico()
{
  auto resumo = admin.obterResumoEstatistico();

  int height = 10;
  int width = 40;
  WINDOW *win = newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
  keypad(win, TRUE);

  desenharMoldura(win);
  desenharTitulo(win, "RESUMO ESTATISTICO");

  mvwprintw(win, 3, 2, "Total de usuarios: %d", resumo.totalUsuarios);
  mvwprintw(win, 4, 2, "Total de produtos: %d", resumo.totalProdutos);
  mvwprintw(win, 5, 2, "Total de pedidos: %d", resumo.totalPedidos);

  mvwprintw(win, 7, 2, "Pressione qualquer tecla...");
  wrefresh(win);
  wgetch(win);
  delwin(win);
  clear();
  refresh();
}

void Interface::mostrarJanelaConsultarPedido()
{
  int height = 8;
  int width = 40;
  WINDOW *input_win = newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
  keypad(input_win, TRUE);

  desenharMoldura(input_win);
  desenharTitulo(input_win, "CONSULTAR PEDIDO");

  std::string id_str = obterInput(input_win, 3, 2, "ID do pedido: ");
  delwin(input_win);

  try
  {
    unsigned int idPedido = std::stoi(id_str);
    auto info = correios.consultarPedido(idPedido);

    height = 10;
    width = 50;
    WINDOW *result_win = newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
    keypad(result_win, TRUE);

    desenharMoldura(result_win);
    desenharTitulo(result_win, "CONSULTA DE PEDIDO");

    if (info.encontrado)
    {
      mvwprintw(result_win, 3, 2, "ID: %u", info.id);
      mvwprintw(result_win, 4, 2, "Status: %s", info.status.c_str());
      mvwprintw(result_win, 5, 2, "Codigo Rastreio: %u", info.codigoRastreio);
    }
    else
    {
      mvwprintw(result_win, 3, 2, "Pedido nao encontrado ou erro.");
    }

    mvwprintw(result_win, 7, 2, "Pressione qualquer tecla...");
    wrefresh(result_win);
    wgetch(result_win);
    delwin(result_win);
  }
  catch (const std::runtime_error &e)
  {
    mostrarMensagem("Erro: " + std::string(e.what()));
  }
  catch (const std::exception &e)
  {
    mostrarMensagem("ID de pedido invalido!");
  }

  clear();
  refresh();
}

void Interface::mostrarJanelaListarEntregas()
{
  try
  {
    auto pedidos = correios.obterPedidosParaEntrega();

    int height = std::min(20, (int)pedidos.size() + 5);
    int width = 80;
    WINDOW *win = newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
    keypad(win, TRUE);

    desenharMoldura(win);
    desenharTitulo(win, "PEDIDOS PARA ENTREGA");

    if (pedidos.empty())
    {
      mvwprintw(win, 2, 2, "Nenhum pedido para entrega encontrado.");
    }
    else
    {
      for (size_t i = 0; i < pedidos.size() && static_cast<int>(i) < height - 4; ++i)
      {
        mvwprintw(win, i + 2, 2, "%.*s", width - 4, pedidos[i].c_str());
      }
    }

    mvwprintw(win, height - 2, 2, "Pressione qualquer tecla...");
    wrefresh(win);
    wgetch(win);
    delwin(win);
  }
  catch (const std::exception &e)
  {
    mostrarMensagem("Erro ao acessar pedidos: " + std::string(e.what()));
  }

  clear();
  refresh();
}

void Interface::mostrarJanelaConfirmarEntrega()
{
  int height = 8;
  int width = 40;
  WINDOW *win = newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
  keypad(win, TRUE);

  desenharMoldura(win);
  desenharTitulo(win, "CONFIRMAR ENTREGA");

  std::string id_str = obterInput(win, 3, 2, "ID do pedido: ");
  delwin(win);

  try
  {
    unsigned int idPedido = std::stoi(id_str);
    bool sucesso = correios.confirmarEntrega(idPedido);

    if (sucesso)
    {
      mostrarMensagem("Entrega confirmada com sucesso!");
    }
    else
    {
      mostrarMensagem("Erro ao confirmar entrega.");
    }
  }
  catch (const std::runtime_error &e)
  {
    mostrarMensagem("Erro: " + std::string(e.what()));
  }
  catch (const std::exception &e)
  {
    mostrarMensagem("ID de pedido invalido!");
  }
}

void Interface::mostrarJanelaReportarProblema()
{
  int height = 10;
  int width = 50;
  WINDOW *win = newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
  keypad(win, TRUE);

  desenharMoldura(win);
  desenharTitulo(win, "REPORTAR PROBLEMA");

  std::string id_str = obterInput(win, 3, 2, "ID do pedido: ");
  std::string problema = obterInput(win, 5, 2, "Problema: ");
  delwin(win);

  try
  {
    unsigned int idPedido = std::stoi(id_str);
    bool sucesso = correios.reportarProblemaEntrega(idPedido, problema);

    if (sucesso)
    {
      mostrarMensagem("Problema reportado com sucesso!");
    }
    else
    {
      mostrarMensagem("Erro ao reportar problema.");
    }
  }
  catch (const std::runtime_error &e)
  {
    mostrarMensagem("Erro: " + std::string(e.what()));
  }
  catch (const std::exception &e)
  {
    mostrarMensagem("ID de pedido invalido!");
  }
}

void Interface::mostrarJanelaAtualizarStatus()
{
  int height = 8;
  int width = 40;
  WINDOW *win = newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
  keypad(win, TRUE);

  desenharMoldura(win);
  desenharTitulo(win, "ATUALIZAR STATUS");

  std::string status_str = obterInput(win, 3, 2, "Novo status (0-7): ");
  delwin(win);

  try
  {
    unsigned int statusNum = std::stoi(status_str);
    correios.setStatus(statusNum);
    mostrarMensagem("Status atualizado com sucesso!");
  }
  catch (const std::runtime_error &e)
  {
    mostrarMensagem("Erro: " + std::string(e.what()));
  }
  catch (const std::exception &e)
  {
    mostrarMensagem("Status invalido!");
  }
}

void Interface::mostrarJanelaCodigoRastreio()
{
  int height = 8;
  int width = 40;
  WINDOW *win = newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
  keypad(win, TRUE);

  desenharMoldura(win);
  desenharTitulo(win, "CODIGO RASTREIO");

  std::string codigo_str = obterInput(win, 3, 2, "Codigo: ");
  delwin(win);

  try
  {
    unsigned int codigoRastreio = std::stoi(codigo_str);
    correios.setcodigoRastreio(codigoRastreio);
    mostrarMensagem("Codigo de rastreio definido!");
  }
  catch (const std::runtime_error &e)
  {
    mostrarMensagem("Erro: " + std::string(e.what()));
  }
  catch (const std::exception &e)
  {
    mostrarMensagem("Codigo invalido!");
  }
}

void Interface::mostrarJanelaAlterarSenha()
{
  int height = 10;
  int width = 40;
  WINDOW *win = newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
  keypad(win, TRUE);

  desenharMoldura(win);
  desenharTitulo(win, "ALTERAR SENHA");

  std::string senhaAtual = obterInput(win, 3, 2, "Senha atual: ", true);
  std::string novaSenha = obterInput(win, 5, 2, "Nova senha: ", true);
  delwin(win);

  try
  {
    correios.alterarSenha(senhaAtual, novaSenha);
    mostrarMensagem("Senha alterada com sucesso!");
  }
  catch (const std::exception &e)
  {
    mostrarMensagem("Erro ao alterar senha: " + std::string(e.what()));
  }
}

void Interface::executar()
{
  while (true)
  {
    if (!isLoggedIn && !isAdmin && !isCorreios)
    {
      mostrarMenuPrincipal();
    }
    else if (isLoggedIn)
    {
      mostrarMenuUsuario();
    }
    else if (isAdmin)
    {
      mostrarMenuAdmin();
    }
    else if (isCorreios)
    {
      mostrarMenuCorreios();
    }
  }
}
