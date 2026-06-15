# Sistema de Gerenciamento de Supermercado

Projeto desenvolvido em C para a disciplina de Algoritmos e Estruturas de Dados II (AEDII). Implementa um sistema completo de gestão de funcionários, clientes e produtos, com persistência em arquivos binários, algoritmos de busca, ordenação em disco e intercalação de partições.

---

## Funcionalidades Principais

- **Persistência de Dados**: Registros de funcionários, clientes e produtos armazenados em arquivos `.dat` na pasta `dados/`.
- **Leitura e Impressão**: Funções dedicadas para exibir no terminal as informações completas de cada entidade (código, nome, CPF, estoque, preço, etc.).
- **Atualização de Registros**: Alteração de cargo/salário de funcionários, preço e estoque de produtos diretamente no arquivo binário.
- **Remoção de Registros**: Liberação segura de memória (RAM) dos objetos carregados, zerando o ponteiro original do chamador.
- **Busca Sequencial**: Localização de funcionários (por código), clientes (por CPF) e produtos (por código) percorrendo o arquivo registro a registro.
- **Busca Binária**: Localização otimizada de funcionários e produtos por código, com divisão logarítmica do espaço de busca — exige base ordenada.
- **Ordenação em Disco**: Algoritmo Selection Sort aplicado diretamente sobre o arquivo binário, sem carregar toda a base em memória RAM.
- **Geração de Partições Ordenadas**: Método de Seleção por Substituição — divide um arquivo grande em partições menores já ordenadas internamente, armazenadas em `particoes/`.
- **Intercalação por Árvore de Vencedores**: Combina as partições geradas em um único arquivo final ordenado usando uma árvore binária de vencedores.
- **Suite de Testes Automatizados**: Executa e cronometra os algoritmos de ordenação e intercalação para bases de 1 000, 10 000, 100 000 e 500 000 registros, gravando logs em `logs/`.

---

## Estrutura do Projeto

```
sistema_supermercado/
├── main.c
├── Makefile
│
├── Cliente.c / Cliente.h           — Cadastro e operações de clientes
├── FuncionariosSM.c / FuncionariosSM.h  — Cadastro e operações de funcionários
├── Produtos.c / Produtos.h         — Cadastro e operações de produtos
├── Busca.c / Busca.h               — Algoritmos de busca sequencial e binária
├── OrdenacaoDisco.c / OrdenacaoDisco.h  — Selection Sort direto em arquivo
├── Particoes.c / Particoes.h       — Geração de partições (Seleção por Substituição)
├── Intercalacao.c / Intercalacao.h — Intercalação por Árvore de Vencedores
├── Testes.c / Testes.h             — Suite de testes e benchmarks automáticos
│
├── dados/
│   ├── funcionarios.dat
│   ├── clientes.dat
│   ├── produtos.dat
│   ├── produtos_final.dat
│   └── produtos_<N>.dat / produtos_<N>_final.dat  (gerados pelos testes)
│
├── particoes/
│   ├── part1.dat
│   ├── part2.dat
│   └── ...
│
└── logs/
    ├── log_disco_1000.txt
    ├── log_particoes_1000.txt
    └── ...
```

---

## Módulos

| Arquivo | Responsabilidade |
|---|---|
| `FuncionariosSM` | Criação, leitura, impressão, atualização de cargo/salário e remoção de funcionários |
| `Cliente` | Criação, leitura, impressão e remoção de clientes |
| `Produtos` | Criação, leitura, impressão, atualização de preço/estoque e remoção de produtos |
| `Busca` | Busca sequencial (Func, Cli, Prod) e busca binária (Func, Prod) |
| `OrdenacaoDisco` | Selection Sort em arquivo binário e verificação de ordenação |
| `Particoes` | Geração de partições ordenadas via Seleção por Substituição; retorna o número de partições geradas |
| `Intercalacao` | Intercalação de N partições em arquivo final usando Árvore de Vencedores |
| `Testes` | Geração de bases desordenadas, benchmark dos algoritmos e gravação de logs |

---

## Como Compilar e Executar

Pré-requisitos: GCC e Make instalados.

```bash
# Compilar, criar pastas e executar:
make run

# Apenas compilar:
make

# Remover arquivos objeto, executável e dados gerados:
make clean
```

> **Atenção**: A suite de testes (`executaTodos()`) processa bases de até 500 000 registros. A etapa de Selection Sort para 500 000 elementos pode levar vários minutos, pois trata-se de um algoritmo O(n²) operando sobre disco.

---

## Fluxo do main.c

1. Abre/cria as bases binárias em `dados/`
2. Popula cada base com 100 registros
3. Lê e imprime o primeiro funcionário e o primeiro cliente usando `le()` / `lecli()`
4. Busca sequencial de funcionário (cod=42) — demonstra `buscaSequencialFunc()`
5. Busca binária de funcionário (cod=75) — demonstra `buscaBinariaFunc()`
6. Busca sequencial de cliente por CPF — demonstra `buscaSequencialCli()`
7. Busca sequencial de produto (cod=10) — demonstra `buscaSequencialProd()`
8. Busca binária de produto (cod=50) + alteração de preço — demonstra `buscaBinariaProd()` e `mudarpreço()`
9. Alteração de estoque do produto 20 — demonstra `mudarestoque()`
10. Alteração de cargo/salário do funcionário 5 — demonstra `mudarTrabalho()`
11. Remoção de um funcionário, cliente e produto da memória — demonstra `removerfunc()`, `removercli()`, `removerpro()`
12. Ordenação do arquivo de produtos em disco — demonstra `ordenacaoSelecaoDisco()`
13. Geração de partições + intercalação — demonstra `geraParticoes()` e `intercalaParticoes()`
14. Suite completa de testes e benchmarks — demonstra `executaTodos()`