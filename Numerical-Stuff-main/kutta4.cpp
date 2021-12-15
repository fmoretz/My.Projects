//Rounge-Kutta 4th grade method for differential equations
#include<stdio.h> 
#include<iostream>
#include<iomanip>
#include<cmath>
#include<fstream>
using namespace std;

//introduce Differential equation "dy/dx = f(x,y)" 
float dydx(float x, float y) 
{ 
	// Write the equation:
	return(      cos(x)			); 
} 

//Function
float odeKutta4(float x0, float y0, float x_obj, float h) 
{ 
//Count number of iterations  
	int n = (int)((x_obj - x0) / h); 

	float k1, k2, k3, k4, k5; 

//Iterate for number of iterations 
	float y=y0; 
	for (int i=1; i<=n; i++) 
	{ 
		k1 = h*dydx(x0, y); 
		k2 = h*dydx(x0 + 0.5*h, y + 0.5*k1); 
		k3 = h*dydx(x0 + 0.5*h, y + 0.5*k2); 
		k4 = h*dydx(x0 + h, y + k3); 

		y = y + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4); 

		x0 = x0 + h; 
	} 

	return y; 
} 

//Main function
int main() 
{ 
	cout<<"\nBEFORE START, BE AWARE TO HAVE OPTIMIZE ALL THE SETTINGS IN THE MAIN AND"<<endl;
	cout<<"HAVE CHANGED THE FUNCTION IN THE 'dxdy' SECTION"<<endl;
	cout<<"If yes, ";
	system("pause");
	cout.precision(4); //precisione decimale
	cout.setf(ios::fixed);  //output dei numeri come floating point
	
//Initial Conditions
	float x0 = 0;
	float y0 = 1;
	float h=0.01;
//Aim 
	float x_final = 10;
	
	
	float x_obj=x0;
	float xwrite = x0;
	
	//Number of iterations
	int n=(int)((x_final - x0)/h); 
	double y[n];
		
	for(int i=0; i<=n; i++){
	
		x_obj = x_obj+h;

		y[i] =  odeKutta4(x0, y0, x_obj, h); 
		cout<<"\nThe value of y at x["<<i<<"]: "<<x_obj<<" is : "<<y[i];
	
	}
	ofstream myFile;
		myFile.open("kutta4_output.dat");
		for(int i=0; i<=n; i++){
			
			
			xwrite = xwrite+h;
			myFile<< i << "  "<< xwrite <<"  "<< y[i]<<endl;
		}
	return 0; 
} 







