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

    std::ifstream countFile("data/usuarios.txt");
    std::string line;
    unsigned int nextId = 1;
    while (std::getline(countFile, line))
    {
        nextId++;
    }
    countFile.close();

    this->id_usuario = nextId;

    // Save to file
    std::ofstream file("data/usuarios.txt", std::ios::app);
    file << email << "|" << senha << "|" << nome << "|" << telefone << "|" << cpf_cnpj << "|" << endereco << std::endl;
    file.close();
}

bool Usuario::login(std::string email, std::string senha)
{
    std::ifstream file("data/usuarios.txt");
    std::string line;
    unsigned int currentId = 1;

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
            this->id_usuario = currentId;
            this->email = file_email;
            this->senha = file_senha;
            this->nome = file_nome;
            this->telefone = file_telefone;
            this->cpf_cnpj = file_cpf;
            this->endereco = file_endereco;
            file.close();
            return true;
        }
        currentId++;
    }
    file.close();
    return false;
}

std::vector<Produto> Usuario::obterProdutos()
{
    std::vector<Produto> produtos;
    std::ifstream file("data/produtos.txt");
    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> tokens;

        while (std::getline(ss, item, '|'))
        {
            tokens.push_back(item);
        }

        if (tokens.size() >= 8)
        {
            unsigned int id = std::stoi(tokens[0]);
            std::string nome = tokens[1];
            std::string marca = tokens[2];
            double valor = std::stod(tokens[3]);
            double avaliacao = std::stod(tokens[4]);
            unsigned int quantidade = std::stoi(tokens[5]);
            std::string descricao = tokens[6];
            std::string endereco = tokens[7];

            produtos.emplace_back(id, nome, marca, valor, avaliacao, quantidade, descricao, endereco);
        }
    }
    file.close();
    return produtos;
}

void Usuario::adicionarProdutoAoCarrinho(unsigned int idProduto)
{
    // Find the product by ID and add to cart
    auto produtos = obterProdutos();
    for (const auto &produto : produtos)
    {
        if (produto.id == idProduto)
        {
            carrinho.inserir(produto, 1);
            return;
        }
    }
}

void Usuario::removerProdutoDoCarrinho(unsigned int idProduto)
{
    // Remove product from cart
    carrinho.excluir(idProduto);
}

std::vector<std::shared_ptr<Pedido>> Usuario::obterPedidos()
{
    // Load orders from file for this user
    try
    {
        auto todosPedidos = Pedido::lerTodosPedidos("data/pedidos.txt");
        meusPedidos.clear();

        for (const auto &pedido : todosPedidos)
        {
            if (pedido.getIdComprador() == this->id_usuario)
            {
                meusPedidos.push_back(std::make_shared<Pedido>(pedido));
            }
        }
    }
    catch (const std::exception &e)
    {
        // Return empty list if no orders found or error
    }
    return meusPedidos;
}

bool Usuario::finalizarCompraBusiness()
{
    // Create a new order from the cart
    if (carrinho.carrinhoProdutos.empty())
    {
        return false;
    }

    try
    {
        // Create a new order - assume vendedor ID is 1 for simplicity
        Pedido novoPedido(this->id_usuario, 1, carrinho);

        // Save the order to file
        Pedido::SalvarPedidosCSV("data/pedidos.txt", novoPedido);

        // Add to user's orders
        meusPedidos.push_back(std::make_shared<Pedido>(novoPedido));

        return true;
    }
    catch (const std::exception &e)
    {
        return false;
    }
}

void Usuario::atualizarPerfil(const std::string &novoNome, const std::string &novoEmail,
                              const std::string &novoTelefone, const std::string &novoEndereco)
{
    this->nome = novoNome;
    this->email = novoEmail;
    this->telefone = novoTelefone;
    this->endereco = novoEndereco;

    // Update in file (simplified implementation)
    std::cout << "Perfil atualizado com sucesso!" << std::endl;
}

void Usuario::atualizarSenha(const std::string &novaSenha)
{
    this->senha = novaSenha;
    std::cout << "Senha atualizada com sucesso!" << std::endl;
}

bool Usuario::adicionarNovoProduto(const Produto &produto)
{
    // Add new product to file
    std::ofstream file("data/produtos.txt", std::ios::app);
    file << produto.id << "|" << produto.nome << "|" << produto.marca << "|"
         << produto.valor << "|" << produto.avaliacao << "|" << produto.quantidade
         << "|" << produto.descricao << "|" << produto.endereco << std::endl;
    file.close();
    return true;
}
