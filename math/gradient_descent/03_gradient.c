#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>

inline double hypothesis(
    size_t n_features,
    const double x[static n_features],
    const double weights[static n_features + 1])
{
    // Start with bias (weights[0])
    double y_predicted = weights[0];

    // Accumulate the contribution of each weight except the bias
    for (size_t i = 0; i < n_features; ++i)
    {
        y_predicted += weights[i + 1] * x[i];
    }

    return y_predicted;
}

double *make_predictions(
    size_t n_samples,
    size_t n_features,
    const double X[static n_samples][n_features],
    const double weights[static n_features + 1],
    double y_preds[])
{
    if (y_preds == NULL)
    {
        y_preds = malloc(sizeof(*y_preds) * n_samples);
    }

    if (y_preds == NULL)
    {
        fprintf(stderr, "%s: Memory allocation failed\n", __func__);
        return NULL;
    }

    for (size_t i = 0; i < n_samples; ++i)
    {
        y_preds[i] = hypothesis(n_features, X[i], weights);
    }

    return y_preds;
}

void check_mem_alloc(void *p)
{
    if (p == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}
