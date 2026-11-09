#include <stdio.h>
#include "produtos.h"

struct Produto produtos[MAX_PRODUTOS];

int totalProdutos = 0;


// CADASTRAR PRODUTO

void cadastrarProduto() {

    int codigo;
    int posicao;

    if (totalProdutos >= MAX_PRODUTOS) {
        printf("\nLimite de produtos atingido!\n");
        return;
    }

    printf("\n===== CADASTRAR PRODUTO =====\n");

    printf("Codigo do produto: ");

    if (scanf("%d", &codigo) != 1) {
        printf("\nErro! Digite apenas numeros.\n");

        while (getchar() != '\n') {
        }

        return;
    }

    if (codigo <= 0) {
        printf("Codigo invalido!\n");
        return;
    }

    posicao = buscarProduto(codigo);

    if (posicao != -1) {
        printf("Ja existe um produto com esse codigo!\n");
        return;
    }

    produtos[totalProdutos].codigo = codigo;

    printf("Nome do produto: ");
    scanf(" %49[^\n]", produtos[totalProdutos].nome);

    printf("Preco: ");

    if (scanf("%f", &produtos[totalProdutos].preco) != 1) {
        printf("Erro! Digite um preco valido.\n");

        while (getchar() != '\n') {
        }

        return;
    }

    printf("Quantidade em estoque: ");

    if (scanf("%d", &produtos[totalProdutos].quantidadeEstoque) != 1) {
        printf("Erro! Digite uma quantidade valida.\n");

        while (getchar() != '\n') {
        }

        return;
    }

    if (produtos[totalProdutos].preco <= 0 ||
        produtos[totalProdutos].quantidadeEstoque < 0) {

        printf("\nPreco ou quantidade invalida!\n");
        return;
    }

    totalProdutos++;

    salvarProdutos();

    printf("\nProduto cadastrado com sucesso!\n");
}


// CONSULTAR PRODUTOS

void consultarProdutos() {

    int i;

    printf("\n===== PRODUTOS CADASTRADOS =====\n");

    if (totalProdutos == 0) {
        printf("Nenhum produto cadastrado!\n");
        return;
    }

    for (i = 0; i < totalProdutos; i++) {

        printf("\nCodigo: %d", produtos[i].codigo);
        printf("\nNome: %s", produtos[i].nome);
        printf("\nPreco: R$ %.2f", produtos[i].preco);
        printf("\nQuantidade: %d\n",
               produtos[i].quantidadeEstoque);
    }
}


// ALTERAR PRODUTO

void alterarProduto() {

    int codigo;
    int i, j;
    char novoNome[50];
    float novoPreco;
    int novaQuantidade;

    printf("\n===== ALTERAR PRODUTO =====\n");

    printf("Digite o codigo do produto: ");

    if (scanf("%d", &codigo) != 1) {
        printf("Erro! Digite apenas numeros.\n");

        while (getchar() != '\n') {
        }

        return;
    }

    i = buscarProduto(codigo);

    if (i == -1) {
        printf("\nProduto nao encontrado!\n");
        return;
    }

    printf("\nProduto encontrado: %s\n", produtos[i].nome);

    printf("Novo nome: ");
    scanf(" %49[^\n]", novoNome);

    printf("Novo preco: ");

    if (scanf("%f", &novoPreco) != 1) {
        printf("Erro! Digite um preco valido.\n");

        while (getchar() != '\n') {
        }

        return;
    }

    printf("Nova quantidade: ");

    if (scanf("%d", &novaQuantidade) != 1) {
        printf("Erro! Digite uma quantidade valida.\n");

        while (getchar() != '\n') {
        }

        return;
    }

    if (novoPreco <= 0 || novaQuantidade < 0) {
        printf("Erro! Dados invalidos.\n");
        return;
    }

    for (j = 0; j < 50; j++) {
        produtos[i].nome[j] = novoNome[j];
    }

    produtos[i].preco = novoPreco;
    produtos[i].quantidadeEstoque = novaQuantidade;

    salvarProdutos();

    printf("\nProduto alterado com sucesso!\n");
}


// EXCLUIR PRODUTO

void excluirProduto() {

    int codigo;
    int i;
    int j;

    printf("\n===== EXCLUIR PRODUTO =====\n");

    printf("Digite o codigo do produto: ");

    if (scanf("%d", &codigo) != 1) {
        printf("Erro! Digite apenas numeros.\n");

        while (getchar() != '\n') {
        }

        return;
    }

    i = buscarProduto(codigo);

    if (i == -1) {
        printf("\nProduto nao encontrado!\n");
        return;
    }

    for (j = i; j < totalProdutos - 1; j++) {
        produtos[j] = produtos[j + 1];
    }

    totalProdutos--;

    salvarProdutos();

    printf("\nProduto excluido com sucesso!\n");
}


// BUSCAR PRODUTO PELO CODIGO

int buscarProduto(int codigo) {

    int i;

    for (i = 0; i < totalProdutos; i++) {

        if (produtos[i].codigo == codigo) {
            return i;
        }
    }

    return -1;
}


// SALVAR PRODUTOS

void salvarProdutos() {

    FILE *arquivo;
    int i;

    arquivo = fopen("produtos.txt", "w");

    if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo!\n");
        return;
    }

    for (i = 0; i < totalProdutos; i++) {

        fprintf(arquivo, "%d\n", produtos[i].codigo);
        fprintf(arquivo, "%s\n", produtos[i].nome);
        fprintf(arquivo, "%.2f\n", produtos[i].preco);
        fprintf(arquivo, "%d\n",
                produtos[i].quantidadeEstoque);
    }

    fclose(arquivo);
}


// CARREGAR PRODUTOS

void carregarProdutos() {

    FILE *arquivo;

    arquivo = fopen("produtos.txt", "r");

    if (arquivo == NULL) {
        return;
    }

    totalProdutos = 0;

    while (totalProdutos < MAX_PRODUTOS) {

        if (fscanf(arquivo, "%d",
                   &produtos[totalProdutos].codigo) != 1) {
            break;
        }

        if (fscanf(arquivo, " %49[^\n]",
                   produtos[totalProdutos].nome) != 1) {
            break;
        }

        if (fscanf(arquivo, "%f",
                   &produtos[totalProdutos].preco) != 1) {
            break;
        }

        if (fscanf(arquivo, "%d",
                   &produtos[totalProdutos].quantidadeEstoque) != 1) {
            break;
        }

        totalProdutos++;
    }

    fclose(arquivo);
}
