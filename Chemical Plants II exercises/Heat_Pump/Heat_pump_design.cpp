//Heat pump desgin - Federico Moretta - Chemical Plants II Chp. 3
#include <iostream>
#include <math.h>
#define DTmin 5 //[�C]

#define Sup_Imp 0.75 //for optimal valve opening
#define Inf_Imp 0.50 //for optimal valve closing
#define fx 1 //Geometrical factor related to the nature of the valve (opening-closing function)
#define Indust_Fact 12 //Geometrical factor for the industrial production of the valve

using namespace std;

//Global data
/*Antoine*/
double A = 3.97183;
double B = 1021.864;
double C = -43.231;
/*Physical*/
double CpL = 2.426; //[kJ/kg/K]
double CpV = 1.778; //[kJ/kg/K]
double Hev = 19940; //[kJ/kmol] @Tc
double MW  = 72.15; //[kg/kmol] - isopentane vapour
double rho = 0.620; //[g/cm3]   - isopentane vapour
/*Heat coefficients*/
double Uc  = 375.0; //[W/m2/K]
double Ue  = 340.0; //[W/m2/K]
/*Heat pump specification*/
double Qc  = 7.500; //[kW]
double Tam = 50.00; //[�C]
double Tsy = 95.00; //[�C]

int main(){
	/*Condenser and evaporator*/
	double Tc = Tsy + DTmin; 				 //[�C]
	double Te = Tam - DTmin; 				 //[�C]
	double Pc = pow(10, A-B/(Tc+273.15+C));  //[kPa]
	double Pe = pow(10, A-B/(Te+273.15+C));  //[kPa]

	/*Coefficient of Performance*/
	double Hev_mass = Hev/MW; 			 //[kJ/kg] @Tc
	double COP = Hev_mass/(CpV*(Tc-Te)); //[--]

	/*Flow Rates*/
	double W      = Qc/COP; 					  //[kW]
	double R      = Qc/Hev_mass; 				  //[kg/s]
	double Hev_Te = Hev_mass + (CpV-CpL)*(Tc-Te); //[kJ/kg] @Te
	double L      = R*(1-( CpL*(Tc-Te)/Hev_Te )); //[kg/s]
	double V      = R-L;						  //[kg/s]
	double Qe     = R*(Hev_mass-CpV*(Tc-Te));     //[kW]

	/*Heat Exchanger Design*/
	double DTs = DTmin;       	   //[�C]
	double Ae  = Qe*1000/(Ue*DTs); //[m2]
	double Ac  = Qc*1000/(Uc*DTs); //[m2]

	/*Valve*/
	double DP = Pc-Pe; //[kPa]
	double Cv = Indust_Fact*Sup_Imp*R/( fx*pow(DP/rho,0.5)); //[m]



	/*Showing Results*/
	cout<<"Results:"<<endl;
	cout<<"Condenser and Evaporator data"<<endl;
	cout<<"Param."<<"	|	"<<"Value"<<"	  	"<<"UoM"<<endl;
	cout<<"Qc    "<<"	|	"<<Qc<<"	    |	"<<"kW"<<endl;
	cout<<"Qe    "<<"	|	"<<Qe<<"	    |	"<<"kW"<<endl;
	cout<<"Tc    "<<"	|	"<<Tc<<"	    |	"<<"K"<<endl;
	cout<<"Te    "<<"	|	"<<Te<<"	    |	"<<"K"<<endl;
	cout<<"Pe    "<<"	|	"<<Pe<<"	    |	"<<"kPa"<<endl;
	cout<<"Pc    "<<"	|	"<<Pc<<"	    |	"<<"kPa"<<endl;
	cout<<"Ac    "<<"	|	"<<Ac<<"	    |	"<<"m2"<<endl;
	cout<<"Ae    "<<"	|	"<<Ae<<"	    |	"<<"m2"<<endl;

	cout<<"\nHeat Pump Design Data"<<endl;
	cout<<"COP    "<<"	|	"<<COP<<"	    |"<<"	--"<<endl;
	cout<<"R    "<<"	|	"<<R<<"   |"<<"	kg/s"<<endl;
	cout<<"W    "<<"	|	"<<W<<"	    |"<<"	kW"<<endl;
	cout<<"b    "<<"	|	"<<Pc/Pe<<"      |"<<"	--"<<endl;
	cout<<"V    "<<"	|	"<<V<<"   |"<<"	kg/s"<<endl;
	cout<<"L    "<<"	|	"<<L<<"   |"<<"	kg/s"<<endl;
	cout<<"Qc/Qe"<<"	|	"<<Qc/Qe<<"	    |"<<"	--"<<endl;
	cout<<"Cv"<<"	|	"<<Cv*100<<"		|"<<"	cm"<<endl;
	cout<<"Cv"<<"	|	"<<Cv*100/2.54<<"		|"<<"	in"<<endl;

	return 0;
}
