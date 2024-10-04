import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from typing import Optional


class SecondOrderSystem:
    """
    Represents a second-order control system defined by its damping ratio (zeta),
    natural frequency (omega_n), and gain (k).

    Attributes:
        zeta (float): Damping ratio.
        omega_n (float): Natural frequency.
        k (float): System gain (default 1.0).
    """

    def __init__(self, zeta: float, omega_n: float, k=1.0):
        """
        Initializes the second-order system with the given parameters.

        Args:
            zeta (float): Damping ratio
            omega_n (float): Natural frequency, must be a positive real number.
            k (float, optional): Gain of the system. Defaults to 1.0.

        Raises:
            ValueError: If omega_n is not a positive real number.
        """
        self.zeta = zeta
        self.omega_n = omega_n
        self.k = k

    @property
    def omega_n(self):
        """
        Returns the natural frequency of the system.

        Returns:
            float: The natural frequency (omega_n).
        """
        return self._omega_n

    @omega_n.setter
    def omega_n(self, value):
        """
        Sets and validates the natural frequency of the system.

        Args:
            value (float): The new value for omega_n.

        Raises:
            ValueError: If omega_n is not a positive real number.
        """
        if not isinstance(value, (int, float)) or value <= 0:
            raise ValueError(
                'Natural frequency (omega_n) must be a positive real number.')
        self._omega_n = float(value)

    def __repr__(self):
        """
        Returns a string representation of the transfer function of the system.

        Returns:
            str: The transfer function in the form "k * ω_n^2 / (s^2 + 2ζω_n + ω_n^2)".
        """
        numerator = self.k * self.omega_n**2
        denominator = f"s**2 + {2*self.zeta*self.omega_n}s + {self.omega_n**2}"
        return f"{numerator} / ({denominator})"

    @property
    def stable(self) -> bool:
        """
        Checks if the system is stable based on its damping ratio.

        Returns:
            bool: True if the system is stable (ζ > 0), otherwise False.
        """
        return self.zeta > 0

    @property
    def poles(self) -> tuple[complex, complex]:
        """
        Calculates the poles of the second-order system.

        Returns:
            tuple[complex, complex]: The poles of the system as complex numbers.
        """
        determinant: complex = np.sqrt(
            self.zeta**2 - 1, dtype=complex) * self.omega_n
        p1: complex = -self.zeta*self.omega_n + determinant
        p2: complex = -self.zeta*self.omega_n - determinant
        return p1, p2

    def pole_zero_plot(self, ax: Optional[plt.Axes] = None, format_plot=True) -> plt.Axes:
        """
        Plots the poles of the second-order system on the complex plane.

        Args:
            ax (Optional[plt.Axes], optional): A matplotlib Axes object. Defaults to None.

        Returns:
            plt.Axes: The matplotlib Axes with the poles plotted.
        """
        if ax is None:
            _, ax = plt.subplots()
        if format_plot:
            self._format_plot(ax)

        # Extract real and imaginary parts of the poles
        x = [p.real for p in self.poles]
        y = [p.imag for p in self.poles]

        # Plot poles as 'x' marks
        ax.plot(x, y, "xr", zorder=5)
        ax.set_xlabel('\N{GREEK SMALL LETTER SIGMA}', loc="right")
        ax.set_ylabel('jω', loc='top', rotation=0)

        return ax

    def _format_plot(self, ax):
        # Plot axes at origin
        ax.spines[['left', 'bottom']].set_position('zero')
        ax.spines[['left', 'bottom']].set_color('black')

        # Hide the top and right axes
        ax.spines[['right', 'top']].set_visible(False)
        ax.tick_params(axis='both', direction='inout')

        # Set the arrows marks on axis
        ax.plot(1, 0, ">k", transform=ax.get_yaxis_transform(), clip_on=False)
        ax.plot(0, 0, "<k", transform=ax.get_yaxis_transform(), clip_on=False)
        ax.plot(0, 1, "^k", transform=ax.get_xaxis_transform(), clip_on=False)
        ax.plot(0, 0, "vk", transform=ax.get_xaxis_transform(), clip_on=False)
        ax.grid(True)

    @property
    def alpha(self) -> float:
        """
        Represents the actual damping factor of the second-order system (ζ * ω_n)

        Returns: 
            float: Damping factor of the system.
        """
        return self.zeta * self.omega_n

    @property
    def omega_d(self) -> float:
        """
        Represents the damped frequency of the second-order system.

        Returns:
            float: Damped natural frequency of the system.
        """
        return self.omega_n * np.sqrt(np.abs(self.zeta**2 - 1))

    def impulse_response(self, t: float | np.ndarray, A=1.) -> float | np.ndarray:
        """
        Computes the impulse response of the second-order system for different cases:
        underdamped, critically damped, and overdamped.

        Args:
            t (float | np.ndarray): Time at which to evaluate the response.
            A (_type_, optional): Amplitude of the impulse. Defaults to 1..

        Raises:
            NotImplementedError: The impulse response at time `t`.

        Returns:
            float | np.ndarray: If the system is unstable.
        """
        if not self.stable and self.zeta != 0:
            raise NotImplementedError(
                'Does not support response for unstable systems')

        if self.zeta == 0:
            return self._impulse_undamped(t, A)
        elif 0.0 < self.zeta < 1.0:
            return self._impulse_underdamped(t, A)
        elif self.zeta == 1.0:
            return self._impulse_critically_damped(t, A)
        else:
            return self._impulse_overdamped(t, A)

    def _impulse_undamped(self, t: float | np.ndarray, A: float) -> float | np.ndarray:
        """
        Computes the impulse response for the undamped case (ζ = 0).
        """
        amplitude = A * self.k * self.omega_n
        return amplitude * np.sin(self.omega_n*t)

    def _impulse_underdamped(self, t: float | np.ndarray, A: float) -> float | np.ndarray:
        """
        Computes the impulse response for the underdamped case (0 < ζ < 1).
        """
        amplitude = A*self.k * self.omega_n**2 / self.omega_d
        return amplitude * np.exp(-self.alpha*t) * np.sin(self.omega_d * t)

    def _impulse_critically_damped(self, t: float | np.ndarray, A: float) -> float | np.ndarray:
        """
        Computes the impulse response for the critically damped case (ζ = 1).
        """
        amplitude = A*self.k*self.omega_n**2
        return amplitude * t * np.exp(-self.omega_n*t)

    def _impulse_overdamped(self, t: float | np.ndarray, A: float) -> float | np.ndarray:
        """
        Computes the impulse response for the overdamped case (ζ > 1).
        """
        amplitude = 0.5 * A*self.k * self.omega_n**2 / self.omega_d
        exp_part = np.exp(-(self.alpha - self.omega_d)*t) - \
            np.exp(-(self.alpha + self.omega_d)*t)
        return amplitude * exp_part
