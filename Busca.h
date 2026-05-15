#ifndef BUSCA_H
#define BUSCA_H

#include <stdio.h>
#include "FuncionariosSM.h"
#include "Cliente.h"
#include "Produtos.h"

// --- Buscas para Funcionários ---
TFunc *buscaSequencialFunc(int chave, FILE *in);
TFunc *buscaBinariaFunc(int chave, FILE *in, int tamanhoBase);

// --- Buscas para Produtos ---
TProduto *buscaSequencialProd(int chave, FILE *in);
TProduto *buscaBinariaProd(int chave, FILE *in, int tamanhoBase);

// --- Buscas para Clientes ---
TCliente *buscaSequencialCli(char *cpf, FILE *in);

#endif