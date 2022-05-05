# Federico Moretta -- Feed-stock Blending Optimization + Batch Simulation
import numpy as np
from scipy.integrate import odeint
from scipy.optimize import minimize
from scipy.optimize import LinearConstraint as lc
from scipy.optimize import Bounds as bd
import matplotlib.pyplot as plt

# GLOBALS
# Data - Optimization section
# Feed-stock: Manura
x_M    = 0.6
CN_M   = 16.31
BD_M   = 0.65
BMPe_M = 200
d_M    = 1500

# Feed-stock: Insilato
x_I    = 0.4
CN_I   = 81.1
BD_I   = 0.41
BMPe_I = 120
d_I    = 130

# Data - Simulation section
Ks     = 500
km     = 1.5
kd     = 0.3

# Function definition
def fblending(x, BMP_arr, CN_arr, BD_arr):
	'''
	evaluate the biomethane potential from
	blending of different substrates
	'''
	# Objective Function: Coefficients
	alfa   = 28.8117
	beta   = 4.0036
	gamma  = 174.1055
	epsi   = 1.2937
	theta  = -0.0607
	omega  = 307.0059
	
	CN     = x[0]*CN_arr[0] + x[1]*CN_arr[1]
	BD     = x[0]*BD_arr[0] + x[1]*BD_arr[1]  
	BMP_i  = alfa + beta*CN + gamma*BD + epsi*CN*BD + theta*CN**2 + omega*BD**2
	f_1    = x[0]*BMP_arr[0]
	f_2    = x[1]*BMP_arr[1]
	f_12   = x[0]*x[1]*BMP_i
	fobj   = -f_1 - f_2 - f_12
	return fobj
    
def fsimulate(x, t, k):
	'''
	simulate the kinetic behavior
	inside the digester
	k[0] = km / k[1] = Ks / k[2] = kd
	'''
	S, X, M = x

	dCdt    = np.empty(3)
	dCdt[0] = -k[0]*S/(k[1]+S)*X
	dCdt[1] = -dCdt[0] - k[2]*X
	dCdt[2] = -dCdt[0]*(1-k[2])
	return dCdt


def feffluent(x, d_1, d_2):
	S_1 = d_1*x
	S_2 = d_2*(1-x)
	X_1 = S_1/1000
	X_2 = S_2/1000

	S   = S_1 + S_2
	X   = X_1 + X_2
	return [S, X]

# Solving Section
def main():
	# retrive solving information
	tspan = np.linspace(0, 35, 1000)
	init  = feffluent(x_M, d_M, d_I)
	S0    = init[0]
	X0    = init[1]

	# solve ode system with initial substrate composition
	x_blend_0 = odeint(fsimulate, [S0, X0, 0], tspan, args=([km, Ks, kd],))  
	S_blend_0 = x_blend_0[:, 0]
	X_blend_0 = x_blend_0[:, 1]
	M_blend_0 = x_blend_0[:, 2]

	# obtain the optimized blending stat
	x_0    = [x_M, x_I]
	bounds = bd([0, 0], [1, 1])
	constr = lc([[CN_M, CN_I], [BD_M, BD_I], [1, 1]], [20, 0.6, 1], [30, 1, 1])
	blend  = minimize(fblending, x_0, args=([BMPe_M, BMPe_I],[CN_M, CN_I],[BD_M, BD_I]), \
		method='trust-constr', bounds=bounds, constraints=constr, tol=1e-9, \
		options={'verbose': 1, 'disp': True})

	# solve ode system with new substrate composition
	init_n    = feffluent(blend.x[0], d_M, d_I)
	S0_n      = init_n[0]
	X0_n      = init_n[1]
	x_blend_1 = odeint(fsimulate, [S0_n, X0_n, 0], tspan, args=([km, Ks, kd],))  
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

