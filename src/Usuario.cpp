#include "Usuario.hpp"
#include "Pedido.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

Usuario::Usuario() : id_usuario(0) {}
Usuario::Usuario(std::string nome, std::string email, std::string senha)
    : id_usuario(0), nome(nome), email(email), senha(senha) {}

void Usuario::cadastrar(std::string nome, std::string email, std::string senha, std::string telefone, std::string cpf_cnpj, std::string endereco)
{
    this->nome = nome;
    this->email = email;
    this->senha = senha;
    this->telefone = telefone;
    this->cpf_cnpj = cpf_cnpj;
    this->endereco = endereco;

    // Save to file
    std::ofstream file("data/usuarios.txt", std::ios::app);
    file << email << "|" << senha << "|" << nome << "|" << telefone << "|" << cpf_cnpj << "|" << endereco << std::endl;
    file.close();

    std::cout << "Usuário cadastrado com sucesso!" << std::endl;
}

bool Usuario::login(std::string email, std::string senha)
{
    std::ifstream file("data/usuarios.txt");
    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string file_email, file_senha, file_nome, file_telefone, file_cpf, file_endereco;

        std::getline(ss, file_email, '|');
        std::getline(ss, file_senha, '|');
        std::getline(ss, file_nome, '|');
        std::getline(ss, file_telefone, '|');
        std::getline(ss, file_cpf, '|');
        std::getline(ss, file_endereco, '|');

        if (file_email == email && file_senha == senha)
        {
            this->email = file_email;
            this->senha = file_senha;
            this->nome = file_nome;
            this->telefone = file_telefone;
            this->cpf_cnpj = file_cpf;
            this->endereco = file_endereco;
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void Usuario::visualizarPerfil()
{
    std::cout << "\n===== PERFIL DO USUÁRIO =====" << std::endl;
    std::cout << "Nome: " << nome << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Telefone: " << telefone << std::endl;
    std::cout << "CPF/CNPJ: " << cpf_cnpj << std::endl;
    std::cout << "Endereço: " << endereco << std::endl;
    std::cout << "=============================" << std::endl;
}

void Usuario::editarPerfil()
{
    int opcao;
    std::cout << "\n===== EDITAR PERFIL =====" << std::endl;
    std::cout << "1. Editar Email" << std::endl;
    std::cout << "2. Editar Senha" << std::endl;
    std::cout << "3. Editar Telefone" << std::endl;
    std::cout << "4. Editar Endereço" << std::endl;
    std::cout << "0. Voltar" << std::endl;
    std::cout << "Escolha: ";
    std::cin >> opcao;

    switch (opcao)
    {
    case 1:
        editarEmail();
        break;
    case 2:
        editarSenha();
        break;
    case 3:
        editarTelefone();
        break;
    case 4:
        editarEndereco();
        break;
    case 0:
        break;
    default:
        std::cout << "Opção inválida!" << std::endl;
    }
}

void Usuario::editarEmail()
{
    std::string novoEmail;
    std::cout << "Novo email: ";
    std::cin >> novoEmail;
    this->email = novoEmail;
    std::cout << "Email atualizado com sucesso!" << std::endl;
}

void Usuario::editarSenha()
{
    std::string novaSenha;
    std::cout << "Nova senha: ";
    std::cin >> novaSenha;
    this->senha = novaSenha;
    std::cout << "Senha atualizada com sucesso!" << std::endl;
}

void Usuario::editarTelefone()
{
    std::string novoTelefone;
    std::cout << "Novo telefone: ";
    std::cin >> novoTelefone;
    this->telefone = novoTelefone;
    std::cout << "Telefone atualizado com sucesso!" << std::endl;
}

void Usuario::editarEndereco()
{
    std::string novoEndereco;
    std::cout << "Novo endereço: ";
    std::cin.ignore();
    std::getline(std::cin, novoEndereco);
    this->endereco = novoEndereco;
    std::cout << "Endereço atualizado com sucesso!" << std::endl;
}

// Produto functions
void Usuario::visualizarProdutos()
{
    std::ifstream file("produtos.txt");
    std::string line;

    std::cout << "\n===== PRODUTOS DISPONÍVEIS =====" << std::endl;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string id, nome, marca, valor, avaliacao, quantidade, descricao, endereco;

        std::getline(ss, id, '|');
        std::getline(ss, nome, '|');
        std::getline(ss, marca, '|');
        std::getline(ss, valor, '|');
        std::getline(ss, avaliacao, '|');
        std::getline(ss, quantidade, '|');
        std::getline(ss, descricao, '|');
        std::getline(ss, endereco, '|');

        std::cout << "ID: " << id << " | Nome: " << nome << " | Marca: " << marca
                  << " | Valor: R$" << valor << " | Quantidade: " << quantidade << std::endl;
    }
    file.close();
}

void Usuario::cadastrarProduto()
{
    std::string nome, marca, descricao;
    double valor, avaliacao;
    int quantidade;

    std::cout << "\n===== CADASTRAR PRODUTO =====" << std::endl;
    std::cout << "Nome: ";
    std::cin.ignore();
    std::getline(std::cin, nome);
    std::cout << "Marca: ";
    std::getline(std::cin, marca);
    std::cout << "Valor: R$";
    std::cin >> valor;
    std::cout << "Quantidade: ";
    std::cin >> quantidade;
    std::cout << "Descrição: ";
    std::cin.ignore();
    std::getline(std::cin, descricao);
    avaliacao = 0.0; // Initial rating

    // Generate simple ID
    int id = rand() % 10000 + 1;

    // Save to file
    std::ofstream file("produtos.txt", std::ios::app);
    file << id << "|" << nome << "|" << marca << "|" << valor << "|"
         << avaliacao << "|" << quantidade << "|" << descricao << "|" << this->endereco << std::endl;
    file.close();

    std::cout << "Produto cadastrado com sucesso! ID: " << id << std::endl;
}

void Usuario::adicionarAoCarrinho()
{
    int produtoId, quantidade;
    std::cout << "ID do produto: ";
    std::cin >> produtoId;
    std::cout << "Quantidade: ";
    std::cin >> quantidade;

    // Find product in file
    std::ifstream file("produtos.txt");
    std::string line;
    bool encontrado = false;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string id, nome, marca, valor, avaliacao, qtd, descricao, endereco;

        std::getline(ss, id, '|');
        std::getline(ss, nome, '|');
        std::getline(ss, marca, '|');
        std::getline(ss, valor, '|');
        std::getline(ss, avaliacao, '|');
        std::getline(ss, qtd, '|');
        std::getline(ss, descricao, '|');
        std::getline(ss, endereco, '|');

        if (std::stoi(id) == produtoId)
        {
            Produto produto(std::stoi(id), nome, marca, std::stod(valor),
                            std::stod(avaliacao), std::stoi(qtd), descricao, endereco);
            carrinho.inserir(produto, quantidade);
            std::cout << "Produto adicionado ao carrinho!" << std::endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado)
    {
        std::cout << "Produto não encontrado!" << std::endl;
    }
    file.close();
}

void Usuario::removerDoCarrinho()
{
    int produtoId;
    std::cout << "ID do produto para remover: ";
    std::cin >> produtoId;
    carrinho.excluir(produtoId);
    std::cout << "Produto removido do carrinho!" << std::endl;
}

void Usuario::visualizarCarrinho()
{
    std::cout << "\n===== SEU CARRINHO =====" << std::endl;
    std::cout << carrinho.exibir();
    std::cout << "========================" << std::endl;
}

void Usuario::finalizarCompra()
{
    if (carrinho.carrinhoProdutos.empty())
    {
        std::cout << "Carrinho vazio!" << std::endl;
        return;
    }

    if (confirmarAcao())
    {
        // Create pedido
        Pedido pedido(this->id_usuario, 1, carrinho); // Assuming seller ID 1 for simplicity

        // Save pedido
        pedido.SalvarPedidos("pedidos.csv");

        // Clear cart
        carrinho.excluir();

        std::cout << "Compra finalizada com sucesso!" << std::endl;
    }
}

void Usuario::visualizarPedidos()
{
    try
    {
        auto pedidos = Pedido::lerTodosPedidos("pedidos.csv");

        std::cout << "\n===== MEUS PEDIDOS =====" << std::endl;
        for (const auto &pedido : pedidos)
        {
            if (pedido.getIdComprador() == this->id_usuario)
            {
                std::cout << "Pedido ID: " << pedido.getId()
                          << " | Status: " << pedido.getStatus() << std::endl;
            }
        }
        std::cout << "========================" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Nenhum pedido encontrado." << std::endl;
    }
}

bool Usuario::confirmarAcao()
{
    char resposta;
    std::cout << "Confirma a ação? (s/n): ";
    std::cin >> resposta;
    return (resposta == 's' || resposta == 'S');
}

std::string Usuario::getEmail()
{
    return this->email;
}

std::string Usuario::getNome()
{
    return this->nome;
}

// Placeholder implementations for missing methods
void Usuario::detalhesProduto()
{
    int produtoId;
    std::cout << "ID do produto: ";
    std::cin >> produtoId;

    std::ifstream file("produtos.txt");
    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string id, nome, marca, valor, avaliacao, quantidade, descricao, endereco;

        std::getline(ss, id, '|');
        std::getline(ss, nome, '|');
        std::getline(ss, marca, '|');
        std::getline(ss, valor, '|');
        std::getline(ss, avaliacao, '|');
        std::getline(ss, quantidade, '|');
        std::getline(ss, descricao, '|');
        std::getline(ss, endereco, '|');

        if (std::stoi(id) == produtoId)
        {
            std::cout << "\n===== DETALHES DO PRODUTO =====" << std::endl;
            std::cout << "ID: " << id << std::endl;
            std::cout << "Nome: " << nome << std::endl;
            std::cout << "Marca: " << marca << std::endl;
            std::cout << "Valor: R$" << valor << std::endl;
            std::cout << "Avaliação: " << avaliacao << std::endl;
            std::cout << "Quantidade disponível: " << quantidade << std::endl;
            std::cout << "Descrição: " << descricao << std::endl;
            std::cout << "Localização: " << endereco << std::endl;
            std::cout << "===============================" << std::endl;
            file.close();
            return;
        }
    }

    std::cout << "Produto não encontrado!" << std::endl;
    file.close();
}

void Usuario::aplicarFiltroNome()
{
    std::string nomeBusca;
    std::cout << "Nome do produto: ";
    std::cin.ignore();
    std::getline(std::cin, nomeBusca);

    std::ifstream file("produtos.txt");
    std::string line;
    bool encontrou = false;

    std::cout << "\n===== PRODUTOS ENCONTRADOS =====" << std::endl;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string id, nome, marca, valor, avaliacao, quantidade, descricao, endereco;

        std::getline(ss, id, '|');
        std::getline(ss, nome, '|');
        std::getline(ss, marca, '|');
        std::getline(ss, valor, '|');
        std::getline(ss, avaliacao, '|');
        std::getline(ss, quantidade, '|');
        std::getline(ss, descricao, '|');
        std::getline(ss, endereco, '|');

        if (nome.find(nomeBusca) != std::string::npos)
        {
            std::cout << "ID: " << id << " | Nome: " << nome << " | Valor: R$" << valor << std::endl;
            encontrou = true;
        }
    }

    if (!encontrou)
    {
        std::cout << "Nenhum produto encontrado com esse nome." << std::endl;
    }
    file.close();
}

void Usuario::aplicarFiltroCategoria()
{
    std::string categoria;
    std::cout << "Categoria/Marca: ";
    std::cin.ignore();
    std::getline(std::cin, categoria);

    std::ifstream file("produtos.txt");
    std::string line;
    bool encontrou = false;

    std::cout << "\n===== PRODUTOS ENCONTRADOS =====" << std::endl;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string id, nome, marca, valor, avaliacao, quantidade, descricao, endereco;

        std::getline(ss, id, '|');
        std::getline(ss, nome, '|');
        std::getline(ss, marca, '|');
        std::getline(ss, valor, '|');
        std::getline(ss, avaliacao, '|');
        std::getline(ss, quantidade, '|');
        std::getline(ss, descricao, '|');
        std::getline(ss, endereco, '|');

        if (marca.find(categoria) != std::string::npos)
        {
            std::cout << "ID: " << id << " | Nome: " << nome << " | Marca: " << marca << " | Valor: R$" << valor << std::endl;
            encontrou = true;
        }
    }

    if (!encontrou)
    {
        std::cout << "Nenhum produto encontrado nessa categoria." << std::endl;
    }
    file.close();
}

void Usuario::aplicarFiltroPreco()
{
    double precoMax;
    std::cout << "Preço máximo: R$";
    std::cin >> precoMax;

    std::ifstream file("produtos.txt");
    std::string line;
    bool encontrou = false;

    std::cout << "\n===== PRODUTOS ENCONTRADOS =====" << std::endl;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string id, nome, marca, valor, avaliacao, quantidade, descricao, endereco;

        std::getline(ss, id, '|');
        std::getline(ss, nome, '|');
        std::getline(ss, marca, '|');
        std::getline(ss, valor, '|');
        std::getline(ss, avaliacao, '|');
        std::getline(ss, quantidade, '|');
        std::getline(ss, descricao, '|');
        std::getline(ss, endereco, '|');

        if (std::stod(valor) <= precoMax)
        {
            std::cout << "ID: " << id << " | Nome: " << nome << " | Valor: R$" << valor << std::endl;
            encontrou = true;
        }
    }

    if (!encontrou)
    {
        std::cout << "Nenhum produto encontrado nessa faixa de preço." << std::endl;
    }
    file.close();
}

void Usuario::editarProduto()
{
    std::cout << "Funcionalidade de editar produto não implementada." << std::endl;
}

void Usuario::excluirProduto()
{
    std::cout << "Funcionalidade de excluir produto não implementada." << std::endl;
}

void Usuario::cancelarPedido()
{
    std::cout << "Funcionalidade de cancelar pedido não implementada." << std::endl;
}
