### Descrição geral do trabalho:

O objetivo do trabalho é implementar uma árvore binária de busca com persistência parcial seguindo o método descrito em sala. A entrada do programa é um arquivo de texto com várias operações sobre a estrutura (uma por linha) e a saída será um arquivo de texto com o resultado das operações (apenas daquelas cujo resultado pode ser impresso). 

### Variação para pós-graduação:

Para a pós graduação apenas, a árvore binária de busca deve ser uma árvore rubro-negra.

### Operações:

- **Inclusão:** Uma operação de inclusão será identificada por uma linha escrito INC seguido de um espaço e depois um inteiro. Este elemento deve ser incluído na estrutura de dados, uma nova versão criada e nada precisa ser impresso.  
Exemplo de linha de inclusão:  
`INC 13`

- **Remoção:** Uma operação de remoção será identificada por uma linha escrito REM seguido de um espaço e depois um inteiro. Um nó com este valor deve ser removido (apenas um se houver repetição). Caso não haja um nó com o valor especificado, a estrutura não deve ser alterada. Em ambos os casos uma nova versão deve ser criada e nada precisa ser impresso.  
Exemplo de linha de remoção:  
`REM 42`

- **Sucessor:** Uma operação de sucessor será identificada por uma linha escrito SUC seguido de um espaço, um inteiro, outro espaço e outro inteiro. O sucessor do número x é o menor valor na estrutura que é estritamente maior que x. O primeiro inteiro será o valor (que não precisa estar na estrutura) cujo sucessor deseja-se saber e o segundo será a versão em que o sucessor deverá ser procurado. Caso a versão fornecida não exista, o sucessor deve ser procurado na versão mais recente e caso não exista valor na estrutura maior que o primeiro inteiro fornecido, o sucessor será infinito. Essa operação não cria uma nova versão na estrutura e imprime a própria operação e o resultado no arquivo de saída.  
Exemplo de linha de sucessor:  
`SUC 50 65`  
Exemplo de linha no arquivo de saída:  
`SUC 50 65`  
`52`

- **Imprimir:** Uma operação de impressão será identificada por uma linha escrito IMP seguido de um espaço e um inteiro. O inteiro indica a versão da estrutura que deve ser impressa, isto é, cada elemento da estrutura na versão indicada deve ser impresso em ordem crescente seguido da sua profundidade e cor separados por vírgula. Caso a versão fornecida não exista, a impressão deve ocorrer na versão mais recente. Essa operação não cria uma nova versão na estrutura e imprime a própria operação e o resultado no arquivo de saída.  
Exemplo de linha de impressão:  
`IMP 65`  
Exemplo de linha no arquivo de saída:  
`IMP 65`  
`13,2,R 42,1,N 50,0,N 52,2,R 65,1,N`

### Versões:

A estrutura inicialmente começa na versão 0. Cada operação de inclusão e remoção aumenta a versão da estrutura em 1. Haverá no máximo 99 operações de inclusão e remoção, de modo que haverá no máximo 100 versões diferentes da estrutura, então os identificadores das versões (raiz da estrutura e quais em quais versões ela opera) podem ser guardados num vetor de tamanho 100. Não há limite para o número de operações de sucessor e de impressão, mas estas não criam novas versões.

### Grupos e Entrega:

- Cada equipe da graduação pode ser formada por até 3 membros.
- Cada equipe da pós-graduação pode ser formada por até 2 membros.
Você deve enviar o seu código e indicando sua linguagem de programação e como compilar o seu programa. Deve haver um arquivo de descrição do trabalho que indica como rodar o seu programa e descrevendo as funções e estruturas (equivalente ao struct em C) que são usadas no seu código e em que arquivos eles se encontram.
