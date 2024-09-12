#include <stdio.h>
#include <math.h>
#include "../vector/vector.h"
#include <stdlib.h>

double trapz(double(f)(double), double a, double b, size_t n);

int main(void)
{
    double a = 0;
    double b = PI;
    double n = 10000;

    vector_t *x = linspace(a, b, n);
    vector_t *y = function_like(x, sin);

    printf("array: %.15g\n", trapz(sin, a, b, n));
    printf("vector: %.15g\n", trapezoidal_rule(y, x));

    free(x);
    free(y);
}

double trapz(double(f)(double), double a, double b, size_t n)
{
    double h = (b - a) / (n - 1.0);
    double integral = 0.0;

    for (size_t i = 0; i < n - 1; ++i)
    {
        integral += (f(a + h * i) + f(a + h * (i + 1))) * h;
    }
    return integral / 2.0;
}
