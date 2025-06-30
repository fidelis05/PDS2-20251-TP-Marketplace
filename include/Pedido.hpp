#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include "Carrinho.hpp"
#include "Produto.hpp"
#include "Usuario.hpp"
#include <chrono>
#include <iostream>
#include <map>
#include <string>

struct Status
{
  std::map<int, std::string> status_map;

  Status()
  {
    status_map[0] = "Esperando aprovação do pagamento";
    status_map[1] = "Enviado";
    status_map[2] = "Vendedor ciente";
    status_map[3] = "Despachado";
    status_map[4] = "A caminho";
    status_map[5] = "Saiu para Entrega";
    status_map[6] = "Entregue";
    status_map[7] = "Cancelado";
  }
};

class Pedido
{
private:
  int id;
  int idVendedor, idComprador;
  bool pagamento = true;                       // inicializado como true por padrão pra futuras implementações
  std::chrono::year_month_day createdAt;       // criado junto ao constructor
  std::chrono::year_month_day previsaoEntrega; // cabe à Correios informar e futuramente poderia ser implementando um algoritmo atrelado ào CEP para estabelecer um tempo médio
  std::chrono::year_month_day dataEntrega;     // cabe à Correios mudar ou o próprio consumidor

  Carrinho compra; // herda as características inerentes ao carrinho

protected:
  Status status;          // composição que serve pra informar qual a situação do pedido
  std::string statusInfo; // é igualado ào map do status e serve pra informar o status atual do pedido
  int codigoRastreio;     // cabe à Correios informar

public:
  // Constructor
  Pedido(int idComprador, int idVendedor, Carrinho y);

  // Getters
  int getId() { return this->id; }
  int getIdVendedor() { return this->idVendedor; }
  int getIdComprador() { return this->idComprador; }
  bool getPagamento() { return this->pagamento; }
  std::chrono::year_month_day getCreatedAt() { return this->createdAt; }
  std::chrono::year_month_day getPrevisaoEntrega() { return this->previsaoEntrega; }
  std::chrono::year_month_day getDataEntrega() { return this->dataEntrega; }
  std::string getStatus() const { return this->statusInfo; }
  int getCodigoRastreio() const { return this->codigoRastreio; }

  // Ações básicas
  void pagamentoConcluido();
  void cancelarPedido();

  // Ações específicas
  void devolverPedido(int idComprador); // Remove parameter since it uses the stored idComprador
  void enviarPedido(int usuarioId);     // Verifica se é o vendedor
};

#endif
