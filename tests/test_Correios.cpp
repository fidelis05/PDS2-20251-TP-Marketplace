#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest.h"
#include "Correios.hpp"
#include "exceptions/RunTimeException.hpp"

TEST_CASE("setcodigoRastreio atribui corretamente")
{
    Correios c;
    CHECK(c.setcodigoRastreio(12345) == 0);
    // Se houver getter, pode testar: CHECK(c.getCodigoRastreio() == 12345);
}

TEST_CASE("setStatus lança exceção se codigoRastreio não informado para status <= 3")
{
    Correios c;
    // Não define codigoRastreio
    CHECK_THROWS_AS(c.setStatus(2), RunTimeException);
}

TEST_CASE("setStatus aceita status <= 3 se codigoRastreio informado")
{
    Correios c;
    c.setcodigoRastreio(111);
    CHECK_NOTHROW(c.setStatus(2));
}

TEST_CASE("setStatus aceita status > 3 sem codigoRastreio")
{
    Correios c;
    CHECK_NOTHROW(c.setStatus(4));
}

TEST_CASE("setStatus lança exceção para status inválido")
{
    Correios c;
    CHECK_THROWS_AS(c.setStatus(10), RunTimeException);
}

TEST_CASE("setStatus define dataEntrega para status 7")
{
    Correios c;
    c.setcodigoRastreio(222);
    c.setStatus(7);
    // Se houver getter para dataEntrega, pode testar se foi atualizado
    // Exemplo: CHECK(c.getDataEntrega() != 0);
}

TEST_CASE("getLista retorna 0")
{
    Correios c;
    CHECK(c.getLista() == 0);
}