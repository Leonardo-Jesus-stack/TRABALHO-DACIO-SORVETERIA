#ifndef ESTOQUE_H
#define ESTOQUE_H

// Consultar os produtos e suas quantidades
void consultarEstoque(void);

// Adicionar quantidades ao estoque
void reporEstoque(void);

// Verificar se existe quantidade suficiente
int verificarEstoque(int codigo, int quantidade);

// Diminuir o estoque apos uma venda
int baixarEstoque(int codigo, int quantidade);

#endif
