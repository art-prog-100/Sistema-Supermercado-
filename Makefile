# Variáveis de compilação
CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ = main.o Cliente.o FuncionariosSM.o Produtos.o Busca.o
EXEC = sistema_supermercado

# Regra principal: Gera o executável
all: $(EXEC)

# Linkagem: Une todos os arquivos objeto (.o) no executável final
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) -lm

# Compilação dos módulos individuais para arquivos objeto
main.o: main.c Cliente.h FuncionariosSM.h Produtos.h Busca.h
	$(CC) $(CFLAGS) -c main.c

Cliente.o: Cliente.c Cliente.h
	$(CC) $(CFLAGS) -c Cliente.c

FuncionariosSM.o: FuncionariosSM.c FuncionariosSM.h
	$(CC) $(CFLAGS) -c FuncionariosSM.c

Produtos.o: Produtos.c Produtos.h
	$(CC) $(CFLAGS) -c Produtos.c

Busca.o: Busca.c Busca.h FuncionariosSM.h Cliente.h Produtos.h
	$(CC) $(CFLAGS) -c Busca.c

# Limpeza: Remove os arquivos temporários e o executável
clean:
	rm -f *.o $(EXEC)
	rm -f *.dat

# Executa o programa
run: all
	./$(EXEC)

