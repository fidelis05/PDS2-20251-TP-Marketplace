#ifndef CORREIOS_HPP
#define CORREIOS_HPP

#include <Pedido.hpp>

class Correios : public Pedido
{
  int id;
  int setStatus(int n){ this->Status = this->Status[n]; }
};

#endif