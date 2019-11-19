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

#define N 1000

int main(int argc, const char * argv[]) 
{
    int i,j;
    int size = N * N;
    int A[size], B[size], S[size];

    srand(time(NULL));
    
    // /* Inicializar las matrices */
    #pragma omp parallel for private(i) shared(A, B, size)
    for (i = 0; i < size; ++i) {
            A[i] = rand() % 100;
            B[i] = rand() % 100;
    }
    
    /* Sumar las matrices */
    #pragma omp parallel for private(i, j) shared(A, B, S) collapse(2)
    for (i = 0; i < N; ++i) 
    {
        for (j = 0; j < N; ++j) 
        {
            int pos = i * N + j;
            S[pos] = A[pos] + B[pos];
        }
    }

    /* Imprimir la matriz */
    for (i = 0; i < N; ++i) 
    {
        for (j = 0; j < N; ++j) 
        {
            int pos = i * N + j;
            printf("[%d,%d] = %d\t", i, j , S[pos]);
        }

        printf("\n");
    }

    

    return 0;
}
