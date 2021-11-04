void aloca_matriz(double **mat, double lin, double col){

  mat = malloc ((lin) * sizeof (double*)) ;
  for (int i=0; i <= (lin); i++){
    mat[i] = malloc ((col) * sizeof (double));
  }

  for(int i = 0; i<= (lin); i++){
    for(int j = 0; j <= (col) ; j++){
      mat[i][j] = 0;
    }
  }

}



void SL(entrada *e, double **matrix_diag, double **mat){
  // preenche o sistema linear (matriz principal) ------------------------------

  int intervalo = (e->k - 1)/2; //2 pra cima 2 pra baixo

  // diagonais nos extremos 
  for(int i = 1; i<=intervalo; i++){
    for(int j = i, l = 0; j <= (e->n - 1) ; j++, l++){
      mat[l][j] = matrix_diag[intervalo-i][l];
      mat[j][l] = matrix_diag[intervalo+i][l];
    }
  }

    // diagonal principal
  for(int i=0; i<= (e->n - 1); i++){
    mat[i][i] = matrix_diag[intervalo][i];
  }

  e->f = mat;
  
}

void aloca_matriz(double **mat, double lin, double col){

  //alocamos vetor de ponteiros com linhas
  mat = malloc (lin * sizeof (double*)) ;
  for (int i=0; i <= (lin); i++){
    //alocamos colunas ligadas aos ponteiros linhas
    mat[i] = malloc ((col) * sizeof (double));
  }

  //limpa matriz
  for(int i = 0; i<= (lin); i++){
    for(int j = 0; j <= (col) ; j++){
      mat[i][j] = 0;
    }
  }

  double *indep = (double *) malloc((e->n) * sizeof(double));
  for(i = 0; i <= (e->n - 1); i++){
    indep[i] = matrix_diag[e->n - 1][i];
  }
  e->termos_independentes = indep;

}