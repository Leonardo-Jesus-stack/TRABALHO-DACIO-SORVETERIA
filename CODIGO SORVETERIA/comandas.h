
#ifndef COMANDAS_H
#define COMANDAS_H

#include "produtos.h"

#define MAX_COMANDAS 100
#define MAX_ITENS 20

// Estrutura dos produtos dentro da comanda
struct ItemComanda {
    int codigoProduto;
    char nomeProduto[50];
    float precoUnitario;
    int quantidade;
};

// Estrutura da comanda
struct Comanda {
    char nomeCliente[50];
    struct ItemComanda itens[MAX_ITENS];
    int totalItens;
    int aberta;
};

extern struct Comanda comandas[MAX_COMANDAS];
extern int totalComandas;

// Funcoes principais
void criarComanda();
void adicionarItem();
void alterarQuantidadeItem();
void removerItem();
void consultarComanda();
void listarComandasAbertas();

// Funcoes auxiliares
int buscarComanda(char nomeCliente[]);
int selecionarComanda();
int buscarItem(int posicaoComanda, int codigoProduto);

// Calculos
float calcularSubtotal(int posicaoComanda, int posicaoItem);
float calcularTotalComanda(int posicaoComanda);

// Arquivos
void salvarComandas();
void carregarComandas();

#endif

