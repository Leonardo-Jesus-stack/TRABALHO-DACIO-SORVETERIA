#ifndef PRODUTOS_H
#define PRODUTOS_H

#define MAX_PRODUTOS 100

struct Produto {
    int codigo;
    char nome[50];
    float preco;
    int quantidadeEstoque;
};

/* Produtos cadastrados */
extern struct Produto produtos[MAX_PRODUTOS];
extern int totalProdutos;

/* Funcoes de produtos */
void cadastrarProduto();
void consultarProdutos();
void alterarProduto();
void excluirProduto();

/* Buscar produto pelo codigo */
int buscarProduto(int codigo);

/* Salvar e carregar produtos */
void salvarProdutos();
void carregarProdutos();

#endif
