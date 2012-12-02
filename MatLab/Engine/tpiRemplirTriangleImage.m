function im=tpiRemplirTriangleImage(im, ZB, Sommets, Barry, Couleur)

% Remplit  l'image im de taille size(im) = [H W 3] avec 
% la couleur Couleur = [R G B] dans le triangle 2D de sommmets S1, S2, S3 donn�s par
% Sommets = [S1.lig S1.col ; S2.lig S2.col ; S3.lig S3.col]
% si la distance donn�e par la valeur Barry est celle contenue dans le ZBuffer ZB
Sommets=fliplr(Sommets);

S=sortrows(Sommets);
V1=S(2,:)-S(1,:);
V2=S(3,:)-S(1,:);
SigneDet=det([V1;V2])>0;

if SigneDet,
    % Point interm?diaire ? gauche
    [COL, LIG]=bresenhamGauche(S(1,:),S(2,:));
    Lignes=LIG;
    ColonnesGauche=COL;
    [COL, LIG]=bresenhamGauche(S(2,:),S(3,:));
    N=size(LIG,2);
    Lignes=[Lignes LIG(2:N)];
    ColonnesGauche=[ColonnesGauche COL(2:N)];
    [ColonnesDroit, LIG]=bresenhamDroit(S(1,:),S(3,:));
else
 % Point interm?diaire ? droite
    [COL, LIG]=bresenhamDroit(S(1,:),S(2,:));
    Lignes=LIG;
    ColonnesDroit=COL;
    [COL, LIG]=bresenhamDroit(S(2,:),S(3,:));
    N=size(LIG,2);
    Lignes=[Lignes LIG(2:N)];
    ColonnesDroit=[ColonnesDroit COL(2:N)];
    [ColonnesGauche, LIG]=bresenhamGauche(S(1,:),S(3,:));
end
%Lignes
%LIG
 for n=1:size(Lignes,2),
    for c=ColonnesGauche(n)-2:ColonnesDroit(n)+2,
        if abs(ZB(Lignes(n),c)-Barry)<0.5,
            im(Lignes(n),c,1)=Couleur(1);
            im(Lignes(n),c,2)=Couleur(2);
            im(Lignes(n),c,3)=Couleur(3);
        end
    end
 end

end

function [x y]=bresenham(x1,y1,x2,y2)

x1=round(S(1,2)); x2=round(S(2,2));
y1=round(S(1,1)); y2=round(S(2,1));
dx=abs(x2-x1);
dy=abs(y2-y1);
steep=abs(dy)>abs(dx);
if steep 
    t=dx;
    dx=dy;
    dy=t; 
end
if dy==0 
    q=zeros(dx+1,1);
else
    q=[0;diff(mod([floor(dx/2):-dy:-dy*dx+floor(dx/2)]',dx))>=0];
end


if steep
    if y1<=y2 y=[y1:y2]'; else y=[y1:-1:y2]'; end
    if x1<=x2 x=x1+cumsum(q);else x=x1-cumsum(q); end
else
    if x1<=x2 x=[x1:x2]'; else x=[x1:-1:x2]'; end
    if y1<=y2 y=y1+cumsum(q);else y=y1-cumsum(q); end
end
end

function [x y]=bresenhamGauche(S1,S2)

x1=round(S1(2)); x2=round(S2(2));
y1=round(S1(1)); y2=round(S2(1));
dx=abs(x2-x1);
dy=abs(y2-y1);
steep=abs(dy)>abs(dx);
if steep 
    t=dx;
    dx=dy;
    dy=t; 
end

if dy==0 
    q=zeros(dx+1,1);
else
    q=[0;diff(mod([floor(dx/2):-dy:-dy*dx+floor(dx/2)]',dx))>=0];
end

if steep
    if y1<=y2 y=[y1:y2]'; else y=[y1:-1:y2]'; end
    if x1<=x2 x=x1+cumsum(q);else x=x1-cumsum(q); end
else
    
    if x1<=x2 x=[x1:x2]'; else x=[x1:-1:x2]'; end
    if y1<=y2 y=y1+cumsum(q);else y=y1-cumsum(q); end
    xx(1,1)=x(1); yy(1,1)=y(1);
    N=size(q,1);
    for n=1:N
        if q(n)==1,
            xx=[xx; x(n)];
            yy=[yy; y(n)];
        end
    end
    x=xx; y=yy;
    
end
x=x'; y=y';
end


function [x y]=bresenhamDroit(S1,S2)

x1=round(S1(2)); x2=round(S2(2));
y1=round(S1(1)); y2=round(S2(1));

dx=abs(x2-x1);
dy=abs(y2-y1);
steep=abs(dy)>abs(dx);
if steep 
    t=dx;
    dx=dy;
    dy=t; 
end

if dy==0 
    q=zeros(dx+1,1);
else
    q=[0;diff(mod([floor(dx/2):-dy:-dy*dx+floor(dx/2)]',dx))>=0];
end


if steep
    if y1<=y2 y=[y1:y2]'; else y=[y1:-1:y2]'; end
    if x1<=x2 x=x1+cumsum(q);else x=x1-cumsum(q); end
else
    
    if x1<=x2 x=[x1:x2]'; else x=[x1:-1:x2]'; end
    if y1<=y2 y=y1+cumsum(q);else y=y1-cumsum(q); end
    xx=[]; yy=[];
    N=size(q,1);
    for n=1:N
        if q(n)==1,
            xx=[xx; x(n)-1];
            yy=[yy; y(n)-1];
        end
    end
    xx=[xx; x(N)];
    yy=[yy; y(N)];
    x=xx; y=yy;
    
end
x=x'; y=y';

end