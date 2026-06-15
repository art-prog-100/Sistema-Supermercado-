#include <stdio.h>
#include <stdlib.h>
#include "Particoes.h"
 
int menorNoBuffer(TProduto *buffer, int *congelados, int tamBuffer)
{
    int i;
    int menorIdx = -1;
    
    for(i = 0; i < tamBuffer; i++) 
    {
        if(congelados[i] == 0)
        {
            if(menorIdx == -1)
            {
                menorIdx = i;
            }
            else
            {
                if(buffer[i].cod < buffer[menorIdx].cod)
                {
                    menorIdx = i;
                }
            }
        }
    }
     return menorIdx;
 
}
 
 
 int todosCongelos(int *congelados, int tamBuffer)
 {
    int i;
 
    for(i = 0; i < tamBuffer; i++)
    {
        if(congelados[i] == 0)
        {
            return 0;
        }
    }
 
    return 1;
 }
 
int geraParticoes(const char *nomeEntrada, int totalRegistros, int tamBuffer) {
    int i, idx, numParticao, registrosLidos;
    TProduto *buffer, novoReg, ultimoGravado;
    int *congelados;
    FILE *arqEntrada, *arqParticao;
    char nomeParticao[100];
 
    // abre arquivo de entrada
    arqEntrada = fopen(nomeEntrada, "rb");
    if (!arqEntrada) {
        printf("Erro ao abrir arquivo %s\n", nomeEntrada);
        return 0;
    }
 
    // aloca buffer e array de congelados
    buffer = (TProduto *) malloc(tamBuffer * sizeof(TProduto));
    congelados = (int *) malloc(tamBuffer * sizeof(int));
    if (!buffer || !congelados) {
        printf("Erro ao alocar memoria\n");
        fclose(arqEntrada);
        return 0;
    }
 
    // inicializa congelados como 0
    for (i = 0; i < tamBuffer; i++)
        congelados[i] = 0;
 
    // carrega primeiros registros no buffer
    for (i = 0; i < tamBuffer; i++)
        fread(&buffer[i], sizeof(TProduto), 1, arqEntrada);
 
    registrosLidos = tamBuffer;
    numParticao = 1;
    ultimoGravado.cod = -1;
 
    // abre primeira particao
    sprintf(nomeParticao, "particoes/part%d.dat", numParticao);
    arqParticao = fopen(nomeParticao, "wb");
    if (!arqParticao) {
        printf("Erro ao criar particao %s\n", nomeParticao);
        fclose(arqEntrada);
        free(buffer);
        free(congelados);
        return 0;
    }
 
    // loop principal
    while (1) {
        idx = menorNoBuffer(buffer, congelados, tamBuffer);
 
        // grava menor na particao atual
        fwrite(&buffer[idx], sizeof(TProduto), 1, arqParticao);
        ultimoGravado = buffer[idx];
 
        // tenta ler novo registro
        if (registrosLidos < totalRegistros) {
            fread(&novoReg, sizeof(TProduto), 1, arqEntrada);
            registrosLidos++;
 
            if (novoReg.cod < ultimoGravado.cod) {
                congelados[idx] = 1;     // congela
                buffer[idx] = novoReg;
            } else {
                buffer[idx] = novoReg;   // entra normal
            }
        } else {
            congelados[idx] = 1;         // sem novos registros, congela
        }
 
        // verifica se todos congelados
        if (todosCongelos(congelados, tamBuffer)) {
            fclose(arqParticao);
 
            // verifica se ainda há registros no buffer
            if (registrosLidos >= totalRegistros) {
                break;
            }
 
            // abre nova particao
            numParticao++;
            sprintf(nomeParticao, "particoes/part%d.dat", numParticao);
            arqParticao = fopen(nomeParticao, "wb");
            if (!arqParticao) {
                printf("Erro ao criar particao %s\n", nomeParticao);
                break;
            }
 
            // descongela todos
            for (i = 0; i < tamBuffer; i++)
                congelados[i] = 0;
 
            ultimoGravado.cod = -1;
        }
    }
 
    fclose(arqEntrada);
    free(buffer);
    free(congelados);
 
    printf("%d particoes geradas em particoes/\n", numParticao);
    return numParticao;
}
 