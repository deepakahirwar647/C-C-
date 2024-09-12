#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

// Function to generate random weights
void initialize_random_weights(std::vector<double>& weights) {
    for (double& w : weights) {
        w = static_cast<double>(rand()) / RAND_MAX;
    }
}

// C++ gradient descent function with default values for parameters
std::vector<double> gradient_descent(
    size_t data_size,
    size_t num_weights,
    const std::vector<std::vector<double>>& x,
    const std::vector<double>& y,
    std::vector<double> weights = {},
    double learn_rate = 0.1,
    size_t n_iter = 100000,
    double tolerance = 1e-06)
{
    // If weights are not provided, initialize them randomly
    if (weights.empty()) {
        weights.resize(num_weights);
        initialize_random_weights(weights);
    }

    std::vector<double> errors(data_size);
    std::vector<double> step(num_weights);
    std::vector<double> w_gradients(num_weights, 0.0);

    double inv_data_size = 1.0 / static_cast<double>(data_size);

    for (size_t i = 0; i < n_iter; ++i) {
        std::fill(w_gradients.begin(), w_gradients.end(), 0.0);

        // Calculating errors and gradients of each weight
        for (size_t j = 0; j < data_size; ++j) {
            double h = weights[0];
            for (size_t k = 1; k < num_weights; ++k) {
                h += weights[k] * x[j][k - 1];
            }
            errors[j] = h - y[j];

            // Handle the bias term separately
            w_gradients[0] += errors[j];

            for (size_t k = 1; k < num_weights; ++k) {
                w_gradients[k] += errors[j] * x[j][k - 1];
            }
        }

        bool within_tolerance = true;

        // Normalizing gradients, calculating steps, and updating weights
        for (size_t j = 0; j < num_weights; ++j) {
            w_gradients[j] *= inv_data_size;
            step[j] = -learn_rate * w_gradients[j];
            weights[j] += step[j];

            if (std::fabs(step[j]) > tolerance)
                within_tolerance = false;
        }

        if (within_tolerance)
            break;
    }

    return weights;
}

// int main() {
//     srand(static_cast<unsigned>(time(0)));  // Initialize random seed

//     // Example usage of the gradient_descent function
//     size_t data_size = 100;
//     size_t num_weights = 3;

//     // Assuming x and y are initialized with appropriate values
//     std::vector<std::vector<double>> x(data_size, std::vector<double>(num_weights - 1));
//     std::vector<double> y(data_size);

//     // Call gradient_descent with default parameters
//     std::vector<double> weights = gradient_descent(data_size, num_weights, x, y);

//     // Print weights
//     for (double w : weights) {
//         std::cout << w << " ";
//     }
//     std::cout << std::endl;

//     return 0;
// }


#define DATA_SIZE 6
#define N_WEIGHTS 2

int main(void)
{
    const std::vector<std::vector<double>> x{{5}, {15}, {25}, {35}, {45}, {55}};
    const std::vector<double> y{5, 20, 14, 32, 22, 38};
    // std::vector<double> weights{0.5, 0.5};

    // const double x[DATA_SIZE][N_WEIGHTS - 1] = {5, 15, 25, 35, 45, 55};
    // const double y[DATA_SIZE] = {5, 20, 14, 32, 22, 38};
    // double weights[N_WEIGHTS] = {0.5, 0.5};
    double learn_rate = 0.0008;
    size_t n_iter = 100000;
    double tolerance = 1e-06;

    std::vector<double> weights = gradient_descent(
        DATA_SIZE,
        N_WEIGHTS,
        x,
        y
        );

    for (int i = 0; i < weights.size(); ++i)
    {
        std::cout << weights[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}