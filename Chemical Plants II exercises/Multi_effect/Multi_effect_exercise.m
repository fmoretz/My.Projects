% Exercise Multi-Effect
clear all; clc; close all;
opt = optimoptions('fsolve','Display','Off');

global U1 DHev_s A1 mf Cp_s DHvap_1 Tf Ts DHvap_2 DHvap_3 mv3 zf_salts U2 A2 A3 U3

% Data
mf = 15000; 
zf_salts = 3.6/100;
zf_water = 1-zf_salts;
Tf = 60+273; 
Ts = 120+273;
mv3 = 12000;
Cp_s = 1;
DHev_s = 526;

% 1st effect
A1 = 200;
DHvap_1 = 537.3;
U1 = 750;

% 2nd effect
A2 = 200;
DHvap_2 = 549;
U2 = 550;

% 3rd effect
A3 = 200;
DHvap_3 = 571.3;
U3 = 300;


% Calculations
BPE_0 = 17.8*zf_salts;


sol = fsolve(@Multi_Effect, [6000,11000,7000,3000], opt);
ms = sol(1)
ml1 = sol(2)
ml2 = sol(3)
ml3 = sol(4)

DT1 = ms*DHev_s/(U1*A1);
T1 = Ts - DT1;
mv1 = mf-ml1;
x1 = mf*zf_salts/ml1;
BPE1 = 17.8*x1;
Tv1 = T1-BPE1;

DT2 = mv1*DHvap_1/(U2*A2);
T2 = Tv1 - DT2;
mv1 = mf-ml1;
x2 = ml1*x1/ml2;
BPE2 = 17.8*x2;
Tv2 = T2-BPE2;
mv2 = ml1-ml2;

DT3 = mv2*DHvap_2/(U3*A3);
T3 = Tv2 - DT3;
x3 = ml2*x2/ml3;
BPE3 = 17.8*x3;
Tv3 = T3-BPE3;

P1 = Pvap(T1)/1e5
P2 = Pvap(T2)/1e5
P3 = Pvap(T3)/1e5

fprintf('1st Effect:\n')


%% Functions
function F = Multi_Effect(x)
global U1 DHev_s A1 mf Cp_s DHvap_1 Tf Ts DHvap_2 DHvap_3 mv3 zf_salts U2 A2 A3 U3
ms = x(1); ml1 = x(2); ml2 = x(3); ml3 = x(4); 

% Tboil = fsolve(@T_Patm,100+273,opt);
% BPE = 17.8*x1;

T1 = Ts - DT1;
ms = U1*A1/(DHev_s);
mv1 = mf*(1-zf_salts)-ml1;
x1 = mf*zf_salts/ml1;
BPE1 = 17.8*x1;
Tv1 = T1-BPE1;

DT2 = mv1*DHvap_1/(U2*A2);
T2 = Tv1 - DT2;
x2 = ml1*x1/ml2;
BPE2 = 17.8*x2;
Tv2 = T2-BPE2;
mv2 = ml1-ml2;

DT3 = mv2*DHvap_2/(U3*A3);
T3 = Tv2 - DT3;
x3 = ml2*x2/ml3;
BPE3 = 17.8*x3;
Tv3 = T3-BPE3;

F(1) = mf*Cp_s*Tf+ms*DHev_s - (ml1*Cp_s*T1 + mv1*(Cp_s*T1+DHvap_1));
F(2) = ml1*Cp_s*T1+mv1*(Cp_s*T1+DHvap_1) - (ml2*Cp_s*T2 + mv2*(Cp_s*T2+DHvap_2));
F(3) = ml2*Cp_s*T2+mv2*(Cp_s*T2+DHvap_2) - (ml3*Cp_s*T3 + mv3*(Cp_s*T3+DHvap_3));
end

function P = Pvap(T)
C1 = -5.8002206e3;
C2 = 1.3914993;
C3 = -4.8640239e-2;
C4 = 4.1764768e-5;
C5 = -1.4452093e-8;
C6 = 6.5459673;

P = exp( C1/T+C2+C3*T+C4*T^2+C5*T^3+C6*log(T));
end




