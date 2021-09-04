program IterationSolveEquation;
const
D=0.0001;
X01=2;
x02=3;
var
curr,next,help:real;
begin
{Xn=arccos(-x*x/10) - first form of solution}
next:=X01;
writeln;
writeln('****   Xn=arccos(-(Xn-1)*(Xn-1)/10)     ****');
repeat
curr:=next;
help:=-0.1*sqr(curr);
next:=Pi-arctan(sqrt(-1+1/sqr(help)));
{there is not arccos in pascal;         }
{if x=cos(y) and Pi>y>Pi/2 then y=arccos(x)=Pi-arctan(û(1/(x*x)-1)}
writeln(curr:2:5);
if abs(curr-next)<=d then writeln(next:2:5);
until abs(curr-next)<=d;
(****** solution Xn=û(-10*cos(Xn-1) *******)
writeln;
writeln('****   Xn=û(-10*cos(Xn-1))     ****');
next:=X02;
writeln;
repeat
curr:=next;
next:=sqrt(-10*cos(curr));
writeln(curr:2:5);
if abs(curr-next)<=d then writeln(next:2:5);
until abs(curr-next)<=d;
(****** solution Xn+1=Xn+Xn*Xn+10*cos(Xn) *******)
writeln;
writeln('****   Xn+1=Xn-Xn*Xn+10*cos(Xn)    ****');
next:=1;
writeln;
repeat
curr:=next;
next:=curr+cos(curr*curr+10*cos(curr))-1;
writeln(curr:2:5);
if abs(curr-next)<=d then writeln(next:2:5);
until abs(curr-next)<=d;
end.