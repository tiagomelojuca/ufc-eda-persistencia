# ufc-eda-persistencia
O presente projeto foi desenvolvido para a cadeira de Estrutura de Dados Avançada da Universidade Federal do Ceará. Consiste na implementação de uma Árvore Binária de Busca enquanto Estrutura de Dados Persistente. Em particular, foi utilizada Persistencia Parcial, conforme requisito da especificação.

## Equipe
- Tiago Melo Jucá
- Rafael de Paiva Lima Filho
- Lucas Cabral Amador Mourao

## Build
Assim como a maioria dos projetos C++, utilizamos CMake, um meta-build system capaz de gerar o projeto para diferentes build systems (MAKE, ninja, Visual Studio etc). É necessário no mínimo a versão 3.24, conforme especificado no arquivo de orquestração. A utilização exata depende da configuração do ambiente, mas, em linhas gerais, não foge do exemplo abaixo, utilizado o generator do Visual Studio 2022:  
`cd C:\raiz\do\repositorio`  
`cmake -S . -B out`  
`cmake --build out --config RelWithDebInfo --target install`  

Exemplo com a toolchain do projeto GNU (gcc + make):  
`cd C:\raiz\do\repositorio`  
`cmake -S . -B out -G "MinGW Makefiles"`  
`cmake --build out --target install`  

Note que é necessário um compilador com suporte pelo menos ao standard de 2014 (as versões mais recentes de gcc, clang e msvc funcionam sem problemas). A instalação será gerada em **out/exeobj_cmake**, contendo uma ferramenta para interação cli e uma suíte de testes unitários.

## Execução
O binário `cli` gerado na pasta de instalação do CMake pode ser utilizado com a seguinte sintaxe:  
`./cli [arquivo_entrada] [arquivo_saida]`  
  
O arquivo de entrada especifica a rotina a ser executada, cujos resultados são impressos no arquivo de saída. O instrumentador ignora linhas em branco, linhas com instruções inválidas e linhas com número de argumentos não condizentes com a especificação (vide `SPEC.md`).

> **⚠️ AVISO**
> 
> Não foi implementada verificação de sobrescrita para arquivos já existentes, então recomenda-se cautela para não inverter a ordem dos argumentos, pois isso geraria a sobrescrita com uma saída potencialmente vazia.

## Créditos
- **gtest:** framework do Google para testes unitários em C++
