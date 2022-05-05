clc
close all
clear all

global hla hga Kua DHev A P B Gdry CpL Cu

% Physical Properties
Lin=20000;                                      % kg/h
Gin=15000;          							% kg/h
Tinwat=50;      								% °C
Toutwat=25;         							% °C
Tinair=20;      								% °C
P=760;      									% mmHg
Z=0.5;      									% relative humidity
Cu=0.26;        								% kcal/kg*K
CpL=1;          								% kcal/kg*K	
DHev=580;       								% kcal/kg
hga=4000;       								% kcal/m/h/K
hla=30000;              						% kcal/m/h/K

% Vapor Pressure Correlation
A=-49.705;                              		% Pev 1st coeff	mmHg vs °C
B=2.71;                                     	% Pev 2nd coeff    mmHg vs °C

% Humidity
Usair=0.62*(A+B*Tinair)/P;                      % kg/kg
Uair=Z*Usair;                                   % kg/kg
Kua=hga/Cu;                                     % kg/m/h
Gdry=Gin/(1+Uair);                              % kg/h      NOTE: Since U is very low Gin ~= Gdry

% Integration
L0=19292;                           			% kg/h

zspan=0:0.05:10;
y0=[Uair Toutwat Tinair L0 Gin];

[z,y]=ode15s(@solver,zspan,y0);

figure(1)
plot(zspan,y(:,2))
hold on
plot(zspan,y(:,3))
legend('Tl','Tg')
xlabel('Packed bed height')
ylabel('Temperature [K]')
grid on

figure(2)
plot(zspan,y(:,4))
xlabel('Packed bed height')
ylabel('Liquid flowrate [kg/h]')
grid on