#include <stdio.h>
#include <stdlib.h>
#include "FuncionariosSM.h"
#include "Cliente.h"
#include "Produtos.h"
#include "Busca.h"

int main() {
    // Usar "wb+" para criar bases limpas (ou "ab+" para continuar de onde parou)
    FILE *arqFunc = fopen("funcionarios.dat", "wb+");
    FILE *arqCli  = fopen("clientes.dat", "wb+");
    FILE *arqProd = fopen("produtos.dat", "wb+");

    if (!arqFunc || !arqCli || !arqProd) return 1;

    // --- 1. POPULANDO BASES (100 itens cada) ---
    for (int i = 1; i <= 100; i++) {
        char buffer[50];
        
        // Funcionarios
        sprintf(buffer, "Funcionario %d", i);
        TFunc *f = funcionario(i, buffer, "000.000.000-00", "01/01/1990", "Operacional", 2000.0);
        salva(f, arqFunc);
        free(f);

        // Clientes
        sprintf(buffer, "Cliente %d", i);
        TCliente *c = cliente(buffer, "111.111.111-11", "9999-9999");
        salvacli(c, arqCli);
        free(c);

        // Produtos
        sprintf(buffer, "Produto %d", i);
        TProduto *p = produto(i, buffer, "Geral", 50, 10.0);
        salvarpro(p, arqProd);
        free(p);
    }

    // --- 2. TESTE DE ATUALIZAÇÃO EM MASSA (Exemplo: Alterar item 50) ---
    
    // Atualizando Produto 50
    TProduto *pBusca = buscaBinariaProd(50, arqProd, 100);
    if (pBusca) {
        mudarpreço(pBusca, 99.9);
        fseek(arqProd, (50 - 1) * sizeof(TProduto), SEEK_SET);
        salvarpro(pBusca, arqProd);
        free(pBusca);
    }

    // --- 3. REMOÇÃO DE UM ITEM ---
    // (Lembre-se que em arquivos binários, remover é complexo; 
    // geralmente marca-se o registro como "removido" ou copia-se o arquivo sem ele)
    
    fclose(arqFunc);
    fclose(arqCli);
    fclose(arqProd);
    
    printf("Operacoes concluidas com sucesso.\n");
    return 0;
}