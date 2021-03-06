#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

 

int main(int argc, const char *argv[])
{
    int i;
    double x;
    double pi;
    long steps = 1000000000;

    if (argc > 1)
    {
        steps = atoi(argv[1]);
    }
    else {
        printf("Use: %s [puntos]\n", argv[0]);
    }

    double step = 1.0 / (double)steps;

    double sum = 0.0;
    double start = omp_get_wtime();

    #pragma omp parallel for reduction(+ : sum) private(x, i)
    for (i = 0; i < steps; i++)
    {
        x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    pi = step * sum;
    double delta = omp_get_wtime() - start;

    printf("PI = %.16g calculado en %.4g segundos con %ld puntos\n", pi, delta, steps);
}