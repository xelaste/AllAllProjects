--*********************************************************
with Ada.Numerics;
use  Ada.Numerics;
with Ada.Numerics.Elementary_Functions;
use  Ada.Numerics.Elementary_Functions;
package body SHAPE is
-----------------------------------------------------------
procedure SET  (P:in out POINT;X,Y:FLOAT) is
begin
P.X:=X;
P.Y:=Y;
end SET;--point
-----------------------------------------------------------
procedure SET  (L:in out LINE;X0,Y0,X1,Y1:FLOAT) is
begin
L.X:=X0;
L.Y:=Y0;
L.X1:=X1;
L.Y1:=Y1;
end SET;--line
--------------------------------------------------------------
procedure SET  (C:in out CIRCLE;X,Y,RADIUS:FLOAT) is
begin
SET(POINT(C),X,Y);
C.RADIUS:=RADIUS;
end SET;--circle
----------------------------------------------------------------
function LENGTH (P:POINT) return float is
begin
return 0.0;
end LENGTH;-- point
-----------------------------------------------------------------
function LENGTH (L:LINE) return float is
begin
return SQRT(((L.X-L.X1)**2)+(L.Y-L.Y1)**2);
end LENGTH;-- LINE
-----------------------------------------------------------------
function LENGTH (C:CIRCLE) return float is
begin
return 2.0*PI*C.RADIUS;
end LENGTH;--CIRCLE
------------------------------------
function AREA (P:POINT)   return float is
begin
return 0.0;
end AREA;-- POINT
--------------------------------------------
function AREA (L:LINE)        return float is
begin
return 0.0;
end AREA;--LINE
-----------------------------------------
function AREA (C:CIRCLE) return float is
begin
return PI*C.RADIUS**2;
end AREA;--CIRCLE
end SHAPE;