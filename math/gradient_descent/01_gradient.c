/*
Performs gradient descent for 2 weights
and 1D x-array
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "01_gradient.h"

#define DATA_SIZE 6

int main(void)
{
    const double x[DATA_SIZE] = {5, 15, 25, 35, 45, 55};
    const double y[DATA_SIZE] = {5, 20, 14, 32, 22, 38};
    double weights[2] = {0.5, 0.5};
    double learn_rate = 0.0008;
    size_t n_iter = 100000;
    double tolerance = 1e-06;

    double *errors = gradient_descent(
        DATA_SIZE,
        x,
        y,
        weights,
        learn_rate,
        n_iter,
        tolerance);

    show_array(weights, 2);
    show_array(errors, DATA_SIZE);
    printf("Cost funtions: %lf\n", cost_function(errors, DATA_SIZE));
    free(errors);
}

void show_array(const double *arr, size_t n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("%lf ", arr[i]);
    }
    printf("\n");
}

void check_mem_alloc(void *p)
{
    if (p == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

double *gradient_descent(
    size_t data_size,
    const double x[static data_size],
    const double y[static data_size],
    double weights[static 2],
    double learn_rate,
    size_t n_iter,
    double tolerance)
{
    double *errors = malloc(sizeof(*errors) * data_size);
    check_mem_alloc(errors);

    double step[2];

    for (size_t i = 0; i < n_iter; ++i)
    {
        double dc_dw0 = 0.0;
        double dc_dw1 = 0.0;

        // Calculating erros and gradients of each weight
        for (size_t j = 0; j < data_size; ++j)
        {
            double h = hypothesis(weights, x[j]);
            errors[j] = h - y[j];
            dc_dw0 += errors[j];
            dc_dw1 += errors[j] * x[j];
        }

        // Normalizing gradients
        dc_dw0 = dc_dw0 / data_size;
        dc_dw1 = dc_dw1 / data_size;

        // Adjusting weights
        step[0] = -learn_rate * dc_dw0;
        step[1] = -learn_rate * dc_dw1;

        if (is_within_tolerance(2, step, tolerance))
            break;

        weights[0] += step[0];
        weights[1] += step[1];
    }

    return errors;
}

double hypothesis(const double weights[static 2], double x)
{
    return weights[0] + weights[1] * x;
}

bool is_within_tolerance(size_t n, const double step_sizes[static n], double tolerance)
{
    for (size_t i = 0; i < n; ++i)
    {
        if (fabs(step_sizes[i]) > tolerance)
            return false;
    }
    return true;
}

double mean(const double res[], size_t n)
{
    assert(n != 0);
    double sum = 0.0;
    for (size_t i = 0; i < n; ++i)
    {
        sum += res[i];
    }
    return sum / n;
}

double cost_function(const double errors[], size_t n)
{
    assert(n != 0);
    double sum_of_squared_errs = 0.0;
    for (size_t i = 0; i < n; ++i)
    {
        sum_of_squared_errs += errors[i] * errors[i];
    }
    return sum_of_squared_errs / (2.0 * (double)n);
}