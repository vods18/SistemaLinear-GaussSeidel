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

//função para "limpar" string
void clean_fgets(char *pos) { 
  strtok(pos, "\n");
}

// Gauss-Seidel 
void gaussSeidel(bag *e) {
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


  for(i=0;i<n;i++){ //copiar dados calculados para *x
    x[i] = r[i];
  }

  e->r = x; //copiar dados para estrutura
}

void SL(bag *e, double **mat, double **matrix_diag){

  int intervalo = (e->k - 1)/2; 
  // preenche as diagonais secundárias
  for(int i = 1; i<=intervalo; i++){
    for(int j = i, k = 0; j <= (e->n - 1) ; j++, k++){
      mat[k][j] = matrix_diag[intervalo-i][k];
      mat[j][k] = matrix_diag[intervalo+i][k];
    }
  }

  // preenche a diagonal principal
  for(int i=0; i<= (e->n - 1); i++){
    mat[i][i] = matrix_diag[intervalo][i];
  }

  e->f = mat;

}

void calcula_independentes(bag *e, double **matrix_diag){

  double *indep = (double *) malloc((e->n) * sizeof(double));
  for(int i = 0; i <= (e->n - 1); i++){
    indep[i] = matrix_diag[e->n - 1][i];
  }
  e->termos_independentes = indep;

}

void calcula_tempo(bag *e){

  //calculamos tempo antes de executar o gaussSeidel e depois pra fazermos a diferença de ambos
  e->tempo=0;
  e->tempo = timestamp();
  gaussSeidel(e);
  e->tempo = timestamp() - e->tempo;


}

void imprime_saida(bag *e){

  printf("SL gerado:\n");  //impressao do sistema linear gerado
  for (int row=0; row<=e->k; row++){
    for(int columns=0; columns<e->n; columns++){
      printf("%f     ", e->f[row][columns]);
    }
    printf("\n");
  }

  printf("\nTermos independentes: \n");  //impressao dos termos independentes
  for(int i=0; i <=(e->n - 1); i++){
    printf("%f     ", e->termos_independentes[i]);
  }

  printf("\n\n----------------------------------\n\n");

  printf("solucao:   "); //impressao do vetor de solucao
  for(int i=0; i <=(e->n - 1); i++){
    printf("%f     ", e->r[i]);
  }

  printf("\n");
  printf("tempo: %f  ",e->tempo); //impressao do tempo de execucao
  printf("\n");

}

void exerc02(bag *e){

  // usar libmatheval para gerar vetores com os valor de 0 até n para cada equação
  int i, j, k, l, row, columns;
  double **matrix_diag, linha[e->n], func;

  matrix_diag = malloc ((e->k) * sizeof (double*)); //aloca espaco para matrix_diag com valores da diagonal 
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
  
  double **mat; //aloca espaco da matriz mat com possiveis resultados
  mat = malloc ((e->n) * sizeof (double*)) ;
  for (i=0; i <= (e->n); i++){
    mat[i] = malloc ((e->n) * sizeof (double));
  }

  for(i = 0; i<= (e->n); i++){
    for(j = 0; j <= (e->n) ; j++){
      mat[i][j] = 0;
    }
  }

  SL(e, mat, matrix_diag); //Gera sistema linear
  calcula_independentes(e, matrix_diag); //Calcula termos independentes
  calcula_tempo(e); //calcula tempo de execucao
  imprime_saida(e); //imprime saida final
  
} 