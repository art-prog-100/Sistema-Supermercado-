#include "Testes.h"
#include "Particoes.h"

// Embaralha um array de inteiros (Fisher-Yates)
static void embaralha(int *arr, int n) {
    int i, j, temp;
    srand(time(NULL));
    for (i = n - 1; i > 0; i--) {
        j = rand() % (i + 1);
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void geraBaseDesordenada(const char *nomeArquivo, int tamanho) {
    int i;
    char buffer[50];
    FILE *arq;
    TProduto *prod;

    // cria array de cod sequenciais e embaralha
    int *cods = (int *) malloc(tamanho * sizeof(int));
    if (!cods) {
        printf("Erro ao alocar memoria\n");
        return;
    }

    for (i = 0; i < tamanho; i++)
        cods[i] = i + 1;

    embaralha(cods, tamanho);

    arq = fopen(nomeArquivo, "wb");
    if (!arq) {
        printf("Erro ao abrir arquivo %s\n", nomeArquivo);
        free(cods);
        return;
    }

    for (i = 0; i < tamanho; i++) {
        sprintf(buffer, "Produto %d", cods[i]);
        prod = produto(cods[i], buffer, "Geral", 50, 10.0);
        salvarpro(prod, arq);
        free(prod);
    }

    fclose(arq);
    free(cods);

    printf("Base desordenada gerada: %s (%d registros)\n", nomeArquivo, tamanho);
}

void testaOrdenacaoDisco(int tamanho) {
    char nomeArq[100];
    char nomeLog[100];
    clock_t inicio, fim;
    double tempo;
    FILE *log;
    int ordenado;

    sprintf(nomeArq, "dados/produtos_%d.dat", tamanho);
    sprintf(nomeLog, "logs/log_disco_%d.txt", tamanho);

    // gera base desordenada
    geraBaseDesordenada(nomeArq, tamanho);

    // mede tempo da ordenação
    inicio = clock();
    ordenacaoSelecaoDisco(nomeArq, tamanho);
    fim = clock();

    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    ordenado = arquivoEstaOrdenado(nomeArq, tamanho);

    // grava log
    log = fopen(nomeLog, "w");
    if (log) {
        fprintf(log, "=== TESTE ORDENACAO EM DISCO ===\n");
        fprintf(log, "Metodo: Selection Sort em Disco\n");
        fprintf(log, "Tamanho da base: %d registros\n", tamanho);
        fprintf(log, "Tempo gasto: %.6f segundos\n", tempo);
        fprintf(log, "Arquivo ordenado: %s\n", ordenado ? "SIM" : "NAO");
        fclose(log);
    }

    printf("[Disco] Tamanho: %d | Tempo: %.6fs | Ordenado: %s\n",
           tamanho, tempo, ordenado ? "SIM" : "NAO");
}

void testaParticoesIntercalacao(int tamanho) {
    char nomeArq[100];
    char nomeArqFinal[100];
    char nomeLog[100];
    clock_t inicio, fim;
    double tempoParticoes, tempoIntercalacao;
    FILE *log;
    int ordenado;

    sprintf(nomeArq, "dados/produtos_%d.dat", tamanho);
    sprintf(nomeArqFinal, "dados/produtos_%d_final.dat", tamanho);
    sprintf(nomeLog, "logs/log_particoes_%d.txt", tamanho);

    // gera base desordenada
    geraBaseDesordenada(nomeArq, tamanho);

    // mede tempo da geração de partições
    inicio = clock();
    int numParticoes = geraParticoes(nomeArq, tamanho, TAM_BUFFER);
    fim = clock();
    tempoParticoes = (double)(fim - inicio) / CLOCKS_PER_SEC;

    // mede tempo da intercalação
    inicio = clock();
    intercalaParticoes(nomeArqFinal, numParticoes);
    fim = clock();
    tempoIntercalacao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    ordenado = arquivoEstaOrdenado(nomeArqFinal, tamanho);

    // grava log
    log = fopen(nomeLog, "w");
    if (log) {
        fprintf(log, "=== TESTE PARTICOES + INTERCALACAO ===\n");
        fprintf(log, "Metodo geração: Seleção por Substituição\n");
        fprintf(log, "Metodo intercalação: Árvore Binária de Vencedores\n");
        fprintf(log, "Tamanho da base: %d registros\n", tamanho);
        fprintf(log, "Partições geradas: %d\n", numParticoes);
        fprintf(log, "Tempo geração de partições: %.6f segundos\n", tempoParticoes);
        fprintf(log, "Tempo intercalação: %.6f segundos\n", tempoIntercalacao);
        fprintf(log, "Tempo total: %.6f segundos\n", tempoParticoes + tempoIntercalacao);
        fprintf(log, "Arquivo ordenado: %s\n", ordenado ? "SIM" : "NAO");
        fclose(log);
    }

    printf("[Particoes+Intercalacao] Tamanho: %d | Tempo total: %.6fs | Ordenado: %s\n",
           tamanho, tempoParticoes + tempoIntercalacao, ordenado ? "SIM" : "NAO");
}

void executaTodos() {
    int i;
    printf("\n=== INICIANDO TESTES ===\n\n");

    for (i = 0; i < NUM_TESTES; i++) {
        printf("--- Tamanho: %d ---\n", TAMANHOS[i]);
        testaOrdenacaoDisco(TAMANHOS[i]);
        testaParticoesIntercalacao(TAMANHOS[i]);
        printf("\n");
    }

    printf("=== TESTES CONCLUIDOS ===\n");
    printf("Logs gravados em logs/\n");
}