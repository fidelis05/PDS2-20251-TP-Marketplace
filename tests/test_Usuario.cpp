#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest.h"
#include "Usuario.hpp"

TEST_CASE("Construtor padrão de Usuario")
{
    Usuario u;
    CHECK(u.getNome() == "");
    CHECK(u.getEmail() == "");
}

TEST_CASE("Construtor parametrizado de Usuario")
{
    Usuario u("Joao", "joao@email.com", "senha123");
    CHECK(u.getNome() == "Joao");
    CHECK(u.getEmail() == "joao@email.com");
}

TEST_CASE("Login bem-sucedido")
{
    Usuario u("Maria", "maria@email.com", "senha456");
    CHECK(u.login("maria@email.com", "senha456") == true);
}

TEST_CASE("Login falha com senha errada")
{
    Usuario u("Maria", "maria@email.com", "senha456");
    CHECK(u.login("maria@email.com", "errada") == false);
}