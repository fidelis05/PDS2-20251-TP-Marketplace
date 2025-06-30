#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include "Carrinho.hpp"
#include "Produto.hpp"
#include "Usuario.hpp"
#include <ctime>
#include <iostream>
#include <map>
#include <string>
#include <fstream>  // Added for file operations

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
  bool pagamento = true; // inicializado como true por padrão pra futuras implementações

  Carrinho compra;

protected:
  Status status;
  std::string statusInfo;
  int codigoRastreio;
  std::time_t createdAt;
  std::time_t previsaoEntrega;
  std::time_t dataEntrega;

public:

    // Constructor
    Pedido(int idComprador, int idVendedor, const Carrinho& y); 

    // Getters
    int getId() const { return this->id; }
    int getIdVendedor() const { return this->idVendedor; }
    int getIdComprador() const { return this->idComprador; }
    bool getPagamento() const { return this->pagamento; }
    std::time_t getCreatedAt() const {return this->createdAt;}
    std::time_t getPrevisaoEntrega() const {return this->previsaoEntrega;}
    std::time_t getDataEntrega() const {return this->dataEntrega;}
    std::string getStatus() const {return this->statusInfo;}
    int getCodigoRastreio() const {return this->codigoRastreio;}


  // Ações básicas
  void pagamentoConcluido();
  void cancelarPedido();


  // Ações específicas
  void devolverPedido(int idComprador); // Remove parameter since it uses the stored idComprador
  void enviarPedido(int usuarioId);     // Verifica se é o vendedor


    // CSV operations
    void saveToCSV(const std::string& filename) const;
    static void appendToCSV(const std::string& filename, const Pedido& pedido);
    static std::string timeToString(std::time_t time);

};

#endif
