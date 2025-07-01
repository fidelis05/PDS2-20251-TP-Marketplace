/**
 * @file test_comprehensive.cpp
 * @brief Testes abrangentes para todas as classes do sistema Marketplace
 * @author Sistema de Testes
 * @version 1.0
 * @date 2025
 * 
 * Este arquivo contém testes unitários abrangentes para verificar o funcionamento
 * correto de todas as principais classes do sistema de marketplace.
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Usuario.hpp"
#include "Produto.hpp"
#include "Carrinho.hpp"
#include "Pedido.hpp"
#include "Admin.hpp"

/**
 * @brief Testa a funcionalidade da classe Usuario
 * 
 * Verifica operações básicas como cadastro, login e acesso a propriedades
 * do usuário.
 */
TEST_CASE("Usuario class functionality")
{
  Usuario user;

  SUBCASE("Usuario registration")
  {
    /// @brief Testa o cadastro de um novo usuário
    /// @details Verifica se o cadastro é realizado sem lançar exceções
    user.cadastrar("Test User Doctest", "testdoctest@email.com", "password123", "11999999999", "123.456.789-10", "Test Address");
    // Registration should complete without throwing exceptions
    CHECK(true); // If we reach here, registration worked
  }

  SUBCASE("Usuario login - valid credentials")
  {
    /// @brief Testa login com credenciais válidas
    /// @details Verifica se o login retorna true para credenciais corretas
    user.cadastrar("Test User Valid", "valid@email.com", "validpass", "11999999999", "123.456.789-10", "Test Address");
    CHECK(user.login("valid@email.com", "validpass") == true);
  }

  SUBCASE("Usuario login - invalid credentials")
  {
    /// @brief Testa login com credenciais inválidas
    /// @details Verifica se o login retorna false para credenciais incorretas
    CHECK(user.login("wrong@email.com", "wrongpass") == false);
  }

  SUBCASE("Usuario getters")
  {
    /// @brief Testa os métodos getter da classe Usuario
    /// @details Verifica se os dados retornados correspondem aos cadastrados
    user.cadastrar("John Doe", "john@email.com", "pass123", "11999999999", "123.456.789-10", "John Street");
    user.login("john@email.com", "pass123");
    CHECK(user.getNome() == "John Doe");
    CHECK(user.getEmail() == "john@email.com");
  }
}

/**
 * @brief Testa a funcionalidade da classe Produto
 * 
 * Verifica propriedades básicas, redução de estoque e operadores de comparação.
 */
TEST_CASE("Produto class functionality")
{
  Produto produto(100, "Test Product", "Test Brand", 99.99, 4.5, 10, "Test Description", "Test Location");

  SUBCASE("Produto basic properties")
  {
    /// @brief Testa as propriedades básicas do produto
    /// @details Verifica se todos os valores foram atribuídos corretamente
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
    /// @brief Testa redução de estoque com quantidade válida
    /// @details Verifica se o estoque é reduzido corretamente
    int initialStock = produto.quantidade;
    produto.reduzirEstoque(2);
    CHECK(produto.quantidade == initialStock - 2);
  }

  SUBCASE("Produto stock reduction - insufficient stock")
  {
    /// @brief Testa redução de estoque com quantidade insuficiente
    /// @details Verifica se uma exceção é lançada para estoque insuficiente
    int initialStock = produto.quantidade;
    CHECK_THROWS(produto.reduzirEstoque(1000)); // Should throw exception for more than available
    CHECK(produto.quantidade == initialStock);  // Should remain unchanged after exception
  }

  SUBCASE("Produto comparison operator")
  {
    /// @brief Testa o operador de comparação entre produtos
    /// @details Verifica se a comparação é baseada no ID do produto
    Produto produto1(1, "Product A", "Brand A", 10.0, 5.0, 1, "Desc A", "Loc A");
    Produto produto2(2, "Product B", "Brand B", 20.0, 4.0, 2, "Desc B", "Loc B");
    CHECK(produto1 < produto2);
    CHECK_FALSE(produto2 < produto1);
  }
}

/**
 * @brief Testa a funcionalidade da classe Carrinho
 * 
 * Verifica operações de inserção, remoção e exibição de produtos no carrinho.
 */
TEST_CASE("Carrinho class functionality")
{
  Carrinho carrinho;
  Produto produto1(1, "Product 1", "Brand 1", 50.0, 4.0, 5, "Description 1", "Location 1");
  Produto produto2(2, "Product 2", "Brand 2", 75.0, 4.5, 3, "Description 2", "Location 2");

  SUBCASE("Carrinho insertion")
  {
    /// @brief Testa inserção de produto no carrinho
    /// @details Verifica se o produto é adicionado com a quantidade correta
    carrinho.inserir(produto1, 2);
    CHECK(carrinho.carrinhoProdutos.size() == 1);
    CHECK(carrinho.carrinhoProdutos[produto1] == 2);
  }

  SUBCASE("Carrinho multiple products")
  {
    /// @brief Testa inserção de múltiplos produtos no carrinho
    /// @details Verifica se o carrinho pode conter vários produtos diferentes
    carrinho.inserir(produto1, 1);
    carrinho.inserir(produto2, 3);
    CHECK(carrinho.carrinhoProdutos.size() == 2);
  }

  SUBCASE("Carrinho display")
  {
    /// @brief Testa a exibição do conteúdo do carrinho
    /// @details Verifica se a string retornada contém informações do produto
    carrinho.inserir(produto1, 1);
    std::string result = carrinho.exibir();
    CHECK_FALSE(result.empty());
    CHECK(result.find("Product 1") != std::string::npos);
  }

  SUBCASE("Carrinho remove specific product")
  {
    /// @brief Testa remoção de produto específico do carrinho
    /// @details Verifica se apenas o produto especificado é removido
    carrinho.inserir(produto1, 1);
    carrinho.inserir(produto2, 2);
    carrinho.excluir(1); // Remove product with ID 1
    CHECK(carrinho.carrinhoProdutos.size() == 1);
  }

  SUBCASE("Carrinho clear all")
  {
    /// @brief Testa limpeza completa do carrinho
    /// @details Verifica se todos os produtos são removidos do carrinho
    carrinho.inserir(produto1, 1);
    carrinho.inserir(produto2, 2);
    carrinho.excluir(); // Clear all
    CHECK(carrinho.carrinhoProdutos.empty());
  }
}

/**
 * @brief Testa a funcionalidade da classe Pedido
 * 
 * Verifica criação de pedidos, confirmação de pagamento, envio e avaliação.
 */
TEST_CASE("Pedido class functionality")
{
  Carrinho carrinho;
  Produto produto(1, "Test Product", "Test Brand", 99.99, 4.5, 10, "Test Description", "Test Location");
  carrinho.inserir(produto, 1);

  SUBCASE("Pedido creation")
  {
    /// @brief Testa a criação de um novo pedido
    /// @details Verifica se os IDs do comprador e vendedor são atribuídos corretamente
    Pedido pedido(1, 2, carrinho);
    CHECK(pedido.getIdComprador() == 1);
    CHECK(pedido.getIdVendedor() == 2);
    CHECK(pedido.getPagamento() == true); // Default value
  }

  SUBCASE("Pedido payment confirmation")
  {
    /// @brief Testa a confirmação de pagamento do pedido
    /// @details Verifica se o status do pedido é atualizado após confirmação
    Pedido pedido(1, 2, carrinho);
    CHECK_NOTHROW(pedido.pagamentoConcluido());
    // Status should be updated after payment confirmation
    CHECK(pedido.getStatus() != "Esperando aprovação do pagamento");
  }

  SUBCASE("Pedido shipment by seller")
  {
    /// @brief Testa o envio do pedido pelo vendedor autorizado
    /// @details Verifica se o vendedor correto pode confirmar o envio
    Pedido pedido(1, 2, carrinho);
    pedido.pagamentoConcluido();
    CHECK_NOTHROW(pedido.enviarPedido(2)); // Seller with ID 2 confirms
  }

  SUBCASE("Pedido shipment by non-seller should fail")
  {
    /// @brief Testa tentativa de envio por vendedor não autorizado
    /// @details Verifica se uma exceção é lançada para vendedor incorreto
    Pedido pedido(1, 2, carrinho);
    pedido.pagamentoConcluido();
    CHECK_THROWS(pedido.enviarPedido(3)); // Wrong seller ID
  }

  SUBCASE("Pedido evaluation")
  {
    /// @brief Testa a avaliação do pedido
    /// @details Verifica validação de notas (1-5) e comentários
    Pedido pedido(1, 2, carrinho);
    CHECK_NOTHROW(pedido.avaliarPedido(5, "Excellent product!"));
    CHECK_THROWS(pedido.avaliarPedido(6, "Invalid rating")); // Rating > 5
    CHECK_THROWS(pedido.avaliarPedido(0, "Invalid rating")); // Rating < 1
  }
}

/**
 * @brief Testa a funcionalidade da classe Admin
 * 
 * Verifica operações administrativas como obtenção de estatísticas e listas.
 */
TEST_CASE("Admin class functionality")
{
  Admin admin;

  SUBCASE("Admin statistics")
  {
    /// @brief Testa obtenção de estatísticas do sistema
    /// @details Verifica se as estatísticas são obtidas sem erros
    // This should not throw any exceptions
    CHECK_NOTHROW(admin.obterResumoEstatistico());
  }

  SUBCASE("Admin user management")
  {
    /// @brief Testa gerenciamento de usuários pelo admin
    /// @details Verifica se a lista de usuários é obtida sem erros
    CHECK_NOTHROW(admin.obterListaDeUsuarios());
  }

  SUBCASE("Admin product management")
  {
    /// @brief Testa gerenciamento de produtos pelo admin
    /// @details Verifica se a lista de produtos é obtida sem erros
    CHECK_NOTHROW(admin.obterListaDeProdutos());
  }

  SUBCASE("Admin order management")
  {
    /// @brief Testa gerenciamento de pedidos pelo admin
    /// @details Verifica se a lista de pedidos é obtida sem erros
    CHECK_NOTHROW(admin.obterListaDePedidos());
  }
}

/**
 * @brief Testes de integração do sistema
 * 
 * Verifica fluxos completos de uso do sistema, testando a interação
 * entre múltiplas classes.
 */
TEST_CASE("Integration tests")
{
  SUBCASE("Complete purchase flow")
  {
    /// @brief Testa fluxo completo de compra
    /// @details Simula um fluxo completo: cadastro → login → adicionar ao carrinho → criar pedido
    
    // Create user
    Usuario user;
    user.cadastrar("Integration User", "integration@test.com", "testpass", "11999999999", "123.456.789-10", "Test Address");
    CHECK(user.login("integration@test.com", "testpass") == true);

    // Create product and add to cart
    Produto produto(999, "Integration Product", "Test Brand", 199.99, 4.8, 5, "Integration test product", "Test Location");
    Carrinho &carrinho = user.carrinho; // Access user's cart
    carrinho.inserir(produto, 1);
    CHECK(carrinho.carrinhoProdutos.size() == 1);

    // Simulate purchase (create pedido)
    Pedido pedido(user.getId(), 100, carrinho); // Seller ID 100
    CHECK(pedido.getIdComprador() == user.getId());
    CHECK(pedido.getIdVendedor() == 100);
  }
}
