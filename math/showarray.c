#include <stdio.h>
#include <stdbool.h>
#include "showarray.h"

void showarray_double(const double array[], size_t n)
{
    putchar('[');
    for (int i = 0; i < n; ++i)
    {
        printf("%g", array[i]);

        bool not_last_element = (i + 1) != n;
        bool add_newline = (i + 1) % NEW_LINE_AT == 0 && not_last_element;

        if (not_last_element)
            printf(", ");
        if (add_newline)
            printf("\n ");
    }
    puts("]");
}

void showarray_float(const float array[], size_t n)
{
    putchar('[');
    for (int i = 0; i < n; ++i)
    {
        printf("%g", array[i]);

        bool not_last_element = (i + 1) != n;
        bool add_newline = (i + 1) % NEW_LINE_AT == 0 && not_last_element;

        if (not_last_element)
            printf(", ");
        if (add_newline)
            printf("\n ");
    }
    puts("]");
}

void showarray_int(const int array[], size_t n)
{
    putchar('[');
    for (int i = 0; i < n; ++i)
    {
        printf("%i", array[i]);

        bool not_last_element = (i + 1) != n;
        bool add_newline = (i + 1) % NEW_LINE_AT == 0 && not_last_element;

        if (not_last_element)
            printf(", ");
        if (add_newline)
            printf("\n ");
    }
    puts("]");
}

void showarray_default(const void *array, size_t n)
{
    printf("Can't dispaly this type of array\n");
}
