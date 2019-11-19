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

    #pragma omp parallel private(i)
    {
       int nhilos = omp_get_num_threads();
       int id = omp_get_thread_num();
	
       int num = n / nhilos;
       int inicio = id * num;
       int fin = inicio + num;

       if (id == (nhilos - 1)) { fin = n; }

       int suma_local = 0;

        for (i = inicio; i < fin; ++i) {
            suma_local += numeros[i];
        }

        //printf("La suma parcial del hilo %d = %d\n", id, suma_local);

        #pragma omp critical
        {
            suma += suma_local;
        }

        printf("Soy el hilo %d de %d y proceso el elemento [%d]\n", id, nhilos, i);
    }

    t_final = omp_get_wtime();

    printf("La suma del vector demoró %.5f\n", t_final - t_inicial);

    //printf("La suma = %d\n", suma);
    
    return 0;

}
