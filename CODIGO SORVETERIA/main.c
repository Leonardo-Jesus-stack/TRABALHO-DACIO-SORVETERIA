
#include <stdio.h>
#include "produtos.h"
#include "comandas.h"
#include "estoque.h"
#include "pagamento.h"

// MENU DE PRODUTOS

void menuProdutos() {
    int opcao;

    do {
        printf("\n===== GERENCIAR PRODUTOS =====\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Consultar produtos\n");
        printf("3 - Alterar produto\n");
        printf("4 - Excluir produto\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");

        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n') {
            }
            opcao = -1;
        }

        if (opcao == 1) {
            cadastrarProduto();
        } else if (opcao == 2) {
            consultarProdutos();
        } else if (opcao == 3) {
            alterarProduto();
        } else if (opcao == 4) {
            excluirProduto();
        } else if (opcao != 0) {
            printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);
}


// MENU DE COMANDAS

void menuComandas() {
    int opcao;

    do {
        printf("\n===== GERENCIAR COMANDAS =====\n");
        printf("1 - Criar comanda\n");
        printf("2 - Adicionar produto\n");
        printf("3 - Alterar quantidade\n");
        printf("4 - Remover produto\n");
        printf("5 - Consultar comanda\n");
        printf("6 - Listar comandas abertas\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");

        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n') {
            }
            opcao = -1;
        }

        if (opcao == 1) {
            criarComanda();
        } else if (opcao == 2) {
            adicionarItem();
        } else if (opcao == 3) {
            alterarQuantidadeItem();
        } else if (opcao == 4) {
            removerItem();
        } else if (opcao == 5) {
            consultarComanda();
        } else if (opcao == 6) {
            listarComandasAbertas();
        } else if (opcao != 0) {
            printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);
}


// MENU DE ESTOQUE

void menuEstoque() {
    int opcao;

    do {
        printf("\n===== GERENCIAR ESTOQUE =====\n");
        printf("1 - Consultar estoque\n");
        printf("2 - Repor estoque\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");

        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n') {
            }
            opcao = -1;
        }

        if (opcao == 1) {
            consultarEstoque();
        } else if (opcao == 2) {
            reporEstoque();
        } else if (opcao != 0) {
            printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);
}


// REALIZAR PAGAMENTO

void pagarComanda() {
    int c, i, codigo, quantidade;
    int posicao, resultado;
    int podePagar = 1;
    float total;

    printf("\n===== PAGAR COMANDA =====\n");

    c = selecionarComanda();

    if (c == -1) {
        return;
    }

    if (comandas[c].totalItens == 0) {
        printf("\nComanda sem produtos!\n");
        return;
    }

    // Verificar todos os produtos antes do pagamento
    for (i = 0; i < comandas[c].totalItens; i++) {
        codigo = comandas[c].itens[i].codigoProduto;
        quantidade = comandas[c].itens[i].quantidade;

        if (verificarEstoque(codigo, quantidade) == 0) {
            printf("\nEstoque insuficiente para: %s\n",
                   comandas[c].itens[i].nomeProduto);
            podePagar = 0;
        }
    }

    if (podePagar == 0) {
        printf("\nPagamento nao permitido!\n");
        return;
    }

    total = calcularTotalComanda(c);

    printf("\nCliente: %s\n", comandas[c].nomeCliente);
    printf("Total da comanda: R$ %.2f\n", total);

    // O pagamento retorna 1 quando confirmado
    resultado = registrarPagamento(c + 1, total);

    if (resultado == 1) {

        // Descontar os produtos vendidos
        for (i = 0; i < comandas[c].totalItens; i++) {
            codigo = comandas[c].itens[i].codigoProduto;
            quantidade = comandas[c].itens[i].quantidade;

            posicao = buscarProduto(codigo);

            if (posicao != -1) {
                baixarEstoque(codigo, quantidade);
            }
        }

        // Fechar a comanda
        comandas[c].aberta = 0;
        salvarComandas();

        printf("\nComanda fechada com sucesso!\n");
        printf("Pagamento concluido!\n");

    } else {
        printf("\nPagamento cancelado!\n");
        printf("A comanda continua aberta.\n");
    }
}


// PROGRAMA PRINCIPAL

int main() {
    int opcao;

    carregarProdutos();
    carregarComandas();

    do {
        printf("\n========== SORVETERIA ==========\n");
        printf("1 - Gerenciar produtos\n");
        printf("2 - Gerenciar comandas\n");
        printf("3 - Gerenciar estoque\n");
        printf("4 - Realizar pagamento\n");
        printf("0 - Sair do sistema\n");
        printf("\nEscolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n') {
            }
            opcao = -1;
        }

        if (opcao == 1) {
            menuProdutos();
        } else if (opcao == 2) {
            menuComandas();
        } else if (opcao == 3) {
            menuEstoque();
        } else if (opcao == 4) {
            pagarComanda();
        } else if (opcao == 0) {
            salvarProdutos();
            salvarComandas();
            printf("\nSaindo do sistema...\n");
        } else {
            printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}

