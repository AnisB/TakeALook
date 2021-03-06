function [ P ] = DefColors( P )

nbTriangle=size(P,1);
delta=0.05;
    for m=1:nbTriangle
        if(P(m,14)<0)
            facteur1=1;
        else
             facteur1=1-P(m,14);
        end
            if(facteur1<0.5)
                    facteur1=0.5;
            end
                
             facteur2=P(m,15);
             if(facteur2<0.5)
                     facteur1=0.5;
             end
            facteur=facteur1*facteur2;
     
     
            %Coloriage des troncs
            if(P(m,13)==-1)
                c=rand(1)*delta;
                fill([P(m,1) P(m,4) P(m,7)],[P(m,2) P(m,5) P(m,8)],[0.6-c ,0.4-c,0.1-c],'EdgeColor','none')
            %Coloriage des feuilles
            else if(P(m,13)==-2)
                c=rand(1)*delta; 
                fill([P(m,1) P(m,4) P(m,7)],[P(m,2) P(m,5) P(m,8)],[0.7-c ,0.2,0.2  ],'EdgeColor','none')
            % Coloriage de l'eau
            else if(P(m,12)<590)

                 fill([P(m,1) P(m,4) P(m,7)],[P(m,2) P(m,5) P(m,8)],[facteur*0.4,facteur*0.7,facteur*1],'EdgeColor','none');
            % Coloriage du sable
            else if((P(m,12)>=590)&&(P(m,12)<600))
                    fill([P(m,1) P(m,4) P(m,7)],[P(m,2) P(m,5) P(m,8)],[facteur*0.99,facteur*0.8,facteur*0.6],'EdgeColor','none');
                    
            else if ((P(m,12)<750)&&(P(m,12)>=600))
                    c=rand(1)*delta;
                    fill([P(m,1) P(m,4) P(m,7)],[P(m,2) P(m,5) P(m,8)],[facteur*(0.4-c) ,facteur*(0.6-c),facteur*(0.3-c)],'EdgeColor','none');
                    X=[P(m,1)-P(m,4) P(m,2)- P(m,5) P(m,3)- P(m,6)];
                    Y=[P(m,1)-P(m,7) P(m,2)- P(m,8) P(m,3)- P(m,9)];
                    Z=cross(X,Y);
                    Z=Z/norm(Z);
                    p=Z*[0 ;0 ;1];
                     if(((abs(p)<0.60)&&(P(m,12)>600)))
                         c=rand(1)*delta;
                        fill([P(m,1) P(m,4) P(m,7)],[P(m,2) P(m,5) P(m,8)],[facteur*(0.6-c) ,facteur*(0.6-c),facteur*(0.6-c)],'EdgeColor','none');
                     end
                else 
                      c=rand(1)*delta;
                      fill([P(m,1) P(m,4) P(m,7)],[P(m,2) P(m,5) P(m,8)],[facteur*(0.7-c) ,facteur*(0.7-c),facteur*(0.7-c)],'EdgeColor','none');
                end
                end
                end
                end
            end
          if(P(m,12)>860) 
              proba=randn(1);
              if(proba>0.3)
                c=rand(1)*0.1;
                fill([P(m,1) P(m,4) P(m,7)],[P(m,2) P(m,5) P(m,8)],[0.9-c ,0.9-c,0.9-c],'EdgeColor','none');
              end
          end
    end   
end

