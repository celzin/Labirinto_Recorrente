#include "matriz.h"

// funcao que tokeniza a matriz do arquivo
void tokenizarMatriz(char *str, int cont, int **matrix) {
    int val, col=0;
	const char sep[] = " ";
	char *tokens;
	tokens = strtok(str, sep);
	
    while (tokens != NULL) {

        if(strcmp("#", tokens) == 0){
            val = PAREDE;
        }
        else if(strcmp("*", tokens) == 0){
            val = PERIGO;
        }
        else{
            val = atoi(tokens);
        }
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
        if(aux == 0){
            *n = atoi(tokens);
            aux++;
        }else{
            *m = atoi(tokens);
        }
		tokens = strtok(NULL, sep);
	}
}

// funcao que le tamanho e matrizes do aquivo
int **readFile(Dados *dados) {
	char *str = (char *)malloc(TAM);
	strcpy(str, "dataset/example.data");
    int aux = 0;
    int n, m, cont = 0, **mat;

	FILE *file = fopen(str, "r");

	char *result, linha[TAM];
    int varCHK=1;

	if (file == NULL) {
		printf("Nao foi possivel abrir o arquivo\n");
	} else {
		while (!feof(file)) {
			result = fgets(linha, sizeof(linha), file);

			if (result) {
				if(aux == 0){
                    aux = 1;
                    tokenizarLinha(linha, &n, &m);
                    dados->m = m;
                    dados->n = n;
                    
                    mat = malloc(n*sizeof(int **));

                    for(int i=0; i<m; i++){
                        mat[i] = malloc(m*sizeof(int *));
                    }
                }else if(strlen(linha) > 1){
                    tokenizarMatriz(linha, cont, mat);
                    cont++;
                }else{
                    if(cont == n){
                        createCheckpoint(mat, n, m, varCHK++);
                    }
                    cont=0;
                }
            }
		}
	}
    if(cont == n){
      createCheckpoint(mat, n, m, varCHK++);
    }
    dados->maxFile=varCHK-1;
	fclose(file);
    return mat;
}

void readCheckpoint(Dados *dados){
    char *str = (char *)malloc(TAM);
	sprintf(str, "dataset/checkpoint/check_m%d.data", dados->chk);
    int aux = 0;
    int cont = 0;

	FILE *file = fopen(str, "r");

	char *result, linha[TAM];
    int varCHK=1;

	if (file == NULL) {
		printf("Nao foi possivel abrir o arquivo: %s\n", str);
	} else {
		while (!feof(file)) {
			result = fgets(linha, sizeof(linha), file);

			if (result) {
				if(aux == 0){
                    aux = 1;
                    tokenizarLinha(linha, &dados->n, &dados->m);
                    
                    dados->mat = malloc(dados->n*sizeof(int **));

                    for(int i=0; i<dados->m; i++){
                        dados->mat[i] = malloc(dados->m*sizeof(int *));
                    }
                }else if(strlen(linha) > 1){
                    tokenizarMatriz(linha, cont, dados->mat);
                    cont++;
                }
            }
		}
	}
    if(cont == dados->n){
      createCheckpoint(dados->mat, dados->n, dados->m, dados->chk);
    }
	fclose(file);
}

void createCheckpoint(int **mat, int n, int m, int chk) {
	char *str = (char *)malloc(TAM);
    sprintf(str, "dataset/checkpoint/check_m%d.data", chk);

	FILE *file = fopen(str, "w");

	if (file == NULL) {
		printf("Nao foi possivel abrir o arquivo\n");
	} else {
        fprintf(file, "%d %d\n", n, m);
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
		        char *var = (char *)malloc(5);
                sprintf(var, "%3d", mat[i][j]);
		        fprintf(file, "%s", var);
		        free(var);
            }
            fprintf(file, "%s", "\n");
        }
	}
	fclose(file);
	free(str);
}