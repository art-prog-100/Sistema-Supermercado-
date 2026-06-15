#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Intercalacao.h"

void constroiArvore(NoArvore *arvore, FILE **particoes, int numParticoes) {
    int i;
    for (i = 0; i < numParticoes; i++) {
        arvore[i].particaoIdx = i;
        if (fread(&arvore[i].reg, sizeof(TProduto), 1, particoes[i]) == 1) {
            arvore[i].valido = 1;
        } else {
            arvore[i].valido = 0;
        }
    }
}

int vencedor(NoArvore *arvore, int numParticoes) {
    int i, idxVencedor = -1;

    for (i = 0; i < numParticoes; i++) {
        if (arvore[i].valido) {
            if (idxVencedor == -1 || arvore[i].reg.cod < arvore[idxVencedor].reg.cod) {
                idxVencedor = i;
            }
        }
    }
    return idxVencedor;
}

void atualizaArvore(NoArvore *arvore, FILE **particoes, int numParticoes, int idxVencedor) {
    if (fread(&arvore[idxVencedor].reg, sizeof(TProduto), 1, particoes[idxVencedor]) != 1) {
        arvore[idxVencedor].valido = 0;  // partição esgotada
    }
}

void intercalaParticoes(const char *nomeArqSaida, int numParticoes) {
    int i, idxVenc;
    FILE **particoes;
    FILE *arqSaida;
    NoArvore *arvore;
    char nomeParticao[100];

    // abre todos os arquivos de partição
    particoes = (FILE **) malloc(numParticoes * sizeof(FILE *));
    if (!particoes) {
        printf("Erro ao alocar memoria para particoes\n");
        return;
    }

    for (i = 0; i < numParticoes; i++) {
        sprintf(nomeParticao, "particoes/part%d.dat", i + 1);
        particoes[i] = fopen(nomeParticao, "rb");
        if (!particoes[i]) {
            printf("Erro ao abrir %s\n", nomeParticao);
            return;
        }
    }

    // abre arquivo de saída
    arqSaida = fopen(nomeArqSaida, "wb");
    if (!arqSaida) {
        printf("Erro ao abrir arquivo de saida\n");
        return;
    }

    // aloca e constrói a árvore
    arvore = (NoArvore *) malloc(numParticoes * sizeof(NoArvore));
    if (!arvore) {
        printf("Erro ao alocar memoria para arvore\n");
        return;
    }

    constroiArvore(arvore, particoes, numParticoes);

    // loop principal — enquanto houver vencedor válido
    while ((idxVenc = vencedor(arvore, numParticoes)) != -1) {
        // grava vencedor no arquivo final
        fwrite(&arvore[idxVenc].reg, sizeof(TProduto), 1, arqSaida);

        // atualiza árvore com próximo da partição vencedora
        atualizaArvore(arvore, particoes, numParticoes, idxVenc);
    }

    // fecha tudo e libera memória
    for (i = 0; i < numParticoes; i++)
        fclose(particoes[i]);

    fclose(arqSaida);
    free(particoes);
    free(arvore);

    printf("Intercalacao concluida em %s\n", nomeArqSaida);
}