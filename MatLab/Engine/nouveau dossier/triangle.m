
sourceLumineuse1 =[15 0 600];
Direction =[ 0  0 -1];
nombreIteration=3;
X= Terrain(nombreIteration);

nlig=size(X,1);
ncol=size(X,2);

Y=zeros(((nlig-1)*(ncol-1))*2,9);

k=1;

%matriceDeTriangleFinie=0;

RemiseEchelle=100/(2^(nombreIteration));
for i=2:nlig
    for j=2:ncol
        Y(k,:)=[(i-1)*RemiseEchelle (j-1)*RemiseEchelle  X(i-1,j-1) (i-1)*RemiseEchelle  (j)*RemiseEchelle  X(i-1,j) i*RemiseEchelle  j*RemiseEchelle  X(i,j)];
        k=k+1;
        Y(k,:)=[(i-1)*RemiseEchelle  (j-1)*RemiseEchelle  X(i-1,j-1) i*RemiseEchelle  j*RemiseEchelle  X(i,j) i*RemiseEchelle  (j-1)*RemiseEchelle  X(i,j-1)];
        k=k+1;
    end
end
nYlig=size(Y,1);
%matriceDeTriangleFinie=1;




% pos=[ 500 500 500];
%  
%  Teta=[ 1 0 0;  0 cosd(30) -sind(30); 0 cosd(30) sind(30)];
%  Alpha=[ cosd(70) -sind(50) 0; cosd(50) sind(50) 0;0 0 1];
%  
% Inv=inv(Alpha*Teta);
%  ChangBase=Inv;
%  
% Passage=ChangBase;
%   Passage(4,4)=1;
%   Passage(1,4)=pos(1);
%    Passage(2,4)=pos(2);
%     Passage(3,4)=pos(3);
%     Passage(4,4)=1;

Z=Y;
pos=[2000 -1000 900];
PR=[0 1000 920];


% pos=[ -200 -150 900];
% PR=[15 25 650];


W=pos-PR;

norm= W(1)*W(1)+W(2)*W(2)+W(3)*W(3);

norm=sqrt(norm);
W= W/norm;
U =cross([0,0,1],W);
norm=U(1)*U(1)+U(2)*U(2)+U(3)*U(3);
U=U/sqrt(norm);
V= cross(W,U);
aMatrix=eye(3);
aMatrix(:,1)=U';
aMatrix(:,2)=V';
aMatrix(:,3)=W';
Rot=eye(4);
Rot(1:3,1:3)=inv(aMatrix);
Translation=eye(4);
Translation(1,4)=pos(1);
Translation(2,4)=pos(2);
Translation(3,4)=pos(3);
Translation(4,4)=1;



Passage=Rot*inv(Translation);

Z=barycentre(Z,pos);
Z=barrage(Z);

Z=lumierePonctuelle(Z,sourceLumineuse1,0);
Z=lumiereDiphuse(Z,Direction);
Z=Arbres(Z,RemiseEchelle);
nombreTri=size(Z,1);



for m=1:nombreTri
    
    Vect1=[ Z(m,1) Z(m,2) Z(m,3) 1];
    Vect1=Vect1';
    Vect1=Passage*Vect1;
    Vect1=Vect1';
      Vect1=[Vect1(1)/Vect1(4) Vect1(2)/Vect1(4) Vect1(3)/Vect1(4)];
    
    Vect2=[ Z(m,4) Z(m,5) Z(m,6) 1];
    Vect2=Vect2';
    Vect2=Passage*Vect2;
    Vect2=Vect2';
    Vect2=[Vect2(1)/Vect2(4) Vect2(2)/Vect2(4) Vect2(3)/Vect2(4)];  
    
    
    Vect3=[ Z(m,7) Z(m,8) Z(m,9) 1];
    Vect3=Vect3';
    Vect3=Passage*Vect3;
    Vect3=Vect3';
    Vect3=[Vect3(1)/Vect3(4) Vect3(2)/Vect3(4) Vect3(3)/Vect3(4)];
    
    
    Z(m,1:3)=Vect1;
    Z(m,4:6)=Vect2;
    Z(m,7:9)=Vect3;
end
Z=perspective(Z,5);

% [Q,a]=bords(Z,nombreTri);
% F=zeros(size(Z,1)+a*2);
% F((a*2):size(Z,1),:)=Z;
% F(1:(a*2),:)=Q;
% hold off

hold on
axis([-1 1 -1 1]);

DefColors(Z);



hold off


