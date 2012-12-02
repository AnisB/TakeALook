function [ P ] = lumierePonctuelle( P,source,numero )

nbTri=size(P,1);
for i=1:nbTri
    V=P(i,10:12);
    Dist=V-source;
    N=norm(Dist);
    N=abs(N);
    N=N/20;
    if(N<1)
        P(i,14+numero)=0.5;
    else
    P(i,14+numero)=( 1/N);
    
    end
end


end

