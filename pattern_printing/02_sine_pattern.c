/*
Prints the 1-6 cycles of sine wave on console as provided by user
*/

#include <stdio.h>
#include <math.h>

#define PI 3.14159265
#define HEIGHT 20
#define WIDTH 60
#define SPACE ' '
#define SYMBOL '*'

void print_plot(const int plot[HEIGHT][WIDTH]);

int main(void)
{
    int plot[HEIGHT][WIDTH];

    // Initializing the plot with spaces
    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            plot[i][j] = SPACE;
        }
    }
    int cycles = 1;

    // Asking the user for number of cycles
    printf("Enter the number of cycles (1-6): ");
    // Checking if user porvided the valid data or not
    if (scanf("%d", &cycles) != 1 || cycles <= 0 || cycles > 6)
    {
        fprintf(stderr, "Invalid number of cycles. Using cycles = 1\n");
        cycles = 1;
    }

    const int PERIOD = WIDTH / cycles;

    // Mark the points for sine wave
    for (int x = 0; x < WIDTH; ++x)
    {
        double y = sin(2.0 * PI * (double)x / (double)PERIOD);
        int y_pos = (int)((y + 1.0) * (HEIGHT - 1) / 2.0);
        plot[y_pos][x] = SYMBOL;
    }

    print_plot(plot);
}

void print_plot(const int plot[HEIGHT][WIDTH])
{
    // Reversing the y-axis for correct printing
    for (int y = HEIGHT - 1; y >= 0; y--)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            plot[y][x] == SYMBOL ? putchar(SYMBOL) : putchar(SPACE);
        }
        putchar('\n');
    }
}
