#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
    long steps = 1000000000;

    if (argc > 1)
    {
        steps = atoi(argv[1]);
    }
    else
    {
        printf("Use: %s [puntos]\n", argv[0]);
    }

    double step = 1.0 / (double)steps;

    double sum = 0.0;
    double start = omp_get_wtime();

#pragma omp parallel
    {
        int nhilos = omp_get_num_threads();
        int id = omp_get_thread_num();

        int num = steps / nhilos;
        int inicio = id * num;
        int fin = inicio + num;

        if (id == (nhilos - 1))
        {
            fin = steps;
        }

        int suma_local = 0;
        double x;

        for (int i = inicio; i < fin; i++)
        {
                x = (i + 0.5) * step;
                suma_local += 4.0 / (1.0 + x * x);    
        }

          #pragma omp critical
            {
                sum += suma_local;
            }

    }

    double pi = step * sum;
    double delta = omp_get_wtime() - start;

    printf("PI = %.16g calculado en %.4g segundos con %ld puntos\n", pi, delta, steps);
}