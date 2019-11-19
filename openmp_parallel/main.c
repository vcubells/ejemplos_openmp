//
//  main.c
//  openmp_parallel
//
//  Created by Vicente Cubells Nonell on 27/10/14.
//  Copyright (c) 2014 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <omp.h>

int main(int argc, const char * argv[]) {
    
    int n = 1000000;
    
    int suma = 0;
    
    int i;
    
    int numeros[n];
    
    for (i = 0; i < n; ++i) {
        numeros[i] = 1;
    }
    
    
    
#pragma omp parallel default(none) shared(n, numeros, suma) private(i) num_threads(8) if (n > 100)
{
    int nhilos = omp_get_num_threads();
    int id = omp_get_thread_num();
    
    int bloque = n / nhilos;
    
    int inicio = id * bloque;
    int fin = (id + 1) * bloque;
   
    for (i = inicio; i < fin; ++i) {
       // Región crítica
#pragma omp critical
        {
        suma += numeros[i];
        }
        
    }
    
    printf("La suma del hilo %d de %d = %d\n", id, nhilos, suma);
}

    printf("La suma total es = %d\n", suma);
    
    return 0;
}
