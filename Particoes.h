#ifndef PARTICOES_H_INCLUDED
#define PARTICOES_H_INCLUDED
#include <stdio.h>
#include "FuncionariosSM.h"
#include "Produtos.h"
#include "Cliente.h"


int geraParticoes(const char *nomeEntrada, int totalRegistros, int tamBuffer);

int menorNoBuffer(TProduto *buffer, int *congelados, int tamBuffer);

int todosCongelos(int *congelados, int tamBuffer);



#endif //PARTICOES_H_INCLUDED