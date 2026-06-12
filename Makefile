# Variáveis de compilação
CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ = main.o Cliente.o FuncionariosSM.o Produtos.o Busca.o OrdenacaoDisco.o Particoes.o
EXEC = sistema_supermercado

# Pastas de saída
DIRS = dados particoes logs

# Regra principal: cria pastas e gera o executável
all: $(DIRS) $(EXEC)

# Cria as pastas se não existirem
$(DIRS):
	mkdir -p $(DIRS)

# Linkagem
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) -lm

# Compilação dos módulos
main.o: main.c Cliente.h FuncionariosSM.h Produtos.h Busca.h OrdenacaoDisco.h Particoes.h
	$(CC) $(CFLAGS) -c main.c

Cliente.o: Cliente.c Cliente.h
	$(CC) $(CFLAGS) -c Cliente.c

FuncionariosSM.o: FuncionariosSM.c FuncionariosSM.h
	$(CC) $(CFLAGS) -c FuncionariosSM.c

Produtos.o: Produtos.c Produtos.h
	$(CC) $(CFLAGS) -c Produtos.c

Busca.o: Busca.c Busca.h FuncionariosSM.h Cliente.h Produtos.h
	$(CC) $(CFLAGS) -c Busca.c

OrdenacaoDisco.o: OrdenacaoDisco.c OrdenacaoDisco.h Produtos.h
	$(CC) $(CFLAGS) -c OrdenacaoDisco.c

Particoes.o: Particoes.c Particoes.h Produtos.h
	$(CC) $(CFLAGS) -c Particoes.c

# Limpeza completa
clean:
	rm -f *.o $(EXEC)
	rm -f dados/*.dat
	rm -f particoes/*.dat
	rm -f logs/*.txt

# Executa o programa
run: all
	./$(EXEC)