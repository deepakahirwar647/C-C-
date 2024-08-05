/*
Prints the 1-10 cycles (as per user) of sine wave in file,
If fails to output to file, then prints the plot on console.
*/

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define PI 3.14159265
#define HEIGHT 20
#define WIDTH 100
#define SPACE ' '
#define SYMBOL '*'

bool write_file(const char *filename, const int plot[HEIGHT][WIDTH]);
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
    printf("Enter the number of cycles (1-10): ");
    // Checking if user porvided the valid cycles or not
    if (scanf("%d", &cycles) != 1 || cycles <= 0 || cycles > 10)
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

    const char *filename = "sine_pattern.txt";
    if (write_file(filename, plot))
    {
        printf("Sucessfully written data to '%s'\n", filename);
    }
    else
    {
        print_plot(plot);
    }
}

bool write_file(const char *filename, const int plot[HEIGHT][WIDTH])
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        return false;
    }

    // Reversing the y-axis for correct printing
    for (int y = HEIGHT - 1; y >= 0; y--)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            plot[y][x] == SYMBOL ? putc(SYMBOL, fp) : putc(SPACE, fp);
        }
        putc('\n', fp);
    }

    if (fclose(fp) != 0)
    {
        perror("Failed to close the file");
        return false;
    }

    return true;
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
