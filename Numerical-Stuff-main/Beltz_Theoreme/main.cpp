//
//  main.cpp
//  Teorema_Beltz
//
//  Created by Federico Moretta on 12/05/21.
//

#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>

using namespace std;

int main() {
    
    // Velocity ratio evaluation Vf/Vi
    vector<double>VfVi;
    double unit = 1;
    
    for(int i=0; i<100; i++){
        VfVi.push_back(unit/100);
        unit += 1;
    };
    
    // Power evaluation
    vector<double>PgPmax;
    
    for(int i=0; i<100; i++){
        PgPmax.push_back( 0.5*(1+VfVi.at(i))*( 1-pow(VfVi.at(i),2) ) );
    };
    
    ofstream Plot("Power Generation.txt");
    
    for(int i=0; i<PgPmax.size(); i++){
        Plot << VfVi.at(i) << ";" << PgPmax.at(i) << endl;
    };
    Plot.close();
    
    
    return 0;
}
