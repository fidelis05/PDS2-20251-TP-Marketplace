#include "Produto.hpp"
#include <iostream>
#include <string>

Produto::Produto(int id, const std::string &nome, const std::string &marca, double valor,
                double avaliacao, int quantidade, const std::string &descricao, const std::string &endereco)
    : id(id), nome(nome), marca(marca), valor(valor),
      avaliacao(avaliacao), quantidade(quantidade),
      descricao(descricao), endereco(endereco) {}