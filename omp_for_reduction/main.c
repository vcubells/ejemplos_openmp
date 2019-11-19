//
//  main.c
//  omp_for_reduction
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
    
#pragma omp parallel for default(none) shared(n, numeros) private(i)
    for (i = 0; i < n; ++i) {
        numeros[i] = 1;
    }
    
    
    
#pragma omp parallel for default(none) shared(n, numeros) private(i) reduction(+:suma)
    for (i = 0; i < n; ++i) {
            suma += numeros[i];
    }
    
    printf("La suma total es = %d\n", suma);
    
    return 0;
}


