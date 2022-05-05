#include<iostream>
#include<fstream>
#include<vector>
#include<math.h>
#include<algorithm>
#include<iterator>

using namespace std;

double VF1 = 6;
double LF1 = 20;
double tF1 = 60;
double VW1 = 1;
double day = 24*60;
double tload = 2;
double tdrain = 3;
double tass = 6;
double VF2 = 3.6;
double LF2 = 12;

int main()
{
    double toff = tload*2 + tdrain*2 + tass;
    cout << "Filter Unit Design and Optimization" << endl;
    cout << "(I) Daily Filtrate Volume with:" << endl;
    cout << "VF: " << VF1 << " m3" <<endl;
    cout << "L cake: " << LF1 << " mm" << endl;

    double alpha1 = VF1/VW1;
    double tW1 = 2*tF1/alpha1;
    double tcycle = toff + tW1 + tF1;
    double ncycle = day/tcycle;
    double dayP_1 = ncycle*VF1;

    cout << "\nResults" <<endl;
    cout << "alpha: " << alpha1 << endl;
    cout << "t washing: " << tW1 << " min" << endl;
    cout << "t filter: " << tF1 << " min" << endl;
    cout << "t dead: " << toff << " min" << endl;
    cout << "total t cycle: " << tcycle << " min" << endl;
    cout << "N. cycle x day: " << ncycle << " day-1" << endl;
    cout << "Daily Productivity = " << dayP_1 << " m3/day" << endl;

    cout << "\n(II) Daily Filtrate Volume with:" << endl;
    cout << "VF: " << VF2 << " m3" <<endl;
    cout << "L cake: " << LF2 << " mm" << endl;

    double K = VF1*VF1/(2*tF1); // = VF2*VF2 / 2 / tF2
    double tF2 = VF2*VF2/(2*K);
    double tW2 = 2*tF2/alpha1;
    double tcycle2 = toff + tW2 + tF2;
    double ncycle2 = day/tcycle2;
    double dayP_2 = VF2*ncycle2;

    cout << "\nResults" <<endl;
    cout << "t washing: " << tW2 << " min" << endl;
    cout << "t filter: " << tF2 << " min" << endl;
    cout << "t dead: " << toff << " min" << endl;
    cout << "total t cycle: " << tcycle2 << " min" << endl;
    cout << "N. cycle x day: " << ncycle2 << " day-1" << endl;
    cout << "Daily Productivity = " << dayP_2 << " m3/day" << endl;

    cout << "\n(III) Optimization of filter unit productivity over filtering time:" << endl;
    cout << "Data are the same of the (I) case" << endl;

    vector<double> P_vec;
    vector<double> t_vec;

    int stepslimit = 100000;
    double tF_iter = 0;

    for(int i=0; i<stepslimit; i++)
    {
        tF_iter = tF_iter + 0.05;
        P_vec.push_back( pow(2*K*tF_iter,0.5) * day/(toff + (1+2/alpha1)*tF_iter) );
        t_vec.push_back(tF_iter);
    }

    int j=0;
    double P_optim = *max_element(P_vec.begin(), P_vec.end());
    double tF_optim, Parr[P_vec.size()];
    for(j; j<P_vec.size(); j++)
    {
        Parr[j] = P_vec.at(j);
        if(Parr[j] == P_optim)
        {
            tF_optim = t_vec.at(j);
        }
    }

    double tW3 = 2*tF_optim/alpha1;
    double tcycle3 = toff + tW3 + tF_optim;
    double ncycle3 = day/tcycle3;
    double VF3 = P_optim/ncycle3;

    cout << "\nMax productivity: " << P_optim << " m3/day" <<endl;
    cout << "filtering time needed: " << tF_optim << " m3/day" << endl;
    cout << "Relative filtered volume: " << VF3 << " m3" << endl;
    cout << "\nOther results" <<endl;
    cout << "t washing: " << tW3 << " min" << endl;
    cout << "t dead: " << toff << " min" << endl;
    cout << "total t cycle: " << tcycle3 << " min" << endl;
    cout << "N. cycle x day: " << ncycle3 << " day-1" << endl;

    return 0;
}
