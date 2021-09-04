-- ******************** Body FIXED POLYNOM ********************************
with TEXT_IO; 
package body FIXED_POLYNOM is
MAX_DEGREE:constant:=100; 
type REAL is digits 10; 
type NODE is array (NATURAL range 0..MAX_DEGREE) of REAL;
package REAL_IO is new TEXT_IO.FLOAT_IO(REAL);
package NATURAL_IO is new TEXT_IO.INTEGER_IO(NATURAL);
--=======================================================================
function GET_POLYNOM return POLYNOM is
ORDER:NATURAL;
RESULT:POLYNOM:=null;
--------------------------------------------------------------------------
begin
TEXT_IO.NEW_LINE;
TEXT_IO.PUT("Input polynom order from 0 to ");
NATURAL_IO.PUT(MAX_DEGREE,4);
TEXT_IO.NEW_LINE;
NATURAL_IO.GET(ORDER);
if ORDER>MAX_DEGREE then raise CONSTRAINT_ERROR; end if;
RESULT:=new NODE'(others=>REAL(0));
TEXT_IO.PUT_LINE ("Input factor for every member of polynom");
for I in reverse 0..ORDER loop
    RESULT.all(I):=REAL(0);
    TEXT_IO.PUT("X^");
    NATURAL_IO.PUT(I,1);
    TEXT_IO.PUT(": ");
    REAL_IO.GET(RESULT.all(I));
end loop; 
return RESULT;
exception
 when CONSTRAINT_ERROR=> TEXT_IO.PUT("Invalid polynom order");
                         return null;    
 when others=>return null;
end GET_POLYNOM;
--=====================================================================
procedure PRINT_POLYNOM (HEAD:POLYNOM) is
MEMBER_COUNTER:INTEGER;
begin
MEMBER_COUNTER:=0;
FOR I in reverse 0..MAX_DEGREE loop
if HEAD.all(I)/=REAL(0) 
   then
   if MEMBER_COUNTER=0 
      then if HEAD.all(I)<REAL(0)
              then TEXT_IO.PUT('-');
           end if;
      elsif HEAD.all(I)<REAL(0)      
            then TEXT_IO.PUT(" - "); 
            else TEXT_IO.PUT(" + ");
      end if;      
   if I>0 then if abs(HEAD.all(I))/=REAL(1)
                  then REAL_IO.PUT(abs(HEAD.all(I)),5,2,0); 
                       TEXT_IO.PUT("*X");
                  else TEXT_IO.PUT(" X");
                  end if;   
           else REAL_IO.PUT(abs(HEAD.all(I)),5,2,0); 
   end if;
   if I>1 
      then TEXT_IO.PUT('^');
           NATURAL_IO.PUT (I,1);
   end if;        
MEMBER_COUNTER:=INTEGER'SUCC(MEMBER_COUNTER);
end if;
end loop;
end PRINT_POLYNOM;                                   
--====================================================================
function "+" (LEFT,RIGHT:POLYNOM) return POLYNOM is
RESULT:POLYNOM;
begin
RESULT:=new NODE'(others=>REAL(0));
for I in 0..MAX_DEGREE loop
RESULT.ALL(I) :=RESULT.ALL(I)+LEFT.ALL(I)+RIGHT.ALL(I);
end loop;-- for
return RESULT;
end "+";                        
--===================================================================
function "*" (LEFT,RIGHT:POLYNOM) return POLYNOM is
RESULT:POLYNOM;
begin
RESULT:=new NODE'(others=>REAL(0));
for I in 0..MAX_DEGREE loop
    for J in 0..MAX_DEGREE loop
    if LEFT.ALL(I)*RIGHT.ALL(J)/=REAL(0) and then I+J<=MAX_DEGREE  
       then RESULT.ALL(I+J):=RESULT.ALL(I+J)+LEFT.ALL(I)*RIGHT.ALL(J);
    end if;   
    end loop;
end loop;        
return RESULT;
exception
 when CONSTRAINT_ERROR=> TEXT_IO.PUT("Invalid result polynom order");
                         return null;    
 when others=>return null;
end "*"; 
--===============================================================
function "-" (LEFT,RIGHT:POLYNOM) return POLYNOM is 
MINUS_ONE:POLYNOM;                                  
begin                                               
MINUS_ONE:=new NODE'(0=>REAL(-1),others=>REAL(0));              
return LEFT+MINUS_ONE*RIGHT;                        
end "-";                                            
--================================================================
FUNCTION DIFFERENTIAL_OF (EXPRESSION:POLYNOM) return POLYNOM is
RESULT:POLYNOM;
begin
if EXPRESSION=null then return null; end if;
RESULT:=new NODE'(others=>REAL(0));
for I in 0..MAX_DEGREE loop
if I>0 THEN RESULT(I-1):=REAL(I)*EXPRESSION.ALL(I); end if;
end loop;
return RESULT;
end DIFFERENTIAL_OF;              
--===========================================================================
function "=" (LEFT,RIGHT:POLYNOM) return BOOLEAN is 
I:NATURAL:=0;
begin
if ACCESS_NODE(LEFT)=null and ACCESS_NODE(RIGHT)=null 
   then return TRUE; 
   elsif ACCESS_NODE(LEFT)=null or ACCESS_NODE(RIGHT)=null  
         then return FALSE;
end if;
while I in 0..MAX_DEGREE and then LEFT.ALL(I)=RIGHT.ALL(I) 
loop
I:=NATURAL'SUCC(I);
end loop;
return (I>MAX_DEGREE);
end "=";   
--===========================================================================
end FIXED_POLYNOM;