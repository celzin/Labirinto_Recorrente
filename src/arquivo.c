#include "matriz.h"

// funcao que tokeniza a matriz do arquivo
void tokenizarMatriz(char *str, int cont, int **matrix, Espelho *espelho) {
	int val, col = 0;
	const char sep[] = " ";
	char *tokens;
	tokens = strtok(str, sep);

	while (tokens != NULL) {

		if (strcmp("#", tokens) == 0) {
			val = PAREDE;

			if (espelho != NULL)
				espelho->mat[cont][col] = PAREDE_C;
		} else if (strcmp("*", tokens) == 0) {
			val = PERIGO;

			if (espelho != NULL)
				espelho->mat[cont][col] = PERIDO_C;
		} else {
			val = atoi(tokens);

			if (espelho != NULL) {
				if (strcmp(tokens, "+") == 0)
					espelho->mat[cont][col] = TRUE_C;
				else
					espelho->mat[cont][col] = FALSE_C;
			}
		}
		if (matrix != NULL)
			matrix[cont][col] = val;


		col++;
		tokens = strtok(NULL, sep);
	}
}

// funcao que tokeniza a primeira linha do arquivo
void tokenizarLinha(char *str, int *n, int *m) {
	const char sep[] = " ";
	char *tokens;
	int aux = 0;
	tokens = strtok(str, sep);

	while (tokens != NULL) {
		if (aux == 0) {
			*n = atoi(tokens);
			aux++;
		} else {
			*m = atoi(tokens);
			return;
		}
		tokens = strtok(NULL, sep);
	}
}

// funcao que le tamanho e matrizes do aquivo
void readFile(Dados *dados, Espelho *espelho) {
	char *str = (char *)malloc(TAM);
	strcpy(str, "dataset/input.data");
	int aux = 0;
	int cont = 0;
	int n, m, **mat;

	FILE *fileClean = fopen("dataset/output.data", "w");
	fclose(fileClean);

	FILE *file = fopen(str, "r");

	char *result, linha[TAM];
	int varCHK = 1;

	if (file == NULL) {
		printf("Nao foi possivel abrir o arquivo\n");
	} else {
		while (!feof(file)) {
			result = fgets(linha, sizeof(linha), file);
			linha[strcspn(linha, "\n")] = 0; // remove o \n e atualiza o strlen

			if (result) {
				if (aux == 0) { // quando for 1 quer dizer que nao e mais primeira linha
					aux = 1;
					tokenizarLinha(linha, &n, &m);
					dados->m = m;
					dados->n = n;

					espelho->m = m;
					espelho->n = n;

					espelho->mat = malloc(n * sizeof(int **));
					mat = malloc(n * sizeof(int **));

					for (int i = 0; i < m; i++) {
						mat[i] = malloc(m * sizeof(int *));
						espelho->mat[i] = malloc(m * sizeof(int *));
					}
				} else if (strlen(linha) > 1) { // para pegar apenas linhas que nao sejam vazias
					tokenizarMatriz(linha, cont, mat, espelho);
					cont++; // cada cont representa a linha atual

					if (cont == n) { // se cont == n entao a matriz atual foi lida
						espelho->chk = varCHK;
						dados->maxFile = varCHK;

						dados->mat = mat;
						dados->chk = varCHK;

						createCheckpoint(dados);
						createCheckpointEspelho(espelho);

						varCHK++; // para contar quantas matrizes existem

						cont = 0; // se tiver mais matrizes, entao a linha reseta
					}
				}
			}
		}
	}
	fclose(file);
}

void readCheckpoint(Dados *dados) {
	char *str = (char *)malloc(TAM);
	sprintf(str, "dataset/checkpoint/check_m%d.data", dados->chk);
	int aux = 0;
	int cont = 0;

	FILE *file = fopen(str, "r");

	char *result, linha[TAM];

	if (file == NULL) {
		printf("Nao foi possivel abrir o arquivo: %s\n", str);
	} else {
		while (!feof(file)) {
			result = fgets(linha, sizeof(linha), file);

			if (result) {
				if (aux == 0) {
					aux = 1;
					tokenizarLinha(linha, &dados->n, &dados->m);

					dados->mat = malloc(dados->n * sizeof(int **));

					for (int i = 0; i < dados->m; i++) {
						dados->mat[i] = malloc(dados->m * sizeof(int *));
					}
				} else if (strlen(linha) > 1) {
					tokenizarMatriz(linha, cont, dados->mat, NULL);
					cont++;
				}
			}
		}
	}
	if (cont == dados->n) {
		createCheckpoint(dados);
	}
	fclose(file);
}

void readCheckpointEspelho(Espelho *espelho) {
	char *str = (char *)malloc(TAM);
	sprintf(str, "dataset/espelho/check_m%d.data", espelho->chk);
	int aux = 0;
	int cont = 0;

	FILE *file = fopen(str, "r");

	char *result, linha[TAM];

	if (file == NULL) {
		printf("Nao foi possivel abrir o arquivo: %s\n", str);
	} else {
		while (!feof(file)) {
			result = fgets(linha, sizeof(linha), file);

			if (result) {
				if (aux == 0) {
					aux = 1;
					tokenizarLinha(linha, &espelho->n, &espelho->m);

					espelho->mat = malloc(espelho->n * sizeof(int **));

					for (int i = 0; i < espelho->m; i++) {
						espelho->mat[i] = malloc(espelho->m * sizeof(int *));
					}
				} else if (strlen(linha) > 1) {
					tokenizarMatriz(linha, cont, NULL, espelho);
					cont++;
				}
			}
		}
	}
	if (cont == espelho->n) {
		createCheckpointEspelho(espelho);
	}
	fclose(file);
}

void contLidoeNaoLido(int *lido, int *naoLido, int max) {
	Espelho espelho;
	for (int i = 1; i < max + 1; i++) {
		espelho.chk = i;
		readCheckpointEspelho(&espelho);
		for (int j = 0; j < espelho.n; j++) {
			for (int k = 0; k < espelho.m; k++) {
				if (espelho.mat[j][k] == '+') (*lido)++;
				else if (espelho.mat[j][k] == '-') (*naoLido)++;
			}
		}
	}

}

// void createCheckpoint(int **mat, int n, int m, int chk) {
void createCheckpoint(Dados *dados) {
	char *str = (char *)malloc(TAM);
	sprintf(str, "dataset/checkpoint/check_m%d.data", dados->chk);

	FILE *file = fopen(str, "w");

	if (file == NULL) {
		printf("Nao foi possivel abrir o arquivo\n");
	} else {
		fprintf(file, "%d %d\n", dados->n, dados->m);
		for (int i = 0; i < dados->n; i++) {
			for (int j = 0; j < dados->m; j++) {
				char *var = (char *)malloc(5);
				sprintf(var, "%3d", dados->mat[i][j]);
				fprintf(file, "%s", var);
				free(var);
			}
			fprintf(file, "%s", "\n");
		}
	}
	fclose(file);
	free(str);
}

void createCheckpointEspelho(Espelho *espelho) {
	char *str = (char *)malloc(TAM);
	sprintf(str, "dataset/espelho/check_m%d.data", espelho->chk);

	FILE *file = fopen(str, "w");

	if (file == NULL) {
		printf("Nao foi possivel abrir o arquivo: %s\n", str);
	} else {
		fprintf(file, "%d %d\n", espelho->n, espelho->m);
		for (int i = 0; i < espelho->n; i++) {
			for (int j = 0; j < espelho->m; j++) {
				char *var = (char *)malloc(5);
				sprintf(var, "%c ", espelho->mat[i][j]);
				fprintf(file, "%s", var);
				free(var);
			}
			fprintf(file, "%s", "\n");
		}
	}
	fclose(file);
	free(str);
}

void createOutput(Dados *dados) {
	char *str = (char *)malloc(TAM);
	sprintf(str, "dataset/output.data");

	FILE *file = fopen(str, "a");

	if (file == NULL) {
		printf("Nao foi possivel abrir o arquivo\n");
	} else {
		char c[] = "(x)";
		fprintf(file, "\nMatriz atual: %d\n", dados->chk);
		fprintf(file, "Posição atual: (%d, %d)\n", (dados->i) + 1, (dados->j) + 1);
		fprintf(file, "Vidas: %d\n", dados->vida);
		for (int i = 0; i < dados->n; i++) {
			for (int j = 0; j < dados->m; j++) {
				if (dados->i == i && dados->j == j) fprintf(file, "%-5s ", c);
				else fprintf(file, "%-5d ", dados->mat[i][j]);
			}
			fprintf(file, "\n");
		}
		fprintf(file, "\n");
	}
	fclose(file);
	free(str);
}

void createRelatorio(int itens, int perigos, int lido, int naoLido, int vidaGanha) {
	char *str = (char *)malloc(TAM);
	sprintf(str, "dataset/relatorio.data");

	FILE *file = fopen(str, "w");

	if (file == NULL) {
		printf("Nao foi possivel abrir o arquivo\n");
	} else {
		fprintf(file, "\nRelatório Final: \n");
		fprintf(file, "\n(A) Casas percorridas: %d\n", lido);
		fprintf(file, "\n(B) Itens consumidos: %d\n", itens);
		fprintf(file, "\n(C) Casas não exploradas: %d\n", naoLido);
		fprintf(file, "\n(D) Perigos enfrentados: %d\n", perigos);
		fprintf(file, "\n(E) Vidas ganhas: %d\n", vidaGanha);
		fprintf(file, "\n");
	}
	fclose(file);
	free(str);
}