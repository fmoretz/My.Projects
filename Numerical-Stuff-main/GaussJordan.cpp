//Gauss-Jordan method for linear problem
#include <iostream>
#include "funcalc.h"
#include <cmath>

using namespace std;

int main(){
//Advise
	cout<<"NOTE THAT THE GAUSS-JORDAN WORK WITH SQUARE MATRIX"<<endl;
	
	system ("pause");
	
	while(true){
		
		int col,row,i,r,c;
		double d,e1;
		
	//Matrix of coefficients
		cout<<"\nCreation of coerricients matrix:\n";
		cout<<"enter number of rows & columns : ";
		cin>>row;
		col=row;
		
		double a[row*2][col*2];
		
		for(i=1;i<=row; i++){
			for(int j=1; j<=col; j++){
			cout<<"enter the value of the matrix a["<<i<<"]["<<j<<"]"<<" : ";
			cin>>a[i][j];
			}
			cout<<endl;
		}
		
	//Vector of known terms
		cout<<"Creation of known term vector\n";
		
		double b[row*2], x[(row*2)];
		
		for(i=1;i<=row; i++){
					cout<<"enter the value of the known term b["<<i<<"]"<<" : ";
			cin>>b[i];
			x[i]=0;
		}
		cout<<endl;
	
	//Calculations
		for (r=1; r<=row;r++){
			d = -1/a[r][r];
			for(c=1; c<=col; c++){
				
				if (c==r)(c++);
				a[r][c]=a[r][c]*d;
				
				}
			d = -d;
			for(i=1; i<=row; i++){
				
				if(i==r)(i++);
				e1 = a[i][r];
				for(c=1;c<=col;c++){
					
					if(c==r)(a[i][r] = a[i][r]*d);
					else(a[i][c]=a[i][c]+a[r][c]*e1);			
								
				}
			}
			a[r][r]=d;
		}
		
		for(i=1;i<=row;i++){
			
			for(c=1;c<=row;c++){
				
				x[i]=x[i]+b[c]*a[i][c];		//unknowns calculation
				
			}
			
		}
		
	//Show solutions
		for(i=1;i<=row;i++){
			cout<<"uknown "<<i<<" solution:	x["<<i<<"]= "<<x[i]<<endl;
		}
		
		system ("pause");
	}
return 0;
}
