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
- Como usuário, quero cadastrar um novo produto, informando nome, descrição, preço e quantidade, para colocá-lo à venda.
- Como usuário, quero visualizar meus pedidos realizados, para acompanhar o histórico de compras.
- Como usuário, quero cancelar um pedido ainda não processado, para corrigir enganos ou desistências.
- Como usuário, quero editar ou excluir meus produtos cadastrados, para manter o controle sobre meus anúncios.
- Como usuário, quero ver uma confirmação ao realizar ações importantes (como deletar produto ou finalizar pedido), para evitar erros.
### Administrador:
- Como administrador, quero listar e excluir usuário, para gerenciar o acesso ao sistema.
- Como administrador, quero listar e excluir produtos cadastrados, para garantir a qualidade e organização do marketplace.
- Como administrador, quero listar e excluir pedidos realizados, para poder resolver problemas e manter o controle das operações.
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
├── docs/
├── include
│   ├── Admin.hpp
│   ├── Carrinho.hpp
│   ├── Correios.hpp
│   ├── Interface.hpp
│   ├── Pedido.hpp
│   ├── Produto.hpp
│   └── Usuario.hpp
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

## Como rodar o programa
- Primeiramente se deve ter instalado a biblioteca ncurses: 
  ``` bash
  sudo apt-get install libncurses5-dev libncursesw5-dev
  ```

- Rodar testes:
  ``` bash
  make test
  ```

- Rodar o programa:
  ``` bash
  make run
  ```
  - Login admin: `admin123`
  - Login correios: `user: correios` e `senha: correios123`

## 📚 Documentação

### Preview da Documentação via GitHub Pages
[https://fidelis05.github.io/PDS2-20251-TP-Marketplace/](https://fidelis05.github.io/PDS2-20251-TP-Marketplace/)

### Gerando a Documentação
O projeto utiliza Doxygen para gerar documentação automática do código. A documentação inclui:

- **Comentários detalhados** em todas as classes principais (Usuario, Produto, Admin, Carrinho, etc.)
- **Descrições dos métodos** com parâmetros e valores de retorno
- **Documentação dos testes** explicando o que cada teste verifica
- **Diagramas de classes** (quando disponível)

Para gerar a documentação:

```bash
make docs
```

### Visualizando a Documentação
Após gerar a documentação, você pode visualizá-la:

1. **Via navegador**: Abra o arquivo `docs/html/index.html` em qualquer navegador web
2. **No VS Code**: Use o Simple Browser integrado para navegar pela documentação

A documentação estará organizada com:
- **Classes**: Lista de todas as classes com seus métodos e atributos
- **Arquivos**: Códigos-fonte com syntax highlighting
- **Módulos**: Organização lógica das funcionalidades
- **Testes**: Documentação dos casos de teste

### Limpando a Documentação
Para remover os arquivos de documentação gerados:

```bash
make clean-docs
```

Para limpar tudo (compilação + documentação):

```bash
make clean-all
```

## Cartões CRC
![image](https://github.com/user-attachments/assets/2a512a95-cff4-4781-8a84-7f81776086c7)
