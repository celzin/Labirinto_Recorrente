#include "matriz.h"

int main() {
    Dados dados;
    Espelho espelho;

    readFile(&dados, &espelho);

    dados.chk = 1;
    dados.vida = 10;
    espelho.chk = dados.chk;
    dados.seq = 0;
    int itens = 0;
    int perigos = 0;
    int vidaGanha = 0;

    percorrerMatriz(&dados, &espelho, &itens, &perigos, &vidaGanha);
    int lido = 0, naoLido = 0;
    contLidoeNaoLido(&lido, &naoLido, dados.maxFile);
    createRelatorio(itens, perigos, lido, naoLido, vidaGanha);

    printf("\n[!] PERCURSO DE MATRIZES CRIADO NA PASTA DATASET COM O NOME DE OUTPUT.DATA \n");
    printf("[!] RELATORIO DE PERCURSO CRIADO NA PASTA DATASET COM O NOME DE RELATORIO.DATA \n\n");

    return 0;
}