-- *********************** Linked polynom body ****************************
with TEXT_IO; 
package body LINKED_POLYNOM is
MAX_DEGREE:constant:=100;
type REAL is digits 10;  
type NODE is
     record
     FACTOR:REAL:=REAL(0);
     DEGREE:NATURAL:=0;
     NEXT  :POLYNOM:=null;
     end record;
ZERO_NODE:constant NODE:=(REAL(0),0,null);
package REAL_IO is new TEXT_IO.FLOAT_IO(REAL);
package NATURAL_IO is new TEXT_IO.INTEGER_IO(NATURAL);
--=======================================================================
function GET_POLYNOM return POLYNOM is
FACTOR:REAL;
ORDER:NATURAL;
LAST,
RESULT:POLYNOM:=null;
--------------------------------------------------------------------------
begin
TEXT_IO.NEW_LINE;
TEXT_IO.PUT("Input polynom order from 0 to ");
NATURAL_IO.PUT(MAX_DEGREE,4);
TEXT_IO.NEW_LINE;
NATURAL_IO.GET(ORDER);
if ORDER>MAX_DEGREE then raise CONSTRAINT_ERROR; end if;
TEXT_IO.PUT_LINE ("Input factor for every member of polynom");
for I in reverse 0..ORDER loop
    FACTOR:=REAL(0);
    TEXT_IO.PUT("X^");
    NATURAL_IO.PUT(I,1);
    TEXT_IO.PUT(": ");
    REAL_IO.GET(FACTOR);
    if FACTOR/=REAL(0) 
       then  if ACCESS_NODE(RESULT)=null --polynom is empty     
                then RESULT:=new NODE'(FACTOR,I,null);     
                     LAST:=RESULT;                              
                else LAST.NEXT:=new NODE'(FACTOR,I,null); 
                     LAST:=LAST.NEXT;                          
                end if;                                           
    end if; 
end loop; 
return RESULT;
exception
 when CONSTRAINT_ERROR=> TEXT_IO.PUT("Invalid polynom order");
                         return null;    
 when others=>return null;
end GET_POLYNOM;
--=====================================================================
procedure PRINT_POLYNOM (HEAD:POLYNOM) is
TEMP:POLYNOM;
begin
TEMP:=HEAD;
while TEMP/=null loop
if TEMP=HEAD 
   then if TEMP.FACTOR<REAL(0)
           then TEXT_IO.PUT('-');
           end if;
   elsif TEMP.FACTOR<REAL(0)      
         then TEXT_IO.PUT(" - "); 
         else TEXT_IO.PUT(" + ");
end if;      
if TEMP.DEGREE>0 then if abs(TEMP.FACTOR)/=REAL(1)
                         then REAL_IO.PUT(abs(TEMP.FACTOR),5,2,0); 
                              TEXT_IO.PUT("*X");
                         else TEXT_IO.PUT(" X");
                       end if;   
                  else REAL_IO.PUT(abs(TEMP.FACTOR),5,2,0); 
end if;
if TEMP.DEGREE>1 
   then TEXT_IO.PUT('^');
   NATURAL_IO.PUT (TEMP.DEGREE,1);
end if;        
TEMP:=TEMP.NEXT;
end loop;
end PRINT_POLYNOM;                                   
--====================================================================
function "+" (LEFT,RIGHT:POLYNOM) return POLYNOM is
NODES:array(1..2) of POLYNOM:=(LEFT,RIGHT);
RESULT,
CURRENT:POLYNOM:=null;
DEGREE:NATURAL;
FACTOR:REAL;
begin
while (NODES(1)/=null) or (NODES(2)/=null) loop
if NODES(1)=null
   then FACTOR  :=NODES(2).FACTOR;
        DEGREE  :=NODES(2).DEGREE;
        NODES(2):=NODES(2).NEXT;   
   elsif NODES(2)=null 
          then FACTOR  :=NODES(1).FACTOR;
               DEGREE  :=NODES(1).DEGREE;
               NODES(1):=NODES(1).NEXT;
        elsif NODES(1).DEGREE=NODES(2).DEGREE
              then FACTOR  :=NODES(1).FACTOR+NODES(2).FACTOR;
                   DEGREE  :=NODES(1).DEGREE;
                   NODES(1):=NODES(1).NEXT;
                   NODES(2):=NODES(2).NEXT;                
              elsif NODES(1).DEGREE>NODES(2).DEGREE      
                    then FACTOR  :=NODES(1).FACTOR;
                         DEGREE  :=NODES(1).DEGREE;                 
                         NODES(1):=NODES(1).NEXT;
                     else FACTOR  :=NODES(2).FACTOR;      
                          DEGREE  :=NODES(2).DEGREE; 
                          NODES(2):=NODES(2).NEXT;
end if;                            
if FACTOR/=REAL(0)
   then if RESULT=null 
           then RESULT:=new NODE'(ZERO_NODE);
                CURRENT:=RESULT;
           else CURRENT.NEXT:=new NODE'(ZERO_NODE);  
                CURRENT:=CURRENT.NEXT;
         end if;
         CURRENT.DEGREE:=DEGREE;
         CURRENT.FACTOR:=FACTOR;
end if;                           
end loop;
return RESULT;
end "+";                        
--===================================================================
function "*" (LEFT,RIGHT:POLYNOM) return POLYNOM is
RESULT,
CURRENT,
CURRENT_RIGHT
:POLYNOM;
begin
if LEFT=null or RIGHT=null then return null; end if;
RESULT:=NEW NODE'(ZERO_NODE);
CURRENT:=RESULT;
CURRENT_RIGHT:=RIGHT;
while CURRENT_RIGHT/=null loop
CURRENT.FACTOR:=LEFT.FACTOR*CURRENT_RIGHT.FACTOR;
CURRENT.DEGREE:=LEFT.DEGREE+CURRENT_RIGHT.DEGREE;
CURRENT_RIGHT:=CURRENT_RIGHT.NEXT;
if CURRENT_RIGHT/=null 
   then CURRENT.NEXT:=new NODE'(ZERO_NODE);
        CURRENT:=CURRENT.NEXT;
end if;         
end loop;
return (RESULT+LEFT.NEXT*RIGHT);
end "*"; 
--===============================================================
function "-" (LEFT,RIGHT:POLYNOM) return POLYNOM is 
MINUS_ONE:POLYNOM;
begin
MINUS_ONE:=new NODE'(REAL(-1),0,null);
return LEFT+MINUS_ONE*RIGHT;
end "-";
--==============================================================
FUNCTION DIFFERENTIAL_OF (EXPRESSION:POLYNOM) return POLYNOM is
ITEM,
RESULT,
CURRENT,
PREV:POLYNOM;
begin
if EXPRESSION=null then return null; end if;
RESULT:=new NODE'(ZERO_NODE);
CURRENT:=RESULT;
PREV   :=RESULT;
ITEM:=EXPRESSION;
while ITEM/=null loop
      CURRENT.FACTOR:=ITEM.FACTOR*REAL(ITEM.DEGREE);
      if ITEM.DEGREE>0 
         then CURRENT.DEGREE:=ITEM.DEGREE-1; 
         else PREV.NEXT:=null; 
      end if;
      exit when ITEM.DEGREE=0;  
      ITEM:=ITEM.NEXT;
      if ITEM/=null 
      then CURRENT.NEXT:=new NODE'(ZERO_NODE); 
           PREV:=CURRENT;
           CURRENT:=CURRENT.NEXT;          
      end if;
end loop;
return RESULT;
end DIFFERENTIAL_OF;              
--===========================================================================
function "=" (LEFT,RIGHT:POLYNOM) return BOOLEAN is 
begin
if ACCESS_NODE(LEFT)=null and ACCESS_NODE(RIGHT)=null 
   then return TRUE; 
   elsif ACCESS_NODE(LEFT)=null or ACCESS_NODE(RIGHT)=null  
         then return FALSE;
         elsif LEFT.DEGREE=RIGHT.DEGREE and LEFT.FACTOR=RIGHT.FACTOR
               then return LEFT.NEXT=RIGHT.NEXT;
               else return FALSE;
end if;                
end "=";   
--===========================================================================
end LINKED_POLYNOM;