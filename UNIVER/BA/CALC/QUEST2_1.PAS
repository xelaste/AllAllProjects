program help;
var
X0,X,Xn,X1,X2,Fx,Dfx,Dfx1:real;
i:integer;
begin
X0:=PI/2;
Xn:=X0;
i:=0;
writeln('******* X0=',PI/2:1:5,'***************');
writeln('   n      x       F(x)     DF(x)     Xn     X-Xn');
repeat
X:=Xn;
Fx:=sin(X)-X/2;
DFx:=cos(X)-1/2;
Xn:=X-Fx/DFx;
Writeln(i:4,' ',X:2:5,' ',Fx:2:8,' ',DFx:2:5,' ',Xn:2:5,' ',X-Xn:2:8);
i:=i+1;
until abs(X-Xn)<0.00001;
writeln;
X0:=5*PI;
Xn:=X0;
i:=0;
writeln('******* X0=5*PI ',5*PI:1:5,'***************');
writeln('   n      x            F(x)          DF(x)        Xn        X-Xn');
repeat
X:=Xn;
Fx:=sin(X)-X/2;
DFx:=cos(x)-1/2;
Xn:=X-Fx/DFx;
Writeln(i:4,' ',X:2:8,'    ',Fx:2:8,'    ',DFx:2:5,'    ',Xn:2:5,'    ',X-Xn:2:8);
i:=i+1;
until abs(X-Xn)<0.00001;
writeln;
writeln('******* The Find Middle Method ***************');
writeln('X1=PI/3 ',PI/3:1:8,' , X2=2*PI/3 ',2*PI/3:1:8);
X1:=PI/3;X2:=2*PI/3;
i:=0;
writeln;
writeln('   n      x1   F(x1)      x2    F(x2)       x     F(x)');
repeat
X:=(X1+X2)/2;
Fx:=sin(x)-x/2;
Writeln(i:4,' ',X1:2:5,' ',(sin(x1)-x1/2):2:5,' ',X2:2:5,' ',(sin(x2)-x2/2):2:5,' ',X:2:5,' ',Fx:2:6,' ');
if Fx>0 then X1:=X else X2:=X;
i:=i+1;
until abs(X1-X2)<0.00001;
writeln('X=',(x1+x2)/2:1:6);
end.