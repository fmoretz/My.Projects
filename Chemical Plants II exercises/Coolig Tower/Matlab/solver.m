function coolingtower=solver(z,x)

global hla hga Kua DHev A P B Gdry CpL Cu

U=x(1);
Tl=x(2);
Tg=x(3);
L=x(4);
G=x(5);

Ti=(hla*Tl+hga*Tg+Kua*DHev*(U-0.62*A/P))/(hla+hga+Kua*DHev*0.62*B/P);
Ui=0.62*(A+B*Ti)/P;

coolingtower(1)=Kua*(Ui-U)/Gdry;
coolingtower(2)=hla*(Tl-Ti)/L/CpL;
coolingtower(3)=hga*(Ti-Tg)/Gdry/Cu;
coolingtower(4)=Kua*(Ui-U);
coolingtower(5)=Kua*(Ui-U);
    
coolingtower=coolingtower';
end