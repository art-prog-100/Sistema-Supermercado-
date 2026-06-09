#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "FuncionariosSM.h"

TFunc *funcionario(int cod, char *nome, char *cpf, char *data_nascimento, char *trabalho, double salario){
 TFunc *func = (TFunc *) malloc(sizeof(TFunc));
    //inicializa espaco de memoria com ZEROS
    if (func) memset(func, 0, sizeof(TFunc));
    //copia valores para os campos de func
    func->cod = cod;
    strcpy(func->nome, nome);
    strcpy(func->cpf, cpf);
    strcpy(func->data_nascimento, data_nascimento);
    strcpy(func->trabalho, trabalho);
    func->salario = salario;
    return func;
}

void mudarTrabalho(TFunc *func, char *novoTrabalho, double novoSalario) {
    // Verifica se o ponteiro para o funcionário é válido (se ele existe)
    if (func == NULL) {
        printf("Erro: Funcionário não encontrado.\n");
        return;
    }

    strcpy(func->trabalho, novoTrabalho);

    func->salario = novoSalario;

    printf("Dados atualizados com sucesso!\n");
}

void salva(TFunc *func, FILE *out) {
    fwrite(func, sizeof(TFunc), 1, out);
}

TFunc *le(FILE *in) {
    TFunc *func = (TFunc *) malloc(sizeof(TFunc));
    if (!func) return NULL;
    if (fread(func, sizeof(TFunc), 1, in) < 1) {
        free(func);
        return NULL;
    }
    return func;
}

void removerfunc(TFunc **func){
   if (func == NULL || *func == NULL) {
        printf("\nErro: ponteiro inválido.\n");
        return;
    }
    free(*func);      // libera a memória no heap
    *func = NULL;     // zera o ponteiro ORIGINAL do chamador

    printf("\nFuncionário removido com sucesso.\n");
} 

void imprime(TFunc *func) {
    printf("**********************************************");
    printf("\nFuncionario de codigo ");
    printf("%d", func->cod);
    printf("\nNome: ");
    printf("%s", func->nome);
    printf("\nCPF: ");
    printf("%s", func->cpf);
    printf("\nData de Nascimento: ");
    printf("%s", func->data_nascimento);
    printf("\nTrabalho: ");
    printf("%s", func->trabalho);
    printf("\nSalario: ");
    printf("%4.2f", func->salario);
    printf("\n**********************************************");
}