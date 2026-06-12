#include <stdio.h>
#include <stdlib.h>
#include "Produtos.h"
#include "OrdenacaoDisco.h"

void ordenacaoSelecaoDisco(const char *nomeArquivo, int totalRegistros)
{
    
    int i, j, menorIdx;
    TProduto regI, regJ, regMenor;
    FILE *arq = fopen(nomeArquivo, "rb+");

    if (!arq) {
        printf("Erro ao abrir arquivo %s\n", nomeArquivo);
        return;
    }

       for (i = 0; i < totalRegistros; i++) {
        // assume que i é o menor
        menorIdx = i;
        fseek(arq, i * sizeof(TProduto), SEEK_SET);
        fread(&regMenor, sizeof(TProduto), 1, arq);

        // procura o menor no restante do arquivo
        for (j = i + 1; j < totalRegistros; j++) {
            fseek(arq, j * sizeof(TProduto), SEEK_SET);
            fread(&regJ, sizeof(TProduto), 1, arq);

            if (regJ.cod < regMenor.cod) {
                regMenor = regJ;
                menorIdx = j;
            }
        }

        // se achou um menor diferente de i, troca no arquivo
        if (menorIdx != i) {
            // lê o registro na posição i
            fseek(arq, i * sizeof(TProduto), SEEK_SET);
            fread(&regI, sizeof(TProduto), 1, arq);

            // escreve regMenor na posição i
            fseek(arq, i * sizeof(TProduto), SEEK_SET);
            fwrite(&regMenor, sizeof(TProduto), 1, arq);

            // escreve regI na posição menorIdx
            fseek(arq, menorIdx * sizeof(TProduto), SEEK_SET);
            fwrite(&regI, sizeof(TProduto), 1, arq);
        }
    }

    fclose(arq);
}

int arquivoEstaOrdenado(const char *nomeArquivo, int totalRegistros) 
{
    int i;
    TProduto regAtual, regProximo;
    FILE *arq = fopen(nomeArquivo, "rb");

    if (!arq)
    {
        printf("Erro ao abrir arquivo %s\n", nomeArquivo);
        return -1;
    }

    for (i = 0; i < totalRegistros - 1; i++) 
    {
        // lê registro atual
        fseek(arq, i * sizeof(TProduto), SEEK_SET);
        fread(&regAtual, sizeof(TProduto), 1, arq);

        // lê próximo registro
        fseek(arq, (i + 1) * sizeof(TProduto), SEEK_SET);
        fread(&regProximo, sizeof(TProduto), 1, arq);

        // se atual maior que próximo, não está ordenado
        if (regAtual.cod > regProximo.cod) 
        {
            fclose(arq);
            return 0;
        }
    }

    fclose(arq);
    return 1;
}
