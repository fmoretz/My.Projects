# Workshop.py
# Federico Moretta(c)
# 2) NLS SOLVER

from scipy.optimize import fsolve
import matplotlib.pyplot as plt
import numpy as np


def vle(u, F, zA, P, PvA, PvB):

    yA, xA, V, L = u

    xB = 1-xA
    yB = 1-yA

    f = np.empty(4)

    f[0] = F-V-L
    f[1] = F*zA-V*yA-L+xA
    f[2] = P*yA-PvA*xA
    f[3] = P*yB-PvB*xB

    return f


def main():

    F = 1000                     # kmol/h
    zA, zB = 0.6, 0.4            # --
    P, PvA, PvB = 1, 2.34, 3.45  # bar

    guess = [0.2, 0.1, 300, 700]

    sol_nls = fsolve(vle, guess, args=(F, zA, P, PvA, PvB))

    yA, xA, V, L = sol_nls

    xB = 1-xA
    yB = 1-yA

    print('Luquid frac. A:', "{:.3f}".format(xA))
    print('Luquid frac. B:', "{:.3f}".format(xB))
    print('Vapour frac. A:', "{:.3f}".format(yA))
    print('Vapour frac. A:', "{:.3f}".format(yB))
    print('Vapour stream :', "{:.1f}".format(V), 'kmol/h')
    print('Liquid stream :', "{:.1f}".format(L), 'kmol/h')

    return 0


if __name__ == "__main__":
    main()
