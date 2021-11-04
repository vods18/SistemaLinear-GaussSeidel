#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "utils.h"
#include <inttypes.h>


int main (){

  //declaracao de variáveis e vetor de acordo com formato proposto
  entrada *e;

  //leitura das variáveis a partir de um arquivo 
  scanf("%i", &(e->n));
  scanf("%i", &(e->k));

  //e->eq = malloc(sizeof(500));
  e->eq[e->k]; 


  for(int i=0; i<=e->k; i++){
    char *equacao = malloc(sizeof(500));
    fgets(equacao, 24, stdin);
    char ch;
    if(strlen(equacao) > 0){
      ch = equacao[0];
    }
    if(equacao == NULL || equacao == "" || equacao == " " || equacao == "\n" || equacao == "\0" || ch == 13 || ch==10){
      fgets(equacao, 24, stdin);
    }
    e->eq[i] = equacao;
  }

  for(int i=0; i<=e->k; i++){
    printf("equação = %s",e->eq[i]);
  }


  scanf("%le", &(e->epsilon));
  scanf("%i", &(e->max_iter));

  printf("n = %d\n",e->n);
  printf("k = %d\n",e->k);
  printf("epsilon = %f\n", e->epsilon);
  printf("max_int = %d\n", e->max_iter);

  generate_matrix(e);

  //func_compare(equacao, x0, epsilon, max_iter); //execução do laço principal para a execução das aproximações de cada iteração necessária

}
