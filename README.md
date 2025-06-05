# ufc-eda-persistencia
O presente projeto foi desenvolvido para a cadeira de Estrutura de Dados Avançada da Universidade Federal do Ceará. Consiste na implementação de uma Árvore Binária de Busca enquanto Estrutura de Dados Persistente. Em particular, foi utilizada Persistencia Parcial, conforme requisito da especificação.

## Equipe
- Tiago Melo Jucá
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

Note que é necessário um compilador com suporte pelo menos ao standard de 2017 (as versões mais recentes de gcc, clang e msvc funcionam sem problemas). A instalação será gerada em **out/exeobj_cmake**, contendo uma ferramenta para interação cli e uma suíte de testes unitários. É possível desligar a construção dos testes unitários no momento da geração do projeto por meio da flag `BUILD_UNIT_TESTS`, prevista no arquivo de especificação do projeto `CMakeLists.txt`, e com isso diminuindo o requisito do compilador para suporte a C++14 ou superior (a necessidade de C++17 é devido ao framework `googletest`).

## Execução
O binário `cli` gerado na pasta de instalação do CMake pode ser utilizado com a seguinte sintaxe:  
`./cli [arquivo_entrada] [arquivo_saida]`  
  
O arquivo de entrada especifica a rotina a ser executada, cujos resultados são impressos no arquivo de saída. O instrumentador ignora linhas em branco, linhas com instruções inválidas e linhas com número de argumentos não condizentes com a especificação (vide `SPEC.md`).

> **⚠️ AVISO**
> 
> Não foi implementada verificação de sobrescrita para arquivos já existentes, então recomenda-se cautela para não inverter a ordem dos argumentos, pois isso geraria a sobrescrita com uma saída potencialmente vazia.

## Estrutura
O projeto foi dividido em módulos, de forma a separar a implementação da ABB persistente (regra de negócio propriamente dita) dos demais arquivos que não são o objeto de estudo principal (ruído, basicamente). A estrutura de dados fica isolada e agnóstica em relação ao uso. O arquivo `main.cpp` atua como ponto de entrada do programa, apenas redirecionando as responsabilidades ao consumir as classes explicitadas abaixo:  
  
### persistencia
Módulo principal, onde pode ser encontrada a estrutura de dados persistente propriamente dita  
  
- `abb.h`: Árvore Binária de Busca persistente com suporte a inclusão, remoção, verificação de sucessor, verificação de profundidade, verificação da última versão criada e visita em ordem dos nós

### io
Módulo onde ficam as classes e funções relacionadas a e/s  
  
- `arg_parser.h`: classe responsável pela validação da entrada do usuário na linha de comando (ex.: a quantidade de argumentos está correta? a extensão dos arquivos é válida? senão, qual o erro?)
- `file_parser.h`: realiza a leitura do arquivo de entrada fornecido pelo usuário e interpreta as instruções contidas nele, convertendo-as para um formato estruturado (vide `operacao.h`) que serão executadas pelo instrumentador (vide `executor.h`)
- `file_writer.h`: realiza a escrita em arquivo das operações
- `operacao.h`: abstração das possíveis instruções e parâmetros que o usuário pode fornecer no arquivo de entrada
- `executor.h`: instrumenta a execução sequencial das operações lidas do arquivo de entrada
- `utils.h`: funções de uso geral

### testes
Módulo onde ficam os testes unitários escritos no framework `googletest` para validar as implementações supracitadas. Para não ser redundante em relação à seção acima, é suficiente dizer que o arquivo `foo_test.cpp` se refere aos testes unitários da classe `foo.h`. Informações mais específicas podem ser encontradas nos comentários e títulos de cada Test Case, se for de interesse.

## Créditos
- **gtest:** framework do Google para testes unitários em C++ [BSD]
