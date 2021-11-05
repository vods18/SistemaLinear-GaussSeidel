#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>
#include <inttypes.h>

typedef struct bag {
    int n; //dimensao do SL
    int k; //numero de diagonais
    char **eq; //strings com equacoes auxiliares pra montagem da matriz
    double **f; //matriz de strings com as expressoes
    double *termos_independentes;  
    double epsilon; //tolerancia no metodo de gauss seidel
    int max_iter; //numero maximo de iterações
    double *r; //vetor de resultados finais
    double tempo; //tempo de execucao
}bag;

double timestamp();

void clean_fgets(char *pos);

void exerc02(bag *e);

void SL(bag *e, double **matrix_diag, double **mat);

void calcula_independentes(bag *e, double **matrix_diag);

void calcula_tempo(bag *e);

void imprime_saida(bag *e);

void gaussSeidel(bag *e);

#endif // __UTILS_H__
