from math import sin, pi
from time import sleep
import rich

SPACE = " "
SYMBOL = "*"


def print_vertical_sinewave(STOP_ITERATION_COUNT=10_000):
    AMPLITUDE = 10
    SAMPLING_RATE = 20
    DELAY_S = 50 / 1000  # Delay time(50ms) in seconds
    for i in range(STOP_ITERATION_COUNT):
        offset = AMPLITUDE*(sin(2*pi*i / SAMPLING_RATE) + 1)
        rich.print(f'[green]{SPACE * int(offset) + SYMBOL}')
        sleep(DELAY_S)


def print_horizontal_sinewave(sampling_rate=30, cycles=1, amplitude=10):
    assert sampling_rate > 0, "sampling_rate must be positive number"
    assert cycles > 0, "cycles must be positive number"
    assert amplitude > 0, "amplitude must be positive numbercycles"

    TOTAL_SAMPLES = sampling_rate * cycles

    for y in range(amplitude, -amplitude, -1):
        for x in range(TOTAL_SAMPLES):
            y_val = amplitude * sin(2 * pi * x / sampling_rate)
            print(end=SYMBOL) if y == int(y_val) else print(end=SPACE)
        print()
