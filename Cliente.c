#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cliente.h"

// Cria um novo cliente na memória RAM (Heap)
TCliente *cliente(char *nome, char *cpf, char *telefone) {
    TCliente *cli = (TCliente *) malloc(sizeof(TCliente));
    
    if (cli) {
        memset(cli, 0, sizeof(TCliente));
        // Copia as strings para os campos da struct
        strcpy(cli->nome, nome);
        strcpy(cli->cpf, cpf);
        strcpy(cli->telefone, telefone);
    }
    return cli;
}

void salvacli(TCliente *cli, FILE *out) {
    fwrite(cli, sizeof(TCliente), 1, out);
}

TCliente *lecli(FILE *in) {
    TCliente *cli = (TCliente *) malloc(sizeof(TCliente));
    if (!cli) return NULL;
    if (fread(cli, sizeof(TCliente), 1, in) < 1) {
        free(cli);
        return NULL;
    }
    return cli;
}

void removercli(TCliente **cli){
   if (cli == NULL || *cli == NULL) {
        printf("\nErro: ponteiro inválido.\n");
        return;
    }
    free(*cli);      // libera a memória no heap
    *cli = NULL;     // zera o ponteiro ORIGINAL do chamador

    printf("\nCliente removido com sucesso.\n");
}

void imprimecli(TCliente *cli) {
    if (cli == NULL) {
        printf("ERRO: Cliente não encontrado.\n");
    } else {
        printf("**********************************************\n");
        printf("CLIENTE:\n");
        printf("Nome: %s\n", cli->nome);
        printf("CPF: %s\n", cli->cpf);
        printf("Telefone: %s\n", cli->telefone);
        printf("**********************************************\n");
    }
}