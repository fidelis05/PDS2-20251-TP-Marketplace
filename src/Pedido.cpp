#include "Pedido.hpp"
#include <iomanip>
#include <sstream>

Pedido::Pedido(int idComprador, int idVendedor, const Carrinho& y) {
    this->idComprador = idComprador;
    this->idVendedor = idVendedor;
    this->compra = y;
    this->createdAt = std::time(nullptr);
    this->statusInfo = status.status_map[0];
    this->previsaoEntrega = this->createdAt; // Por simplicidade, mesmo dia por enquanto
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
    } else {
        this->statusInfo = status.status_map[7]; //fica cancelado
    }

}

void Pedido::devolverPedido() {
    if (this->statusInfo == status.status_map[6]) {    
        std::time_t now = std::time(nullptr);
        double diff = std::difftime(now, this->dataEntrega);
        
        if (diff <= 168 * 3600) { // 7 days * 24 hours * 3600 seconds
            this->statusInfo = "Em processo de devolução";
            statusInfo = status.status_map[7];  // Changed == to =
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

std::string Pedido::timeToString(std::time_t time) {
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void Pedido::SalvarPedidos(const std::string& filename) const {
    SalvarPedidosCSV(filename, *this);
}

void Pedido::SalvarPedidosCSV(const std::string& filename, const Pedido& pedido) {
    bool fileExists = std::ifstream(filename).good();
    std::ofstream file(filename, std::ios::app);
    
    // Write header if file is new
    if (!fileExists) {
        file << "ID,Comprador ID,Vendedor ID,Status,Codigo Rastreio,Data Criacao,Previsao Entrega,Data Entrega,Pagamento\n";
    }
    
    // Write order data
    file << pedido.getId() << ","
         << pedido.getIdComprador() << ","
         << pedido.getIdVendedor() << ","
         << pedido.getStatus() << ","
         << pedido.getCodigoRastreio() << ","
         << timeToString(pedido.getCreatedAt()) << ","
         << timeToString(pedido.getPrevisaoEntrega()) << ","
         << timeToString(pedido.getDataEntrega()) << ","
         << (pedido.getPagamento() ? "Sim" : "Não") << "\n";
    
    file.close();
}

std::time_t Pedido::stringToTime(const std::string& timeStr) {
    std::tm tm = {};
    std::istringstream ss(timeStr);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    return std::mktime(&tm);
}

std::vector<Pedido> Pedido::lerTodosPedidos(const std::string& filename) {
    std::vector<Pedido> pedidos;
    std::ifstream file(filename);
    std::string line;
    
    // Skip header
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;
        
        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        
        if (tokens.size() >= 9) {
            int id = std::stoi(tokens[0]);
            int compradorId = std::stoi(tokens[1]);
            int vendedorId = std::stoi(tokens[2]);
            std::string status = tokens[3];
            int codigoRastreio = std::stoi(tokens[4]);
            std::time_t createdAt = stringToTime(tokens[5]);
            std::time_t previsaoEntrega = stringToTime(tokens[6]);
            std::time_t dataEntrega = stringToTime(tokens[7]);
            bool pagamento = (tokens[8] == "Sim");
            
            // Create a new Pedido object with the data
            // Note: This requires an empty Carrinho for now
            Carrinho carrinhoVazio;
            Pedido pedido(compradorId, vendedorId, carrinhoVazio);
            
            // Set the remaining fields
            pedido.id = id;
            pedido.statusInfo = status;
            pedido.codigoRastreio = codigoRastreio;
            pedido.createdAt = createdAt;
            pedido.previsaoEntrega = previsaoEntrega;
            pedido.dataEntrega = dataEntrega;
            pedido.pagamento = pagamento;
            
            pedidos.push_back(pedido);
        }
    }
    
    return pedidos;
}

Pedido Pedido::lerPedidoPorId(const std::string& filename, int searchId) {
    std::ifstream file(filename);
    std::string line;
    
    // Skip header
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;
        
        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        
        if (tokens.size() >= 9) {
            int id = std::stoi(tokens[0]);
            
            if (id == searchId) {
                int compradorId = std::stoi(tokens[1]);
                int vendedorId = std::stoi(tokens[2]);
                std::string status = tokens[3];
                int codigoRastreio = std::stoi(tokens[4]);
                std::time_t createdAt = stringToTime(tokens[5]);
                std::time_t previsaoEntrega = stringToTime(tokens[6]);
                std::time_t dataEntrega = stringToTime(tokens[7]);
                bool pagamento = (tokens[8] == "Sim");
                
                Carrinho carrinhoVazio;
                Pedido pedido(compradorId, vendedorId, carrinhoVazio);
                
                // Set the remaining fields
                pedido.id = id;
                pedido.statusInfo = status;
                pedido.codigoRastreio = codigoRastreio;
                pedido.createdAt = createdAt;
                pedido.previsaoEntrega = previsaoEntrega;
                pedido.dataEntrega = dataEntrega;
                pedido.pagamento = pagamento;
                
                return pedido;
            }
        }
    }
    
    throw std::runtime_error("Pedido não encontrado");
}

void Pedido::iniciarLogisticaReversa() {
    if (!this->devolucaoIniciada) {
        // Gera um código de postagem único para devolução
        this->codigoPostagemDevolucao = "DEV" + std::to_string(this->id) + "REV" + std::to_string(std::time(nullptr));
        this->devolucaoIniciada = true;
        
        // Notifica sobre o início do processo de devolução
        this->notificarMudancaStatus("Devolução iniciada. Código de postagem: " + this->codigoPostagemDevolucao);
    } else {
        throw std::runtime_error("Processo de devolução já foi iniciado");
    }
}

void Pedido::atualizarStatusDevolucao(const std::string& novoStatus) {
    if (this->devolucaoIniciada) {
        this->statusInfo = novoStatus;
        this->notificarMudancaStatus("Status da devolução atualizado: " + novoStatus);
    } else {
        throw std::runtime_error("Devolução ainda não foi iniciada");
    }
}

void Pedido::avaliarPedido(int nota, const std::string& comentario) {
    if (this->statusInfo == status.status_map[6]) { // Verifica se foi entregue
        if (nota >= 1 && nota <= 5) {
            this->avaliacaoProduto = nota;
            this->comentarioAvaliacao = comentario;
            this->notificarMudancaStatus("Avaliação registrada com sucesso");
        } else {
            throw std::runtime_error("Nota deve estar entre 1 e 5");
        }
    } else {
        throw std::runtime_error("Só é possível avaliar pedidos entregues");
    }
}

void Pedido::notificarMudancaStatus(const std::string& mensagem) {
    // Por enquanto, apenas imprime no console
    // Em uma implementação real, isso poderia enviar email, SMS, ou notificação push
    std::cout << "Notificação para Pedido #" << this->id << ": " << mensagem << std::endl;
}
