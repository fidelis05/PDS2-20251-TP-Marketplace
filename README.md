# _Tema_ 💡
**Marketplace:** Sistema que permite a compra e venda de produto entre entre usuários

# _Integrantes_ 👥
- Gustavo de Oliveira Cardoso Rezende - [GustavoORezende](https://github.com/GustavoORezende)
- Miguel Fidelis Pedrosa Martins - [fidelis05](https://github.com/fidelis05)
- Samara Fernandes Cordeiro - [SamaraCordeiro](https://github.com/SamaraCordeiro)
- Teo Mendes Araujo - [TeoMAraujo](https://github.com/TeoMAraujo)

---
## Histórias de Usuário:
### Usuário:
- Como usuário, quero criar uma conta com login e senha, para poder acessar o sistema.
- Como usuário, quero fazer login com meu e-mail e senha, para acessar minha conta com segurança.
- Como usuário, quero visualizar a lista de produtos à venda e aplicar filtros (nome, categoria, preço), para encontrar o que desejo com facilidade.
- Como usuário, quero acessar os detalhes de um produto, para ver sua descrição completa e informações do vendedor.
- Como usuário, quero adicionar produtos ao meu carrinho, para realizar uma compra com múltiplos itens.
- Como usuário, quero remover produtos do meu carrinho, para gerenciar o que será comprado.
- Como usuário, quero finalizar a compra dos itens do meu carrinho, para concluir o pedido.
- Como usuário, quero comprar um produto diretamente da página de anúncio, para agilizar o processo de compra.
- Como usuário, quero cadastrar um novo produto, informando nome, descrição, preço e quantidade, para colocá-lo à venda.
- Como usuário, quero visualizar meus pedidos realizados, para acompanhar o histórico de compras.
- Como usuário, quero cancelar um pedido ainda não processado, para corrigir enganos ou desistências.
- Como usuário, quero editar ou excluir meus produtos cadastrados, para manter o controle sobre meus anúncios.
- Como usuário, quero ver uma confirmação ao realizar ações importantes (como deletar produto ou finalizar pedido), para evitar erros.
### Administrador:
- Como administrador, quero listar, filtrar, editar, excluir e cadastrar usuário, para gerenciar o acesso ao sistema.
- Como administrador, quero listar, filtrar, editar e excluir produtos cadastrados, para garantir a qualidade e organização do marketplace.
- Como administrador, quero listar, filtrar, editar e excluir pedidos realizados, para poder resolver problemas e manter o controle das operações.
- Como administrador, quero visualizar um resumo estatístico (ex: total de usuários, produtos e pedidos), para ter uma visão geral do sistema.


## Estrutura dos Arquivos

```
PDS2-20251-TP-Marketplace-main
|
├── bin
├── data
│   ├── pedidos.txt
│   ├── produtos.txt
│   └── usuarios.txt
├── html*
├── include
│   ├── Admin.hpp
│   ├── Carrinho.hpp
│   ├── Correios.hpp
│   ├── Interface.hpp
│   ├── Pedido.hpp
│   ├── Produto.hpp
│   └── Usuario.hpp
├── latex*
├── Makefile
├── README.md
├── src
│   ├── Admin.cpp
│   ├── Carrinho.cpp
│   ├── Correios.cpp
│   ├── Interface.cpp
│   ├── main.cpp
│   ├── Pedido.cpp
│   ├── Produto.cpp
│   └── Usuario.cpp
├── test-ncurses.cpp
└── tests
    ├── doctest.h
    ├── test_all.cpp
    ├── test_comprehensive.cpp
    ├── test_pedido.cpp
    └── test_usuario.cpp*
```
"$*$" são folders que apresentam dados referentes àpenas ao Doxygen


## Cartões CRC
![image](https://github.com/user-attachments/assets/2a512a95-cff4-4781-8a84-7f81776086c7)
