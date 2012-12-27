function [ Perspectived ] = perspective( Z, focale )

P=eye(4);
P(4,3)=-1/focale;

for m=1:size(Z,1)
    Vect1=[ Z(m,1) Z(m,2) Z(m,3) 1];
   
    Vect1=Vect1';
    Vect1=P*Vect1;
    Vect1=Vect1';
     Vect1=[Vect1(1)/Vect1(4) Vect1(2)/Vect1(4) Vect1(3)/Vect1(4)];  
    
    Vect2=[ Z(m,4) Z(m,5) Z(m,6) 1];
    Vect2=Vect2';
    Vect2=P*Vect2;
    Vect2=Vect2';
    Vect2=[Vect2(1)/Vect2(4) Vect2(2)/Vect2(4) Vect2(3)/Vect2(4)];  
    
    
    Vect3=[ Z(m,7) Z(m,8) Z(m,9) 1];
    Vect3=Vect3';
    Vect3=P*Vect3;
    Vect3=Vect3';
     Vect3=[Vect3(1)/Vect3(4) Vect3(2)/Vect3(4) Vect3(3)/Vect3(4)];  
    
    
    Z(m,1:3)=Vect1;
    Z(m,4:6)=Vect2;
    Z(m,7:9)=Vect3;
end
Perspectived=Z;
end
