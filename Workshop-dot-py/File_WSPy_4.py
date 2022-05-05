# Workshop.py
# Federico Moretta(c)
# 4) LINEAR REGRESSION

from scipy.stats import linregress, t
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df = pd.read_table("data.dat", sep=";", header=None, names=['x', 'y'])
x = df['x']
y = df['y']
reg = linregress(x, y)
model = reg.intercept + reg.slope*x

def tinv(p, df): return abs(t.ppf(p/2, df))

ts = tinv(0.05, len(x-2))

plt.figure()
plt.plot(x, y, 'o', label='raw')
plt.plot(x, model, 'r', label='model')
plt.legend(loc='best')
plt.grid(True)
plt.show()
