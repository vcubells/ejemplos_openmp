#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, const char * argv[]) {

    int n = 100;

    if (argc == 1)
    {
        printf("Use: %s <número de items>\n", argv[0]);
        exit(0);
    }
    else {
        n = atoi(argv[1]);
    }

    int suma = 0;

    int i;

    int numeros[n];
    double t_inicial = 0, t_final = 0;

    t_inicial = omp_get_wtime();

    #pragma omp parallel for private(i) if (n > 100)
    for (i = 0; i < n; ++i) {
        numeros[i] = 1;
    }

    t_final = omp_get_wtime();

    printf("La inicialización del vector demoró %.5f\n", t_final - t_inicial);

    t_inicial = omp_get_wtime();

    #pragma omp parallel for private(i) reduction(+:suma) if (n > 100)
        for (i = 0; i < n; ++i) {
            suma += numeros[i];
            int id = omp_get_thread_num();
            printf("Hilo %d = [%d]\n", id, i);
        }

    t_final = omp_get_wtime();

    printf("La suma del vector demoró %.5f\n", t_final - t_inicial);

    printf("La suma = %d\n", suma);
    
    return 0;

}
