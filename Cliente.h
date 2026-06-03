#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
#include <stdio.h>

typedef struct Cliente {
    char nome[50];
    char cpf[15];
    char telefone[10];

} TCliente;

TCliente *cliente(char *nome, char *cpf, char *telefone); 


void salvacli(TCliente *cliente, FILE *out);

TCliente *lecli(FILE *in);

void removercli(TCliente **cliente);

void imprimecli(TCliente *cliente);


#endif // CLIENTE_H_INCLUDED 