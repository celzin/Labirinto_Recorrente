#include "matriz.h"

void percorrerMatriz(Dados *dados, Espelho *espelho, int *itens, int *perigos, int *vidaGanha) {
	int posicao = 0;
	int i = 2, j = 2;
	int iBckp = i, jBckp = j;
	srand(time(NULL));
	int cont = 0;

	readCheckpoint(dados);
	readCheckpointEspelho(espelho);

	int reset = 10;

	while (!(j == -1 || j == dados->m + 1)) {
		//printf("loop\n");
		// printf("%d %d - %d %d | %d | %d\n", i, j, iBckp, jBckp, dados->mat[i][j], cont);
		// if (reset-- == 0) {
		// 	printf("fim\n");
		// 	return;
		// }

		posicao = (1 + (rand() % 8));
		iBckp = i;
		jBckp = j;

		switch (posicao) {
		case 1: // cima
			if (i - 1 > 0) {
				i--;
				(*itens)++;
			}
			break;
		case 2: // baixo
			if (i + 1 < dados->n) {
				i++;
				(*itens)++;
			}
			break;
		case 3: // esquerda
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
		case 4: // direita
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
		case 6: //diagonal cima direita
			if (i - 1 > 0 && j + 1 < dados->n) {
				i--;
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
		case 7: //diagonal baixo esquerda
			if (i + 1 < dados->n && j - 1 > 0) {
				i++;
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
		case 8: //diagonal baixo direita
			if (i + 1 < dados->n && j + 1 < dados->n) {
				i++;
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
		default:
			printf("\nNao era pra chegar aqui!\n");
			break;
		}

		dados->i = i;
		dados->j = j;

		if (dados->mat[i][j] == PAREDE) {
			// printf("parede\n");
			i = iBckp;
			j = jBckp;

			dados->i = i;
			dados->j = j;

			testaLocal(dados, espelho, perigos, vidaGanha, i, j, &cont);
		} else if (dados->mat[i][j] == PERIGO) {
			//testaLocal(dados, espelho, perigos, vidaGanha, i, j, &cont);
			printf("perigo\n");
			//printf("Perdeu Vida!\n");
			dados->seq = 0;
			(*perigos)++;

			if (--dados->vida == 0) {
				printf("\nFim de Jogo!\n");
				createCheckpoint(dados);
				createCheckpointEspelho(espelho);

				return;
			}
		} else {
			printf("valido\n");
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
			//testaLocal(dados, espelho, perigos, vidaGanha, i, j, &cont);
		}
		createOutput(dados);
		// }
		// else {
		// 	cont++;
		// }
		if (cont == dados->n * dados->n) {
			createCheckpoint(dados);
			createCheckpointEspelho(espelho);
			return;
		}
	}
	createCheckpoint(dados);
	createCheckpointEspelho(espelho);
}

void testaLocal(Dados *dados, Espelho *espelho, int *perigos, int *vidaGanha, int i, int j, int *cont) {
	if (dados->mat[i][j] == PAREDE) {
		// printf("parede 2\n");
		// i = iBckp;
		// j = jBckp;
	} else if (dados->mat[i][j] == PERIGO) {
		// printf("perigo\n");
		//printf("Perdeu Vida!\n");
		dados->seq = 0;
		(*perigos)++;

		if (--dados->vida == 0) {
			printf("\nFim de Jogo!\n");
			createCheckpoint(dados);
			createCheckpointEspelho(espelho);

			return;
		}
	} else {
		// printf("valido\n");
		dados->seq++;
		if (espelho->mat[i][j] == FALSE_C) {
			espelho->mat[i][j] = TRUE_C;
		}

		if (dados->mat[i][j] > 0) {
			dados->mat[i][j]--;
			(*cont) = 0;

			if (dados->vida + 1 <= 10) {
				if (dados->seq == 4) {
					dados->vida++;
					(*vidaGanha)++;
					//printf("Ganhou Vida!\n");
				}
			}
		}
		(*cont)++;
	}
	//createOutput(dados);
}