clear all
close all
clc

global S_target A CpL T0 L0 x0 Tv0 U DHev

S_target = 12000; %kg/h
U = [750 550 300];
A = 200; %m2
CpL = 1;
DHev = [526 537.3 549 571.3];

T0 = 60;
L0 = 15000;
x0 = 3.6/100;
Tv0 = 120;
V0_guess = 15000/3; %kg/h
opz = optimoptions('fsolve','FunctionTolerance',1e-9,'StepTolerance',1e-9,'OptimalityTolerance',1e-9);
V0 = fsolve(@steam, V0_guess,opz);

[T1,L1,x1,V1,Tv1] = evaporation(T0,L0,x0,V0,Tv0,U(1),DHev(1),DHev(2));
[T2,L2,x2,V2,Tv2] = evaporation(T1,L1,x1,V1,Tv1,U(2),DHev(2),DHev(3));
[T3,L3,x3,V3,Tv3] = evaporation(T2,L2,x2,V2,Tv2,U(3),DHev(3),DHev(4));

DT1 = Tv0-T1;
DT2 = Tv1-T2;
DT3 = Tv2-T3;

DTeb1 = 17.8*x1;
DTeb2 = 17.8*x2;
DTeb3 = 17.8*x3;

C1 = -5.8002206e3;
C2 = 1.3914993;
C3 = -4.8640239e-2;
C4 = 4.1764768e-5;
C5 = -1.4452093e-8;
C6 = 6.5459673;

P1 = exp(C1/(T1+273.15)+C2+C3*(T1+273.15)+C4*(T1+273.15)^2+C5*(T1+273.15)^3+C6*log(T1+273.15))/101325;
P2 = exp(C1/(T2+273.15)+C2+C3*(T2+273.15)+C4*(T2+273.15)^2+C5*(T2+273.15)^3+C6*log(T2+273.15))/101325;
P3 = exp(C1/(T3+273.15)+C2+C3*(T3+273.15)+C4*(T3+273.15)^2+C5*(T3+273.15)^3+C6*log(T3+273.15))/101325;
function F = steam(V0)
    global S_target T0 L0 x0 Tv0 U DHev
    [T1,L1,x1,V1,Tv1] = evaporation(T0,L0,x0,V0,Tv0,U(1),DHev(1),DHev(2));
    [T2,L2,x2,V2,Tv2] = evaporation(T1,L1,x1,V1,Tv1,U(2),DHev(2),DHev(3));
    [T3,L3,x3,V3,Tv3] = evaporation(T2,L2,x2,V2,Tv2,U(3),DHev(3),DHev(4));
    S_tot = V1+V2+V3;
    F = (S_tot-S_target)^2;
end
function [T,L,x,V,Tv] = evaporation(T_IN,L_IN,x_IN,V_IN,Tv_IN,U,DHev_v,DHev_sol)
    global A CpL
    
    Q = V_IN*DHev_v;
    DT = Q/U/A;
    T = Tv_IN-DT;
    L = (L_IN*CpL*T_IN + Q - L_IN*(CpL*T+DHev_sol))/(-DHev_sol);
    V = L_IN-L;
    x = L_IN*x_IN/L;
    DTeb = 17.8*x;
    Tv = T-DTeb;
end