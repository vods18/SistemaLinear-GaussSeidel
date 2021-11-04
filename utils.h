#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>
#include <inttypes.h>

typedef struct entrada {
    int n; //dimensao do SL
    int k; //numero de diagonais
    char **eq; //equacoes auxiliares pra montagem da matriz
    double **f; //matriz de strings com as expressoes
    double *termos_independentes;  
    double epsilon; //tolerancia no metodo de gauss seidel
    int max_iter; //numero maximo de iterações
    double *r; // resultados
    double tempo;
}entrada;

double timestamp();

void clean_fgets(char *pos);

void generate_matrix(entrada *e);

void SL(entrada *e, double **matrix_diag, double **mat);

void calcula_tempo(entrada *e);

void imprime_saida(entrada *e);

void gaussSeidel(entrada *e);

#endif // __UTILS_H__
