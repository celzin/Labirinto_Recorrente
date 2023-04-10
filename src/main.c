#include "matriz.h"

int main(){
    int **mat;
    Dados dados;
	mat = readFile(&dados);
    dados.chk = 1;
    dados.vida = 10;
    dados.seq = 0;
    printf("%d\n", dados.maxFile);
    percorrerMatriz(&dados);
    return 0;
}