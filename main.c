#include <stdio.h>
#include <stdlib.h>
#include "FuncionariosSM.h"
#include "Cliente.h"
#include "Produtos.h"
#include "Busca.h"
#include "OrdenacaoDisco.h"
#include "Particoes.h"
#include "Intercalacao.h"
#include "Testes.h"
#include "HashProduto.h"

int main() {
    /* ---------------------------------------------------------- */
    /* 1. ABERTURA DAS BASES (wb+ = cria do zero a cada execucao)  */
    /* ---------------------------------------------------------- */
    FILE *arqFunc = fopen("dados/funcionarios.dat", "wb+");
    FILE *arqCli  = fopen("dados/clientes.dat",     "wb+");
    FILE *arqProd = fopen("dados/produtos.dat",      "wb+");
 
    if (!arqFunc || !arqCli || !arqProd) {
        printf("Erro ao abrir arquivos de dados.\n");
        return 1;
    }
 
    /* ---------------------------------------------------------- */
    /* 2. POPULANDO AS BASES (100 registros cada)                  */
    /* ---------------------------------------------------------- */
    printf("=== POPULANDO BASES ===\n");
    for (int i = 1; i <= 100; i++) {
        char buffer[60];
 
        /* Funcionarios */
        sprintf(buffer, "Funcionario %d", i);
        TFunc *f = funcionario(i, buffer, "000.000.000-00",
                               "01/01/1990", "Operacional", 2000.0);
        salva(f, arqFunc);
        free(f);
 
        /* Clientes */
        sprintf(buffer, "Cliente %d", i);
        TCliente *c = cliente(buffer, "111.111.111-11", "9999-9999");
        salvacli(c, arqCli);
        free(c);
 
        /* Produtos */
        sprintf(buffer, "Produto %d", i);
        TProduto *p = produto(i, buffer, "Geral", 50, 10.0);
        salvarpro(p, arqProd);
        free(p);
    }
    printf("Bases populadas com sucesso.\n\n");
 
    /* ---------------------------------------------------------- */
    /* 3. IMPRESSAO DE UM FUNCIONARIO (funcao imprime)             */
    /* ---------------------------------------------------------- */
    printf("=== LEITURA E IMPRESSAO DE FUNCIONARIO ===\n");
    rewind(arqFunc);
    TFunc *fLido = le(arqFunc);   /* le() — funcao de FuncionariosSM */
    if (fLido) {
        imprime(fLido);
        printf("\n\n");
        free(fLido);
    }
 
    /* ---------------------------------------------------------- */
    /* 4. IMPRESSAO DE UM CLIENTE (funcao imprimecli / lecli)      */
    /* ---------------------------------------------------------- */
    printf("=== LEITURA E IMPRESSAO DE CLIENTE ===\n");
    rewind(arqCli);
    TCliente *cLido = lecli(arqCli);   /* lecli() — funcao de Cliente */
    if (cLido) {
        imprimecli(cLido);
        printf("\n");
        free(cLido);
    }
 
    /* ---------------------------------------------------------- */
    /* 5. BUSCA SEQUENCIAL DE FUNCIONARIO                          */
    /* ---------------------------------------------------------- */
    printf("=== BUSCA SEQUENCIAL — FUNCIONARIO (cod=42) ===\n");
    TFunc *fSeq = buscaSequencialFunc(42, arqFunc);
    if (fSeq) {
        imprime(fSeq);
        printf("\n\n");
        free(fSeq);
    }
 
    /* ---------------------------------------------------------- */
    /* 6. BUSCA BINARIA DE FUNCIONARIO                             */
    /* ---------------------------------------------------------- */
    printf("=== BUSCA BINARIA — FUNCIONARIO (cod=75) ===\n");
    TFunc *fBin = buscaBinariaFunc(75, arqFunc, 100);
    if (fBin) {
        imprime(fBin);
        printf("\n\n");
        free(fBin);
    }
 
    /* ---------------------------------------------------------- */
    /* 7. BUSCA SEQUENCIAL DE CLIENTE POR CPF                      */
    /* ---------------------------------------------------------- */
    printf("=== BUSCA SEQUENCIAL — CLIENTE (CPF) ===\n");
    TCliente *cSeq = buscaSequencialCli("111.111.111-11", arqCli);
    if (cSeq) {
        imprimecli(cSeq);
        printf("\n");
        free(cSeq);
    }
 
    /* ---------------------------------------------------------- */
    /* 8. BUSCA SEQUENCIAL DE PRODUTO                              */
    /* ---------------------------------------------------------- */
    printf("=== BUSCA SEQUENCIAL — PRODUTO (cod=10) ===\n");
    TProduto *pSeq = buscaSequencialProd(10, arqProd);
    if (pSeq) {
        imprimepro(pSeq);
        printf("\n\n");
        free(pSeq);
    }
 
    /* ---------------------------------------------------------- */
    /* 9. BUSCA BINARIA DE PRODUTO + ALTERACAO DE PRECO            */
    /* ---------------------------------------------------------- */
    printf("=== BUSCA BINARIA — PRODUTO (cod=50) + MUDANCA DE PRECO ===\n");
    TProduto *pBin = buscaBinariaProd(50, arqProd, 100);
    if (pBin) {
        printf("\nAntes da alteracao:\n");
        imprimepro(pBin);
        printf("\n");
 
        mudarpreço(pBin, 99.9);   /* mudarpreço() — funcao de Produtos */
 
        fseek(arqProd, (50 - 1) * sizeof(TProduto), SEEK_SET);
        salvarpro(pBin, arqProd);
 
        printf("\nApos a alteracao:\n");
        imprimepro(pBin);
        printf("\n\n");
        free(pBin);
    }
 
    /* ---------------------------------------------------------- */
    /* 10. ALTERACAO DE ESTOQUE DE PRODUTO                         */
    /* ---------------------------------------------------------- */
    printf("=== ALTERACAO DE ESTOQUE — PRODUTO (cod=20) ===\n");
    TProduto *pEst = buscaBinariaProd(20, arqProd, 100);
    if (pEst) {
        mudarestoque(pEst, 200);   /* mudarestoque() — funcao de Produtos */
        fseek(arqProd, (20 - 1) * sizeof(TProduto), SEEK_SET);
        salvarpro(pEst, arqProd);
        printf("\n");
        imprimepro(pEst);
        printf("\n\n");
        free(pEst);
    }
 
    /* ---------------------------------------------------------- */
    /* 11. ALTERACAO DE CARGO E SALARIO DE FUNCIONARIO             */
    /* ---------------------------------------------------------- */
    printf("=== ALTERACAO DE CARGO — FUNCIONARIO (cod=5) ===\n");
    TFunc *fCargo = buscaBinariaFunc(5, arqFunc, 100);
    if (fCargo) {
        mudarTrabalho(fCargo, "Gerente", 5000.0); /* mudarTrabalho() */
        fseek(arqFunc, (5 - 1) * sizeof(TFunc), SEEK_SET);
        salva(fCargo, arqFunc);
        printf("\n");
        imprime(fCargo);
        printf("\n\n");
        free(fCargo);
    }
 
    /* ---------------------------------------------------------- */
    /* 12. REMOCAO DE REGISTROS DA MEMORIA                         */
    /* ---------------------------------------------------------- */
    printf("=== REMOCAO DE REGISTROS DA MEMORIA ===\n");
 
    TFunc *fRem = buscaBinariaFunc(1, arqFunc, 100);
    removerfunc(&fRem);   /* removerfunc() — funcao de FuncionariosSM */
 
    TCliente *cRem = buscaSequencialCli("111.111.111-11", arqCli);
    removercli(&cRem);    /* removercli() — funcao de Cliente */
 
    TProduto *pRem = buscaBinariaProd(1, arqProd, 100);
    removerpro(&pRem);    /* removerpro() — funcao de Produtos */
    printf("\n");
 
    /* ---------------------------------------------------------- */
    /* 13. ORDENACAO EM DISCO (Selection Sort)                     */
    /* ---------------------------------------------------------- */
    printf("=== ORDENACAO EM DISCO (produtos) ===\n");
    fclose(arqProd);
    ordenacaoSelecaoDisco("dados/produtos.dat", 100);
 
    int ord = arquivoEstaOrdenado("dados/produtos.dat", 100);
    printf("Arquivo ordenado: %s\n\n", ord ? "SIM" : "NAO");
 
    /* ---------------------------------------------------------- */
    /* 14. GERACAO DE PARTICOES + INTERCALACAO                     */
    /* ---------------------------------------------------------- */
    printf("=== GERACAO DE PARTICOES ===\n");
    int numPart = geraParticoes("dados/produtos.dat", 100, 10);
 
    printf("=== INTERCALACAO DAS PARTICOES ===\n");
    intercalaParticoes("dados/produtos_final.dat", numPart);
 
    int ordFinal = arquivoEstaOrdenado("dados/produtos_final.dat", 100);
    printf("Arquivo final ordenado: %s\n\n", ordFinal ? "SIM" : "NAO");
 
    /* ---------------------------------------------------------- */
    /* 15. SUITE DE TESTES (bases grandes — pode demorar)          */
    /* ---------------------------------------------------------- */
    printf("=== SUITE DE TESTES COMPLETA ===\n");
    executaTodos();   /* executaTodos() — funcao de Testes */
 
    /* ---------------------------------------------------------- */
    /* FECHAMENTO                                                  */
    /* ---------------------------------------------------------- */
    fclose(arqFunc);
    fclose(arqCli);
    /* arqProd foi fechado antes da ordenacao */

/*
 * TABELA HASH
 */
printf("\n=== TABELA HASH — PRODUTOS ===\n");

/* Inicializa arquivo das gavetas */
inicializaHashProduto("dados/produtos_hash.dat");

/* Abre arquivos */
FILE *gavetas = fopen("dados/produtos_hash.dat", "rb+");

FILE *dadosHash = fopen("dados/produtos_hash_dados.dat", "rb+");
if (!dadosHash)
    dadosHash = fopen("dados/produtos_hash_dados.dat", "wb+");

/* Insere produtos */
printf("Inserindo produtos na Hash...\n");

for (int i = 1; i <= 100; i++) {
    char buffer[60];
    sprintf(buffer, "Produto %d", i);

    TProduto *p = produto(i, buffer, "Geral", 50, 10.0);
    inserirHashProduto(p, gavetas, dadosHash);
    free(p);
}

/* Busca */
printf("Buscando produto codigo 10...\n");

TRegHashProduto reg;
if (buscarHashProduto(10, gavetas, dadosHash, &reg)) {
    imprimeRegHashProduto(&reg);
} else {
    printf("Produto nao encontrado.\n");
}

/* Remocao */
printf("Removendo produto codigo 10...\n");
removerHashProduto(10, gavetas, dadosHash);

/* Confirmacao da remocao */
printf("Buscando novamente o produto 10...\n");
if (!buscarHashProduto(10, gavetas, dadosHash, &reg)) {
    printf("Produto removido com sucesso.\n");
}

/* Reinsercao para demonstrar reaproveitamento */
printf("Inserindo novo produto (codigo 999) reutilizando espaco livre...\n");

TProduto *novo = produto(999, "Produto Reutilizado", "Geral", 30, 99.90);
inserirHashProduto(novo, gavetas, dadosHash);
free(novo);

/* Busca do novo produto */
if (buscarHashProduto(999, gavetas, dadosHash, &reg)) {
    printf("Espaco livre reutilizado com sucesso.\n");
    imprimeRegHashProduto(&reg);
}

fclose(gavetas);
fclose(dadosHash);

printf("\nOperacoes concluidas com sucesso.\n");
return 0;
}