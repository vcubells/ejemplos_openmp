//
//  main.c
//  omp_critical
//
//  Created by Vicente Cubells Nonell on 03/11/14.
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
        
        if (id == nhilos - 1) { fin = n; }
        
        int suma_local = 0;
        
        for (i = inicio; i < fin; ++i) {
            suma_local += numeros[i];
        }
        
        // Región crítica
        #pragma omp critical
        {
            suma += suma_local;
        }

        
        printf("La suma del hilo %d de %d = %d\n", id, nhilos, suma_local);
    }
    
    printf("La suma total es = %d\n", suma);
    
    return 0;
}

