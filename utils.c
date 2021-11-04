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

void gaussSeidel(entrada *e) {
  int i,j,p,q,d;
  unsigned int n = e->n;
  double *r =  malloc((e->n) * sizeof (double)) ;
  double temp,sum,erroMaximo,erroCalculado;
  double **A = e->f;
  double *b = e->termos_independentes;
  double *x = malloc((e->n) * sizeof(double));
  e->r = malloc((e->n) * sizeof(double));

  // A[n][n] = Matriz principal (e->f)
  // b[n] = vetor_independente (e->termos_independentes)

  // Gauss-Seidel --------------------------------------------------------
  for(i=0;i<n;i++){
      r[i] = 0;
  }
  p = 1;
  q = 1;
  do{
      erroCalculado = 0;
      p++;
      q++;
      for(i=0;i<n;i++){
          sum = 0;
          for(j=0;j<n;j++){
              if(i != j){
                  sum = sum + (A[i][j] * r[j]);
              }
          }
          temp = -1.0 / A[i][i] * sum + b[i] / A[i][i];
          erroMaximo = fabs(temp - r[i]);
          r[i] = temp;
          if(erroMaximo > erroCalculado){
              erroCalculado = erroMaximo;
          }
      }
  }while(erroCalculado >= e->epsilon && q<=e->max_iter);
  // -------------------------------------------------------------------------


  for(i=0;i<n;i++){ //copiar dados calculados para *x
    x[i] = r[i];
  }

  e->r = x;

  // colocar resultado na estrutura e

}

void imprime_saida(entrada *e){

  printf("SL gerado:\n");  
  for (int row=0; row<=e->k; row++){
    for(int columns=0; columns<e->n; columns++){
      printf("%f     ", e->f[row][columns]);
    }
    printf("\n");
  }

  printf("\nTermos independentes: \n");
  for(int i=0; i <=(e->n - 1); i++){
    printf("%f     ", e->termos_independentes[i]);
  }

  printf("\n\n----------------------------------\n\n");

  printf("solucao:   ");
  for(int i=0; i <=(e->n - 1); i++){
    printf("%f     ", e->r[i]);
  }

  printf("\n");
  printf("tempo: %f  ",e->tempo);
  printf("\n");

}

void generate_matrix(entrada *e){

  // usar libmatheval para gerar vetores com os valor de 0 até n para cada equação
  int i, j, k, l, row, columns;
  double **matrix_diag, linha[e->n], func;

  matrix_diag = malloc ((e->k) * sizeof (double*)) ;
  for (i=0; i <= (e->k); i++){
    matrix_diag[i] = malloc ((e->n - 1) * sizeof (double));
  }

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


  //int row, columns;
  int intervalo = (e->k - 1)/2; //2 pra cima 2 pra baixo
  double **mat;
  // mat = malloc((e->n-1) * (e->n-1) * sizeof(double));
  mat = malloc ((e->n) * sizeof (double*)) ;
  for (i=0; i <= (e->n); i++){
    mat[i] = malloc ((e->n) * sizeof (double));
  }

  for(i = 0; i<= (e->n); i++){
    for(j = 0; j <= (e->n) ; j++){
      mat[i][j] = 0;
    }
  }

  for(i = 1; i<=intervalo; i++){
    for(j = i, l = 0; j <= (e->n - 1) ; j++, l++){
      mat[l][j] = matrix_diag[intervalo-i][l];
      mat[j][l] = matrix_diag[intervalo+i][l];
    }
  }

  for(i=0; i<= (e->n - 1); i++){
    mat[i][i] = matrix_diag[intervalo][i];
  }

  e->f = mat;

  double *indep = (double *) malloc((e->n) * sizeof(double));
  for(i = 0; i <= (e->n - 1); i++){
    indep[i] = matrix_diag[e->n - 1][i];
  }
  e->termos_independentes = indep;

  e->tempo=0;
  e->tempo = timestamp();
  gaussSeidel(e);
  e->tempo = timestamp() - e->tempo;

  imprime_saida(e);
  
} 