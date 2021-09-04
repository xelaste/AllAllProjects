--================================================================
with TEXT_IO;
with SHAPE;
procedure SHAPE_LIST is
package FLOAT_IO is new TEXT_IO.FLOAT_IO(FLOAT);
type NAME is (POINT,LINE,CIRCLE);
type NODE;--Item in the list of shapes
type ACCESS_NODE is access NODE;
type NODE is
     record 
     NAME_OF_SHAPE:NAME;
     ITEM:SHAPE.ACCESS_OBJECT;
     NEXT:ACCESS_NODE;
     end record; 
P:SHAPE.POINT;
L:SHAPE.LINE;
C:SHAPE.CIRCLE;
HEAD,
CURRENT:ACCESS_NODE;
------------------------------------------------------------------
procedure ADD (THE_NODE:in out ACCESS_NODE;SHAPE_NAME:NAME;
               NEXT_SHAPE:SHAPE.OBJECT'CLASS) is
begin
if THE_NODE=null 
   then THE_NODE     :=new NODE'(SHAPE_NAME,null,null);
   else THE_NODE.NEXT:=new NODE'(SHAPE_NAME,null,null);
        THE_NODE:=THE_NODE.NEXT;
end if;             
THE_NODE.ITEM:=new SHAPE.OBJECT'CLASS'(NEXT_SHAPE);
end ADD;
-------------------------------------------------------------------
procedure PRINT_SHAPE (THE_SHAPE:SHAPE.OBJECT'CLASS) is
begin
TEXT_IO.PUT("LENTH=");
FLOAT_IO.PUT(SHAPE.LENGTH(THE_SHAPE),3,2,0);
TEXT_IO.NEW_LINE;
TEXT_IO.PUT("AREA=");
FLOAT_IO.PUT(SHAPE.AREA(THE_SHAPE),3,2,0);
TEXT_IO.NEW_LINE;
end PRINT_SHAPE;
-------------------------------------------------------------------
begin
--           construct the list of shapes        --------------
SHAPE.SET(P,3.0,4.0);
SHAPE.SET(L,0.0,0.0,3.0,4.0);
SHAPE.SET(C,0.0,0.0,1.0);
HEAD:=null;
ADD(HEAD,POINT,P);
CURRENT:=HEAD;
ADD(CURRENT,LINE,L);
ADD(CURRENT,CIRCLE,C);
-- printing context of the shapes list ---------------------------
CURRENT:=HEAD;
TEXT_IO.NEW_LINE;
while CURRENT/=null loop
TEXT_IO.PUT_LINE(NAME'IMAGE(CURRENT.NAME_OF_SHAPE));
PRINT_SHAPE (CURRENT.ITEM.ALL);
CURRENT:=CURRENT.NEXT;
end loop;
end SHAPE_LIST;
--******************************************************************