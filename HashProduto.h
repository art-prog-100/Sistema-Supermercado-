#ifndef HASHPRODUTO_H_INCLUDED
#define HASHPRODUTO_H_INCLUDED

#include <stdio.h>
#include "Produtos.h"

/* ---------------------------------------------------------------------
   Tabela Hash para a entidade Produto
   - Encadeamento exterior (separate chaining) gravado em disco
   - Arquivo de "gavetas" (buckets): TAM_HASH posicoes + 1 posicao extra
     (POS_LIVRE) que guarda a cabeca da lista de espacos livres
   - Arquivo de dados: registros de tamanho fixo (TRegHashProduto)
   ------------------------------------------------------------------- */

#define TAM_HASH   13         /* M - numero de gavetas (primo)        */
#define POS_LIVRE  TAM_HASH   /* gaveta extra: cabeca da lista livre  */

typedef struct RegHashProduto {
    int    cod;
    char   nome[60];
    char   categoria[30];
    int    estoque;
    double preco;
    int    prox;      /* encadeamento: proximo da mesma gaveta OU da lista de livres */
    int    ocupado;   /* 1 = ocupado | 0 = livre / reutilizavel */
} TRegHashProduto;

/* Cria/zera o arquivo de gavetas com TAM_HASH+1 posicoes = -1 */
void inicializaHashProduto(char *arqGavetas);

/* Funcao hash (metodo da divisao) */
int funcaoHashProduto(int cod);

/* Busca: retorna 1 se encontrou (preenche *reg), 0 caso contrario */
int buscarHashProduto(int cod, FILE *gavetas, FILE *dados, TRegHashProduto *reg);

/* Insere um TProduto (vindo de Produtos.h). Retorna 1 se OK, 0 se chave duplicada */
int inserirHashProduto(TProduto *p, FILE *gavetas, FILE *dados);

/* Remove pela chave. Retorna 1 se removeu, 0 se nao encontrou.
   O espaco liberado eh reaproveitado em insercoes futuras. */
int removerHashProduto(int cod, FILE *gavetas, FILE *dados);

/* Imprime o registro no formato de TProduto */
void imprimeRegHashProduto(TRegHashProduto *reg);

#endif // HASHPRODUTO_H_INCLUDED