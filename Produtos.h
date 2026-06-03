#ifndef PRODUTO_H_INCLUDED
#define PRODUTO_H_INCLUDED
#include <stdio.h>

typedef struct Produto{
    int cod;
    char nome[60];
    char categoria[30];
    int estoque;
    double preço;

} TProduto;

TProduto *produto(int cod, char *nome, char *categoria, int estoque, double produto);

TProduto *leProduto(FILE *in);

void salvarpro(TProduto *prod, FILE *out);

void removerpro(TProduto **prod);

void imprimepro(TProduto *prod);

void mudarpreço(TProduto *prod, double novoPreço);

void mudarestoque(TProduto *prod, int novoEstoque);









#endif // PRODUTO_H_INCLUDED 