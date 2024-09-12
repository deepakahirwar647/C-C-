#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include "vector.h"



vector_t *empty(size_t n)
{
    vector_t *v = malloc(sizeof(*v) + sizeof(double) * n);
    if (v == NULL)
    {
        fprintf(stderr, "%s: Memory allocationd failed\n", __func__);
        return NULL;
    }
    return v;
}

vector_t *empty_like(const vector_t *u)
{
    if (u == NULL)
        return NULL;

    vector_t *v = malloc(sizeof(*v) + sizeof(double) * u->size);

    if (v == NULL)
    {
        fprintf(stderr, "%s: Memory allocation falied\n", __func__);
        return NULL;
    }

    v->size = u->size;

    return v;
}

vector_t *zeros_like(const vector_t *u)
{
    if (u == NULL)
        return NULL;

    vector_t *v = malloc(sizeof(*v) + sizeof(double) * u->size);

    if (v == NULL)
    {
        fprintf(stderr, "%s: Memory allocation falied\n", __func__);
        return NULL;
    }

    v->size = u->size;

    for (size_t i = 0; i < v->size; ++i)
    {
        v->arr[i] = 0;
    }

    return v;
}

vector_t *zeros(size_t n)
{
    vector_t *v = malloc(sizeof(*v) + sizeof(double) * n);

    if (v == NULL)
    {
        fprintf(stderr, "%s: Memory allocation falied\n", __func__);
        return NULL;
    }

    v->size = n;

    for (size_t i = 0; i < v->size; ++i)
    {
        v->arr[i] = 0;
    }

    return v;
}

vector_t *linspace(double start, double end, size_t n)
{
    double step = (end - start) / (n - 1.0);
    assert(step != 0);

    vector_t *v = malloc(sizeof(*v) + sizeof(double) * n);
    if (v == NULL)
    {
        return NULL;
    }

    v->arr[0] = start;
    v->size = n;

    for (size_t i = 1; i < n; ++i)
    {
        v->arr[i] = v->arr[i - 1] + step;
    }

    return v;
}

vector_t *arange(double start, double end, double step)
{
    assert(step != 0);
    step > 0 ? assert(end > start) : assert(start > end);
    const size_t N_TERMS = (size_t)((end - start) / step);

    assert(N_TERMS > 0); // Extra check

    vector_t *v = malloc(sizeof(*v) + sizeof(double) * N_TERMS);

    if (v == NULL)
    {
        fprintf(stderr, "%s: Memory allocation falied\n", __func__);
        exit(1);
    }

    v->size = N_TERMS;

    for (size_t i = 0; i < v->size; ++i)
    {
        v->arr[i] = start + i * step;
    }

    return v;
}

vector_t *gradient(const vector_t *y, const vector_t *x)
{
    assert(y->size == x->size && y->size > 2);

    vector_t *v = malloc(sizeof(*v) + sizeof(double) * y->size);
    const size_t n = y->size;

    if (v == NULL)
    {
        fprintf(stderr, "%s: Memory allocation falied\n", __func__);
        exit(1);
    }

    v->size = y->size;

    // Forward difference for first point
    v->arr[0] = (y->arr[1] - y->arr[0]) / (x->arr[1] - x->arr[0]);

    // Central difference for the interior points
    for (size_t i = 1; i < v->size - 1; ++i)
    {
        v->arr[i] = (y->arr[i + 1] - y->arr[i - 1]) / (x->arr[i + 1] - x->arr[i - 1]);
    }

    // Backward difference for last point
    v->arr[n - 1] = (y->arr[n - 1] - y->arr[n - 2]) / (x->arr[n - 1] - x->arr[n - 2]);

    return v;
}

vector_t *from_array(double arr[static 1], size_t size)
{
    if (arr == NULL)
    {
        fprintf(stderr, "%s: Empty array\n", __func__);
        return NULL;
    }

    vector_t *v = malloc(sizeof(*v) + sizeof(double) * size);

    if (v == NULL)
    {
        fprintf(stderr, "%s: Memory allocation falied\n", __func__);
        exit(1);
    }

    v->size = size;

    for (size_t i = 0; i < v->size; ++i)
    {
        v->arr[i] = arr[i];
    }

    return v;
}

void apply_function(vector_t *v, double (*function)(double))
{
    if (v == NULL)
    {
        fprintf(stderr, "%s: Null vector\n", __func__);
        return;
    }

    for (size_t i = 0; i < v->size; ++i)
    {
        v->arr[i] = function(v->arr[i]);
    }
}

vector_t *function_like(const vector_t *u, double (*function)(double))
{
    if (u == NULL)
    {
        fprintf(stderr, "%s: Null vector\n", __func__);
        return NULL;
    }

    vector_t *v = malloc(sizeof(*v) + sizeof(double) * u->size);

    if (v == NULL)
    {
        fprintf(stderr, "%s: Memory allocation falied\n", __func__);
        exit(1);
    }

    v->size = u->size;

    for (size_t i = 0; i < v->size; ++i)
    {
        v->arr[i] = function(u->arr[i]);
    }

    return v;
}

vector_t *get_copy(const vector_t *u)
{
    if (u == NULL)
    {
        fprintf(stderr, "%s: Null vector\n", __func__);
        return NULL;
    }

    vector_t *v = malloc(sizeof(*v) + sizeof(double) * u->size);

    if (v == NULL)
    {
        fprintf(stderr, "%s: Memory allocation falied\n", __func__);
        exit(1);
    }

    v->size = u->size;

    for (size_t i = 0; i < v->size; ++i)
    {
        v->arr[i] = u->arr[i];
    }

    return v;
}

vector_t *get_result(const vector_t *x, const vector_t *y, double (*function)(double, double))
{
    if (x == NULL || y == NULL)
    {
        fprintf(stderr, "%s: Null vector\n", __func__);
        return NULL;
    }

    if (x->size != y->size)
    {
        fprintf(stderr, "%s: Different size vectors\n", __func__);
        return NULL;
    }

    vector_t *v = malloc(sizeof(*v) + sizeof(double) * x->size);

    if (v == NULL)
    {
        fprintf(stderr, "%s: Memory allocation falied\n", __func__);
        exit(1);
    }

    v->size = x->size;

    for (size_t i = 0; i < v->size; ++i)
    {
        v->arr[i] = function(x->arr[i], y->arr[i]);
    }

    return v;
}

double *to_array(const vector_t *v)
{
    if (v == NULL)
    {
        fprintf(stderr, "%s: Null vector\n", __func__);
        return NULL;
    }

    double *arr = malloc(sizeof(*arr) * v->size);

    for (size_t i = 0; i < v->size; ++i)
        arr[i] = v->arr[i];

    return arr;
}

void print_vector(const vector_t *v)
{
    if (v == NULL)
    {
        puts("[]");
        return;
    }

    printf("[");
    for (size_t i = 0; i < v->size; ++i)
    {
        printf("%g", v->arr[i]);

        if ((i + 1) < v->size)
            printf(", ");

        if ((i + 1) % 10 == 0 && (i + 1) != v->size)
            putchar('\n');
    }
    puts("]\n");
}


double get_ve(const vector_t *v, int index)
{
    return v->arr[index];
}

double trapezoidal_rule(const vector_t *y, const vector_t *x)
{
    if (y == NULL || x == NULL)
    {
        fprintf(stderr, "%s: Null vector\n", __func__);
        return 0.0;
    }
    if (x->size != y->size)
    {
        fprintf(stderr, "%s: x and y must have same size\n", __func__);
    }

    double integral = 0.0;
    for (size_t i = 0; i < x->size - 1; ++i)
    {
        double h = x->arr[i + 1] - x->arr[i];
        double area = (y->arr[i] + y->arr[i + 1]) * h; // Twice the area of trapezoid
        integral += area;
    }

    return integral / 2.0;
}

double reduce(double(f)(double, double), const vector_t *v)
{
    if (v == NULL)
    {
        fprintf(stderr, "%s: Null vector\n", __func__);
        return 0.0;
    }

    double result = v->arr[0];
    for (size_t i = 1; i < v->size; ++i)
    {
        result = f(result, v->arr[i]);
    }
    return result;
}

void free_vector(vector_t *v)
{
    free(v);
    printf("Freed vector\n");
}