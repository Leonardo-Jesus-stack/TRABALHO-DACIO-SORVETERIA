
#include <stdio.h>
#include "produtos.h"
#include "comandas.h"

struct Comanda comandas[MAX_COMANDAS];
int totalComandas = 0;


// COMPARAR NOMES

int nomesIguais(char nome1[], char nome2[]) {
    int i = 0;

    while (nome1[i] != '\0' && nome2[i] != '\0') {
        if (nome1[i] != nome2[i]) {
            return 0;
        }
        i++;
    }

    if (nome1[i] == '\0' && nome2[i] == '\0') {
        return 1;
    }

    return 0;
}


// COPIAR NOME

void copiarNome(char destino[], char origem[]) {
    int i = 0;

    while (origem[i] != '\0' && i < 49) {
        destino[i] = origem[i];
        i++;
    }

    destino[i] = '\0';
}


// CRIAR COMANDA

void criarComanda() {
    char nome[50];

    if (totalComandas >= MAX_COMANDAS) {
        printf("\nLimite de comandas atingido!\n");
        return;
    }

    printf("\n===== NOVA COMANDA =====\n");
    printf("Nome do cliente: ");

    if (scanf(" %49[^\n]", nome) != 1) {
        printf("\nNome invalido!\n");
        return;
    }

    if (buscarComanda(nome) != -1) {
        printf("\nJa existe uma comanda aberta para esse cliente!\n");
        return;
    }

    copiarNome(comandas[totalComandas].nomeCliente, nome);

    comandas[totalComandas].totalItens = 0;
    comandas[totalComandas].aberta = 1;

    totalComandas++;

    salvarComandas();

    printf("\nComanda de %s criada com sucesso!\n", nome);
}


// ADICIONAR PRODUTO

void adicionarItem() {
    int c, codigo, quantidade;
    int p, item, quantidadeFinal;

    printf("\n===== ADICIONAR PRODUTO =====\n");

    c = selecionarComanda();

    if (c == -1) {
        return;
    }

    printf("Codigo do produto: ");

    if (scanf("%d", &codigo) != 1) {
        while (getchar() != '\n') {
        }
        printf("\nCodigo invalido!\n");
        return;
    }

    p = buscarProduto(codigo);

    if (p == -1) {
        printf("\nProduto nao encontrado!\n");
        return;
    }

    printf("Produto: %s - R$ %.2f\n",
           produtos[p].nome, produtos[p].preco);

    if (produtos[p].quantidadeEstoque <= 0) {
        printf("\nProduto sem estoque!\n");
        return;
    }

    printf("Quantidade: ");

    if (scanf("%d", &quantidade) != 1) {
        while (getchar() != '\n') {
        }
        printf("\nQuantidade invalida!\n");
        return;
    }

    if (quantidade <= 0) {
        printf("\nQuantidade invalida!\n");
        return;
    }

    item = buscarItem(c, codigo);

    if (item != -1) {
        if (quantidade >
            produtos[p].quantidadeEstoque -
            comandas[c].itens[item].quantidade) {

            printf("\nEstoque insuficiente!\n");
            return;
        }

        quantidadeFinal =
            comandas[c].itens[item].quantidade + quantidade;

        comandas[c].itens[item].quantidade = quantidadeFinal;

    } else {
        if (quantidade > produtos[p].quantidadeEstoque) {
            printf("\nEstoque insuficiente!\n");
            return;
        }

        if (comandas[c].totalItens >= MAX_ITENS) {
            printf("\nLimite de itens atingido!\n");
            return;
        }

        item = comandas[c].totalItens;

        comandas[c].itens[item].codigoProduto = codigo;

        copiarNome(comandas[c].itens[item].nomeProduto,
                   produtos[p].nome);

        comandas[c].itens[item].precoUnitario = produtos[p].preco;
        comandas[c].itens[item].quantidade = quantidade;

        comandas[c].totalItens++;
    }

    salvarComandas();

    printf("\nProduto adicionado com sucesso!\n");
    printf("Subtotal: R$ %.2f\n", calcularSubtotal(c, item));
}


// ALTERAR QUANTIDADE

void alterarQuantidadeItem() {
    int c, codigo, item, p, novaQuantidade;

    printf("\n===== ALTERAR QUANTIDADE =====\n");

    c = selecionarComanda();

    if (c == -1) {
        return;
    }

    printf("Codigo do produto: ");

    if (scanf("%d", &codigo) != 1) {
        while (getchar() != '\n') {
        }
        printf("\nCodigo invalido!\n");
        return;
    }

    item = buscarItem(c, codigo);

    if (item == -1) {
        printf("\nProduto nao encontrado na comanda!\n");
        return;
    }

    printf("Quantidade atual: %d\n",
           comandas[c].itens[item].quantidade);

    printf("Nova quantidade: ");

    if (scanf("%d", &novaQuantidade) != 1) {
        while (getchar() != '\n') {
        }
        printf("\nQuantidade invalida!\n");
        return;
    }

    if (novaQuantidade <= 0) {
        printf("\nQuantidade invalida!\n");
        return;
    }

    p = buscarProduto(codigo);

    if (p != -1 &&
        novaQuantidade > produtos[p].quantidadeEstoque) {

        printf("\nEstoque insuficiente!\n");
        return;
    }

    comandas[c].itens[item].quantidade = novaQuantidade;

    salvarComandas();

    printf("\nQuantidade alterada com sucesso!\n");
    printf("Novo subtotal: R$ %.2f\n",
           calcularSubtotal(c, item));
}


// REMOVER PRODUTO

void removerItem() {
    int c, codigo, item, j;

    printf("\n===== REMOVER PRODUTO =====\n");

    c = selecionarComanda();

    if (c == -1) {
        return;
    }

    printf("Codigo do produto: ");

    if (scanf("%d", &codigo) != 1) {
        while (getchar() != '\n') {
        }
        printf("\nCodigo invalido!\n");
        return;
    }

    item = buscarItem(c, codigo);

    if (item == -1) {
        printf("\nProduto nao encontrado na comanda!\n");
        return;
    }

    for (j = item; j < comandas[c].totalItens - 1; j++) {
        comandas[c].itens[j] = comandas[c].itens[j + 1];
    }

    comandas[c].totalItens--;

    salvarComandas();

    printf("\nProduto removido da comanda!\n");
}


// CONSULTAR COMANDA

void consultarComanda() {
    int c, i;

    printf("\n===== CONSULTAR COMANDA =====\n");

    c = selecionarComanda();

    if (c == -1) {
        return;
    }

    printf("\nCliente: %s\n", comandas[c].nomeCliente);

    if (comandas[c].totalItens == 0) {
        printf("Comanda sem itens.\n");
        return;
    }

    for (i = 0; i < comandas[c].totalItens; i++) {
        printf("\nCodigo: %d\n",
               comandas[c].itens[i].codigoProduto);

        printf("Produto: %s\n",
               comandas[c].itens[i].nomeProduto);

        printf("Preco: R$ %.2f\n",
               comandas[c].itens[i].precoUnitario);

        printf("Quantidade: %d\n",
               comandas[c].itens[i].quantidade);

        printf("Subtotal: R$ %.2f\n",
               calcularSubtotal(c, i));
    }

    printf("\nTOTAL: R$ %.2f\n", calcularTotalComanda(c));
}


// LISTAR COMANDAS ABERTAS

void listarComandasAbertas() {
    int i;
    int encontradas = 0;

    printf("\n===== COMANDAS ABERTAS =====\n");

    for (i = 0; i < totalComandas; i++) {
        if (comandas[i].aberta == 1) {
            printf("\nCliente: %s\n",
                   comandas[i].nomeCliente);

            printf("Itens: %d\n",
                   comandas[i].totalItens);

            printf("Total: R$ %.2f\n",
                   calcularTotalComanda(i));

            encontradas++;
        }
    }

    if (encontradas == 0) {
        printf("\nNenhuma comanda aberta!\n");
    }
}


// BUSCAR COMANDA

int buscarComanda(char nomeCliente[]) {
    int i;

    for (i = 0; i < totalComandas; i++) {
        if (comandas[i].aberta == 1 &&
            nomesIguais(comandas[i].nomeCliente, nomeCliente) == 1) {
            return i;
        }
    }

    return -1;
}


// SELECIONAR COMANDA

int selecionarComanda() {
    char nome[50];
    int c;

    printf("Nome do cliente: ");

    if (scanf(" %49[^\n]", nome) != 1) {
        printf("\nNome invalido!\n");
        return -1;
    }

    c = buscarComanda(nome);

    if (c == -1) {
        printf("\nComanda nao encontrada ou fechada!\n");
    }

    return c;
}


// BUSCAR ITEM

int buscarItem(int posicaoComanda, int codigoProduto) {
    int i;

    for (i = 0; i < comandas[posicaoComanda].totalItens; i++) {
        if (comandas[posicaoComanda].itens[i].codigoProduto ==
            codigoProduto) {
            return i;
        }
    }

    return -1;
}


// CALCULAR SUBTOTAL

float calcularSubtotal(int posicaoComanda, int posicaoItem) {
    return comandas[posicaoComanda].itens[posicaoItem].precoUnitario *
           comandas[posicaoComanda].itens[posicaoItem].quantidade;
}


// CALCULAR TOTAL

float calcularTotalComanda(int posicaoComanda) {
    int i;
    float total = 0;

    for (i = 0; i < comandas[posicaoComanda].totalItens; i++) {
        total = total + calcularSubtotal(posicaoComanda, i);
    }

    return total;
}


// SALVAR COMANDAS

void salvarComandas() {
    FILE *arquivo;
    int i, j;

    arquivo = fopen("comandas.txt", "w");

    if (arquivo == NULL) {
        printf("\nErro ao salvar comandas!\n");
        return;
    }

    fprintf(arquivo, "%d\n", totalComandas);

    for (i = 0; i < totalComandas; i++) {
        fprintf(arquivo, "%s\n", comandas[i].nomeCliente);
        fprintf(arquivo, "%d\n", comandas[i].aberta);
        fprintf(arquivo, "%d\n", comandas[i].totalItens);

        for (j = 0; j < comandas[i].totalItens; j++) {
            fprintf(arquivo, "%d\n",
                    comandas[i].itens[j].codigoProduto);

            fprintf(arquivo, "%s\n",
                    comandas[i].itens[j].nomeProduto);

            fprintf(arquivo, "%.2f\n",
                    comandas[i].itens[j].precoUnitario);

            fprintf(arquivo, "%d\n",
                    comandas[i].itens[j].quantidade);
        }
    }

    fclose(arquivo);
}


// CARREGAR COMANDAS

void carregarComandas() {
    FILE *arquivo;
    int i, j;

    arquivo = fopen("comandas.txt", "r");

    if (arquivo == NULL) {
        return;
    }

    if (fscanf(arquivo, "%d", &totalComandas) != 1) {
        totalComandas = 0;
        fclose(arquivo);
        return;
    }

    if (totalComandas < 0 || totalComandas > MAX_COMANDAS) {
        totalComandas = 0;
        fclose(arquivo);
        return;
    }

    for (i = 0; i < totalComandas; i++) {
        if (fscanf(arquivo, " %49[^\n]",
                   comandas[i].nomeCliente) != 1 ||
            fscanf(arquivo, "%d",
                   &comandas[i].aberta) != 1 ||
            fscanf(arquivo, "%d",
                   &comandas[i].totalItens) != 1) {

            totalComandas = i;
            break;
        }

        if (comandas[i].totalItens < 0 ||
            comandas[i].totalItens > MAX_ITENS) {
            totalComandas = i;
            break;
        }

        for (j = 0; j < comandas[i].totalItens; j++) {
            if (fscanf(arquivo, "%d",
                       &comandas[i].itens[j].codigoProduto) != 1 ||
                fscanf(arquivo, " %49[^\n]",
                       comandas[i].itens[j].nomeProduto) != 1 ||
                fscanf(arquivo, "%f",
                       &comandas[i].itens[j].precoUnitario) != 1 ||
                fscanf(arquivo, "%d",
                       &comandas[i].itens[j].quantidade) != 1) {

                totalComandas = i;
                break;
            }
        }
    }

    fclose(arquivo);
}

