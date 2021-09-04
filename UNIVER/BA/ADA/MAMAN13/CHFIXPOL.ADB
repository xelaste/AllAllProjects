--*************  Check fixed polynom's package *****************************
with TEXT_IO;                 
with FIXED_POLYNOM;
use FIXED_POLYNOM;
procedure CHECK_FIXED_POLYNOM is
P,
Q:FIXED_POLYNOM.POLYNOM;
begin
TEXT_IO.PUT ("Input polinom P ");
P:=FIXED_POLYNOM.GET_POLYNOM;
TEXT_IO.PUT("P =");
FIXED_POLYNOM.PRINT_POLYNOM(p);
TEXT_IO.NEW_LINE;
TEXT_IO.NEW_LINE; 
TEXT_IO.PUT("Input polinom Q ");
Q:=FIXED_POLYNOM.GET_POLYNOM;  
TEXT_IO.PUT("Q =");
FIXED_POLYNOM.PRINT_POLYNOM(Q);
TEXT_IO.NEW_LINE;
TEXT_IO.PUT("P + Q =");
FIXED_POLYNOM.PRINT_POLYNOM(P+Q);
TEXT_IO.NEW_LINE;
TEXT_IO.PUT("P * Q =");           
FIXED_POLYNOM.PRINT_POLYNOM(P*Q);
TEXT_IO.NEW_LINE;                
TEXT_IO.PUT("P - Q =");          
FIXED_POLYNOM.PRINT_POLYNOM(P-Q);
TEXT_IO.NEW_LINE;                 
TEXT_IO.PUT("P' = ");           
FIXED_POLYNOM.PRINT_POLYNOM (FIXED_POLYNOM.DIFFERENTIAL_OF(P));
TEXT_IO.NEW_LINE;  
if P=Q then TEXT_IO.PUT_LINE("P  equal to Q");
       else TEXT_IO.PUT_LINE("P  not equal to Q");
end if;       
end CHECK_FIXED_POLYNOM;
--*********************************************************************