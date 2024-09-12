#ifndef VECTOR_H_

#define VECTOR_H_

#define PI 3.141592653589793

typedef struct vector_t
{
    size_t size;
    double arr[];
} vector_t;

vector_t *empty_like(const vector_t *u);

vector_t *empty(size_t n);

vector_t *zeros_like(const vector_t *u);

vector_t *zeros(size_t n);

vector_t *arange(double start, double end, double step);

vector_t *linspace(double start, double end, size_t n);

// Returns vector with cacluated derivative at each point
vector_t *gradient(const vector_t *y, const vector_t *x);

// Modifies original vector by applying a function to each vector element
void apply_function(vector_t *v, double (*function)(double));

// Returns new vector by applying a function to each vector element
vector_t *function_like(const vector_t *u, double (*function)(double));

void print_vector(const vector_t *v);

vector_t *get_copy(const vector_t *u);

vector_t *get_result(const vector_t *x, const vector_t *y, double (*function)(double, double));

// Get a vector from an array
vector_t *from_array(double arr[static 1], size_t size);

// Returns the array version of vector
double *to_array(const vector_t *v);

// Function to calculate the trapezoidal integral
double trapezoidal_rule(const vector_t *y, const vector_t *x);

double reduce(double(f)(double, double), const vector_t *v);

void free_vector(vector_t *v);

// Returns the element at ith position
double get_ve(const vector_t *v, int index);

#endif