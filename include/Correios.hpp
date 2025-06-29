#ifndef CORREIOS_HPP
#define CORREIOS_HPP

#include <Pedido.hpp>

class Correios : private Pedido {
private:
  int idCorreios;

public:
  int setStatus(int n);
  int setcodigoRastreio(int x);
  int getLista() {};
};

#endif
