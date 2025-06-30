#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest.h"
#include "Produto.hpp"

TEST_CASE("Construtor de Produto inicializa corretamente")
{
    Produto p(1, "Celular", "MarcaX", 1500.0, 4.5, 10, "Smartphone novo", "Rua A, 123");
    CHECK(p.id == 1);
    CHECK(p.nome == "Celular");
    CHECK(p.marca == "MarcaX");
    CHECK(p.valor == doctest::Approx(1500.0));
    CHECK(p.avaliacao == doctest::Approx(4.5));
    CHECK(p.quantidade == 10);
    CHECK(p.descricao == "Smartphone novo");
    CHECK(p.endereco == "Rua A, 123");
}

TEST_CASE("exibirInformacoes retorna string com dados do produto")
{
    Produto p(2, "Notebook", "MarcaY", 3500.0, 4.8, 5, "Notebook gamer", "Rua B, 456");
    std::string info = p.exibirInformacoes();
    CHECK(info.find("Notebook") != std::string::npos);
    CHECK(info.find("MarcaY") != std::string::npos);
    CHECK(info.find("3500") != std::string::npos);
}

TEST_CASE("reduzirEstoque reduz quantidade corretamente")
{
    Produto p(3, "Mouse", "MarcaZ", 50.0, 4.0, 20, "Mouse óptico", "Rua C, 789");
    p.reduzirEstoque(5);
    CHECK(p.quantidade == 15);
}

TEST_CASE("reduzirEstoque não permite reduzir além do estoque")
{
    Produto p(4, "Teclado", "MarcaW", 100.0, 4.2, 2, "Teclado mecânico", "Rua D, 101");
    std::string msg = p.reduzirEstoque(5);
    CHECK(msg.find("insuficiente") != std::string::npos);
    CHECK(p.quantidade == 2);
}

TEST_CASE("Operador < compara produtos pelo id")
{
    Produto p1(1, "A", "M", 1, 1, 1, "D", "E");
    Produto p2(2, "B", "N", 2, 2, 2, "F", "G");
    CHECK(p1 < p2);
    CHECK_FALSE(p2 < p1);
}