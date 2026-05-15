#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "FuncionariosSM.h"
#include "Cliente.h"
#include "Produtos.h"
#include "Busca.h"

int main() {
    // 1. Abertura de arquivos separados para cada base de dados
    FILE *arqFunc = fopen("funcionarios.dat", "wb+");
    FILE *arqCli  = fopen("clientes.dat", "wb+");
    FILE *arqProd = fopen("produtos.dat", "wb+");

    if (!arqFunc || !arqCli || !arqProd) {
        printf("Erro ao abrir as bases de dados!\n");
        return 1;
    }

    printf("=== SISTEMA DE SUPERMERCADO - TESTE INTEGRADO ===\n\n");

    // --- 2. POVOAMENTO DAS BASES ---
    printf(">> Povoando bases de dados...\n");
    
    // Funcionários
    TFunc *f1 = funcionario(10, "Carlos Gerente", "111.111.111-11", "01/01/1980", "Gerente", 5000.0);
    TFunc *f2 = funcionario(20, "Ana Caixa", "222.222.222-22", "02/02/1990", "Caixa", 2000.0);
    salva(f1, arqFunc);
    salva(f2, arqFunc);

    // Clientes
    TCliente *c1 = cliente("Marcos Silva", "123.456.789-00", "9999-0000");
    salvacli(c1, arqCli);

    // Produtos 
    TProduto *p1 = produto(100, "Feijao 1kg", "Alimentos", 50, 8.50);
    TProduto *p2 = produto(200, "Arroz 5kg", "Alimentos", 30, 25.00);
    salvarpro(p1, arqProd);
    salvarpro(p2, arqProd);

    // Descarrega os buffers para o disco
    fflush(arqFunc); fflush(arqCli); fflush(arqProd);

    // --- 3. TESTE DE BUSCAS E PERFORMANCE ---
    printf("\n=== TESTE DE BUSCAS E PERFORMANCE ===\n");

    // Busca Sequencial em Funcionários
    printf("\nBuscando Funcionario codigo 20 (Sequencial):");
    TFunc *f_encontrado = buscaSequencialFunc(20, arqFunc);
    if (f_encontrado) {
        imprime(f_encontrado);
        free(f_encontrado);
    }

    // Busca Binária em Produtos
    printf("\nBuscando Produto codigo 200 (Binaria):");
    // o fseek le o arquivo de produtos que só contém TProduto
    TProduto *p_encontrado = buscaBinariaProd(200, arqProd, 2); 
    if (p_encontrado) {
        imprimepro(p_encontrado);
        free(p_encontrado);
    }

    // --- 4. OPERAÇÃO DE INTERAÇÃO (VENDA) ---
    printf("\n\n=== OPERAÇÃO DE INTERAÇÃO: VENDA E ATUALIZAÇÃO ===\n");
    
    // Busca o cliente no arquivo de clientes e o produto no de produtos
    TCliente *cli_venda = buscaSequencialCli("123.456.789-00", arqCli);
    TProduto *prod_venda = buscaBinariaProd(200, arqProd, 2);

    if (cli_venda && prod_venda) {
        printf("\nSUCESSO: Cliente %s localizado.", cli_venda->nome);
        printf("\nSUCESSO: Produto %s localizado.", prod_venda->nome);
        
        printf("\nEfetuando venda de 1 unidade...");
        mudarestoque(prod_venda, prod_venda->estoque - 1);
        
        printf("\nNovo estoque de %s: %d\n", prod_venda->nome, prod_venda->estoque);
    } else {
        printf("\nERRO: Cliente ou Produto nao encontrado para a venda.\n");
    }

    // --- 5. LIMPEZA FINAL ---
    printf("\n>> Finalizando programa e limpando memoria...\n");
    free(f1); free(f2);
    free(c1);
    free(p1); free(p2);
    if(cli_venda) free(cli_venda);
    if(prod_venda) free(prod_venda);

    fclose(arqFunc);
    fclose(arqCli);
    fclose(arqProd);

    return 0;
}