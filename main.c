#include <stdio.h>
#include <stdlib.h>
#include "FuncionariosSM.h"
#include "Cliente.h"
#include "Produtos.h"
#include "Busca.h"

int main() {
    // Abertura das bases
    FILE *arqFunc = fopen("funcionarios.dat", "wb+");
    FILE *arqCli  = fopen("clientes.dat", "wb+");
    FILE *arqProd = fopen("produtos.dat", "wb+");

    // --- 1. FUNCIONARIOS ---
    TFunc *f = funcionario(10, "Carlos Gerente", "111.111.111-11", "01/01/80", "Gerente", 5000.0);
    salva(f, arqFunc);
    
    TFunc *fBusca = buscaSequencialFunc(10, arqFunc);
    if(fBusca) {
        mudarTrabalho(fBusca, "Diretor", 8000.0);
        imprime(fBusca);
        removerfunc(fBusca); // Usa a função de remoção
    }
    free(f); // Libera o original

    // --- 2. CLIENTES ---
    TCliente *c = cliente("Joao Silva", "123.456.789-00", "9999-8888");
    salvacli(c, arqCli);
    
    TCliente *cBusca = buscaSequencialCli("123.456.789-00", arqCli);
    if(cBusca) {
        imprimecli(cBusca);
        removercli(cBusca); 
    }
    free(c);

    // --- 3. PRODUTOS ---
    TProduto *p = produto(200, "Teclado", "Informatica", 10, 150.0);
    salvarpro(p, arqProd);
    
    TProduto *pBusca = buscaBinariaProd(200, arqProd, 1);
    if(pBusca) {
        mudarpreço(pBusca, 140.0); 
        mudarestoque(pBusca, 9);    
        
        // Persistência: Atualiza o arquivo
        fseek(arqProd, -sizeof(TProduto), SEEK_CUR);
        salvarpro(pBusca, arqProd);
        
        imprimepro(pBusca);
        removerpro(pBusca);
    }
    free(p);

    fclose(arqFunc);
    fclose(arqCli);
    fclose(arqProd);
    return 0;
}