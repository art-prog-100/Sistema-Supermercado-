#ifndef INTERCALACAO_H
#define INTERCALACAO_H

#include <stdio.h>
#include <stdlib.h>
#include "Produtos.h"

#define MAX_PARTICOES 2500

// Representa um nó da árvore de vencedores
typedef struct {
    TProduto reg;      // registro atual do nó
    int particaoIdx;   // índice de qual partição veio
    int valido;        // 1 = tem registro, 0 = partição esgotada
} NoArvore;

// Protótipos
void intercalaParticoes(const char *nomeArqSaida, int numParticoes);

// Funções auxiliares
void constroiArvore(NoArvore *arvore, FILE **particoes, int numParticoes);
int vencedor(NoArvore *arvore, int numParticoes);
void atualizaArvore(NoArvore *arvore, FILE **particoes, int numParticoes, int idxVencedor);

#endif