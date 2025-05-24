# ufc-eda-persistencia
O presente projeto foi desenvolvido para a cadeira de Estrutura de Dados Avançada da Universidade Federal do Ceará. Consiste na implementação de uma Árvore Binária de Busca enquanto Estrutura de Dados Persistente. Em particular, foi utilizada Persistencia Parcial, conforme requisito da especificação.

## Build
Assim como a maioria dos projetos C++, utilizamos CMake, um meta-build system capaz de gerar o projeto para diferentes build systems (MAKE, ninja, Visual Studio etc). A utilização exata depende da configuração do ambiente, mas em linhas gerais não foge do exemplo abaixo, utilizado o generator do Visual Studio 2022:  
`cd C:\raiz\do\repositorio`  
`cmake -S . -B out`  
`cmake --build out --config RelWithDebInfo --target install`  
  
A instalação será gerada em out/exeobj_cmake

## Créditos
- gtest: framework do Google para testes unitários em C++
