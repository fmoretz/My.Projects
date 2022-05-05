//Federico Moretta Copyright
#include<iostream>
#include<fstream>
#include<math.h>
#include<boost/numeric/odeint.hpp>
#include<vector>

using namespace std;
using namespace boost::numeric::odeint;

//global variables
double Qmilk = 1750;    //kg/h
double Tp0   = 303;     //K
double Gdry  = 72000;   //kg/h
double Tg0   = 403;     //K
double Dp    = 0.2/1000;//m
double P     = 1;       //atm
double Dsec  = 5.5;     //m
double Wfin  = 0.005;   //kg/kg

//Specific Milk Data
double rho_p = 1000;    //kg/m3
double CpM   = 1;   //kcal/kg/K
double DHev  = 540; //kcal/kg
double A = 18.3036; //mmHg/K
double B = 3816.44; //mmHg/K
double C = -46.13;  //mmHg/K

//Specific Air Data
double mu = 2.3E-5; //kg/m/s
double Cpg = 0.25;  //kcal/kg/K
double Dva = 1.8E-5; //m2/s
double k = 8E-6; //kcal/m/s/K


int main()
{







    return 0;
}
