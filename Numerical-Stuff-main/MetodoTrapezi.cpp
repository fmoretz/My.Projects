// Metodo dei Trapezi
#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

double f(double x){
	double I;
	I = x;
	return I;
}

int main(){
	
	while(true){
		
		cout<<"\nwrite your function directly into the code\nif you did it, ";
		system("pause");
		
		//Definizione delle variabiliù
		float limInf, limSup;
		int n;
		
		//Definizione limite superiore
		cout<<"\nEnter the superior limit:"<<endl;
		cin>>limSup;
		
		//Definizione limite inferiore
		cout<<"\nEnter the inferior limit:"<<endl;
		cin>>limInf;
		
		//Definizione numero di step
		cout<<"\nEnter the number of the integration step"<<endl;
		cin>>n;
		
		//Calcolo numero di step
		float h;
		h = (limSup-limInf)/n;
		
		//Calcolo della funzione
		double x[n],y[n];
		for(int i=0; i<=n; i++){
			x[i] = limInf+i*h;
			y[i] = f(x[i]);
		}
		
		//Calcolo dell'area dell'integrale
		float sumy=0, I=0;
		for(int i=0; i<=n; i++){
			sumy = sumy + y[i]*h;
			I = h/2*(y[0]+y[n])+sumy;
		}
		
		//Display dell'integrale
		cout<<"\nValue of Integral: "<<I<<endl;
		
		system("Pause");
	}
	return(0);
}
