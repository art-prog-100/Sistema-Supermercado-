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
    // 1. Aloca memória para um novo produto
    TProduto *prod = (TProduto *) malloc(sizeof(TProduto));
    
    if (prod == NULL) return NULL;

    // 2. Tenta ler o primeiro campo (código). 
    // Se o fread retornar 0, significa que chegamos ao fim do arquivo (EOF).
    if (0 >= fread(&prod->cod, sizeof(int), 1, in)) {
        free(prod); // Libera a memória alocada se não houver nada para ler
        return NULL;
    }

    // 3. Lê os demais campos na exata ordem em que foram salvos no salvarpro
    fread(prod->nome, sizeof(char), sizeof(prod->nome), in);
    fread(prod->categoria, sizeof(char), sizeof(prod->categoria), in);
    fread(&prod->estoque, sizeof(int), 1, in);
    fread(&prod->preço, sizeof(double), 1, in);

    return prod;
}

void salvarpro(TProduto *prod, FILE *out){
    fwrite(&prod->cod, sizeof(int), 1, out);
    //func->nome ao inves de &prod->nome, pois string ja eh um ponteiro
    fwrite(prod->nome, sizeof(char), sizeof(prod->nome), out);
    fwrite(prod->categoria, sizeof(char), sizeof(prod->categoria), out);
    fwrite(&prod->estoque, sizeof(int), 1, out);    
    fwrite(&prod->preço, sizeof(double), 1, out);
}

void removerpro(TProduto **prod){
  if (prod == NULL || *prod == NULL) {
        printf("\nErro: ponteiro inválido.\n");
        return;
    }
    free(*prod);      // libera a memória no heap
    *prod = NULL;     // zera o ponteiro ORIGINAL do chamador

    printf("\nProduto removido com sucesso.\n");
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
