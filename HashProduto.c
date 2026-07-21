#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashProduto.h"

/* ---------- funcoes auxiliares de baixo nivel (int / registro) ---------- */

static void escreveGaveta(FILE *gavetas, int indice, int valor) {
    fseek(gavetas, indice * sizeof(int), SEEK_SET);
    fwrite(&valor, sizeof(int), 1, gavetas);
}

static int leGaveta(FILE *gavetas, int indice) {
    int valor;
    fseek(gavetas, indice * sizeof(int), SEEK_SET);
    fread(&valor, sizeof(int), 1, gavetas);
    return valor;
}

static void escreveRegistro(FILE *dados, int pos, TRegHashProduto *reg) {
    fseek(dados, (long) pos * sizeof(TRegHashProduto), SEEK_SET);
    fwrite(reg, sizeof(TRegHashProduto), 1, dados);
}

static int leRegistro(FILE *dados, int pos, TRegHashProduto *reg) {
    fseek(dados, (long) pos * sizeof(TRegHashProduto), SEEK_SET);
    return fread(reg, sizeof(TRegHashProduto), 1, dados) == 1;
}

/* posicao logo apos o ultimo registro do arquivo (para insercao no "fim") */
static int totalRegistros(FILE *dados) {
    fseek(dados, 0, SEEK_END);
    long bytes = ftell(dados);
    return (int) (bytes / sizeof(TRegHashProduto));
}

/* ---------------------------- API publica -------------------------------- */

void inicializaHashProduto(char *arqGavetas) {
    FILE *f = fopen(arqGavetas, "wb");
    if (!f) return;
    int vazio = -1;
    /* TAM_HASH gavetas de encadeamento + 1 gaveta extra p/ lista de livres */
    for (int i = 0; i <= POS_LIVRE; i++) {
        fwrite(&vazio, sizeof(int), 1, f);
    }
    fclose(f);
}

int funcaoHashProduto(int cod) {
    if (cod < 0) cod = -cod;
    return cod % TAM_HASH;   /* metodo da divisao */
}

int buscarHashProduto(int cod, FILE *gavetas, FILE *dados, TRegHashProduto *reg) {
    int h = funcaoHashProduto(cod);
    int pos = leGaveta(gavetas, h);

    while (pos != -1) {
        if (!leRegistro(dados, pos, reg)) return 0;
        if (reg->ocupado && reg->cod == cod) {
            return 1;
        }
        pos = reg->prox;
    }
    return 0;
}

int inserirHashProduto(TProduto *p, FILE *gavetas, FILE *dados) {
    TRegHashProduto existente;
    if (buscarHashProduto(p->cod, gavetas, dados, &existente)) {
        return 0; /* chave duplicada */
    }

    int h = funcaoHashProduto(p->cod);

    /* 1) obtem uma posicao livre: reaproveita da lista de livres, senao usa o fim do arquivo */
    int topoLivre = leGaveta(gavetas, POS_LIVRE);
    int posNova;
    if (topoLivre != -1) {
        TRegHashProduto livre;
        leRegistro(dados, topoLivre, &livre);
        posNova = topoLivre;
        escreveGaveta(gavetas, POS_LIVRE, livre.prox); /* lista de livres avanca */
    } else {
        posNova = totalRegistros(dados);
    }

    /* 2) monta o novo registro e o encadeia na frente da gaveta h */
    TRegHashProduto novo;
    memset(&novo, 0, sizeof(TRegHashProduto));
    novo.cod = p->cod;
    strncpy(novo.nome, p->nome, sizeof(novo.nome) - 1);
    strncpy(novo.categoria, p->categoria, sizeof(novo.categoria) - 1);
    novo.estoque = p->estoque;
    novo.preco   = p->preço;
    novo.ocupado = 1;
    novo.prox    = leGaveta(gavetas, h);   /* aponta para o antigo inicio da gaveta */

    escreveRegistro(dados, posNova, &novo);
    escreveGaveta(gavetas, h, posNova);    /* gaveta passa a apontar para o novo registro */

    return 1;
}

int removerHashProduto(int cod, FILE *gavetas, FILE *dados) {
    int h = funcaoHashProduto(cod);
    int posAnterior = -1;
    int posAtual = leGaveta(gavetas, h);
    TRegHashProduto reg;

    while (posAtual != -1) {
        if (!leRegistro(dados, posAtual, &reg)) return 0;

        if (reg.ocupado && reg.cod == cod) {
            /* desencadeia o registro da lista da gaveta */
            if (posAnterior == -1) {
                escreveGaveta(gavetas, h, reg.prox);
            } else {
                TRegHashProduto anterior;
                leRegistro(dados, posAnterior, &anterior);
                anterior.prox = reg.prox;
                escreveRegistro(dados, posAnterior, &anterior);
            }

            /* gerenciamento de espaco: devolve a posicao para a lista de livres */
            reg.ocupado = 0;
            reg.prox = leGaveta(gavetas, POS_LIVRE);
            escreveRegistro(dados, posAtual, &reg);
            escreveGaveta(gavetas, POS_LIVRE, posAtual);

            return 1;
        }
        posAnterior = posAtual;
        posAtual = reg.prox;
    }
    return 0; /* nao encontrado */
}

void imprimeRegHashProduto(TRegHashProduto *reg) {
    printf("**********************************************");
    printf("\nCodigo do Produto: %d", reg->cod);
    printf("\nNome: %s", reg->nome);
    printf("\nCategoria: %s", reg->categoria);
    printf("\nEstoque Atual: %d", reg->estoque);
    printf("\nPreco: %4.2f", reg->preco);
    printf("\n**********************************************\n");
}