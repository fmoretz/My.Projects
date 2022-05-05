# Workshop.py
# Federico Moretta(c)
# 1) ODE SOLVER

from scipy.integrate import odeint
import matplotlib.pyplot as plt
import numpy as np


def ode(x, t):

    cA, cB, cC = x

    dc = np.empty(3)

    dc[0] = -3*cA
    dc[1] = 3*cA-2*cB
    dc[2] = 2*cB

    return dc


def main():

    tspan = np.linspace(0, 3, 1000)

    c0 = [4, 0, 0]

    x = odeint(ode, c0, tspan)

    cA = x[:, 0]
    cB = x[:, 1]
    cC = x[:, 2]

    plt.figure()
    plt.plot(tspan, cA, label='cA')
    plt.plot(tspan, cB, label='cB')
    plt.plot(tspan, cC, label='cC')
    plt.grid(True)
    plt.xlabel('Time [s]')
    plt.ylabel('Concentration [kmol/m3]')
    plt.legend(loc='best')
    plt.show()

    return 0


if __name__ == "__main__":
    main()
