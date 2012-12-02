function Coloriage(Terr)

[m,n] = size(Terr);

hold on;

for i = 1:m    

    x = [ Terr(i,1) Terr(i,4) Terr(i,7) ];
    y = [ Terr(i,2) Terr(i,5) Terr(i,8) ];
    
    c = [ Terr(i,11) Terr(i,12) Terr(i,13) ];
    
    fill( x', y', c, 'EdgeColor', 'none' );
end

end