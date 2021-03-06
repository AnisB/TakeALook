% Tableau donnant les altitudes en metres aux points d'un maillage regulier
% dont la taille de la maille est de 100m
% x  va donc de 0 � (13-1)*100 metres
% y  va donc de 0 � (10-1)*100 metres
% Pour se faire une idee de ce terrain il suffit de faire : 
% surf(0:100:(13-1)*100,0:100:(10-1)*100,Terr);
function [ Y ] = Terrain(N)

delta=15;
lambda=0.7;

Terr=[670   672   670   675   690   680   650   675   690   680   700   892   895;
      680   665   640   630   650   645   630   628   648   650   680   875   893;
      630   615   585   580   585   600   590   610   603   603   630   850   895;
      595   568   555   560   575   580   575   570   580   610   625   800   850;
      550   540   538   550   595   575   600   570   575   620   613   700   730;
      525   530   538   550   603   625   615   580   570   610   590   610   720;
      545   540   538   597   575   605   593   578   573   593   608   595   695;
      615   560   543   579   569   560   563   570   580   595   619   638   650;
      625   598   560   559   586   558   578   585   600   615   655   680   683;
      610   600   610   605   615   618   625   638   648   665   680   700   705];
  
  Y=Terr;
  for y=1:N

      ncol=size( Y,2);
      nlig=size( Y,1);

      X=zeros(nlig,2*ncol-1);

      for i=1:ncol
            X(:,2*i-1)= Y(:,i);
      end

      Y=zeros(2*nlig-1,2*ncol-1);
      for i=1:nlig
            Y(2*i-1,:)= X(i,:);
      end

      ncol=size( Y,2);
      nlig=size( Y,1);

      
      for i=2:2:nlig
          for j=2:2:ncol
              
              Y(i,j)=((Y(i-1,j-1)+Y(i+1,j-1)+Y(i-1,j+1)+Y(i+1,j+1))/4)+(randn(1)*delta);
          end
      end


       for i=1:nlig
           j=1+mod(i,2);
          while(j<=ncol)
              if(j~=1 && j~=ncol && i~=1 && i~=nlig)
              Y(i,j)=((Y(i,j-1)+Y(i,j+1)+Y(i-1,j)+Y(i+1,j))/4)+(randn(1)*delta);
              else
                  if(j==1)
                      Y(i,j)=((Y(i-1,j)+Y(i+1,j))/2)+(randn(1)*delta);
                  end
                  if(j==ncol)
                      Y(i,j)=((Y(i-1,j)+Y(i+1,j))/2)+(randn(1)*delta);
                  end
                  if(i==1)
                      Y(i,j)=((Y(i,j-1)+Y(i,j+1))/2)+(randn(1)*delta);
                  end
                  if(i==nlig)
                      Y(i,j)=((Y(i,j-1)+Y(i,j+1))/2)+(randn(1)*delta);
                  end             
              end
              j=j+2;
          end
       end
       delta=delta*lambda;
  end
  %surf(Y);
end
  
          