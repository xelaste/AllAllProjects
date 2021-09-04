with TEXT_IO;
package body HEX_NUM is
function GET_HEX (H:access HEX) return BOOLEAN is 
S:string(1..100):=(others=>' ');
CH:string(1..3):=("' '");
N   :integer;
function CALCULATE_DEC_VALUE return BOOLEAN is                         
begin                                                        
for i in 1..SIZE loop                                      
    H.DEC_VALUE:=H.DEC_VALUE*16+HEX_DIGITS'POS(H.HEX_VALUE(i));
end loop;                                                  
return TRUE;                                                 
exception                                                  
  when NUMERIC_ERROR=>                                  
       TEXT_IO.PUT_LINE ("Source number is too big");          
       return FALSE;                                            
end CALCULATE_DEC_VALUE;                                                         
begin
TEXT_IO.GET_LINE(S,N);
if N>SIZE then N:=SIZE; end if;
for I in reverse 1.. N loop 
    if S(I)/=' ' then   
       case S(I) is
          when 'a'=>S(I):='A';
          when 'b'=>S(I):='B';
          when 'c'=>S(I):='C'; 
          when 'd'=>S(I):='D'; 
          when 'e'=>S(I):='E'; 
          when 'f'=>S(I):='F';
          when others=>null;  
       end case;                      
       CH(2):=S(I);
       H.HEX_VALUE(I+SIZE-N):=HEX_DIGITS'VALUE(CH);
    end if;
end loop; 
return CALCULATE_DEC_VALUE;
exception
       when CONSTRAINT_ERROR=>
       TEXT_IO.PUT_LINE ("Source string is not Hexadecimal number");
       return FALSE;
end GET_HEX;
--======================================================
procedure SHOW_HEX (H:HEX_POINT) is
CH:string(1..3);
begin 
for i in 1..size loop
CH:=HEX_DIGITS'IMAGE(H.HEX_VALUE (i));
TEXT_IO.PUT(CH(2));
end loop;
end SHOW_HEX;
--=======================================================
function GET_DEC (H:access HEX) return INTEGER is
begin return H.DEC_VALUE; end GET_DEC; 
--********************************************************
end HEX_NUM;
