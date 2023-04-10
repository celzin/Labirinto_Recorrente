#ifndef MATRIZ_H
#define MATRIZ_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define TAM 100
#define PAREDE -1
#define PERIGO -2

typedef struct Dados Dados;

struct Dados{
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

void tokenizarMatriz(char *str, int cont, int **matrix);
void tokenizarLinha(char *str, int *n, int *m);
int **readFile(Dados *dados);

void printMatriz(Dados dados);

void createCheckpoint(int **mat, int n, int m, int chk);
void readCheckpoint(Dados *dados);
void percorrerMatriz(Dados *dados);

#endif
