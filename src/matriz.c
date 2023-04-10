#include "matriz.h"

// funcao que imprime no terminal a matriz gerada
void printMatriz(Dados dados){
    char c[]= "(x)";
    printf("Matriz atual: %d\n", dados.chk);
    printf("Vidas: %d\n", dados.vida);
    for (int i=0; i<dados.n; i++){
        for (int j=0; j<dados.m; j++){
            if(dados.i == i && dados.j == j) printf("%-5s ", c);
            else printf("%-5d ", dados.mat[i][j]);
        }
        printf("\n");
	}
    printf("\n");
}

void percorrerMatriz(Dados *dados){
    int posicao = 0;
    int i=0, j=0;
    int iBckp=0, jBckp=0;
    srand (time(NULL));
    int cont=0;

    readCheckpoint(dados);
    //&& cont++ < dados->n*dados->m
    while (!(j == -1 || j == dados->m+1) ){
        posicao = (1+(rand()%8));
        iBckp = i;
        jBckp = j;
        
        switch (posicao){
        case 1:
                if(i-1 > 0) i--;
            break;
        case 2:
                if(i+1 < dados->n) i++;
            break;
        case 3:
                if(j-1 > 0) j--;
                /*
                else{
                    i = j = iBckp = jBckp = 0;
                    createCheckpoint(dados->mat, dados->n, dados->m, dados->chk);
                    
                    if(dados->chk-1 == 0) dados->chk = dados->maxFile;
                    else dados->chk--;

                    readCheckpoint(dados);
                }
                */
            break;
        case 4:
                if(j+1 < dados->n) j++;
                /*
                else{
                    i = j = iBckp = jBckp = 0;
                    createCheckpoint(dados->mat, dados->n, dados->m, dados->chk);
                    
                    if(dados->chk+1 == dados->maxFile) dados->chk = 1;
                    else dados->chk++;

                    readCheckpoint(dados);
                }
                */
            break;
        case 5: //diagonal cima esquerda
                if(i-1 > 0 && j-1 > 0){
                    i--;
                    j--;
                } 
            break;
        case 6: //diagonal cima direita
                if(i-1 > 0 && j+1 < dados->n){
                    i--;
                    j++;
                }
            break;
        case 7: //diagonal baixo esquerda
                if(i+1 < dados->n && j-1 > 0){
                    i++;
                    j--;
                }
            break;
        case 8: //diagonal baixo direita
                if(i+1 < dados->n && j+1 < dados->n){
                    i++;
                    j++;
                }
            break;
        default:
            printf("\nNao era pra chegar aqui!\n");
            break;
        }
        if (!(iBckp == i && jBckp == j)){
            dados->i = i;
            dados->j = j;
            if(!(dados->mat[i][j] == PAREDE)){
                if(dados->mat[i][j] == PERIGO){
                    printf("Perdeu Vida!\n");
                    dados->seq = 0;
                    if(--dados->vida == 0){
                        printf("Fim de Jogo!\n");
                        exit (EXIT_SUCCESS);
                    }
                }
                else{
                    if(dados->mat[i][j] > 0){
                        dados->mat[i][j]--;
                        if(dados->vida+1 <= 20){
                            if(dados->seq == 4){
                                dados->vida++;
                                printf("Ganhou Vida!\n");
                            }
                        }
                    } 
                    //else cont++;
                }
            }           
            //printMatriz(*dados);
        }
    }    
}