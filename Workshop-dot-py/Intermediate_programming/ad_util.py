import numpy as np
def fblending(x, BMP_arr, CN_arr, BD_arr):
	'''optimize the substrae blending fraction to 
		maximize the biomethane potential of the process'''
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
	'''evaluate the substrate and biomass
	content approximately, valuable as first-guess'''		
	S_1 = d_1*x
	S_2 = d_2*(1-x)
	X_1 = S_1/1000
	X_2 = S_2/1000

	S   = S_1 + S_2
	X   = X_1 + X_2
	return [S, X]