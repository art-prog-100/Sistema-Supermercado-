# Sistema de Gerenciamento de Supermercado

Este projeto consiste em um sistema desenvolvido em linguagem C para a gestão de funcionários, clientes e produtos. O software utiliza arquivos binários para garantir que os dados sejam armazenados de forma persistente entre as execuções.

### Funcionalidades Principais

* **Persistência de Dados**: Armazenamento de registros de funcionários, clientes e produtos em arquivos com extensão .dat.
* **Impressão de Dados**: Funções dedicadas para exibir as informações completas de cada entidade (código, nome, CPF, estoque, preço, etc.) no terminal, facilitando a visualização e auditoria do sistema.
* **Remoção de Registros**: O sistema permite a liberação de memória dos objetos carregados (RAM), garantindo uma gestão eficiente dos recursos durante a execução do programa.
* **Busca Binária**: Implementada para a localização otimizada de produtos através de seus códigos de identificação, reduzindo o número de comparações necessárias.
* **Busca Sequencial**: Utilizada para localizar funcionários e clientes na base de dados através de chaves primárias ou CPF.

### Como Compilar e Executar

O projeto utiliza um Makefile para automatizar o processo de construção e linkagem dos múltiplos módulos. Certifique-se de ter o compilador GCC e a ferramenta Make instalados em seu ambiente.

1. Para compilar todos os módulos e rodar os testes integrados:
   make run

2. Para remover os arquivos objetos (.o), o executável e limpar os arquivos de dados (.dat):
   make clean

### Estrutura do Projeto

* **FuncionariosSM**: Gestão de dados de colaboradores, incluindo cargo e salário.
* **Cliente**: Gestão de informações cadastrais de clientes e CPF.
* **Produtos**: Gestão de inventário, categorias e controle de preços.
* **Busca**: Módulo centralizador dos algoritmos de busca sequencial e binária.
