#include "Correios.hpp"
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

// Constructors
Correios::Correios() : Pedido(0, 0, Carrinho()), idCorreios(0), isLoggedIn(false), lastLoginTime(0), tentativasLogin(0) {}

Correios::Correios(unsigned int id, const std::string &usuario, const std::string &senha)
    : Pedido(0, 0, Carrinho()), idCorreios(id), usuarioCorreios(usuario), senhaCorreios(senha),
      isLoggedIn(false), lastLoginTime(0), tentativasLogin(0) {}

// Authentication methods
bool Correios::login(const std::string &usuario, const std::string &senha)
{
    if (verificarBloqueio())
    {
        salvarLog("LOGIN_BLOCKED", "Tentativa de login durante bloqueio");
        std::cout << "Conta bloqueada temporariamente. Tente novamente em alguns minutos." << std::endl;
        return false;
    }

    if (verificarCredenciais(usuario, senha))
    {
        isLoggedIn = true;
        lastLoginTime = std::time(nullptr);
        tentativasLogin = 0;
        registrarTentativaLogin(true);
        salvarLog("LOGIN_SUCCESS", "Login realizado com sucesso");
        std::cout << "Login realizado com sucesso! Bem-vindo, " << usuario << std::endl;
        return true;
    }
    else
    {
        tentativasLogin++;
        registrarTentativaLogin(false);
        salvarLog("LOGIN_FAILED", "Credenciais inválidas");
        std::cout << "Credenciais inválidas. Tentativas restantes: "
                  << (MAX_TENTATIVAS - tentativasLogin) << std::endl;
        return false;
    }
}

void Correios::logout()
{
    if (isLoggedIn)
    {
        salvarLog("LOGOUT", "Logout realizado");
        isLoggedIn = false;
        std::cout << "Logout realizado com sucesso." << std::endl;
    }
}

bool Correios::isAuthenticated() const
{
    return isLoggedIn;
}

void Correios::alterarSenha(const std::string &senhaAtual, const std::string &novaSenha)
{
    if (!isAuthenticated())
    {
        throw std::runtime_error("Acesso negado. Faça login primeiro.");
    }

    if (senhaAtual != senhaCorreios)
    {
        salvarLog("PASSWORD_CHANGE_FAILED", "Senha atual incorreta");
        throw std::runtime_error("Senha atual incorreta.");
    }

    if (novaSenha.length() < 6)
    {
        throw std::runtime_error("Nova senha deve ter pelo menos 6 caracteres.");
    }

    senhaCorreios = novaSenha;
    salvarLog("PASSWORD_CHANGED", "Senha alterada com sucesso");
    std::cout << "Senha alterada com sucesso." << std::endl;
}

// Authentication helper methods
bool Correios::verificarCredenciais(const std::string &usuario, const std::string &senha)
{
    return (usuario == usuarioCorreios && senha == senhaCorreios);
}

bool Correios::verificarBloqueio()
{
    if (tentativasLogin >= MAX_TENTATIVAS)
    {
        std::time_t agora = std::time(nullptr);
        return (agora - lastLoginTime) < BLOQUEIO_TEMPO;
    }
    return false;
}

void Correios::registrarTentativaLogin(bool sucesso)
{
    std::ofstream file("correios_login.log", std::ios::app);
    std::time_t agora = std::time(nullptr);

    file << std::put_time(std::localtime(&agora), "%Y-%m-%d %H:%M:%S")
         << " | Usuario: " << usuarioCorreios
         << " | Status: " << (sucesso ? "SUCCESS" : "FAILED")
         << " | ID: " << idCorreios << std::endl;

    file.close();
}

void Correios::salvarLog(const std::string &acao, const std::string &detalhes)
{
    std::ofstream file("correios_actions.log", std::ios::app);
    std::time_t agora = std::time(nullptr);

    file << std::put_time(std::localtime(&agora), "%Y-%m-%d %H:%M:%S")
         << " | ID: " << idCorreios
         << " | Usuario: " << usuarioCorreios
         << " | Acao: " << acao;

    if (!detalhes.empty())
    {
        file << " | Detalhes: " << detalhes;
    }

    file << std::endl;
    file.close();
}

// Modified existing methods to require authentication
unsigned int Correios::setStatus(unsigned int n)
{
    if (!isAuthenticated())
    {
        throw std::runtime_error("Acesso negado. Faça login primeiro.");
    }

    if (n < 8)
    {
        if (n <= 3)
        {
            if (this->codigoRastreio == 0)
            {
                throw std::runtime_error("Favor informe o Código de Rastreio antes de Prosseguir");
            }
            else
            {
                this->statusInfo = this->status.status_map[n];
                salvarLog("STATUS_UPDATED", "Status alterado para: " + this->status.status_map[n]);
            }
        }
        else
        {
            this->statusInfo = this->status.status_map[n];
            salvarLog("STATUS_UPDATED", "Status alterado para: " + this->status.status_map[n]);
        }
    }
    else
    {
        throw std::runtime_error("Defina um número válido");
    }

    if (n == 6)
    {
        this->dataEntrega = std::time(nullptr);
        salvarLog("DELIVERY_CONFIRMED", "Entrega confirmada");
    }
    return 0;
}

unsigned int Correios::setcodigoRastreio(unsigned int x)
{
    if (!isAuthenticated())
    {
        throw std::runtime_error("Acesso negado. Faça login primeiro.");
    }

    this->codigoRastreio = x;
    salvarLog("TRACKING_CODE_SET", "Código de rastreio definido: " + std::to_string(x));
    return 0;
}

unsigned int Correios::getLista()
{
    if (!isAuthenticated())
    {
        throw std::runtime_error("Acesso negado. Faça login primeiro.");
    }

    salvarLog("LIST_ACCESSED", "Lista de pedidos acessada");
    return 0;
}

// New methods for Correios management
void Correios::consultarPedido(unsigned int idPedido)
{
    if (!isAuthenticated())
    {
        throw std::runtime_error("Acesso negado. Faça login primeiro.");
    }

    try
    {
        Pedido pedido = Pedido::lerPedidoPorId("data/pedidos.txt", idPedido);
        std::cout << "=== CONSULTA DE PEDIDO ===" << std::endl;
        std::cout << "ID: " << pedido.getId() << std::endl;
        std::cout << "Status: " << pedido.getStatus() << std::endl;
        std::cout << "Código de Rastreio: " << pedido.getCodigoRastreio() << std::endl;
        std::cout << "=========================" << std::endl;

        salvarLog("PEDIDO_CONSULTED", "Pedido consultado: " + std::to_string(idPedido));
    }
    catch (const std::exception &e)
    {
        std::cout << "Erro ao consultar pedido: " << e.what() << std::endl;
        salvarLog("PEDIDO_CONSULTATION_ERROR", "Erro ao consultar pedido: " + std::to_string(idPedido));
    }
}

void Correios::listarPedidosParaEntrega()
{
    if (!isAuthenticated())
    {
        throw std::runtime_error("Acesso negado. Faça login primeiro.");
    }

    try
    {
        auto pedidos = Pedido::lerTodosPedidos("data/pedidos.txt");
        std::cout << "=== PEDIDOS PARA ENTREGA ===" << std::endl;

        bool encontrouPedidos = false;
        for (const auto &pedido : pedidos)
        {
            if (pedido.getStatus() == "A caminho" || pedido.getStatus() == "Saiu para Entrega")
            {
                std::cout << "ID: " << pedido.getId()
                          << " | Status: " << pedido.getStatus()
                          << " | Código: " << pedido.getCodigoRastreio() << std::endl;
                encontrouPedidos = true;
            }
        }

        if (!encontrouPedidos)
        {
            std::cout << "Nenhum pedido para entrega encontrado." << std::endl;
        }

        std::cout << "=============================" << std::endl;
        salvarLog("DELIVERY_LIST_ACCESSED", "Lista de entregas acessada");
    }
    catch (const std::exception &e)
    {
        std::cout << "Erro ao listar pedidos: " << e.what() << std::endl;
        salvarLog("DELIVERY_LIST_ERROR", "Erro ao acessar lista de entregas");
    }
}

void Correios::confirmarEntrega(unsigned int idPedido)
{
    if (!isAuthenticated())
    {
        throw std::runtime_error("Acesso negado. Faça login primeiro.");
    }

    try
    {
        // This would update the pedido status to "Entregue"
        setStatus(6); // Status 6 = "Entregue"
        std::cout << "Entrega confirmada para o pedido #" << idPedido << std::endl;
        salvarLog("DELIVERY_CONFIRMED", "Entrega confirmada para pedido: " + std::to_string(idPedido));
    }
    catch (const std::exception &e)
    {
        std::cout << "Erro ao confirmar entrega: " << e.what() << std::endl;
        salvarLog("DELIVERY_CONFIRMATION_ERROR", "Erro ao confirmar entrega: " + std::to_string(idPedido));
    }
}

void Correios::reportarProblemaEntrega(unsigned int idPedido, const std::string &problema)
{
    if (!isAuthenticated())
    {
        throw std::runtime_error("Acesso negado. Faça login primeiro.");
    }

    std::ofstream file("problemas_entrega.log", std::ios::app);
    std::time_t agora = std::time(nullptr);

    file << std::put_time(std::localtime(&agora), "%Y-%m-%d %H:%M:%S")
         << " | Pedido: " << idPedido
         << " | Problema: " << problema
         << " | Funcionario: " << usuarioCorreios
         << " | ID: " << idCorreios << std::endl;

    file.close();

    std::cout << "Problema reportado para o pedido #" << idPedido << std::endl;
    salvarLog("PROBLEM_REPORTED", "Problema reportado para pedido: " + std::to_string(idPedido) + " - " + problema);
}
