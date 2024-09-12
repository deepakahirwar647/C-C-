/*
Performs gradient descent for multiple weights
and 2D x-array
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "02_gradient.h"

#define DATA_SIZE 6
#define N_WEIGHTS 2

int main(void)
{
    const double x[DATA_SIZE][N_WEIGHTS - 1] = {5, 15, 25, 35, 45, 55};
    const double y[DATA_SIZE] = {5, 20, 14, 32, 22, 38};
    double weights[N_WEIGHTS] = {0.5, 0.5};
    double learn_rate = 0.0008;
    size_t n_iter = 100000;
    double tolerance = 1e-06;

    double *errors = gradient_descent(
        DATA_SIZE,
        N_WEIGHTS,
        x,
        y,
        weights,
        learn_rate,
        n_iter,
        tolerance);

    show_array(weights, N_WEIGHTS);
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
    size_t num_weights,
    const double x[static data_size][num_weights - 1],
    const double y[static data_size],
    double weights[static num_weights],
    double learn_rate,
    size_t n_iter,
    double tolerance)
{
    double *errors = malloc(sizeof(*errors) * data_size);
    double *step = malloc(sizeof(*step) * num_weights);
    double *w_gradients = malloc(sizeof(*w_gradients) * num_weights);

    check_mem_alloc(errors);
    check_mem_alloc(step);
    check_mem_alloc(w_gradients);

    memset(w_gradients, 0, sizeof(*w_gradients) * num_weights);

    // Reducing division overhead by calculating reciprocal of data size
    double inv_data_size = 1.0 / (double)data_size;

    for (size_t i = 0; i < n_iter; ++i)
    {
        // Calculating errors and gradients of each weight
        for (size_t j = 0; j < data_size; ++j)
        {
            double h = hypothesis(num_weights, weights, x[j]);
            errors[j] = h - y[j];

            // Handle the bias term separately
            w_gradients[0] += errors[j];

            for (size_t k = 1; k < num_weights; ++k)
            {
                w_gradients[k] += errors[j] * x[j][k - 1];
            }
        }

        bool within_tolerance = true;

        // Normalizing gradients, calculating steps and updating weights
        for (size_t j = 0; j < num_weights; ++j)
        {
            w_gradients[j] *= inv_data_size;
            step[j] = -learn_rate * w_gradients[j];
            weights[j] += step[j];

            if (fabs(step[j]) > tolerance)
                within_tolerance = false;

            // Resetting gradients for next iteration
            w_gradients[j] = 0.0;
        }

        if (within_tolerance)
            break;
    }

    free(step);
    free(w_gradients);

    return errors;
}

double hypothesis(
    size_t num_weights,
    const double weights[static num_weights],
    const double x[static num_weights - 1])
{
    // Start with bias (weights[0])
    double y_predicted = weights[0];

    // Accumulate the contribution of each weight except the bias
    for (size_t i = 1; i < num_weights; ++i)
    {
        y_predicted += weights[i] * x[i - 1];
    }

    return y_predicted;
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