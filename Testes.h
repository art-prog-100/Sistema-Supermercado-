#ifndef TESTES_H
#define TESTES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Produtos.h"
#include "OrdenacaoDisco.h"
#include "Particoes.h"
#include "Intercalacao.h"

// Tamanhos das bases de teste
#define NUM_TESTES 1
static const int TAMANHOS[NUM_TESTES] = {1000};

// Tamanho do buffer para geração de partições
#define TAM_BUFFER 100

// Protótipos
void geraBaseDesordenada(const char *nomeArquivo, int tamanho);
void testaOrdenacaoDisco(int tamanho);
void testaParticoesIntercalacao(int tamanho);
void executaTodos();

#endif