program help;
var
X0,XN,X,FX,S,h:real;
i:integer;
begin
X0:=1.1;XN:=2;h:=0.9/90;S:=0;
i:=0;X:=X0;
while (X<=XN+h/100) do
begin
FX:=X*X*X/sqrt(X-1);
writeln(i:4,' ',X:1:4,' ',FX:1:6);
if (X=X0) then FX:=FX/2;
S:=S+FX;
X:=X+h;
i:=i+1;
end;
Writeln('S=',0.69949+(h*(S-FX/2)):1:6);
end.