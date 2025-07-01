#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "Usuario.hpp"
#include "Admin.hpp"
#include "Correios.hpp"

class Interface
{
private:
  Usuario usuarioLogado;
  Admin admin;
  Correios correios;
  bool isLoggedIn;
  bool isAdmin;
  bool isCorreios;

public:
  Interface();
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
