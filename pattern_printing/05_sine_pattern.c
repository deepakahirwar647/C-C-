/*
Contains functions for printing sine wave directly on console
without the using of arrays
*/

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <windows.h>

#define PI 3.14159265
#define SPACE ' '
#define SYMBOL '*'

void print_spaces(int n);
void print_horizontal_sinewave(int sampling_rate, int cycles, int amplitude);
void print_vertical_sinewave(const size_t STOP_ITERATION_COUNT);

int main()
{
    print_vertical_sinewave(1000);
}

/// @brief prints the sinewave horizontally to the screen
/// @param sampling_rate no. of samples for each cycle (below 100)
/// @param cycles no. of complete waves of sine curve (below 16)
/// @param amplitude maximum and minimum value of sine wave (below 30)
void print_horizontal_sinewave(int sampling_rate, int cycles, int amplitude)
{
    assert(sampling_rate > 0 && sampling_rate < 100);
    assert(cycles > 0 && cycles < 16);
    assert(amplitude > 0 && amplitude < 30);

    const int TOTAL_SAMPLES = sampling_rate * cycles;

    // Reversing y-axis for correct plot
    for (int y = amplitude; y >= -amplitude; --y)
    {
        for (int x = 0; x < TOTAL_SAMPLES; ++x)
        {
            int y_val = (double)amplitude * sin(2.0 * PI * x / sampling_rate);
            y == y_val ? putchar(SYMBOL) : putchar(SPACE);
        }
        putchar('\n');
    }
}

inline void print_spaces(int n)
{
    for (int i = 0; i < n; ++i)
        putchar(SPACE);
}

// Prints sinwave pattern veritcally on console
void print_vertical_sinewave(const size_t STOP_ITERATION_COUNT)
{

    const int AMPLITUDE = 20
    const int SAMPLING_RATE = 30;
    const int DELAY_MS = 50;

    for (size_t i = 0; i < STOP_ITERATION_COUNT; ++i)
    {
        int offset = AMPLITUDE * (sin(2.0 * PI * i / SAMPLING_RATE) + 1.0);
        print_spaces(offset);
        putchar(SYMBOL);
        putchar('\n');
        Sleep(DELAY_MS); // defined in windows.h
    }
}
