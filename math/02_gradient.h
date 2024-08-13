void show_array(const double *arr, size_t n);

void check_mem_alloc(void *p);

double *gradient_descent(
    size_t data_size,
    size_t num_weights,
    const double x[static data_size][num_weights - 1],
    const double y[static data_size],
    double weights[static num_weights],
    double learn_rate,
    size_t n_iter,
    double tolerance);

/// @brief Hypothesis function for linear regression
/// @param num_weights Number of weights
/// @param weights Array containing weights, with bias as the first element
/// @param x Each 1D array in the 2D x array
/// @return Predicted y value
double hypothesis(
    size_t num_weights,
    const double weights[static num_weights],
    const double x[static num_weights - 1]);

double cost_function(const double errors[], size_t n);
