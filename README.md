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
  - 🚧 Paredes que bloqueiam certos passos (#);
    - não há muito o que fazer contra elas a não ser desviar e continuar a rota
  - 💣 Perigos que consomem parte de sua vida (*); 
    - a cada passada, é subtraido 1 de vida do jogador de um total de 10;
    - ao ficar sem pontos de vida o algoritmo deve parar e indicar fim de jogo.
  - 🛣️ Trajetórias (valores positivos que devem ser subtraídos em 1 a cada passagem).

2️⃣ Ao decorrer do jogo, a cada passo correto sob uma estrada, o garoto consome um item, subtraindo esse do valor que compõe a posição x,y. Gravando nessa o valor resultante. A cada subtração bem sucedida é preciso, essa vai para um banco de vida que cheio (a cada 4 ações bem sucedidas) lhe retorna 1 de vida em seu contador. Contudo, pode haver partes do caminho com zero itens, esses devem continuar sendo utilizados, porém, sem computar pontuação.

3️⃣ O labirinto deve ser lido do arquivo [input.data](), o qual apresentará várias matrizes, todas quadráticas conforme já exposto. 

4️⃣ Sua missão é percorrer as matrizes até que todo o caminho percorrido pelo garoto se torne zero ou que ele venha a morrer devido aos perigos enfrentados. 


5️⃣ Ao fim da aplicação é preciso apresentar como resultado: 

    🔹 (A) Quantas casas foram percorridas ao todo; 
    🔹 (B) Qual a soma de itens consumidos pelo caminho; 
    🔹 (C) Quantas casas da matriz ficaram sem serem exploradas; 
    🔹 (D) Quantos perigos foram enfrentados ao decorrer do percurso.

📝 <b>Observação:</b> Para essa atividade, considere selecionar um passo de cada vez de forma aleatória, ou seja, escolha um valor x,y aleatoriamente e vá para ele se possível ou descarte caso seja uma parede. Perigos não são evitados, então, se a posição escolhida for um, enfrente-o. Por fim, a intenção global do problema não é encontrar uma saída, mas sim, tentar consumir o máximo possível de itens até chegar a zerar as possibilidades desse tipo ou morrer tentando.

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
