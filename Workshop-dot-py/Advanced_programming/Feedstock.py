import numpy as np
from scipy.integrate import odeint
from scipy.optimize import minimize
from scipy.optimize import LinearConstraint as lc
from scipy.optimize import Bounds as bd
import matplotlib.pyplot as plt
import ad_util

class Feedstock:
    def __init__(self, name, bmp, cn, bd, d, x) -> None:
        self.name = name
        self.bmp = bmp
        self.cn = cn
        self.bd = bd
        self.d = d
        self.x = x
    
    def fsubstrate(self) -> list:
        '''evaluate the substrate and biomass
        content approximately, valuable as first-guess'''
        S = self.d*self.x
        X = S/1000
        return [S, X]

    def fshow_properties(self) -> None:
        '''print the properites of the 
        feedstock instance'''
        print(self.name, "properties:")
        print("BMP______________: ",self.bmp)
        print("CN_______________: ",self.cn)
        print("BD_______________:",self.bd)
        print("entering as [wt.]: ",self.x)
        print("\n")
     
    def fcodigestion(self, time, k) -> list:
        ''' function to simulate codigestion scenario'''
        S0 = self.d
        X0 = S0/1000
        sol = odeint(ad_util.fsimulate, [S0, X0, 0], np.linspace(0, time, 1000), args=([k[0], k[1], k[2]],))  
        S = sol[:, 0]
        X = sol[:, 1]
        M = sol[:, 2]
        return [S, X, M]