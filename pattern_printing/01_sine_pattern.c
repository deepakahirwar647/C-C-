/*
Prints the one cycle of sine wave on console
*/

#include <stdio.h>
#include <math.h>

#define PI 3.14159265
#define HEIGHT 20
#define WIDTH 60
#define SPACE '.'
#define SYMBOL '0'

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

    // Mark the points for sine wave
    for (int x = 0; x < WIDTH; ++x)
    {
        double y = sin(2.0 * PI * (double)x / (double)WIDTH);
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
            putchar(plot[y][x]);
        }
        putchar('\n');
    }
}
