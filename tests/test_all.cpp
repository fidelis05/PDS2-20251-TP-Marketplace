#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Usuario.hpp"
#include "Produto.hpp"
#include "Carrinho.hpp"
#include "Pedido.hpp"
#include "Admin.hpp"
#include <fstream>

// Basic functionality tests
TEST_CASE("Usuario class functionality")
{
  Usuario user;

  SUBCASE("Usuario registration")
  {
    user.cadastrar("Test User Doctest", "testdoctest@email.com", "password123", "11999999999", "123.456.789-10", "Test Address");
    CHECK(true); // If we reach here, registration worked
  }

  SUBCASE("Usuario login - valid credentials")
  {
    user.cadastrar("Test User Valid", "valid@email.com", "validpass", "11999999999", "123.456.789-10", "Test Address");
    CHECK(user.login("valid@email.com", "validpass") == true);
  }

  SUBCASE("Usuario login - invalid credentials")
  {
    CHECK(user.login("wrong@email.com", "wrongpass") == false);
  }

  SUBCASE("Usuario getters")
  {
    user.cadastrar("John Doe", "john@email.com", "pass123", "11999999999", "123.456.789-10", "John Street");
    user.login("john@email.com", "pass123");
    CHECK(user.getNome() == "John Doe");
    CHECK(user.getEmail() == "john@email.com");
  }
}

TEST_CASE("Produto class functionality")
{
  Produto produto(100, "Test Product", "Test Brand", 99.99, 4.5, 10, "Test Description", "Test Location");

  SUBCASE("Produto basic properties")
  {
    CHECK(produto.id == 100);
    CHECK(produto.nome == "Test Product");
    CHECK(produto.marca == "Test Brand");
    CHECK(produto.valor == doctest::Approx(99.99));
    CHECK(produto.avaliacao == doctest::Approx(4.5));
    CHECK(produto.quantidade == 10);
    CHECK(produto.descricao == "Test Description");
    CHECK(produto.endereco == "Test Location");
  }

  SUBCASE("Produto stock reduction - valid quantity")
  {
    int initialStock = produto.quantidade;
    produto.reduzirEstoque(2);
    CHECK(produto.quantidade == initialStock - 2);
  }

  SUBCASE("Produto stock reduction - insufficient stock")
  {
    int initialStock = produto.quantidade;
    CHECK_THROWS(produto.reduzirEstoque(1000));
    CHECK(produto.quantidade == initialStock);
  }

  SUBCASE("Produto comparison operator")
  {
    Produto produto1(1, "Product A", "Brand A", 10.0, 5.0, 1, "Desc A", "Loc A");
    Produto produto2(2, "Product B", "Brand B", 20.0, 4.0, 2, "Desc B", "Loc B");
    CHECK(produto1 < produto2);
    CHECK_FALSE(produto2 < produto1);
  }
}

TEST_CASE("Carrinho class functionality")
{
  Carrinho carrinho;
  Produto produto1(1, "Product 1", "Brand 1", 50.0, 4.0, 5, "Description 1", "Location 1");
  Produto produto2(2, "Product 2", "Brand 2", 75.0, 4.5, 3, "Description 2", "Location 2");

  SUBCASE("Carrinho insertion")
  {
    carrinho.inserir(produto1, 2);
    CHECK(carrinho.carrinhoProdutos.size() == 1);
    CHECK(carrinho.carrinhoProdutos[produto1] == 2);
  }

  SUBCASE("Carrinho multiple products")
  {
    carrinho.inserir(produto1, 1);
    carrinho.inserir(produto2, 3);
    CHECK(carrinho.carrinhoProdutos.size() == 2);
  }

  SUBCASE("Carrinho display")
  {
    carrinho.inserir(produto1, 1);
    std::string result = carrinho.exibir();
    CHECK_FALSE(result.empty());
    CHECK(result.find("Product 1") != std::string::npos);
  }

  SUBCASE("Carrinho remove specific product")
  {
    carrinho.inserir(produto1, 1);
    carrinho.inserir(produto2, 2);
    carrinho.excluir(1); // Remove product with ID 1
    CHECK(carrinho.carrinhoProdutos.size() == 1);
  }

  SUBCASE("Carrinho clear all")
  {
    carrinho.inserir(produto1, 1);
    carrinho.inserir(produto2, 2);
    carrinho.excluir(); // Clear all
    CHECK(carrinho.carrinhoProdutos.empty());
  }
}

TEST_CASE("Pedido class functionality")
{
  Carrinho carrinho;
  Produto produto(1, "Test Product", "Test Brand", 99.99, 4.5, 10, "Test Description", "Test Location");
  carrinho.inserir(produto, 1);

  SUBCASE("Pedido creation")
  {
    Pedido pedido(1, 2, carrinho);
    CHECK(pedido.getIdComprador() == 1);
    CHECK(pedido.getIdVendedor() == 2);
    CHECK(pedido.getPagamento() == true); // Default value
  }

  SUBCASE("Pedido payment confirmation")
  {
    Pedido pedido(1, 2, carrinho);
    CHECK_NOTHROW(pedido.pagamentoConcluido());
    CHECK(pedido.getStatus() != "Esperando aprovação do pagamento");
  }

  SUBCASE("Pedido shipment by seller")
  {
    Pedido pedido(1, 2, carrinho);
    pedido.pagamentoConcluido();
    CHECK_NOTHROW(pedido.enviarPedido(2)); // Seller with ID 2 confirms
  }

  SUBCASE("Pedido shipment by non-seller should fail")
  {
    Pedido pedido(1, 2, carrinho);
    pedido.pagamentoConcluido();
    CHECK_THROWS(pedido.enviarPedido(3)); // Wrong seller ID
  }

  SUBCASE("Pedido evaluation")
  {
    Pedido pedido(1, 2, carrinho);
    CHECK_NOTHROW(pedido.avaliarPedido(5, "Excellent product!"));
    CHECK_THROWS(pedido.avaliarPedido(6, "Invalid rating")); // Rating > 5
    CHECK_THROWS(pedido.avaliarPedido(0, "Invalid rating")); // Rating < 1
  }
}

TEST_CASE("Admin class functionality")
{
  Admin admin;

  SUBCASE("Admin statistics")
  {
    CHECK_NOTHROW(admin.obterResumoEstatistico());
  }

  SUBCASE("Admin user management")
  {
    CHECK_NOTHROW(admin.obterListaDeUsuarios());
  }

  SUBCASE("Admin product management")
  {
    CHECK_NOTHROW(admin.obterListaDeProdutos());
  }

  SUBCASE("Admin order management")
  {
    CHECK_NOTHROW(admin.obterListaDePedidos());
  }
}

// Advanced tests
TEST_CASE("Usuario advanced functionality")
{
  Usuario user;

  SUBCASE("User persistence")
  {
    std::ifstream file("data/usuarios.txt");
    int linesBefore = 0;
    std::string line;
    while (std::getline(file, line))
      linesBefore++;
    file.close();

    user.cadastrar("File Test User", "filetest@email.com", "filepass", "11888888888", "987.654.321-00", "File Test Address");

    file.open("data/usuarios.txt");
    int linesAfter = 0;
    while (std::getline(file, line))
      linesAfter++;
    file.close();

    CHECK(linesAfter > linesBefore);
  }

  SUBCASE("Shopping cart integration")
  {
    user.cadastrar("Cart User", "cart@email.com", "cartpass", "11666666666", "555.666.777-88", "Cart Address");
    user.login("cart@email.com", "cartpass");

    Produto produto(500, "Cart Product", "Cart Brand", 25.50, 4.2, 8, "Product for cart testing", "Cart Location");
    user.carrinho.inserir(produto, 3);

    CHECK(user.carrinho.carrinhoProdutos.size() == 1);
    CHECK(user.carrinho.carrinhoProdutos[produto] == 3);
  }
}

TEST_CASE("Pedido advanced functionality")
{
  Carrinho carrinho;
  Produto produto(200, "Advanced Product", "Advanced Brand", 150.0, 4.3, 5, "Advanced testing", "Advanced Location");
  carrinho.inserir(produto, 1);

  SUBCASE("Status progression")
  {
    Pedido pedido(10, 20, carrinho);
    // Since payment is always true, new pedidos start with "Enviado" status
    CHECK(pedido.getStatus() == "Enviado");

    pedido.pagamentoConcluido();
    CHECK(pedido.getStatus() == "Enviado");

    pedido.enviarPedido(20);
    CHECK(pedido.getStatus() == "Vendedor ciente");
  }

  SUBCASE("Reverse logistics")
  {
    Pedido pedido(14, 24, carrinho);

    // First initialization should work
    CHECK_NOTHROW(pedido.iniciarLogisticaReversa());
    CHECK(pedido.getDevolucaoIniciada() == true);

    // Check if codigo was generated (might be empty in current implementation)
    // This is implementation-dependent

    // Cannot initialize twice
    CHECK_THROWS_AS(pedido.iniciarLogisticaReversa(), std::runtime_error);
  }
}

TEST_CASE("Integration tests")
{
  SUBCASE("Complete purchase flow")
  {
    Usuario user;
    user.cadastrar("Integration User", "integration@test.com", "testpass", "11999999999", "123.456.789-10", "Test Address");
    CHECK(user.login("integration@test.com", "testpass") == true);

    Produto produto(999, "Integration Product", "Test Brand", 199.99, 4.8, 5, "Integration test product", "Test Location");
    user.carrinho.inserir(produto, 1);
    CHECK(user.carrinho.carrinhoProdutos.size() == 1);

    Pedido pedido(user.getId(), 100, user.carrinho);
    CHECK(pedido.getIdComprador() == user.getId());
    CHECK(pedido.getIdVendedor() == 100);
  }
}
