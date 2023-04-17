# Labirinto Recorrente

<div style="display: inline_block">
  <img align="center" alt="C" src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" />
  <img align="center" alt="Linux" src="https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black" />
  <img align="center" alt="VS" src="https://img.shields.io/badge/Visual_Studio_Code-0078D4?style=for-the-badge&logo=visual%20studio%20code&logoColor=white" />
</div><br/>

<p> </p>
<p> </p>

# ⚠️ Apresentação do Problema 
<div align="justify">
     
1️⃣ Um garoto se encontra perdido em um labirinto, o qual é compreendido por nós como sendo uma matriz cujas posição de sua localização é dada por um valor (x, y) dessa estrutura. Nesse labirinto há: 
  - <b>🚧 Paredes (#)</b> => | bloqueiam certos passos |
    - não há muito o que fazer contra elas a não ser desviar e continuar a rota.
  - <b>💣 Perigos (*)</b> => | consomem parte de sua vida |
    - a cada passada, é subtraído 1 de vida (-💔) e os itens são zerados (-💰);
    - ao ficar sem pontos de vida o algoritmo deve parar e indicar fim de jogo;
    - os perigos são estáticos, não somem de lugar depois de serem caminhados.
  - <b>🛣️ Trajetórias</b> => | valores positivos que devem ser subtraídos em 1 a cada passagem |
    - caso o valor da casa seja 0 não existem itens para serem consumidos e nada é feito;
    - a regra para os "portais" é de escolha do aluno;
    - não é possível se "teletransportar" diretamente para uma parede em outra matriz; 
    - não é possível startar em um "portal" e já se "teletransportar";
    - é possível percorrer uma matriz mais de uma vez.
  - <b>💖 Vida</b> 
    - o máximo de vidas é 10 (💕);
    - caso jogador obtenha 4 itens, estando com o máximo de vida a quantidade de itens é zerada.
  - <b>💰 Itens</b>
    - a cada 4 itens coletados é ganho 1 de vida (+💖);
    - cada casa possui um valor (0 - 10) que consiste diretamente no quantidade de itens que possui;
    - caso a casa possua o valor 0 ela não possui itens.
  - <b>🌀 Portais</b>
    - as extremidades da esquerda (portal laranja) e direita (portal azul) funcionam como "portais";
    - ao chegar na extremidade esquerda o jogador volta para a matriz anterior;
    - já ao chegar na extremidade direita o jogador avança para a matriz posterior;
    - caso esteja na primeira matriz e encoste na extremidade esquerda o jogador pula para a última matriz;
    - já caso esteja na útima matriz e encoste na extremidade direita o jogador pula para a primeira matriz;
</div>

<p align="center">
<img src="imgs/esboço.png" width="700"/> 
</p>
<p align="center">
<em>Imagem 1: Imagem representativa do labirinto.</em>
</p>

<div align="justify">

2️⃣ Ao decorrer do jogo, a cada passo correto sob uma estrada, o garoto consome um item, subtraindo esse do valor que compõe a posição (x, y). Gravando nessa o valor resultante. A cada subtração bem sucedida é preciso, essa vai para um banco de vida que cheio (a cada 4 ações bem sucedidas) lhe retorna 1 de vida em seu contador. Contudo, pode haver partes do caminho com zero itens, esses devem continuar sendo utilizados, porém, sem computar pontuação.

</div>

<p align="center">
<img src="imgs/esboço2.png" width="700"/> 
</p>
<p align="center">
<em>Imagem 2: Imagem representativa das possíveis ações no labirinto.</em>
</p>

<div align="justify">

3️⃣ O labirinto deve ser lido do arquivo [input.data](), o qual apresentará várias matrizes, todas quadráticas conforme já exposto. 

4️⃣ Sua missão é percorrer as matrizes até que todo o caminho percorrido pelo garoto se torne zero ou que ele venha a morrer devido aos perigos enfrentados. 


5️⃣ Ao fim da aplicação é preciso apresentar como resultado: 

    🔹 (A) Quantas casas foram percorridas ao todo; 
    🔹 (B) Qual a soma de itens consumidos pelo caminho; 
    🔹 (C) Quantas casas da matriz ficaram sem serem exploradas; 
    🔹 (D) Quantos perigos foram enfrentados ao decorrer do percurso.

📝 <b>Observação:</b> A intenção global do problema não é encontrar uma saída, mas sim, tentar consumir o máximo possível de itens até chegar a zerar as possibilidades desse tipo ou morrer tentando.

❓ Qual o custo computacional da sua estratégia randômica? Se mostrou uma boa alternativa de execução?

</div>
  
# 🔄 Compilação e Execução

<p align="justify">
Esse programa possui um arquivo Makefile que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução:
</p>

| Comando                |  Função                                                                                               |                     
| -----------------------| ------------------------------------------------------------------------------------------------------|
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                            |
|  `make`                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build               |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                     |

## Contatos

<div style="display: inline-block;">
<a href="https://t.me/celso_vsf">
<img align="center" height="20px" width="90px" src="https://img.shields.io/badge/Telegram-2CA5E0?style=for-the-badge&logo=telegram&logoColor=white"/> 
</a>

</div>
