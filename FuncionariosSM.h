#ifndef FUNCIONARIOSSM_H_INCLUDED
#define FUNCIONARIOSSM_H_INCLUDED
#include <stdio.h>  

typedef struct Funcionario {
    int cod;
    char nome[50];
    char cpf[15];
    char data_nascimento[11];
    char trabalho[30];
    double salario;
} TFunc;


// Cria funcionario.
TFunc *funcionario(int cod, char *nome, char *cpf, char *data_nascimento, char *trabalho, double salario);

void mudarTrabalho(TFunc *func, char *novoTrabalho, double novoSalario);

// Salva funcionario no arquivo out, na posicao atual do cursor
void salva(TFunc *func, FILE *out);

// Le um funcionario do arquivo in na posicao atual do cursor
// Retorna um ponteiro para funcionario lido do arquivo
TFunc *le(FILE *in);

void removerfunc(TFunc **func);

// Imprime funcionario
void imprime(TFunc *func); 







#endif // FUNCIONARIOSSM_H_INCLUDED





