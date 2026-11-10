
#include <stdio.h>
#include "pagamento.h"

int registrarPagamento(int codigoComanda, float total) {

    int opcao;
    float valorPago;
    float troco;

    if (total <= 0) {
        printf("\nValor da comanda invalido!\n");
        return 0;
    }

    while (1) {

        printf("\n===== PAGAMENTO =====\n");
        printf("Comanda: %d\n", codigoComanda);
        printf("Total: R$ %.2f\n", total);

        printf("\n1 - Dinheiro\n");
        printf("2 - PIX\n");
        printf("3 - Cartao\n");
        printf("0 - Voltar\n");

        printf("\nEscolha a forma de pagamento: ");

        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n') {
            }

            printf("\nOpcao invalida! Tente novamente.\n");

        } else if (opcao == 1) {

            printf("\nValor recebido: R$ ");

            if (scanf("%f", &valorPago) != 1) {
                while (getchar() != '\n') {
                }

                printf("\nValor invalido! Tente novamente.\n");

            } else if (valorPago < total) {

                printf("\nValor insuficiente!\n");
                printf("1 - Tentar novamente\n");
                printf("0 - Voltar\n");
                printf("Opcao: ");

                if (scanf("%d", &opcao) != 1) {
                    while (getchar() != '\n') {
                    }

                    printf("\nOpcao invalida!\n");

                } else if (opcao == 0) {
                    return 0;
                }

            } else {

                troco = valorPago - total;

                printf("\nPagamento realizado em dinheiro!\n");
                printf("Troco: R$ %.2f\n", troco);

                return 1;
            }

        } else if (opcao == 2 || opcao == 3) {

            if (opcao == 2) {
                printf("\nPagamento por PIX selecionado.\n");
            } else {
                printf("\nPagamento por cartao selecionado.\n");
            }

            printf("1 - Confirmar pagamento\n");
            printf("0 - Voltar\n");
            printf("Opcao: ");

            if (scanf("%d", &opcao) != 1) {
                while (getchar() != '\n') {
                }

                printf("\nOpcao invalida!\n");

            } else if (opcao == 1) {

                printf("\nPagamento confirmado!\n");
                return 1;

            } else if (opcao == 0) {

                printf("\nVoltando ao pagamento...\n");

            } else {

                printf("\nOpcao invalida!\n");
            }

        } else if (opcao == 0) {

            printf("\nVoltando ao menu principal...\n");
            return 0;

        } else {

            printf("\nOpcao invalida! Tente novamente.\n");
        }
    }
}

