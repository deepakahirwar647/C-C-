#include <stdio.h>
#include <stdlib.h>
#include "showarray.h"
#include <assert.h>
#include "vector.h"
#include <math.h>

const double pi = 4.0 * atan(1);

int main(void)
{
    vector_t *x = linspace(0, 2 * PI, 10000);
    vector_t *y = function_like(x, sin);
    vector_t *dydx = gradient(y, x);

    // Finds x values where dydx is zero
    for (size_t i = 0; i < dydx->size - 1; ++i)
    {
        double prod = dydx->arr[i] * dydx->arr[i + 1];
        if (prod < 0)
        {
            printf("%g ", x->arr[i + 1]);
            printf("%g ", y->arr[i + 1]);
        }
    }

    free(x);
    free(y);
    free(dydx);
}