<!--
2º Projeto de Introdução à Computação 2017/2018 (c) by Nuno Fachada

2º Projeto de Introdução à Computação 2017/2018 is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.
-->

# 2º Projeto de Introdução à Computação 2017/2018

> Este enunciado está em construção mas os alunos podem começar a planear o
> trabalho com base na informação já disponibilizada.

O projeto deve ser realizado em grupos de 2 a 3 alunos. A constituição dos
grupos deve ser comunicada ao docente via Moodle até 23 de dezembro, data a
partir da qual se assume que os alunos não pretendem realizar o projeto na 1ª
época.

## Descrição do problema

Pretende-se que os alunos desenvolvam um jogo/simulador no qual zombies
perseguem e infetam humanos. O jogo desenrola-se numa grelha 2D
toroidal<sup>[1](#fn1)</sup> com dimensões _X_ e _Y_ e vizinhança de
Moore<sup>[2](#fn2)</sup>. Em cada célula da grelha pode estar no máximo um
agente, que pode ser um **zombie** ou um **humano**. No início da simulação
existem _n<sub>z</sub>_ zombies e _n<sub>h</sub>_ humanos, num total de _n =
n<sub>z</sub>_ + _n<sub>h</sub>_ agentes. Os agentes devem ser espalhados
aleatoriamente pela grelha no início de cada jogo.

O jogo é _turn-based_, e em cada _turn_ (iteração) cada agente pode realizar
uma ação. Os humanos podem apenas realizar um tipo de ação: movimento. Os
zombies podem realizar dois diferentes tipos de ação: 1) movimento; e, 2)
infeção de humanos. O movimento dos agentes pode ser realizado para uma célula
vazia numa vizinhança de Moore de raio 1. A infeção de humanos pode ser
realizada por zombies quando o humano está numa célula adjacente na vizinhança
de Moore. A ordem em que os agentes executam as suas ações em cada _turn_ é
aleatória<sup>[3](#fn3)</sup>, de modo a que nenhum agente em específico
obtenha a vantagem de agir cedo durante todo o jogo.

Os agentes podem ser controlados pelo computador através de uma AI básica, ou
podem ser controlados por jogadores. Neste último caso, um jogador que controle
determinado agente pode decidir o destino do mesmo. Se o agente for um zombie,
a ação de infeção equivale à indicação de movimento para o local onde
está um humano. Nesse caso o zombie não se move (pois o local já está ocupado
pelo humano), mas o humano é convertido em zombie. Se o humano era controlado
por um jogador, deixa de o ser, e passa a ser controlado pela AI. O jogo
termina quando não existirem mais agentes do tipo humano na grelha.

Caso um agente seja controlado pela AI, as suas decisões dependem do tipo de
agente:

* Humano - Tenta mover-se na direção oposta ao zombie mais próximo. Se a célula
  para onde o humano deseja mover-se estiver ocupada, o humano fica no mesmo
  local.
* Zombie - Caso exista um humano numa célula adjacente, infeta-o. Caso
  contrário, tenta mover-se na direção do humano mais próximo. Se a célula para
  onde o zombie deseja mover-se estiver ocupada, o zombie fica no mesmo local.

O jogo termina quando o número máximo de _turns_ for atingido, ou quando não
existirem mais humanos na simulação.

## Modo de funcionamento

### Invocação do programa

O programa deve aceitar como único parâmetro um ficheiro de configuração em
formato [INI]<sup>[4](#fn4)</sup>, de acordo com o seguinte exemplo:

```INI
; Dimensao da grelha de jogo
xdim=20
ydim=20
; Numero inicial de zombies e humanos
nzombies=20
nhumans=20
; Numero de zombies e humanos controlados por jogadores
nzplayers=0
nhplayers=1
; Numero de turns maximo
maxturns=1000
```

Os campos indicados no exemplo anterior são obrigatórios e o programa deve
saber interpreta-los corretamente. O programa deve ainda ignorar campos que
não conheça. Os alunos podem acrescentar campos que considerem úteis para o
desenvolvimento do projeto, mas estes devem ser opcionais. Por outras palavras,
o programa deve assumir valores por omissão para campos opcionais extra. Um
ficheiro INI usado para um projeto deve funcionar sem erros noutro projeto.

Senão for indicado o ficheiro de configuração, o programa deve terminar com uma
mensagem de erro para `stderr`, indicando o modo de uso.

### Modos de jogo

#### Modo automático

O programa entra em modo automático quando não existem agentes controlados
por jogadores. Neste modo o jogo desenrola-se sem intervenção direta do
utilizador. A visualização deve ser atualizada no fim de cada _turn_ (pelo
menos). No entanto, de modo a ser possível observar a evolução da simulação,
poderá ser boa ideia solicitar ao utilizador para pressionar uma tecla ou
clicar num botão antes de se dar início à próxima _turn_.

#### Modo interativo

Neste modo, cada vez que um agente controlado pelo jogador é chamado a agir,
o programa fica a aguardar o _input_ do jogador sobre que ação tomar. A
visualização do jogo deve ser atualizada imediatamente antes de ser solicitado
_input_ a um jogador (pelo menos).

## Desenvolvimento do projeto

### Primeira parte

#### Objetivos a atingir

* Jogo deve funcionar como especificado.
* Código deve compilar sem erros no compilador [GCC] e/ou [Clang] com as opções
  `-std=c99 -Wall -Wextra -Wpedantic`.
* Código deve estar devidamente comentado e indentado.

As seguintes limitações são aceitáveis e não serão penalizadas na primeira
entrega:

* Tamanho do ambiente e número de agentes fixo após compilação: _X_=20, _Y_=20,
_n<sub>z</sub>_=20, _n<sub>h</sub>_=20.
  * Sugestão: usar constantes e ignorar valores lidos do ficheiro de
    configuração.
* Código pode ser entregue num único ficheiro `.c`.
* Visualização do jogo pode ser feita com código exemplo disponibilizado na
  secção [Visualização do jogo](#visualize).

#### Entrega

A 1ª parte do projeto deve ser entregue via Moodle até às 23h de 14 de janeiro
de 2018. Deve ser submetido um ficheiro `zip` com a pasta do projeto que deve
ter os seguintes conteúdos:

* Ficheiro(s) `.c` (e possivelmente ficheiros `.h` se os alunos decidirem
  organizar o código em vários ficheiros logo para a primeira entrega).
* Pasta escondida `.git` contendo o repositório Git local do projeto.
* Ficheiro `README.md` contendo o relatório do projeto em formato [Markdown],
  contendo as seguintes secções:
  * Título do projeto.
  * Nomes dos autores (primeiro e último) e respetivos números de aluno.
  * Descrição da solução:
    * Arquitetura da solução, com breve explicação de como o programa foi
      estruturado. Um fluxograma simples, que mostre o funcionamento de alto
      nível do programa, pode ajudar bastante a explicar a arquitetura do
      mesmo.
    * Estruturas de dados: grelha de simulação, agentes, outras estruturas
      auxiliares relevantes.
    * Algoritmos: procura de agente mais próximo, cáculo de direção na grelha,
      _shuffling_ (embaralhamento) dos agentes antes de cada _turn_, outros
      algoritmos relevantes.
  * Manual de utilizador:
    * Como compilar (qual o comando completo para compilação).
    * Como jogar: que teclas pressionar e/ou onde clicar para mover agentes
      (modo interativo); tecla e/ou botão para passar para a próxima _turn_
      (modo automático); outras funcionalidades importantes que o utilizador
      possa controlar.
  * Conclusões e matéria aprendida.
  * Referências:
    * Incluindo trocas de ideias com colegas, código aberto reutilizado e
      bibliotecas de terceiros utilizadas. Devem ser o mais detalhados possível.
  * **Nota:** o relatório deve ser simples e breve, com informação mínima e
    suficiente para que seja possível ter uma boa ideia do que foi feito.

**Atenção**: Todos os ficheiros C e Markdown devem ser gravado em codificação
UTF-8<sup>[5](#fn5)</sup>.

#### Critério de avaliação

A primeira parte do projeto, que tem um peso de 4 valores na nota final da
disciplina, será avaliada segundo os critérios indicados na Tabela 1.

**Tabela 1** - Critérios absolutos da 1ª parte do projeto.

| Critério                                               | Peso      |
|--------------------------------------------------------|-----------|
| Funcionamento segundo especificações                   | 1 val.    |
| Qualidade do código e das soluções<sup>[6](#fn6)</sup> | 0,6 val.  |
| Indentação  e comentários                              | 0,5 val.  |
| Compilação sem erros e _warnings_                      | 0,4 val.  |
| Relatório                                              | 1 val.    |
| Desenvolvimento do projeto com Git<sup>[7](#fn7)</sup> | 0,5 val.  |
| Antecipação de objetivos da 2ª parte do projeto        | Bónus!    |

A nota máxima da 1ª parte do projeto é de 4 valores, sendo que o bónus poderá
servir apenas para compensar avaliações piores nos critérios principais.

### Segunda parte

<a name="objetivos2parte"></a>

#### Objetivos a atingir

* Tamanho da grelha e número de agentes variável após compilação, tal como
  especificado no ficheiro de configuração.
* Documentação do projeto com [Doxygen].
* Organização do programa em vários ficheiros `.c` e `.h` com uso de _Makefile_.
* Visualização do jogo deve ser feita com recurso a uma biblioteca gráfica ou
  de jogos. Algumas sugestões:
  * [g2] - Simples mas limitada.
  * [Ncurses] - ASCII art (texto), ver referência [\[2\]](#ref2).
  * [Allegro5] - Bom meio termo, com bons exemplos em C.
  * [SDL2] - Muito versátil e abrangente, mas poucos exemplos em C.
  * [Raylib] - Muito interessante, mas instalação no Ubuntu não é trivial (ver
    instruções no Wiki da [página no GitHub][Raylib-gh]).

#### Entrega

A 2ª parte do projeto deve ser entregue via Moodle até às 23h de 21 de janeiro
de 2018. Deve ser submetido um ficheiro `zip` com a pasta do projeto que deve
ter os seguintes conteúdos:

* Ficheiros `.c` e `.h`, bem como a _Makefile_.
* Ficheiro `README.md` em formato [Markdown] gravado em codificação ASCII ou
  UTF-8<sup>[5](#fn5)</sup>.
* Pasta escondida `.git` contendo o repositório Git local do projeto.

#### Critério de avaliação

A segunda parte do projeto, que tem um peso de 4 valores na nota final da
disciplina, será avaliada usando duas tabelas distintas. A tabela 2 indica os
critérios absolutos, que totalizam 4 valores:

**Tabela 2** - Critérios absolutos da 2ª parte do projeto.

| Critério                                               | Peso      |
|--------------------------------------------------------|-----------|
| Tamanho da grelha/número de agentes variável           | 1 val.    |
| Visualização com recurso a biblioteca externa          | 1 val.    |
| Documentação com [Doxygen]                             | 1 val.    |
| Organização do projecto e _Makefile_                   | 1 val.    |
| [Extensões opcionais e Global Game Jam](#gamejam)      | Bónus!    |

A nota máxima da 2ª parte do projeto é de 4 valores, sendo que o bónus poderá
servir apenas para compensar avaliações piores nos critérios principais. No
entanto, como os critérios absolutos não fazem sentido sem que os objetivos da
1ª parte do projeto tenham sido atingidos, a nota final da 2ª parte também
depende de uma percentagem baseada nesses objetivos, tal como indicado na
Tabela 3.

**Tabela 3** - Critérios relativos da 2ª parte do projeto.

| Critério                                               | Peso      |
|--------------------------------------------------------|-----------|
| Funcionamento segundo especificações                   | 25,0%     |
| Qualidade do código e das soluções<sup>[6](#fn6)</sup> | 15,0%     |
| Indentação  e comentários                              | 12,5%     |
| Compilação sem erros e _warnings_                      | 10,0%     |
| Relatório                                              | 25,0%     |
| Desenvolvimento do projeto com Git<sup>[7](#fn7)</sup> | 12,5%     |

A nota final da 2ª parte do projeto é dada pelo total dos critérios absolutos
multiplicado pela percentagem obtida nos critérios relativos.

### Divisão do código em vários Ficheiros

#### Vantagens

Existem várias vantagens em dividir um programa por vários ficheiros, como por
exemplo [\[3\]](#ref3):

* Facilita cooperação entre vários programadores, uma vez que cada programador
  pode trabalhar num ficheiro ou grupo de ficheiros diferente sem receio de
  conflitos.
* Permite uma abordagem orientada a objetos. Por outras palavras, cada par de
  ficheiros `.c` e `.h` pode definir um tipo (ou vários tipos relacionados),
  bem como, bem como operações (funções) sobre esse tipo ou tipo(s), e até
  possíveis constantes associadas. Isto leva a que os programas fiquem muito
  bem estruturados.
* Na sequência do ponto anterior, o código fica organizado em forma de
  biblioteca, sendo facilmente reutilizável noutros projetos e programas,
  reduzindo o tempo de desenvolvimento.
* Quando um ficheiro é modificado, apenas esse ficheiro precisa de ser
  recompilado para o programa ser reconstruído. O programa [`make`] automatiza
  este processo.

#### Como dividir um programa em vários ficheiros

Regra geral, existe um ficheiro `.c` principal que contém a função `main` e
eventualmente outras funções, variáveis ou definições apenas relevantes no
contexto do programa a ser desenvolvido. Os restantes ficheiros estão agrupados
em pares `.c` e `.h` que disponibilizam funcionalidades num contexto
específico, na prática sendo usados como bibliotecas locais de funções.

Tipicamente, quando se define um tipo, por exemplo uma `struct`, todas as
funções que acedem e/ou manipulam variáveis desse tipo são colocadas no mesmo
par `.c` e `.h`. Numa linguagem de programação orientada a objectos, como o
Java ou C#, os tipos são chamados de _classes_, as variáveis de dado tipo são
chamadas de _objectos_, e as funções que operam sobre dado tipo são chamadas de
_métodos_.

De modo a que os tipos (_classes_) e funções que operam sobre esses tipos
(_métodos_) possam ser utilizados por outros programas e funções, é necessário
colocar as definições de tipos e os protótipos (cabeçalhos) das funções
associadas no ficheiro `.h` (_header file_), e posteriormente incluir
(`#include`) esse ficheiro no código no qual se pretende ter acesso à
funcionalidade desenvolvida. Cada ficheiro `.h` tem um ficheiro `.c`
correspondente, onde são colocados os corpos das funções, bem como tipos e
variáveis que apenas tenham relevância no contexto desse ficheiro (ou seja,
que não valha a pena exportar). O ficheiro `.h` pode ser considerado a parte
pública da biblioteca (por exemplo, definição de tipos e protótipos de funções),
que pode ser usada por outro código, enquanto o ficheiro `.c` tem a parte
privada (por exemplo, o corpo das funções).

#### Como compilar um programa dividido em vários ficheiros

* Todos de uma vez
* Um a um
* Usando uma Makefile

### Documentação do código automática com Doxygen

Work in progress

<a name="visualize">

### Visualização do jogo

A pasta [code](code) contém codigo auxiliar para a desenhar o mundo do jogo no
ecrã. A organização deste código está indicada na Figura 1.

![arquitectura](https://user-images.githubusercontent.com/3018963/34446014-d09091f8-eccf-11e7-8378-90221db5fc9a.png)

**Figura 1** - Organização do código auxiliar para desenhar o mundo do jogo no
ecrã.

O ficheiro [showworld.h](code/showworld.h) define três tipos que devem ser
usados para o desenvolvimento da parte de visualização do projeto, nomeadamente:

* [`AGENT_TYPE`](code/showworld.h#L34) - Enumeração que define os diferentes
  tipos de agente, tal como indicado na Tabela 5.
* [`get_agent_info_at`](code/showworld.h#L44) - Tipo de função que retorna
  informação sobre um agente em dado local do mundo de jogo.
* [`show_world`](code/showworld.h#L62) - Tipo de função que mostra/atualiza a
  visualização do mundo de jogo.

A biblioteca definida nos ficheiros [simple_showworld.h](code/simple_showworld.h)
e [simple_showworld.c](code/simple_showworld.c) fornece uma função de nome
[`simple_show_world()`](code/simple_showworld.c#L35). Esta função obedece ao
tipo [`show_world`](code/showworld.h#L62), e mostra o mundo de jogo de forma
simples no terminal, podendo ser utilizada na 1ª parte do projeto. Na 2ª parte
do projeto os alunos devem implementar a sua própria biblioteca de visualização
do jogo, obedecendo aos tipos definidos em [showworld.h](code/showworld.h),
mas fazendo uso de uma biblioteca de terceiros tal como indicado
[anteriormente](#objetivos2parte).

O ficheiro [example.c](code/example.c) contém um exemplo de como usar a função
`simple_show_world()`, obedecendo aos tipos definidos em
[showworld.h](code/showworld.h).

As próximas sub-secções descrevem em detalhe como este código auxiliar pode ser
usado nas duas partes do projeto.

#### 1ª parte do projeto

Para a primeira parte do projeto, os alunos podem simplesmente usar a função
`simple_show_world()` cujo protótipo (cabeçalho) se encontra no ficheiro
[simple_showworld.h](code/simple_showworld.h), e cujo corpo está definido no
ficheiro [simple_showworld.c](code/simple_showworld.c). Esta função mostra o
mundo do jogo no terminal, indicando se o agente é zombie (`z`) ou humano (`h`),
o ID do agente em hexadecimal (por exemplo, `z0A`), e diferenciando com `Z` ou
`H` maiúsculo caso o agente em questão seja controlado por um jogador (por
exemplo, `H19`). Caso não exista um agente na célula em questão, a função
imprime um ponto (`.`). Para um mundo 5x5 com 4 zombies e 1 humano, com um dos
zombies controlado por um jogador, a função mostra algo parecido com a Figura
2.

```
.   .  Z02  .   .

.  z00  .   .   .

.   .   .   .   .

.   .  z03  .   .

.  z01  .  h04  .
```

**Figura 2** - Exemplo do mundo de jogo com dimensões 5x5, tal como mostrado
pela função `simple_show_world()`.

A função `simple_show_world()` obedece ao tipo [`show_world`](code/showworld.h#L62)
e tem o seguinte protótipo:

```c
void simple_show_world(
    void *world,
    unsigned int xdim,
    unsigned int ydim,
    get_agent_info_at ag_info);
```

A função não devolve nada (`void`), mas aceita quatro argumentos. O primeiro
argumento, `world`, é do tipo `void *` (apontador genérico), e aponta para a
estrutura de dados que contém o mundo do jogo. O segundo e terceiro argumentos,
`xdim` e `ydim`, são as dimensões horizontal e vertical do mundo,
respetivamente. O quarto e último argumento, `ag_info`, é um apontador para uma
função que obtém informação sobre um agente localizado numa dada posição no
mundo do jogo, obedecendo ao tipo [`get_agent_info_at`](code/showworld.h#L44).
Como é possível observar no [código](code/simple_showworld.c#L35), a função
`simple_show_world()` percorre todas as células da grelha de simulação, por
linha e por coluna, obtém informação sobre o agente em cada posição (usando a
função apontada por `ag_info`), e imprime no ecrã, de forma formatada, a
informação obtida. A função `simple_show_world()` não precisa de saber nada
sobre o mundo de simulação, apontado pela variável `world`, pois este é passado
como argumento e interpretado pela função apontada por `ag_info`.

No entanto, após esta descrição existe ainda uma questão crucial e não
esclarecida. Onde está definida a estrutura de dados que contém o mundo de
simulação, bem como a função que a sabe interpretar? A reposta é a seguinte:
tanto a estrutura de dados, bem como a função que a interpreta, devem ser
desenvolvidas no código do projeto. Uma vez que o mundo de simulação vai ser
definido de forma específica por cada grupo, faz então sentido que a função que
obtém informação sobre um agente em determinada localização no mundo seja
também definida pelo grupo. Esta função deve obedecer ao tipo
`get_agent_info_at`, definido no ficheiro [showworld.h](code/showworld.h), da
seguinte forma:

```c
typedef unsigned int (*get_agent_info_at)(
    void *world,
    unsigned int x,
    unsigned int y);
```

Por outras palavras, funções do tipo `get_agent_info_at` devem devolver um
`unsigned int` contendo informação sobre um agente, recebendo como argumentos
a variável `world` (apontador genérico para o mundo do jogo), bem como as
coordenadas `(x,y)` da posição sobre a qual se pretende obter informação. O
`unsigned int` com informação sobre um agente está organizado internamente
como indicado na Tabela 4.

**Tabela 4** - Informação sobre um agente tal como devolvida por funções do
tipo `get_agent_info_at`.

| Bits            | _31–19_ | _18–3_       | _2_             | _1–0_          |
|-----------------|---------|--------------|-----------------|----------------|
| **Significado** | Livre   | ID do agente | Agente jogável? | Tipo de agente |


Os dois bits menos significativos, nas posições 0 e 1, representam o tipo de
agente. O bit na posição 2 indica se o agente é controlado por um jogador (`1`)
ou pela AI (`0`). Os bits entre as posições 3 e 18 contêm o ID do agente.
Finalmente, os bits mais significativos (posições 19 a 31) estão livres para
uso do aluno, caso assim o entenda.

Os possíveis tipos de agente (posições 0 e 1) estão definidos numa enumeração
de nome `AGENT_TYPE` no ficheiro [showworld.h](code/showworld.h#L34), tal como
indicado na Tabela 5. O tipo `Unknown` nunca deve ocorrer. Se tal acontecer,
significa que o jogo tem um _bug_.

**Tabela 5** - Tipos de agentes definidos na enumeração
[`AGENT_TYPE`](code/showworld.h).

| Tipo      | Significado            | Código (dec.)  | Código (bin.)  |
|-----------|------------------------|----------------|----------------|
| `None`    | Nenhum agente presente | 0              | 00             |
| `Human`   | Agente humano          | 1              | 01             |
| `Zombie`  | Agente zombie          | 2              | 10             |
| `Unknown` | Agente desconhecido    | 3              | 11             |

Um exemplo desta abordagem está disponível no ficheiro
[example.c](code/example.c). Este programa cria uma grelha de simulação de
dimensões 20x20, na qual os agentes são colocados em cada célula com uma
probabilidade de 10%, invocando depois a função `simple_show_world()` para
mostrar o mundo aleatoriamente gerado. A grelha de simulação (mundo do jogo) é
definida como um _array_ bidimensional de agentes, onde cada posição `[i][j]`
do _array_, correspondente a uma coordenada `(x,y)` no mundo do jogo, contém
um agente. Por sua vez, os agentes são definidos como uma [estrutura de nome
`AGENT` com três campos](code/example.c#L42): tipo de agente (`AGENT_TYPE`),
agente jogável (`unsigned char`, 0 ou 1), e ID do agente (`unsigned short`). A
função [`example_get_ag_info()`](code/example.c#L151), que obedece ao tipo
`get_agent_info_at`, sabe interpretar a variável `world` como _array_ de
agentes, sabendo também como obter informação sobre um agente em determinada
posição do _array_. Esta função é passada como último argumento da função
`simple_show_world()` quando a mesma é
[invocada no exemplo](code/example.c#L141).

Convém referir que as estruturas de dados usadas neste exemplo poderão não ser
adequadas ou suficientes para o desenvolvimento do projeto.

#### 2ª parte do projeto

Um dos [objetivos](#objetivos2parte) para a 2ª parte do projeto consiste em
implementar a visualização do mundo do jogo usando uma biblioteca de terceiros.
Os alunos devem implementar a visualização na forma de uma biblioteca local que
substituirá a biblioteca simples fornecida nos ficheiros
[simple_showworld.c](code/simple_showworld.c) e
[simple_showworld.h](code/simple_showworld.h). Tal como esta última, a
biblioteca desenvolvida pelos alunos deve obedecer aos tipos definidos em
[showworld.h](code/showworld.h), de forma a que o código de visualização
desenvolvido por um grupo funcione no projeto de qualquer outro grupo. A Figura
3 mostra uma possível organização de um projeto com visualização baseada em
[SDL2], omitindo possíveis ficheiros associados a funcionalidades não
discutidas nesta secção.

**Figura 3** - Possível organização de um projeto, omitindo possíveis
componentes associadas com outras funcionalidades específicas.

![orgproj](https://user-images.githubusercontent.com/3018963/34391685-44e7f88a-eb3f-11e7-9e26-636233178e16.png)

### Sugestões para o desenvolvimento do projeto

1. Começar com coisas simples
2. Usar Git para colaboração
3. Usar [cppcheck] para verificação estática
4. Usar [Valgrind] para erros de acesso à memória
5. Usar [GDB] para _debugging_

<a name="gamejam"></a>

### Extensões opcionais, trabalho futuro e Global Game Jam

* Melhor AI.
* Melhor integração com biblioteca preferida: [Ncurses], [Allegro5], [SDL2] ou
  [Raylib]. Infelizmente [g2] não é apropriada para jogos "a sério".
* Desenvolvimento do jogo na Global Game Jam.

## Honestidade académica

Nesta disciplina, espera-se que cada aluno siga os mais altos padrões de
honestidade académica. Isto significa que cada ideia que não seja do
aluno deve ser claramente indicada, com devida referência ao respectivo
autor. O não cumprimento desta regra constitui plágio.

O plágio inclui a utilização de ideias, código ou conjuntos de soluções
de outros alunos ou indivíduos, ou quaisquer outras fontes para além
dos textos de apoio à disciplina, sem dar o respectivo crédito a essas
fontes. Os alunos são encorajados a discutir os problemas com outros
alunos e devem mencionar essa discussão quando submetem os projetos.
Essa menção **não** influenciará a nota. Os alunos não deverão, no
entanto, copiar códigos, documentação e relatórios de outros alunos, ou dar os
seus próprios códigos, documentação e relatórios a outros em qualquer
circunstância. De facto, não devem sequer deixar códigos, documentação e
relatórios em computadores de uso partilhado.

Nesta disciplina, a desonestidade académica é considerada fraude, com
todas as consequências legais que daí advêm. Qualquer fraude terá como
consequência imediata a anulação dos projetos de todos os alunos envolvidos
(incluindo os que possibilitaram a ocorrência). Qualquer suspeita de
desonestidade académica será relatada aos órgãos superiores da escola
para possível instauração de um processo disciplinar. Este poderá
resultar em reprovação à disciplina, reprovação de ano ou mesmo
suspensão temporária ou definitiva da ULHT<sup>[8](#fn8)</sup>.

## Notas

<sup><a name="fn1">1</a></sup> Nota de rodapé sobre toros

<sup><a name="fn2">2</a></sup> Nota de rodapé sobre Moore

<sup><a name="fn3">3</a></sup> Nota de rodapé sobre _shuffling_

<sup><a name="fn4">4</a></sup> Nota de rodapé sobre bibliotecas para leitura de
ficheiros INI

<sup><a name="fn5">5</a></sup> Nota de rodapé sobre ASCII e UTF-8 em Windows

<sup><a name="fn6">6</a></sup> Nota de rodapé sobre qualidade do código

<sup><a name="fn7">7</a></sup> Nota de rodapé sobre Git local e remoto

<sup><a name="fn8">8</a></sup> Texto adaptado da disciplina de [Algoritmos e
Estruturas de Dados][aed] do [Instituto Superior Técnico][ist].

## Referências

* <a name="ref1">\[1\]</a> Pereira, A. (2017). C e Algoritmos, 2ª edição. Sílabo.
* <a name="ref2">\[2\]</a> Reagan, P. (2014). [Game Programming in C with the
Ncurses Library](https://www.viget.com/articles/game-programming-in-c-with-the-ncurses-library),
Viget Labs.
* <a name="ref3">\[3\]</a> Marshall, D. (1999).
[Writing Larger Programs](http://users.cs.cf.ac.uk/Dave.Marshall/C/node35.html),
Cardiff School of Computer Science and Informatics


## Licenças

Todo o código neste repositório é disponibilizado através da licença [GPLv3].
O enunciado e restante documentação são disponibilizados através da licença
[CC BY-NC-SA 4.0].

## Metadados

* Autor: [Nuno Fachada]
* Curso:  [Licenciatura em Aplicações Multimédia e Videojogos][lamv]
* Instituição: [Universidade Lusófona de Humanidades e Tecnologias][ULHT]

[GPLv3]:https://www.gnu.org/licenses/gpl-3.0.en.html
[CC BY-NC-SA 4.0]:https://creativecommons.org/licenses/by-nc-sa/4.0/
[lamv]:https://www.ulusofona.pt/licenciatura/aplicacoes-multimedia-e-videojogos
[Nuno Fachada]:https://github.com/fakenmc
[ULHT]:https://www.ulusofona.pt/
[aed]:https://fenix.tecnico.ulisboa.pt/disciplinas/AED-2/2009-2010/2-semestre/honestidade-academica
[ist]:https://tecnico.ulisboa.pt/pt/
[Markdown]:https://guides.github.com/features/mastering-markdown/
[GCC]:https://gcc.gnu.org/
[Clang]:https://clang.llvm.org/
[Gedit]:https://wiki.gnome.org/Apps/Gedit
[Geany]:https://www.geany.org/
[Code::Blocks]:http://www.codeblocks.org/
[Atom]:https://atom.io/
[XCode]:https://developer.apple.com/xcode/
[Notepad++]:https://notepad-plus-plus.org/
[Remarkable]:https://remarkableapp.github.io/
[Git]:https://git-scm.com/
[repositório]:https://github.com/VideojogosLusofona/ic2017p1
[GitHub]:https://github.com/
[git-tutorial]:https://try.github.io/levels/1/challenges/1
[Moodle]:https://secure.grupolusofona.pt/ulht/moodle/
[GitLab]:https://gitlab.com/
[BitBucket]:https://bitbucket.org/
[NotABug]:https://notabug.org/
[StackEdit]:https://stackedit.io/editor
[(GitHub-Flavored) Markdown Editor]:https://jbt.github.io/markdown-editor/
[Doxygen]:http://www.stack.nl/~dimitri/doxygen/
[Ncurses]:https://www.gnu.org/software/ncurses/ncurses.html
[g2]:http://www.ncbr.muni.cz/~martinp/g2/index.html
[Allegro5]:http://liballeg.org/
[SDL2]:https://www.libsdl.org/
[raylib]:http://www.raylib.com/
[raylib-gh]:https://github.com/raysan5/raylib
[INI]:https://en.wikipedia.org/wiki/INI_file
[GDB]:https://www.gnu.org/software/gdb/
[cppcheck]:http://cppcheck.sourceforge.net/
[Valgrind]:http://valgrind.org/
[`make`]:https://www.gnu.org/software/make/manual/make.html
