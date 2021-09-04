--=================================================================
package SHAPE is
type OBJECT is abstract tagged private;  
type ACCESS_OBJECT is access OBJECT'CLASS;

type POINT is new OBJECT with private;
type LINE is new POINT with private;
type CIRCLE is new POINT with private;

procedure SET                           is abstract;
function LENGTH (O:OBJECT) return float is abstract;
function AREA   (O:OBJECT) return float is abstract;

procedure SET  (P:in out POINT;X,Y:FLOAT);
procedure SET  (L:in out LINE;X0,Y0,X1,Y1:FLOAT);
procedure SET  (C:in out CIRCLE;X,Y,RADIUS:FLOAT);

function LENGTH (P:POINT)  return float;
function LENGTH (L:LINE)   return float;
function LENGTH (C:CIRCLE) return float;

function AREA (P:POINT)  return float;
function AREA (L:LINE)   return float;
function AREA (C:CIRCLE) return float;

private
type OBJECT is abstract tagged  
     record       
     X:float;    
     Y:float;    
     end record;  
type POINT is new OBJECT with null record;
type LINE  is new POINT with
 record
 X1:FLOAT;
 Y1:FLOAT;
 end record;   
type CIRCLE is new POINT with
 record
 RADIUS:FLOAT;
 end record;   
end SHAPE; 