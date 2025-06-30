#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest.h"
#include "Pedido.hpp"
#include "Carrinho.hpp"
#include "exceptions/RunTimeException.hpp"

TEST_CASE("Construtor de Pedido não lança exceção")
{
    Carrinho c;
    CHECK_NOTHROW(Pedido(1, 2, c));
}

TEST_CASE("pagamentoConcluido não lança exceção se pagamento for true")
{
    Carrinho c;
    Pedido p(1, 2, c);

    CHECK_NOTHROW(p.pagamentoConcluido());
}

TEST_CASE("cancelarPedido não lança exceção para status inicial")
{
    Carrinho c;
    Pedido p(1, 2, c);
    CHECK_NOTHROW(p.cancelarPedido());
}
