#include <stdio.h>
#include "produtos.h"
#include "estoque.h"

// CONSULTAR ESTOQUE

void consultarEstoque(void) {
    int i;

    printf("\n===== CONSULTAR ESTOQUE =====\n");

    if (totalProdutos == 0) {
        printf("Nenhum produto cadastrado!\n");
        return;
    }

    for (i = 0; i < totalProdutos; i++) {
        printf("\nCodigo: %d\n", produtos[i].codigo);
        printf("Produto: %s\n", produtos[i].nome);
        printf("Quantidade disponivel: %d\n",
               produtos[i].quantidadeEstoque);
    }
}


// REPOR ESTOQUE

void reporEstoque(void) {
    int codigo;
    int quantidade;
    int posicao;

    printf("\n===== REPOR ESTOQUE =====\n");

    printf("Codigo do produto: ");
    if (scanf("%d", &codigo) != 1) {
        while (getchar() != '\n') {
        }
        printf("Codigo invalido!\n");
        return;
    }

    if (codigo <= 0) {
        printf("Codigo invalido!\n");
        return;
    }

    posicao = buscarProduto(codigo);

    if (posicao == -1) {
        printf("Produto nao encontrado!\n");
        return;
    }

    printf("\nProduto: %s\n", produtos[posicao].nome);
    printf("Estoque atual: %d\n",
           produtos[posicao].quantidadeEstoque);

    printf("\nQuantidade para reposicao: ");

    if (scanf("%d", &quantidade) != 1) {
        while (getchar() != '\n') {
        }
        printf("Quantidade invalida!\n");
        return;
    }

    if (quantidade <= 0) {
        printf("Quantidade invalida!\n");
        return;
    }

    // Evita ultrapassar o limite de quantidade
    if (quantidade > 1000000 ||
        produtos[posicao].quantidadeEstoque > 1000000 - quantidade) {
        printf("Quantidade muito alta!\n");
        return;
    }

    produtos[posicao].quantidadeEstoque =
        produtos[posicao].quantidadeEstoque + quantidade;

    salvarProdutos();

    printf("\nReposicao realizada com sucesso!\n");
    printf("Novo estoque: %d\n",
           produtos[posicao].quantidadeEstoque);
}


// VERIFICAR ESTOQUE

int verificarEstoque(int codigo, int quantidade) {
    int posicao;

    if (codigo <= 0 || quantidade <= 0) {
        return 0;
    }

    posicao = buscarProduto(codigo);

    if (posicao == -1) {
        return 0;
    }

    if (produtos[posicao].quantidadeEstoque >= quantidade) {
        return 1;
    } else {
        return 0;
    }
}


// BAIXAR ESTOQUE APOS VENDA

int baixarEstoque(int codigo, int quantidade) {
    int posicao;

    if (verificarEstoque(codigo, quantidade) == 0) {
        printf("\nVenda nao permitida!\n");
        printf("Produto inexistente, quantidade invalida ou estoque insuficiente.\n");
        return 0;
    }

    posicao = buscarProduto(codigo);

    produtos[posicao].quantidadeEstoque =
        produtos[posicao].quantidadeEstoque - quantidade;

    salvarProdutos();

    printf("\nEstoque atualizado com sucesso!\n");
    printf("Quantidade restante: %d\n",
           produtos[posicao].quantidadeEstoque);

    return 1;
}
