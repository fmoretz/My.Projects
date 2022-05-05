# Workshop.py
# Federico Moretta(c)
# 2) NLS SOLVER

from scipy.optimize import minimize
import matplotlib.pyplot as plt
import numpy as np


def reconcile(F, Fm, p):

    Ff, Fv, Fl, Fw = F

    f_ = ((Ff-Fm[0])/Fm[0])**2
    v_ = ((Fv-Fm[1])/Fm[1])**2
    l_ = ((Fl-Fm[2])/Fm[2])**2
    w_ = ((Fw-Fm[3])/Fm[3])**2

    err = f_+v_+l_+w_

    pen = p*(Ff-Fv-Fl-Fw)**2

    return err + pen


def main():

    valin = [146, 38, 43, 82]

    p = 1000

    rec = minimize(reconcile, valin, args=(valin, p))

    Ff, Fv, Fl, Fw = rec.x

    print('Feed     stream :', "{:.3f}".format(Ff), 'kg/h')
    print('Withdraw stream :', "{:.3f}".format(Fw), 'kg/h')
    print('Vapour   stream :', "{:.3f}".format(Fv), 'kg/h')
    print('Liquid   stream :', "{:.3f}".format(Fl), 'kg/h')


if __name__ == "__main__":
    main()
