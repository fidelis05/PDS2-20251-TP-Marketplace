#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include "Produto.hpp"
#include "Usuario.hpp"
#include "Carrinho.hpp"
#include <iostream>
#include <string>
#include <map>

struct Status{
    map<int, std::string> status; 

    status{0} = "Esperando aprovação do pagamento";
    status{1} = "Enviado";
    status{2} = "Vendedor ciente";
    status{3} = "Despachado";
    status{4} = "A caminho";
    status{5} = "Saiu para Entrega";
    status{6} = "Entregue";
};

class Pedido
{
<<<<<<< Updated upstream
public:
  int id;
  std::string createdAt;
  std::string codigoRastreio;
    Carrinho Compra
=======
  private:
  static long int id; //vai verificar qual o ultimo item id da lista
  long int id; // sera atribuido o id com b
  std::string createdAt;
  std::string codigoRastreio;
  Carrinho Compra
  protected:
    Status status; //so pra ter uma métrica
    std::string Status; 
  public:
    void getId
    void getcreatedAt
    void getcodigoRastreio

>>>>>>> Stashed changes

  Pedido(Usuario x, Carrinho y);
<<<<<<< Updated upstream

  void cancelarPedido();
=======
    void statusdoPedido();
    void devolverPedido();
    void pagamentoConcluido();
    void prazodeEntrega();
    void cancelarpedido
>>>>>>> Stashed changes
};

#endif
