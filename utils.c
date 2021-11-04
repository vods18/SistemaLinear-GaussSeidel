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

void gauss_seidel(entrada *c){
  
}

void generate_matrix(entrada *e){

  // usar libmatheval para gerar vetores com os valor de 0 até n para cada equação
  int i, j;
  double matrix_diag[e->k][e->n], linha[e->n], func;

  for(i=0; i<=e->k ; i++){
    clean_fgets(e->eq[i]);
    printf("equation: %s - size:  %lu\n", e->eq[i], strlen(e->eq[i]));
    void *f = evaluator_create(e->eq[i]);
    assert(f);
    for(j=0; j<=e->n; j++){
        func = evaluator_evaluate_x(f, j);
        linha[j] = func;
    }
    *matrix_diag[i] = *linha;
    free(f);
  }

int row, columns;
for (row=0; row<=e->k; row++)
{
    for(columns=0; columns<=e->n; columns++)
    {
         printf("%le     ", matrix_diag[row][columns]);
    }
    printf("\n");
}
  

  // int min = e->n/2 + 1;
  // for(i=0; i<=e->n-1; i++){
  //   for(j=0; j<=min; j++){

  //   }
    
  //   if(min < e->k && i <ceil(e->k/2)){
  //     min++;
  //   } else if(min == e->k){
  //     min--;
  //   } else if(min < e->k && i >ceil(e->k/2)){
  //     min--;
  //   }
  // }
  

}