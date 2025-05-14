#include "Produto.hpp"
#include <iostream>
#include <string>

Produto ::Produto(int id, const std::string &nome, const std::string &marca, double valor,
                  double avaliacao, int quantidade, const std::string &descricao, const std::string &endereco)
    : IdProduto(id), NomeProduto(nome), MarcaProduto(marca), ValorProduto(valor),
      AvaliacaoProduto(avaliacao), QuantidadeProduto(quantidade),
      DescricaoProduto(descricao), EnderecoProduto(endereco) {}