#include "Pedido.hpp"
#include <iomanip>
#include <sstream>
#include "exceptions/MarketPlaceException.hpp"

Pedido::Pedido(unsigned int idComprador, unsigned int idVendedor, const Carrinho &y)
{
    this->idComprador = idComprador;
    this->idVendedor = idVendedor;
    this->id = idComprador + idVendedor; //passivel a erros caso seja feito o mesmo pedido, porem a implementacao necessaria seria colocar um getid e colocar baseado na quantidade na ultimo pedido do historico, soq n deu tempo foi mal kk 
    this->compra = y;
    this->createdAt = std::time(nullptr);
    this->pagamento = true;                  // Always set payment as true
    this->statusInfo = status.status_map[1]; // Since payment is always true, start with "Enviado"
    this->previsaoEntrega = this->createdAt; // Por simplicidade, mesmo dia por enquanto
    this->devolucaoIniciada = false;         // Initialize to false
    this->avaliacaoProduto = 0;              // Initialize rating
    this->codigoRastreio = 0;                // Initialize tracking code
}

void Pedido::pagamentoConcluido()
{
    // Payment is always true, so directly update status
    this->statusInfo = status.status_map[1];
}

void Pedido::cancelarPedido()
{
    if (this->statusInfo == status.status_map[3] ||
        this->statusInfo == status.status_map[4] ||
        this->statusInfo == status.status_map[5] ||
        this->statusInfo == status.status_map[6])
    {
        throw PedidoException("Pedido não pode ser cancelado");
    }
    else
    {
        this->statusInfo = status.status_map[7]; // fica cancelado
    }
}

void Pedido::devolverPedido()
{
    if (this->statusInfo == status.status_map[6])
    {
        std::time_t now = std::time(nullptr);
        double diff = std::difftime(now, this->dataEntrega);

        if (diff <= 168 * 3600)
        { // 7 days * 24 hours * 3600 seconds
            this->statusInfo = "Em processo de devolução";
            this->statusInfo = status.status_map[7];
            // implementar a logística reversa
        }
        else
        {
            throw PedidoException("O tempo de devolução foi excedido (máximo 7 dias)");
        }
    }
    else
    {
        throw PedidoException("Pedido não pode ser devolvido, pois não foi entregue");
    }
}
// criar uma função ou uma subclasse que atrela o pedido a uma devolução onde aparecerá uma mensgem ao usuário informando que o pedido pode ser devolvido e que ele deve levar o produto ao correios para iniciar a logística reversa

void Pedido::enviarPedido(unsigned int usuarioId)
{
    if (usuarioId == this->idVendedor)
    {
        // Payment is always true, so no need to check
        this->statusInfo = status.status_map[2];
    }
    else
    {
        throw PedidoException("Apenas o vendedor pode confirmar o pedido");
    }
}

std::string Pedido::timeToString(std::time_t time)
{
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void Pedido::SalvarPedidos(const std::string &filename) const
{
    SalvarPedidosCSV(filename, *this);
}

void Pedido::SalvarPedidosCSV(const std::string &filename, const Pedido &pedido)
{
    bool fileExists = std::ifstream(filename).good();
    std::ofstream file(filename, std::ios::app);

    // Write header if file is new
    if (!fileExists)
    {
        file << "ID,Comprador ID,Vendedor ID,Status,Codigo Rastreio,Data Criacao,Previsao Entrega,Data Entrega,Pagamento\n";
    }

    // Write order data
    file << pedido.getId() << "|"
         << pedido.getIdComprador() << "|"
         << pedido.getIdVendedor() << "|"
         << pedido.getStatus() << "|"
         << pedido.getCodigoRastreio() << "|"
         << timeToString(pedido.getCreatedAt()) << "|"
         << timeToString(pedido.getPrevisaoEntrega()) << "|"
         << timeToString(pedido.getDataEntrega()) << "|"
         << (pedido.getPagamento() ? "Sim" : "Não") << "\n";

    file.close();
}

std::time_t Pedido::stringToTime(const std::string &timeStr)
{
    std::tm tm = {};
    std::istringstream ss(timeStr);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    return std::mktime(&tm);
}

std::vector<Pedido> Pedido::lerTodosPedidos(const std::string &filename)
{
    std::vector<Pedido> pedidos;
    std::ifstream file(filename);
    std::string line;

    // Skip header
    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;

        while (std::getline(ss, token, '|'))
        {
            tokens.push_back(token);
        }

        if (tokens.size() >= 9)
        {
            unsigned int id = std::stoul(tokens[0]);
            unsigned int compradorId = std::stoul(tokens[1]);
            unsigned int vendedorId = std::stoul(tokens[2]);
            std::string status = tokens[3];
            unsigned int codigoRastreio = std::stoul(tokens[4]);
            std::time_t createdAt = stringToTime(tokens[5]);
            std::time_t previsaoEntrega = stringToTime(tokens[6]);
            std::time_t dataEntrega = stringToTime(tokens[7]);
            // Payment is always true, ignore CSV value
            bool pagamento = true;

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
            pedido.pagamento = pagamento; // Always true

            pedidos.push_back(pedido);
        }
    }

    return pedidos;
}

Pedido Pedido::lerPedidoPorId(const std::string &filename, unsigned int searchId)
{
    std::ifstream file(filename);
    std::string line;

    // Skip header
    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;

        while (std::getline(ss, token, '|'))
        {
            tokens.push_back(token);
        }

        if (tokens.size() >= 9)
        {
            unsigned int id = std::stoul(tokens[0]);

            if (id == searchId)
            {
                unsigned int compradorId = std::stoul(tokens[1]);
                unsigned int vendedorId = std::stoul(tokens[2]);
                std::string status = tokens[3];
                unsigned int codigoRastreio = std::stoul(tokens[4]);
                std::time_t createdAt = stringToTime(tokens[5]);
                std::time_t previsaoEntrega = stringToTime(tokens[6]);
                std::time_t dataEntrega = stringToTime(tokens[7]);
                // Payment is always true, ignore CSV value
                bool pagamento = true;

                // Create empty carrinho for reconstruction
                Carrinho carrinhoVazio;
                Pedido pedido(compradorId, vendedorId, carrinhoVazio);

                // Set the remaining fields
                pedido.id = id;
                pedido.statusInfo = status;
                pedido.codigoRastreio = codigoRastreio;
                pedido.createdAt = createdAt;
                pedido.previsaoEntrega = previsaoEntrega;
                pedido.dataEntrega = dataEntrega;
                pedido.pagamento = pagamento; // Always true

                return pedido;
            }
        }
    }

    throw PedidoException("Pedido não encontrado");
}

void Pedido::iniciarLogisticaReversa()
{
    if (!this->devolucaoIniciada)
    {
        // Gera um código de postagem único para devolução
        this->codigoPostagemDevolucao = "DEV" + std::to_string(this->id) + "REV" + std::to_string(std::time(nullptr));
        this->devolucaoIniciada = true;

        // Notifica sobre o início do processo de devolução
        this->notificarMudancaStatus("Devolução iniciada. Código de postagem: " + this->codigoPostagemDevolucao);
    }
    else
    {
        throw PedidoException("Processo de devolução já foi iniciado");
    }
}

void Pedido::notificarMudancaStatus(const std::string &mensagem)
{
    std::cout << "Notificação do Pedido #" << this->id << ": " << mensagem << std::endl;
}

void Pedido::atualizarStatusDevolucao(const std::string &novoStatus)
{
    this->statusInfo = novoStatus;
    notificarMudancaStatus("Status de devolução atualizado para: " + novoStatus);
}

void Pedido::avaliarPedido(unsigned int nota, const std::string &comentario)
{
    if (nota >= 1 && nota <= 5)
    {
        this->avaliacaoProduto = nota;
        this->comentarioAvaliacao = comentario;
        notificarMudancaStatus("Pedido avaliado com " + std::to_string(nota) + " estrelas");
    }
    else
    {
        throw PedidoException("Nota deve estar entre 1 e 5");
    }
}
