program Iteration_Jacob_Method;
const D=0.000001;
Type
vector=array[1..100] of real;
function NormaOfVector(x:vector;size:integer):real;
var
max:real;
i:integer;
begin
max:=abs(x[1]);
for i:=2 to size do if abs(x[i])>max then max:=abs(x[i]);
NormaOfVector:=max;
end;
var
M:array[1..100,1..100] of integer;
X,XK,B:vector;
NX,NXk:real;
size,i,j,k:integer;
sign:char;
begin
for i:=1 to 100 do
begin
X[i]:=0;Xk[i]:=0;B[i]:=0;
for j:=1 to 100 do M [i,j]:=0;
end;
read(size);
for i:=1 to size do for j:=1 to size do read(M[i,j]);
for i:=1 to size do read(B[i]);
for i:=1 to size do
begin
writeln;
for j:=1 to size do
begin
if j=size then sign:=' ' else sign:='+';
write(M[i,j]:4,'*X',j,' ',sign,' ');
end;
write('= ',B[i]:4:0);
end;
writeln;writeln;
for i:=1 to size do write('     ','X',i,'   ');
k:=0;
repeat
for i:=1 to size do X[i]:=Xk[i];
k:=k+1;
for i:=1 to size do
begin
Xk[i]:=0;
for j:=1 to size do if (i<>j) then Xk[i]:=Xk[i]-(M[i,j]*X[j]);
Xk[i]:=(Xk[i]+B[i])/M[i,i];
end;
for i:=1 to size do X[i]:=X[i]-Xk[i];
NX:=NormaOfVector(X,size);
writeln;
write(k:3,'.');
for j:=1 to size do write(' ',Xk[j]:4:6);
until abs(NX)<=D;
end.