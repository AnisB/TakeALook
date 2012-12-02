function [ Matrice ] = barrage( Matrice )


for i=1:size(Matrice,1)
    
    if(Matrice(i,3)<=590)
        Matrice(i,3)=590;
    end
            if(Matrice(i,6)<=590)
        Matrice(i,6)=590;
            end
            if(Matrice(i,9)<=590)
        Matrice(i,9)=590;
            end
%    maxVal=0;
%     if((Matrice(i,3)>= Matrice(i,6)) && Matrice(i,3)>= Matrice(i,9))
%         maxVal=3;
%     end
%     if((Matrice(i,3)>= Matrice(i,3)) && Matrice(i,9)>= Matrice(i,6))
%         maxVal=9;
%     end
%     if((Matrice(i,6)>= Matrice(i,3)) && Matrice(i,6)>= Matrice(i,9))
%         maxVal=6;
%     end
%     
%     if (Matrice(i,maxVal)<590)
%         Matrice(i,3)=590;
%         Matrice(i,6)=590;
%         Matrice(i,9)=590;
%     end
%     
end


end

