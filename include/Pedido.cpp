#include "Pedido.hpp"
#include "./exceptions/RunTimeException.hpp"

Pedido::Pedido(int idComprador, int idVendedor, Carrinho y)
{
    this->idComprador = idComprador;
    this->idVendedor = idVendedor;
    this->compra = y;
    this->createdAt = std::time(nullptr);
    this->statusInfo = status.status_map[0];
    this->previsaoEntrega = this->createdAt; // Por simplicidade, mesmo dia por enquanto
}

void Pedido::pagamentoConcluido()
{
    if (this->pagamento == true)
    {
        this->statusInfo = status.status_map[1];
    }
    else
    {
        throw RunTimeException("Pagamento não concluído");
    }
}

void Pedido::cancelarPedido()
{
    if (this->statusInfo == status.status_map[3] ||
        this->statusInfo == status.status_map[4] ||
        this->statusInfo == status.status_map[5] ||
        this->statusInfo == status.status_map[6])
    {
        throw std::runtime_error("Pedido não pode ser cancelado");
    }
    else
    {
        this->statusInfo = status.status_map[7]; // fica cancelado
    }
}

void Pedido::devolverPedido(int idComprador)
{
    if (this->statusInfo == status.status_map[6])
    {
        std::time_t now = std::time(nullptr);
        double diff = std::difftime(now, this->dataEntrega);

        if (diff <= 168 * 3600)
        { // 7 days * 24 hours * 3600 seconds
            this->statusInfo = "Em processo de devolução";
            // implementar a logística reversa
        }
        else
        {
            throw RunTimeException("O tempo de devolução foi excedido (máximo 7 dias)");
        }
    }
    else
    {
        throw RunTimeException("Pedido não pode ser devolvido, pois não foi entregue");
    }
}
// criar uma função ou uma subclasse que atrela o pedido a uma devolução onde aparecerá uma mensgem ao usuário informando que o pedido pode ser devolvido e que ele deve levar o produto ao correios para iniciar a logística reversa

void Pedido::enviarPedido(int usuarioId)
{
    if (usuarioId == this->idVendedor)
    {
        if (this->pagamento == false)
        {
            throw RunTimeException("Pagamento ainda não foi aprovado");
        }
        this->statusInfo = status.status_map[2];
    }
    else
    {
        throw RunTimeException("Apenas o vendedor pode confirmar o pedido");
    }
}
