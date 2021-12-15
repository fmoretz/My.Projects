#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

//Funzione Sommatoria
double sum(double array[], float n_of_elements, float ris){
	for (int i = 0; i<n_of_elements;i++){
		ris = ris+array[i];
	}
	return ris;
}


// Linear Regression

int main()
{
while(int i=0; i<100; i++){
	cout.precision(4); //precisione decimale
	cout.setf(ios::fixed);  //output dei numeri come floating point
	
	//definizione numero di dati
	int pairs = 0;
	cout<<"\nEnter number of data pairs (x,y)\n";
	cin>>pairs;
	
	//Definizione vettori di dati
	double X[pairs], Y[pairs];
	
	//Vettore delle x
	cout<<"\nEnter X - data\n";
	for (int i=0; i<pairs; i++){
		cin>>X[i];
	}
	
	//Vettore delle y
	cout<<"\nEnter y - data\n";
	for (int i=0; i<pairs; i++){
		cin>>Y[i];
	}
	
	//Operazioni per calcolare slope e intercetta
	float xsum, ysum, x2sum, xysum;
	xsum = sum(X,pairs,0);
	ysum = sum(Y,pairs,0);
	
	for (int i = 0; i<pairs; i++){
		x2sum = x2sum + pow(X[i], 2);
		xysum = xysum+X[i]*Y[i];
	}
	
	//Calcolo di slope e intercetta
	float m,q;
	m = (pairs*xysum-xsum*ysum)/(pairs*x2sum-pow(xsum,2));
	q = (x2sum*ysum-xsum*xysum)/(x2sum*pairs-xsum*xsum);
	cout<<"\nSlope : "<<m;
	cout<<"\nIntercept : "<<q;
	cout<<"\nModel : "<<"y_model = "<<m<<"x + ("<<q<<")\n";
	
	
	//Calcolo y del modello diagramma input-output
	double ymodel[pairs];
	for (int i = 0; i<pairs; i++){
		ymodel[i] = m*X[i]+q;
	} 
	
	//Calcolo della R2 e residui
	 float R2, SSres, SStot, yavg; 
	 double diff1[pairs], diff2[pairs];
	 for (int i = 0; i<pairs; i++){
	 	diff1[i] = ymodel[i]-Y[i];
	 	diff1[i] = pow(diff1[i], 2);
	 	SSres = sum(diff1, pairs, 0);
	 	yavg = ysum/pairs;
	 	diff2[i] = Y[i]-yavg;
	 	diff2[i] = pow(diff2[i],2);
	 	SStot = sum(diff2,pairs,0);
	 }
	 R2 = 1-SSres/SStot;
	 cout<<"\nR2 = "<<R2<<endl;
	 
	 system("pause");	
	}
return (0);
}
