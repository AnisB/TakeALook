function [ P ] = lumiereDiphuse( P ,Direction)

for m=1:size(P)
    X=[P(m,1)-P(m,4) P(m,2)- P(m,5) P(m,3)- P(m,6)]
    Y=[P(m,1)-P(m,7) P(m,2)- P(m,8) P(m,3)- P(m,9)]
    Z=cross(X,Y)
    Z=Z/norm(Z);
    S=Z*Direction'
    if(S>1)
        S=1;
    end
    P(m,15)=S;
end
end

