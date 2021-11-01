#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "utils.h"
#include <inttypes.h>


int main (){

  //declaracao de variáveis e vetor de acordo com formato proposto
  int n,k,i, max_int;
  float epsilon;

  //leitura das variáveis a partir de um arquivo 
  scanf("%i", &n);
  scanf("%i", &k);

  char* equacoes[k];


  for(i=0; i<=k; i++){
    char *equacao = malloc(sizeof(500));
    fgets(equacao, 24, stdin);
    char ch;
    if(strlen(equacao) > 0){
      ch = equacao[0];
    }
    if(equacao == NULL || equacao == "" || equacao == " " || equacao == "\n" || equacao == "\0" || ch == 13){
      fgets(equacao, 24, stdin);
    }
    equacoes[i] = equacao;
  }

  for(i=0; i<=k; i++){
    printf("equação %d = %s",i,equacoes[i]);
  }


  scanf("%f", &epsilon);
  scanf("%i", &max_int);

  printf("n = %d\n",n);
  printf("k = %d\n",k);
  printf("epsilon = %f\n",epsilon);
  printf("max_int = %d\n",max_int);

  generate_matrix(equacoes, n, k);

  //func_compare(equacao, x0, epsilon, max_iter); //execução do laço principal para a execução das aproximações de cada iteração necessária

}
