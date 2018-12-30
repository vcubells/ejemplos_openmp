//
//  main.c
//  omp_sections
//
//  Created by Vicente Cubells Nonell on 06/11/14.
//  Copyright (c) 2014 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <omp.h>

#define N 100000

int main(int argc, const char * argv[]) {
    
    int suma[N], resta[N], A[N], B[N];
    int i;
    
    omp_set_nested(1);
    
    /* Incializar los arreglos */
#pragma omp parallel for private(i) shared(A, B)
    for (i = 0; i < N; ++i) {
        A[i] = rand() % 100;
        B[i] = rand() % 100;
    }
    
    #pragma omp parallel num_threads(2)
    {
        #pragma omp master
        printf("No. hilos externos = %d\n", omp_get_num_threads());
        
            #pragma omp sections
            {
                #pragma omp section
                {
                    //printf("Hilo %d realiza la suma\n", omp_get_thread_num());
                    #pragma omp parallel for private(i) num_threads(4)
                    for (i = 0; i < N; ++i)
                    {
                        //printf("Hilo interno %d resuelve suma[%d]\n",
                        //       omp_get_thread_num(), i);
                        suma[i] = A[i] + B[i];
                    }
                }
                
                #pragma omp section
                {
                    //printf("Hilo %d realiza la resta\n", omp_get_thread_num());
                    #pragma omp parallel for private(i) num_threads(4)
                    for (i = 0; i < N; ++i)
                    {
                        //printf("Hilo interno %d resuelve resta[%d]\n",
                         //      omp_get_thread_num(), i);
                        resta[i] = A[i] - B[i];
                    }
                }
            }
    }
    
    return 0;
}
