#include "utils.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>

void clean_fgets(char *pos) { //função para "limpar" string
  strtok(pos, "\n");
}

void generate_matrix(char* equacoes, int n, int k){

  // usar libmatheval para gerar vetores com os valor de 0 até n para cada equação
  double* values[k];
  int i, j;
  for(i=0; i<=k ; i++){
    double linha[n];
    for(j=0; j<=n; j++){
        void *f;
        double func[];
        f = evaluator_create(equacoes[j]);
        func = evaluator_evaluate_x(f, j);
        linha[j] = func;
    }
    values[i] = linha;
  }
  

  int min = n/2 + 1;
  for(i=0; i<=n-1; i++){
    for(j=0; j<=min; j++){

    }
    
    if(min < k && i <ceil(k/2)){
      min++;
    } else if(min == k){
      min--;
    } else if(min < k && i >ceil(k/2)){
      min--;
    }
  }




}