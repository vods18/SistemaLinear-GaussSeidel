#include "utils.h"
#include <string.h>
#include <math.h>
#include <matheval.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <stdlib.h>

//calcula tempo de execucao em milisegundos
double timestamp(){
  struct timeval tp;
  gettimeofday(&tp, NULL);
  return((double)(tp.tv_sec*1000.0 + tp.tv_usec/1000.0));
}

void clean_fgets(char *pos) { //função para "limpar" string
  strtok(pos, "\n");
}

void gauss_seidel(entrada *e){
  
}
/*
void SL(entrada *e, double **matrix_diag){
  int largura = (e->k - 1)/2; //2 pra cima 2 pra baixo
  for(int i = 1; i<=largura; i++){
    for(int j = i, l = 0; j < (e->n -1) ; j++, l++){
      e->f[l][j] = matrix_diag[largura-i][l];
      e->f[j][l] = matrix_diag[largura+i][l];
    }
  }
}*/

void generate_matrix(entrada *e){

  // usar libmatheval para gerar vetores com os valor de 0 até n para cada equação
  int i, j, k, l;
  double matrix_diag[e->k][e->n - 1], linha[e->n], func;

  for(i=0; i<=e->k ; i++){
    clean_fgets(e->eq[i]);
    void *f = evaluator_create(e->eq[i]);
    assert(f);

    for(j=0; j<e->n; j++){
      func = evaluator_evaluate_x(f, j);
      linha[j] = func;
    }

    for(k=0; k<e->n; k++){
      matrix_diag[i][k] = linha[k];
    }
    
    free(f);
  }

  int row, columns;
  for (row=0; row<=e->k; row++)
  {
      for(columns=0; columns<e->n; columns++)
      {
          printf("%le     ", matrix_diag[row][columns]);
      }
      printf("\n");
  }

  int q = (e->k - 1)/2; //2 pra cima 2 pra baixo
  printf("%d", q);
  for(i = 1; i<=q; i++){
    for(j = i, l = 0; j < (e->n -1) ; j++, l++){
      e->f[l][j] = matrix_diag[q-i][l];
      e->f[j][l] = matrix_diag[qecvt+i][l];
      printf("%le     ", e->f[l][j]);
      printf("%le     ", e->f[j][l]);
    }
    printf("\n");
  }

  //SL(e, matrix_diag);

  for (row=0; row<=e->k; row++){
      for(columns=0; columns<e->n; columns++)
      {
          printf("%le     ", e->f[row][columns]);
      }
      printf("\n");
  }

}

  