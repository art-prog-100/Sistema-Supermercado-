#include "Busca.h"
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

// --- BUSCA SEQUENCIAL (Funcionário) ---
TFunc *buscaSequencialFunc(int chave, FILE *in) {
    TFunc *f = NULL;
    int comp = 0;
    clock_t tempo_inicio = clock();

    rewind(in);
    while ((f = le(in)) != NULL) {
        comp++;
        if (f->cod == chave) {
            clock_t tempo_fim = clock();
            printf("\n[Busca Sequencial] Comparações: %d | Tempo: %f s", comp, (double)(tempo_fim - tempo_inicio) / CLOCKS_PER_SEC);
            return f;
        }
        free(f); 
    }
    return NULL;
}

// --- BUSCA BINÁRIA (Produto) ---
TProduto *buscaBinariaProd(int chave, FILE *in, int tamanhoBase) {
    int inicio = 0;
    int fim = tamanhoBase - 1;
    int comp = 0;
    clock_t tempo_inicio = clock();

    while (inicio <= fim) {
        comp++;
        int meio = (inicio + fim) / 2;
        
        // Posiciona o cursor no registro do meio
        // tamanho_registro() deve ser substituído por sizeof(TProduto)
        fseek(in, meio * sizeof(TProduto), SEEK_SET);
        
        TProduto *p = leProduto(in);
        if (!p) break;

        if (p->cod == chave) {
            clock_t tempo_fim = clock();
            printf("\n[Busca Binária] Comparações: %d | Tempo: %f s", comp, (double)(tempo_fim - tempo_inicio) / CLOCKS_PER_SEC);
            return p;
        }

        if (p->cod < chave) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
        free(p);
    }
    return NULL;
}

// --- BUSCA SEQUENCIAL (Cliente por CPF) ---
TCliente *buscaSequencialCli(char *cpf, FILE *in) {
    TCliente *c = NULL;
    rewind(in);
    while ((c = lecli(in)) != NULL) {
        if (strcmp(c->cpf, cpf) == 0) {
            return c;
        }
        free(c);
    }
    return NULL;
}