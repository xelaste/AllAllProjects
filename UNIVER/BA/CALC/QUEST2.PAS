program help;
var
X0,XN,X,FX,S,h:real;
i:integer;
begin
X0:=0;XN:=0.5;h:=0.05;S:=0;
i:=1;X:=X0;
while (X<=XN+h/4) do
begin
if X<(0.5+h/100) then FX:=X*X-1 else FX:=exp(X)*sin(x);
writeln(X:1:2,' ',FX:1:6,' ',i);
S:=S+i*FX;
X:=X+h;
if (i=1) then i:=4
         else if (abs(X-XN)<h/8) then i:=1
                        else if (i=4) then i:=2 else i:=4;

end;
S:=(1/3)*h*S;
writeln(S:1:6);
end.