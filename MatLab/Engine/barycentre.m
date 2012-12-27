function [ Barycentred ] = barycentre( Machine, pointVision )

Barycentred=Machine;

 [nbTriangle,nombrefacteur]=size(Machine);
    for i=1:nbTriangle
        Barycentred(i,10)= ( Barycentred(i,1)+Barycentred(i,4)+Barycentred(i,7))/3;
        Barycentred(i,11)=( Barycentred(i,2)+Barycentred(i,5)+Barycentred(i,8))/3;
        Barycentred(i,12)=( Barycentred(i,3)+Barycentred(i,6)+Barycentred(i,9))/3;
        Vecteur =Barycentred(i,10:12);
        Barycentred(i,13)=1/norm(Vecteur-pointVision);
    end
    
    Barycentred=sortrows(Barycentred,13);
end

