#ifndef CORREIOS_HPP
#define CORREIOS_HPP

#include "Pedido.hpp"
#include <string>
#include <fstream>
#include <vector>
#include <ctime>

class Correios : private Pedido
{
private:
  unsigned int idCorreios;
  std::string usuarioCorreios;
  std::string senhaCorreios;
  bool isLoggedIn;
  std::time_t lastLoginTime;
  unsigned int tentativasLogin;
  static const unsigned int MAX_TENTATIVAS = 3;
  static const std::time_t BLOQUEIO_TEMPO = 300; // 5 minutes in seconds

  // Authentication helper methods
  bool verificarCredenciais(const std::string &usuario, const std::string &senha);
  bool verificarBloqueio();
  void registrarTentativaLogin(bool sucesso);
  void salvarLog(const std::string &acao, const std::string &detalhes = "");

public:
  // Constructors
  Correios();
  Correios(unsigned int id, const std::string &usuario, const std::string &senha);

  // Authentication methods
  bool login(const std::string &usuario, const std::string &senha);
  void logout();
  bool isAuthenticated() const;
  void alterarSenha(const std::string &senhaAtual, const std::string &novaSenha);

  // Existing methods (now require authentication)
  unsigned int setStatus(unsigned int n);
  unsigned int setcodigoRastreio(unsigned int x);
  unsigned int getLista();

  struct InfoPedido
  {
    unsigned int id;
    std::string status;
    unsigned int codigoRastreio;
    bool encontrado;
  };
  InfoPedido consultarPedido(unsigned int idPedido);
  std::vector<std::string> obterPedidosParaEntrega();
  bool confirmarEntrega(unsigned int idPedido);
  bool reportarProblemaEntrega(unsigned int idPedido, const std::string &problema);

  // Getters
  unsigned int getId() const { return idCorreios; }
  std::string getUsuario() const { return usuarioCorreios; }
  std::time_t getLastLoginTime() const { return lastLoginTime; }
};

#endif
