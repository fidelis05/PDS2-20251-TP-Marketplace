#include "doctest.h"
#include "Usuario.hpp"
#include <fstream>

TEST_SUITE("Usuario Advanced Tests")
{
  TEST_CASE("Usuario persistence and file operations")
  {
    Usuario user;

    SUBCASE("User registration creates file entry")
    {
      // Count lines before registration
      std::ifstream file("data/usuarios.txt");
      int linesBefore = 0;
      std::string line;
      while (std::getline(file, line))
        linesBefore++;
      file.close();

      user.cadastrar("File Test User", "filetest@email.com", "filepass", "11888888888", "987.654.321-00", "File Test Address");

      // Count lines after registration
      file.open("data/usuarios.txt");
      int linesAfter = 0;
      while (std::getline(file, line))
        linesAfter++;
      file.close();

      CHECK(linesAfter > linesBefore);
    }

    SUBCASE("Login with existing user")
    {
      // Ensure user exists first
      user.cadastrar("Login Test", "logintest@email.com", "loginpass", "11777777777", "111.222.333-44", "Login Address");

      Usuario newUser;
      CHECK(newUser.login("logintest@email.com", "loginpass") == true);
      CHECK(newUser.getNome() == "Login Test");
      CHECK(newUser.getEmail() == "logintest@email.com");
    }
  }

  TEST_CASE("Usuario shopping cart integration")
  {
    Usuario user;
    user.cadastrar("Cart User", "cart@email.com", "cartpass", "11666666666", "555.666.777-88", "Cart Address");
    user.login("cart@email.com", "cartpass");

    SUBCASE("Add product to cart")
    {
      Produto produto(500, "Cart Product", "Cart Brand", 25.50, 4.2, 8, "Product for cart testing", "Cart Location");
      user.carrinho.inserir(produto, 3);

      CHECK(user.carrinho.carrinhoProdutos.size() == 1);
      CHECK(user.carrinho.carrinhoProdutos[produto] == 3);
    }

    SUBCASE("Multiple products in cart")
    {
      Produto produto1(501, "Product 1", "Brand 1", 10.0, 4.0, 5, "Description 1", "Location 1");
      Produto produto2(502, "Product 2", "Brand 2", 20.0, 4.5, 3, "Description 2", "Location 2");

      user.carrinho.inserir(produto1, 1);
      user.carrinho.inserir(produto2, 2);

      CHECK(user.carrinho.carrinhoProdutos.size() == 2);
    }
  }

  TEST_CASE("Usuario input validation")
  {
    Usuario user;

    SUBCASE("Empty credentials should not crash")
    {
      CHECK_NOTHROW(user.login("", ""));
      CHECK(user.login("", "") == false);
    }

    SUBCASE("Non-existent user login")
    {
      CHECK(user.login("nonexistent@email.com", "anypass") == false);
    }
  }
}
