#ifndef MATRIZ_H
#define MATRIZ_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define TAM 1024
#define PAREDE -1
#define PERIGO -2

#define PAREDE_C '#'
#define PERIDO_C '*'

#define TRUE_C '+'
#define FALSE_C '-'

typedef struct Dados Dados;

struct Dados {
	int **mat;
	int n;
	int m;
	int i;
	int j;
	int chk;
	int vida;
	int maxFile;
	int seq;
};

typedef struct Espelho Espelho;

struct Espelho {
	char **mat;
	int n;
	int m;
	int chk;
};

void tokenizarMatriz(char *str, int cont, int **matrix, Espelho *espelho);
void tokenizarLinha(char *str, int *n, int *m);

void readFile(Dados *dados, Espelho *espelho);
void readCheckpoint(Dados *dados);
void readCheckpointEspelho(Espelho *espelho);

void createCheckpoint(Dados *dados);
void createCheckpointEspelho(Espelho *espelho);
void createOutput(Dados *dados);
void createRelatorio(int itens, int perigos, int lido, int naoLido, int vidaGanha);

void percorrerMatriz(Dados *dados, Espelho *espelho, int *itens, int *perigos, int *vidaGanha);
void printRelatorio(Espelho dados);
void contLidoeNaoLido(int *lido, int *naoLido, int max);

void testaLocal(Dados *dados, Espelho *espelho, int *perigos, int *vidaGanha, int i, int j, int *cont);

#endif
