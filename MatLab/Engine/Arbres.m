function [ P ] = Arbres( P,RemiseEchelle )
nombreArbre=0;
nbTriangleParArbre=4;
S=size(P,1);

for m=1:S
if((P(m,12)>=610)&&(P(m,12)<=700))
    if(rand(1)>0.95)
    
    Ab=[P(m,1) P(m,2)+5 P(m,3)+20 P(m,1) P(m,2)+5 P(m,3) P(m,1) P(m,2) P(m,3) P(m,10) P(m,11) P(m,12) -1 1 1];
    P(m+S+nombreArbre*nbTriangleParArbre,:)=Ab;
    
    Ab=[P(m,1)+5 P(m,2) P(m,3)+20 P(m,1)+5 P(m,2) P(m,3)+20 P(m,1) P(m,2) P(m,3) P(m,10) P(m,11) P(m,12) -1 1 1];
    P(m+S+(nombreArbre*nbTriangleParArbre)+1,:)=Ab;
    
    Ab=[P(m,1) P(m,2)-5 P(m,3)+10 P(m,1) P(m,2)+10 P(m,3)+10 P(m,1) P(m,2)+10 P(m,3)+40 P(m,10) P(m,11) P(m,12) -2 1 1 ];
    P(m+S+(nombreArbre*nbTriangleParArbre)+2,:)=Ab;
    
    Ab=[P(m,1)-5 P(m,2) P(m,3)+10 P(m,1)+5 P(m,2) P(m,3)+10 P(m,1)+5 P(m,2) P(m,3)+40 P(m,10) P(m,11) P(m,12) -2 1 1 ];
    P(m+S+(nombreArbre*nbTriangleParArbre)+3,:)=Ab;
    
    nombreArbre=nombreArbre+1;
    end
end



end

