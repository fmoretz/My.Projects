# Federico Moretta -- Feed-stock Blending Optimization + Batch Simulation
import numpy as np
from scipy.integrate import odeint
from scipy.optimize import minimize
from scipy.optimize import LinearConstraint as lc
from scipy.optimize import Bounds as bd
import matplotlib.pyplot as plt
import ad_util
from Feedstock import *

#GLOBAL - Data - Simulation section
Ks     = 500
km     = 1.5
kd     = 0.3

def main():
    # Create feedstock instances
    manure = Feedstock("dairy", 200, 16.31, 0.65, 1500, 0.5)
    silage = Feedstock("mais", 120, 81.10, 0.41, 130, 0.5)
    silage.fshow_properties()
    manure.fshow_properties()

    # create mixed feedstock instances with averaged data
    cn_mix = ad_util.fco_cn([manure.x, silage.x], [manure.cn, silage.cn])
    bd_mix = ad_util.fco_bd([manure.x, silage.x], [manure.bd, silage.bd])
    d_mix = ad_util.fco_d([manure.x, silage.x], [manure.d, silage.d])
    bmp_mix = -ad_util.fblending([manure.x, silage.x], [manure.bmp, silage.bmp], [manure.cn, silage.cn], [manure.bd, silage.bd])
    mix_fs = Feedstock("mix", bmp_mix, cn_mix, bd_mix, d_mix, 1)
    mix_fs.fshow_properties()
    
	# solve ode system with initial substrate composition
    tspan = np.linspace(0, 35, 1000)
    init_manure = manure.fsubstrate()
    init_silage = silage.fsubstrate()
    S0 = init_manure[0] + init_silage[0]
    X0 = init_manure[1] + init_silage[1]

    x_mix = mix_fs.fcodigestion(35, [km, Ks, kd])
    S_mix = x_mix[0]
    X_mix = x_mix[1]
    M_mix = x_mix[2]

	# obtain the optimized blending stat
    print("\nFeedstock blending optimization has started...")
    x_0    = [manure.x, silage.x]
    bounds = bd([0, 0], [1, 1])
    constr = lc([[manure.cn, silage.cn], [manure.bd, silage.bd], [1, 1]], [20, 0.6, 1], [40, 1, 1])
    blend  = minimize(ad_util.fblending, x_0, args=([manure.bmp, silage.bmp],\
        [manure.cn, silage.cn],[manure.bd, silage.bd]), \
		method='trust-constr', bounds=bounds, constraints=constr, tol=1e-9, \
		options={'verbose': 1, 'disp': True})
    print("\n")
    manure.x = blend.x[0]
    silage.x = blend.x[1]
    manure.fshow_properties()
    silage.fshow_properties()

    # generate the new blended mixture instance
    cn_mix = ad_util.fco_cn([manure.x, silage.x], [manure.cn, silage.cn])
    bd_mix = ad_util.fco_bd([manure.x, silage.x], [manure.bd, silage.bd])
    d_mix = ad_util.fco_d([manure.x, silage.x], [manure.d, silage.d])
    bmp_mix = -ad_util.fblending([manure.x, silage.x], [manure.bmp, silage.bmp], [manure.cn, silage.cn], [manure.bd, silage.bd])
    mix_new = Feedstock("mix", bmp_mix, cn_mix, bd_mix, d_mix, 1)
    mix_new.fshow_properties()

	# solve ode system with new substrate composition
    x_blend = mix_new.fcodigestion(35, [km, Ks, kd])
    S_blend = x_blend[0]
    X_blend = x_blend[1]
    M_blend = x_blend[2] 

	# visualization
    plt.figure(1)
    plt.title('Simulation at original blending stats (i=m=50%)')
    plt.plot(tspan, S_mix, label='S')
    plt.plot(tspan, X_mix, label='X')
    plt.plot(tspan, M_mix, label='M')
    plt.xlabel('time [d]')
    plt.ylabel('concentration [kg/m3]')
    plt.legend(loc = 'best')
    plt.ylim([0, 1500])
    plt.grid(True)

    plt.figure(2)
    newtitle = 'Simulation at new blending stats (i='+'{:.2f}'.format(blend.x[1])+' m='+'{:.2f}'.format(blend.x[0])+')'
    plt.title(newtitle)
    plt.plot(tspan, S_blend, label='S')
    plt.plot(tspan, X_blend, label='X')
    plt.plot(tspan, M_blend, label='M')
    plt.xlabel('time [d]')
    plt.ylabel('concentration [kg/m3]')
    plt.legend(loc = 'best')
    plt.ylim([0, 1500])
    plt.grid(True)

    plt.show()



    return 0

if __name__ == "__main__":
	main()




