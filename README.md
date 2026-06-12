# Sistema de Gerenciamento de Supermercado

Este projeto consiste em um sistema desenvolvido em linguagem C para a gestão de funcionários, clientes e produtos. O software utiliza arquivos binários para garantir que os dados sejam armazenados de forma persistente entre as execuções.

---

### Funcionalidades Principais

* **Persistência de Dados**: Armazenamento de registros de funcionários, clientes e produtos em arquivos `.dat` dentro da pasta `dados/`.
* **Impressão de Dados**: Funções dedicadas para exibir as informações completas de cada entidade (código, nome, CPF, estoque, preço, etc.) no terminal, facilitando a visualização e auditoria do sistema.
* **Remoção de Registros**: O sistema permite a liberação de memória dos objetos carregados (RAM), garantindo uma gestão eficiente dos recursos durante a execução do programa.
* **Busca Binária**: Implementada para a localização otimizada de produtos através de seus códigos de identificação, reduzindo o número de comparações necessárias.
* **Busca Sequencial**: Utilizada para localizar funcionários e clientes na base de dados através de chaves primárias ou CPF.
* **Ordenação em Disco**: Implementação do algoritmo Selection Sort diretamente sobre arquivos binários, permitindo ordenar bases de dados sem carregar todos os registros na memória RAM simultaneamente.
* **Geração de Partições Ordenadas**: Implementação do método de Seleção por Substituição, que divide um arquivo grande em partições menores já ordenadas internamente, armazenadas na pasta `particoes/`.

---

### Estrutura do Projeto
sistema_supermercado/

├── main.c

├── Makefile

│

├── Cliente.c / Cliente.h

├── FuncionariosSM.c / FuncionariosSM.h

├── Produtos.c / Produtos.h

├── Busca.c / Busca.h

├── OrdenacaoDisco.c / OrdenacaoDisco.h

├── Particoes.c / Particoes.h

│

├── dados/

│   ├── funcionarios.dat

│   ├── clientes.dat

│   └── produtos.dat

│

├── pparticoes/

│   ├── part1.dat

│   ├── part2.dat

│   └── ...

│

└── logs/

├── log_1000.txt

├── log_10000.txt

├── log_100000.txt

└── log_500000.txt

---

### Módulos

* **FuncionariosSM**: Gestão de dados de colaboradores, incluindo cargo e salário.
* **Cliente**: Gestão de informações cadastrais de clientes e CPF.
* **Produtos**: Gestão de inventário, categorias e controle de preços.
* **Busca**: Módulo centralizador dos algoritmos de busca sequencial e binária.
* **OrdenacaoDisco**: Ordenação de registros diretamente em arquivo binário via Selection Sort, sem necessidade de carregar toda a base em memória.
* **Particoes**: Geração de partições ordenadas via Seleção por Substituição, utilizando um buffer configurável em RAM para processar bases de grande volume.

---

### Como Compilar e Executar

O projeto utiliza um Makefile para automatizar o processo de construção, criação de pastas e linkagem dos módulos. Certifique-se de ter o compilador GCC e a ferramenta Make instalados.

1. Para compilar todos os módulos, criar as pastas necessárias e executar: make run
2. Para apenas compilar: make
3. Para remover arquivos objeto, executável e todos os arquivos gerados: make clean

