#include "matriz.h"

void percorrerMatriz(Dados *dados, Espelho *espelho, int *itens, int *perigos, int *vidaGanha) {
	int posicao = 0;
	int i = 0, j = 0;
	int iBckp = 0, jBckp = 0;
	srand(time(NULL));
	int cont = 0;

	readCheckpoint(dados);
	readCheckpointEspelho(espelho);

	while (!(j == -1 || j == dados->m + 1)) {
		posicao = (1 + (rand() % 8));
		iBckp = i;
		jBckp = j;

		switch (posicao) {
		case 1:
			if (i - 1 > 0) {
				i--;
				(*itens)++;
			}
			break;
		case 2:
			if (i + 1 < dados->n) {
				i++;
				(*itens)++;
			}
			break;
		case 3:
			if (j - 1 > 0) {
				j--;
				(*itens)++;
			} else {
				i = j = iBckp = jBckp = 0;
				createCheckpoint(dados);
				createCheckpointEspelho(espelho);

				if (dados->chk - 1 == 0) {
					dados->chk = dados->maxFile;
					espelho->chk = dados->chk;
				} else {
					dados->chk--;
					espelho->chk = dados->chk;
				};

				readCheckpoint(dados);
				readCheckpointEspelho(espelho);
			}
			break;
		case 4:
			if (j + 1 < dados->n) {
				j++;
				(*itens)++;
			} else {
				i = j = iBckp = jBckp = 0;
				createCheckpoint(dados);

				createCheckpointEspelho(espelho);

				if (dados->chk + 1 > dados->maxFile) {
					dados->chk = 1;
					espelho->chk = dados->chk;
				} else {
					dados->chk++;
					espelho->chk = dados->chk;
				};

				readCheckpoint(dados);
				readCheckpointEspelho(espelho);
			}
			break;
		case 5: //diagonal cima esquerda
			if (i - 1 > 0 && j - 1 > 0) {
				i--;
				j--;
				(*itens)++;
			}
			break;
		case 6: //diagonal cima direita
			if (i - 1 > 0 && j + 1 < dados->n) {
				i--;
				j++;
				(*itens)++;
			}
			break;
		case 7: //diagonal baixo esquerda
			if (i + 1 < dados->n && j - 1 > 0) {
				i++;
				j--;
				(*itens)++;
			}
			break;
		case 8: //diagonal baixo direita
			if (i + 1 < dados->n && j + 1 < dados->n) {
				i++;
				j++;
				(*itens)++;
			}
			break;
		default:
			printf("\nNao era pra chegar aqui!\n");
			break;
		}
		if (!(iBckp == i && jBckp == j)) {
			dados->i = i;
			dados->j = j;
			if (!(dados->mat[i][j] == PAREDE)) {
				if (dados->mat[i][j] == PERIGO) {
					//printf("Perdeu Vida!\n");
					dados->seq = 0;
					(*perigos)++;

					if (--dados->vida == 0) {
						//printf("Fim de Jogo!\n");
						createCheckpoint(dados);
						createCheckpointEspelho(espelho);

						return;
					}
				} else {
					dados->seq++;
					if (espelho->mat[i][j] == FALSE_C) {
						espelho->mat[i][j] = TRUE_C;
					}

					if (dados->mat[i][j] > 0) {
						dados->mat[i][j]--;
						cont = 0;

						if (dados->vida + 1 <= 10) {
							if (dados->seq == 4) {
								dados->vida++;
								(*vidaGanha)++;
								//printf("Ganhou Vida!\n");
							}
						}
					}
					cont++;
				}
			}
			createOutput(dados);
		} else {
			cont++;
		}
		if (cont == dados->n * dados->n) {
			createCheckpoint(dados);
			createCheckpointEspelho(espelho);
			return;
		}
	}
	createCheckpoint(dados);
	createCheckpointEspelho(espelho);
}
