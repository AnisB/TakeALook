function [ Q,Base ] = bords( P,nombreTri,Coordx,Coordy )
Base=0;
Q=zeros(nombreTri,size(P,2));
for m=1:nombreTri
    if((P(m,10)<=5)||(P(m,11)>=5))
      Q(m,:)=[P(m,1) P(m,2) P(m,3) P(m,1) P(m,2)-100 P(m,3) P(m,1)+3 P(m,2)-100 P(m,3) P(m,10) P(m,11) P(m,12) -3 0 0];
       Q(m*Base+1,:)=[P(m,1)+3 P(m,2) P(m,3) P(m,1)+3 P(m,2)-100 P(m,3) P(m,1) P(m,2) P(m,3) P(m,10) P(m,11) P(m,12) -3 0 0]; 
       Base=Base+1;
    end
end

end

