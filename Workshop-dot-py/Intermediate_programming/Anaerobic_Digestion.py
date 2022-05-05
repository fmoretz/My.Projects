# Federico Moretta -- Feed-stock Blending Optimization + Batch Simulation
import numpy as np
from scipy.integrate import odeint
from scipy.optimize import minimize
from scipy.optimize import LinearConstraint as lc
from scipy.optimize import Bounds as bd
import matplotlib.pyplot as plt
import ad_util
from data import *

def main():
	# retrive solving information
	tspan = np.linspace(0, 35, 1000)
	init  = ad_util.feffluent(x_M, d_M, d_I)
	S0    = init[0]
	X0    = init[1]

	# solve ode system with initial substrate composition
	x_blend_0 = odeint(ad_util.fsimulate, [S0, X0, 0], tspan, args=([km, Ks, kd],))  
	S_blend_0 = x_blend_0[:, 0]
	X_blend_0 = x_blend_0[:, 1]
	M_blend_0 = x_blend_0[:, 2]

	# obtain the optimized blending stat
	x_0    = [x_M, x_I]
	bounds = bd([0, 0], [1, 1])
	constr = lc([[CN_M, CN_I], [BD_M, BD_I], [1, 1]], [20, 0.6, 1], [30, 1, 1])
	blend  = minimize(ad_util.fblending, x_0, args=([BMPe_M, BMPe_I],[CN_M, CN_I],[BD_M, BD_I]), \
		method='trust-constr', bounds=bounds, constraints=constr, tol=1e-9, \
		options={'verbose': 1, 'disp': True})

	# solve ode system with new substrate composition
	init_n    = ad_util.feffluent(blend.x[0], d_M, d_I)
	S0_n      = init_n[0]
	X0_n      = init_n[1]
	x_blend_1 = odeint(ad_util.fsimulate, [S0_n, X0_n, 0], tspan, args=([km, Ks, kd],))  
	S_blend_1 = x_blend_1[:, 0]
	X_blend_1 = x_blend_1[:, 1]
	M_blend_1 = x_blend_1[:, 2]

	print(blend)

	# visualization
	plt.figure(1)
	plt.title('Simulation at original blending stats (i=m=50%)')
	plt.plot(tspan, S_blend_0, label='S')
	plt.plot(tspan, X_blend_0, label='X')
	plt.plot(tspan, M_blend_0, label='M')
	plt.xlabel('time [d]')
	plt.ylabel('concentration [kg/m3]')
	plt.legend(loc = 'best')
	plt.ylim([0, 1500])
	plt.grid(True)

	plt.figure(2)
	newtitle = 'Simulation at new blending stats (i='+'{:.2f}'.format(blend.x[1])+' m='+'{:.2f}'.format(blend.x[0])+')'
	plt.title(newtitle)
	plt.plot(tspan, S_blend_1, label='S')
	plt.plot(tspan, X_blend_1, label='X')
	plt.plot(tspan, M_blend_1, label='M')
	plt.xlabel('time [d]')
	plt.ylabel('concentration [kg/m3]')
	plt.legend(loc = 'best')
	plt.ylim([0, 1500])
	plt.grid(True)
	plt.show()


	return 0

if __name__ == "__main__":
	main()


