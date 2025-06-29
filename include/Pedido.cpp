#include "Pedido.hpp"

Pedido::Pedido(int idComprador, int idVendedor, Carrinho y) {
    this->idComprador = idComprador;
    this->idVendedor = idVendedor;
    this->compra = y;
    this->createdAt = std::chrono::year_month_day{std::chrono::system_clock::now()};
    this->statusInfo = status.status_map[0];
    this->previsaoEntrega = 0; // Por simplicidade, mesmo dia por enquanto
}

void Pedido::pagamentoConcluido() {
    if (this->pagamento == true) {
        this->statusInfo = status.status_map[1];
    }
    else{
        throw std::runtime_error("Pagamento não concluído");
    }
}

void Pedido::cancelarPedido() {
    if (this->statusInfo == status.status_map[3] || 
this->statusInfo == status.status_map[4] || 
this->statusInfo == status.status_map[5] || 
this->statusInfo == status.status_map[6]) {
        throw std::runtime_error("Pedido não pode ser cancelado");
    }else{
    this->statusInfo = status.status_map[7]; //fica cancelado
    }
}

void Pedido::devolverPedido(idComprador) {
    if (this->statusInfo == status.status_map[6]) {    
        auto now = std::chrono::system_clock::now();
        auto entrega = std::chrono::system_clock::from_time_t(std::chrono::system_clock::to_time_t(dataEntrega));
        auto diff = std::chrono::duration_cast<std::chrono::hours>(now - entrega).count();
        
        if (diff <= 168) { // 7 days * 24 hours
            this->statusInfo = "Em processo de devolução";
            // implementar a logística reversa 
        } else {
            throw std::runtime_error("O tempo de devolução foi excedido (máximo 7 dias)");
        }
    }
    else {
        throw std::runtime_error("Pedido não pode ser devolvido, pois não foi entregue");
    }
}
// criar uma função ou uma subclasse que atrela o pedido a uma devolução onde aparecerá uma mensgem ao usuário informando que o pedido pode ser devolvido e que ele deve levar o produto ao correios para iniciar a logística reversa

void Pedido::enviarPedido(int usuarioId) {
    if (usuarioId == this->idVendedor) {
        if (this->pagamento == false) {
            throw std::runtime_error("Pagamento ainda não foi aprovado");
        }
        this->statusInfo = status.status_map[2];
    } else {
        throw std::runtime_error("Apenas o vendedor pode confirmar o pedido");
    }
}
