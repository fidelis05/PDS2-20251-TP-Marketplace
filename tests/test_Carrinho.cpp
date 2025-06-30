#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest.h"
#include "Carrinho.hpp"
#include "Produto.hpp"

TEST_CASE("Inserir produto no carrinho")
{
    Carrinho c;
    Produto p(1, "Celular", "MarcaX", 1000.0, 4.5, 10, "Smartphone", "Rua A");
    c.inserir(p, 2);
    CHECK(c.carrinhoProdutos.size() == 1);
    CHECK(c.carrinhoProdutos[p] == 2);
}

TEST_CASE("Exibir produtos do carrinho")
{
    Carrinho c;
    Produto p(2, "Notebook", "MarcaY", 3000.0, 4.8, 5, "Notebook gamer", "Rua B");
    c.inserir(p, 1);
    std::string info = c.exibir();
    CHECK(info.find("Notebook") != std::string::npos);
    CHECK(info.find("1") != std::string::npos);
}

TEST_CASE("Excluir produto específico do carrinho")
{
    Carrinho c;
    Produto p(3, "Mouse", "MarcaZ", 50.0, 4.0, 20, "Mouse óptico", "Rua C");
    c.inserir(p, 3);
    c.excluir(3);
    CHECK(c.carrinhoProdutos.empty());
}

TEST_CASE("Limpar todo o carrinho")
{
    Carrinho c;
    Produto p1(4, "Teclado", "MarcaW", 100.0, 4.2, 2, "Teclado mecânico", "Rua D");
    Produto p2(5, "Monitor", "MarcaV", 800.0, 4.7, 4, "Monitor LED", "Rua E");
    c.inserir(p1, 1);
    c.inserir(p2, 2);
    c.excluir();
    CHECK(c.carrinhoProdutos.empty());
}