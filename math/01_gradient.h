#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

void check_mem_alloc(void *p);

void show_array(const double *arr, size_t n);

double *gradient_descent(
    size_t data_size,
    const double x[static data_size],
    const double y[static data_size],
    double weights[static 2],
    double learn_rate,
    size_t n_iter,
    double tolerance);

double hypothesis(const double weights[static 2], double x);

bool is_within_tolerance(size_t n, const double step_sizes[static n], double tolerance);

double mean(const double res[], size_t n);

double cost_function(const double errors[], size_t n);
