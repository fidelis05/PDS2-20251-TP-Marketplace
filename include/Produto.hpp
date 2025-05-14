#ifndef PRODUTO_HPP
#define PRODUTO_HPP
#include <iostream>
#include <string>

class Produto
{
public:
    int IdProduto;
    std ::string NomeProduto;
    std ::string MarcaProduto;
    double ValorProduto;
    double AvaliacaoProduto;
    int QuantidadeProduto;
    std ::string DescricaoProduto;
    std ::string EnderecoProduto;

    Produto(int id, const std::string &nome, const std::string &marca, double valor,
            double avaliacao, int quantidade, const std::string &descricao, const std::string &endereco);
}

#endif