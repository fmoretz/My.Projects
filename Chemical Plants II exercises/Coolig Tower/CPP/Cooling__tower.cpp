#include <iostream>
#include <vector>
#include <boost/numeric/odeint.hpp>
#include <fstream>
#include <boost/array.hpp>

using namespace std;
using namespace boost::numeric::odeint;

//DATA
double Lin = 20000;								// kg/h
double Gin = 15000;							// kg/h
double P = 760;									// mmHg
double TinH2O = 50;								// °C
double ToutH2O = 25;							// °C
double Tinair = 20;								// °C
double Z = 0.5;									// relative humidity
double Cu = 0.26;								// kcal/kg*K
double CpL = 1;									// kcal/kg*K
double DHev = 580;								// kcal/kg
double hga = 4000;								// kcal/m/h/K
double hla = 30000;								// kcal/m/h/K
double A = -49.705;								// Pev 1st coeff	mmHg vs °C
double B = 2.71;								// Pev 2nd coeff    mmHg vs °C
double Usair = 0.62*(A + B*Tinair) / P;
double Uair = Z*Usair;
double Kua = hga / Cu;
double Gdry = Gin/(1+Uair);                     // kg/h
double L0 = 19292;								// kg/h: 19292


typedef vector <double> state_type;
vector <double> pack_height;
vector <double> Umidity;
vector <double> T_liquid;
vector <double> T_gas;
vector <double> Liquid_flow;
vector <double> Gas_flow;

void cooling_packing( state_type& x , state_type& dxdt ,  double z )
{// U Tl Tg L G

double Ti = (hla*x[1] + hga*x[2] + Kua*DHev*(x[0] - 0.62*A / P)) / (hla + hga + Kua*DHev*0.62*B / P);
double Ui = (0.62*(A + B*(hla*x[1] + hga*x[2] + Kua*DHev*(x[0] - 0.62*A / P)) / (hla + hga + Kua*DHev*0.62*B / P)) / P);

dxdt[0] = Kua*((0.62*(A + B*(hla*x[1] + hga*x[2] + Kua*DHev*(x[0] - 0.62*A / P)) / (hla + hga + Kua*DHev*0.62*B / P)) / P) - x[0]) / Gdry;
dxdt[1] = hla*(x[1] - (hla*x[1] + hga*x[2] + Kua*DHev*(x[0] - 0.62*A / P)) / (hla + hga + Kua*DHev*0.62*B / P)) / x[3] / CpL;
dxdt[2] = hga*((hla*x[1] + hga*x[2] + Kua*DHev*(x[0] - 0.62*A / P)) / (hla + hga + Kua*DHev*0.62*B / P) - x[2]) / Gdry / Cu;
dxdt[3] = Kua*((0.62*(A + B*(hla*x[1] + hga*x[2] + Kua*DHev*(x[0] - 0.62*A / P)) / (hla + hga + Kua*DHev*0.62*B / P)) / P) - x[0]);
dxdt[4] = Kua*((0.62*(A + B*(hla*x[1] + hga*x[2] + Kua*DHev*(x[0] - 0.62*A / P)) / (hla + hga + Kua*DHev*0.62*B / P)) / P) - x[0]);
}

void write_output( state_type& x,  double z)
{
pack_height.push_back(z);
Umidity.push_back(x[0]);
T_liquid.push_back(x[1]);
T_gas.push_back(x[2]);
Liquid_flow.push_back(x[3]);
Gas_flow.push_back(x[4]);

cout << z << "      " << x[0] << "      " << x[1] << "      " << x[2] << "      " << x[3] << "      " << x[4] << endl;
}

// ----  Steppers definition  ----
// Basic stepper:
// follows given timestep size "dt"
typedef runge_kutta4<state_type> rk4;

// Error stepper, used to create the controlled stepper
typedef runge_kutta_cash_karp54< state_type > rkck54;

// Controlled stepper:
// it's built on an error stepper and allows us to have the output at each
// internally defined (refined) timestep, via integrate_adaptive call
typedef controlled_runge_kutta< rkck54 > ctrl_rkck54;

int main()
{
    state_type x(5);
    x[0] = Uair;
    x[1] = ToutH2O;
    x[2] = Tinair;
    x[3] = L0;
    x[4] = Gin;

    double z0 = 0.0;
    double zf = 10;
    double stepsize = 0.5;

    ofstream Liq;
    Liq.open("Liq.dat");
    ofstream Gas;
    Gas.open("Gas.dat");
    integrate_adaptive( ctrl_rkck54(), cooling_packing , x , z0 , zf , stepsize , write_output );

    const unsigned int sizer = static_cast<int>((zf - z0)/stepsize);
    const unsigned int vec_size = pack_height.size();


    for(int i=0; i<vec_size; i++)
        {
            Liq << pack_height[i] << "\t" << static_cast<double>(T_liquid[i]) << endl;
            Gas << pack_height[i] << "\t" << static_cast<double>(T_gas[i])    << endl;
        }

    Liq.close();
    Gas.close();

    cout << "\nvector size [1]: "      << vec_size       <<endl;
    cout << "vector size [2]: "        << sizer          <<endl;
    cout << "adaptive operator saves " << sizer-vec_size << " iterations" << endl;

    ofstream command;
	command.open("plot_command.txt");
	command << "set terminal pngcairo" <<endl;
	command << "set title 'Temperature Trend'" << endl;
	command << "set xlabel 'pack height [m]'" << endl;
	command << "set ylabel '[°C]'" << endl;
	command << "set grid" <<endl;
    	command << "plot 'Liq.dat' using 1:2 w lines,'Gas.dat' using 1:2 w lines" <<endl;
	command << "set output 'Temp_Trends.png'" <<endl;
	command.close();
	
	system("gnuplot plot_command.txt");

    return 0;
}



