#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include "Carrinho.hpp"
#include "Produto.hpp"
#include "Usuario.hpp"
#include <ctime>
#include <iostream>
#include <map>
#include <string>
#include <fstream> // Added for file operations
#include <vector>  // Added for using vector

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
    unsigned int id;
    unsigned int idVendedor, idComprador;
    bool pagamento = true; // inicializado como true por padrão pra futuras implementações
    std::time_t createdAt;
    std::time_t previsaoEntrega;

    Carrinho compra;

protected:
    Status status;
    std::string statusInfo;
    unsigned int codigoRastreio;
    std::string codigoPostagemDevolucao;
    unsigned int avaliacaoProduto;
    std::string comentarioAvaliacao;
    bool devolucaoIniciada;
    std::time_t dataEntrega;

public:
    // Constructor
    Pedido(unsigned int idComprador, unsigned int idVendedor, const Carrinho &y);

    // Getters
    unsigned int getId() const { return this->id; }
    unsigned int getIdVendedor() const { return this->idVendedor; }
    unsigned int getIdComprador() const { return this->idComprador; }
    bool getPagamento() const { return this->pagamento; }
    std::time_t getCreatedAt() const { return this->createdAt; }
    std::time_t getPrevisaoEntrega() const { return this->previsaoEntrega; }
    std::time_t getDataEntrega() const { return this->dataEntrega; }
    std::string getStatus() const { return this->statusInfo; }
    unsigned int getCodigoRastreio() const { return this->codigoRastreio; }
    std::string getCodigoPostagemDevolucao() const { return this->codigoPostagemDevolucao; }
    bool getDevolucaoIniciada() const { return this->devolucaoIniciada; }
    // Ações básicas
    void pagamentoConcluido();
    void cancelarPedido();

    // Ações específicas
    void devolverPedido();                     // Remove parameter since it uses the stored idComprador
    void enviarPedido(unsigned int usuarioId); // Verifica se é o vendedor
    void iniciarLogisticaReversa();
    void atualizarStatusDevolucao(const std::string &novoStatus);
    void avaliarPedido(unsigned int nota, const std::string &comentario);
    void notificarMudancaStatus(const std::string &mensagem);

    // Métodos para salvar em CSV
    void SalvarPedidos(const std::string &filename) const;
    static void SalvarPedidosCSV(const std::string &filename, const Pedido &pedido);
    static std::string timeToString(std::time_t time);

    // New methods to read from CSV
    static std::vector<Pedido> lerTodosPedidos(const std::string &filename);
    static Pedido lerPedidoPorId(const std::string &filename, unsigned int id);
    static std::time_t stringToTime(const std::string &timeStr);
};

#endif
