#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Produtos.h"

TProduto *produto(int cod, char *nome, char *categoria, int estoque, double preço){
     TProduto *prod = (TProduto *) malloc(sizeof(TProduto));

    //inicializa espaco de memoria com ZEROS
    if (prod) memset(prod, 0, sizeof(TProduto));
    //copia valores para os campos de func
    prod->cod = cod;
    strcpy(prod->nome, nome);
    strcpy(prod->categoria, categoria);
    prod->estoque = estoque;
    prod->preço = preço;
    return prod;
}

TProduto *leProduto(FILE *in){
    TProduto *prod = (TProduto *) malloc(sizeof(TProduto));
    
    if (prod == NULL) return NULL;

    if (fread(prod, sizeof(TProduto), 1, in) < 1) {
        free(prod);
        return NULL;
    }

    return prod;
}

void salvarpro(TProduto *prod, FILE *out){
    fwrite(prod, sizeof(TProduto), 1, out);
}

void removerpro(TProduto *prod){
    free(prod);
    prod = NULL;
    if(prod != NULL){
        printf("\nERRO na remoção do produto");
    } else{
        printf("\nPRODUTO REMOVIDO COM SUCESSO\n");
    }
}

void imprimepro(TProduto *prod){
    if(prod == NULL){
        printf("ERRO: Produto não encontrado");
    }else{
    printf("**********************************************");
    printf("\nCodigo do Produto: ");
    printf("%d", prod->cod);
    printf("\nNome: ");
    printf("%s", prod->nome);
    printf("\nCategoria: ");
    printf("%s", prod->categoria);
    printf("\nEstoque Atual: ");
    printf("%d", prod->estoque);
    printf("\nPreço: ");
    printf("%4.2f", prod->preço);
    printf("\n*******************************************");
    }
}

void mudarpreço(TProduto *prod, double novoPreço){
    if(prod == NULL){
        printf("ERRO: Produto não encontrado");
    }

    prod->preço = novoPreço;

    printf("Dados atualizados com sucesso");

}

void mudarestoque(TProduto *prod, int novoEstoque){
    if(prod == NULL){
        printf("ERRO: Produto não encontrado");
    }

    prod->estoque = novoEstoque;

    printf("Dados atualizados com sucesso");

}

