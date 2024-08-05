/*
Prints the one cycle of cosine wave on console
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
    int plot[HEIGHT][WIDTH] = {0}; // Initialized plot with zeros

    // Marks the points for cosine wave
    for (int x = 0; x < WIDTH; ++x)
    {
        double y = cos(2.0 * PI * (double)x / (double)WIDTH);
        int y_pos = (int)((y + 1.0) * (HEIGHT - 1.0) / 2.0);
        plot[y_pos][x] = SYMBOL;
    }
    print_plot(plot);
}

void print_plot(const int plot[HEIGHT][WIDTH])
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            // Reversing the y-axis for correct printing
            plot[HEIGHT - 1 - i][j] == SYMBOL ? putchar(SYMBOL) : putchar(SPACE);
        }
        putchar('\n');
    }
}
