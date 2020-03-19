//
//  main.c
//  omp_multi_matrices
//
//  Created by Vicente Cubells Nonell on 06/11/14.
//  Copyright (c) 2014 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 10

int main(int argc, const char * argv[]) 
{
    int i,j;
    int A[N][N], B[N][N], S[N][N];

    srand(time(NULL));
    
    // /* Inicializar las matrices */
    #pragma omp parallel for private(i) shared(A, B)
    for (i = 0; i < N; ++i) 
    {
        #pragma omp parallel for private(j)
        for (j = 0; j < N; ++j)
        {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
        }
            
    }
    
    /* Sumar las matrices */
    #pragma omp parallel for private(i) shared(A, B, S)
    for (i = 0; i < N; ++i) 
    {
        #pragma omp parallel for private(j)
        for (j = 0; j < N; ++j) 
        {
            S[i][j] = A[i][j] + B[i][j];
        }
    }

    /* Imprimir la matriz */
    for (i = 0; i < N; ++i) 
    {
        for (j = 0; j < N; ++j) 
        {
            printf("[%d,%d] = %d\t", i, j , S[i][j]);
        }

        printf("\n");
    }

    return 0;
}
