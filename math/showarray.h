#include <stdio.h>

#ifndef SHOWARRAY_H_
#define SHOWARRAY_H_

#define NEW_LINE_AT 10

#define showarray(X, N) _Generic((X), \
    double *: showarray_double,       \
    float *: showarray_float,         \
    int *: showarray_int,             \
    default: showarray_default)(X, N)

void showarray_double(const double array[], size_t n);
void showarray_float(const float array[], size_t n);
void showarray_int(const int array[], size_t n);
void showarray_default(const void *array, size_t n);

#endif