import numpy as np
from typing import Callable
from scipy.integrate import trapezoid


def main():
    a = 0
    b = np.pi
    n = 10000
    x = np.linspace(a, b, n)
    y = np.tan(x)
    print(trapezoidal(np.sin, a, b, n))
    print(trapezoid(y, x))


def trapezoidal(f: Callable, a: float, b: float, n=1000) -> float:
    x = np.linspace(a, b, n)
    y = f(x)
    h = x[1] - x[0]
    return (h / 2.0) * (y[0] + 2.0*np.sum(y[1:-1]) + y[-1])


if __name__ == "__main__":
    main()
