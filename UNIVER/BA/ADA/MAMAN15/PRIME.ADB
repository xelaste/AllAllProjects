--======================================================================
with TEXT_IO;
with Ada.Numerics;                     
use  Ada.Numerics;                     
with Ada.Numerics.Elementary_Functions;
use  Ada.Numerics.Elementary_Functions;
package body PRIME is
procedure FIND_PRIME_NUMBERS(DATA:INPUT_ARRAY_TYPE;
                             TASK_NUMBER:NATURAL) is 
RESULT:INPUT_ARRAY_TYPE(DATA'RANGE):=(others=>0);
CHECKED_NUMBER_COUNTER:INTEGER:=0;
-------------------------------------------------------------
task CONTROL_TASK is
    entry GET_DATA;
    entry ALL_DONE;
end CONTROL_TASK;
---------------------------------------------------------------
task body CONTROL_TASK is
-----------------------------------------------------------               
task type CHECK_IF_NUMBER_IS_PRIME is --task will check if number is prime
    entry START (FIRST:INTEGER);                                       
end CHECK_IF_NUMBER_IS_PRIME;                                             
-------------------------------------------------------------             
TASK_ARRAY:array (1..TASK_NUMBER) of CHECK_IF_NUMBER_IS_PRIME; 
--------------------------------------------------------------
task body CHECK_IF_NUMBER_IS_PRIME is
X,Y,I:INTEGER;
SQRT_OF_X:FLOAT;
begin
select
 accept START (FIRST:INTEGER) do 
        Y:=FIRST;
 end START;       
 while Y<=DATA'LAST loop
  X:=DATA(Y);
  SQRT_OF_X:=FLOAT(X)**0.5;
  if X>3 
     then 
     I:=2;       
     while (X mod I/=0) and FLOAT(I)<=SQRT_OF_X loop I:=I+1; end loop;
     if X mod I = 0 then X:=0; end if; --X is not prime number
     end if;        
  RESULT(Y):=X;
  Y:=Y+TASK_NUMBER;
  CHECKED_NUMBER_COUNTER:=CHECKED_NUMBER_COUNTER+1; 
 end loop;
 or terminate; 
end select;
end CHECK_IF_NUMBER_IS_PRIME; 
---------------------------------------------------------------
begin
loop
 select 
  accept GET_DATA;
         for I in 1..TASK_NUMBER loop
         TASK_ARRAY(I).START (I);--send for check  
         end loop;
  or when CHECKED_NUMBER_COUNTER>=DATA'LAST => accept ALL_DONE;
     exit;
  end select;
end loop;                                            
end CONTROL_TASK; 
-------------------------------------------------------------
procedure PRINT_ARRAY(A:INPUT_ARRAY_TYPE) is
begin
for I in A'RANGE loop
if A(I) >0 then TEXT_IO.PUT(INTEGER'IMAGE(A(I))&","); end if;
end loop;
end PRINT_ARRAY;
--------------------------------------------------------
begin
TEXT_IO.NEW_LINE;
TEXT_IO.PUT_LINE("The input array is: ");
PRINT_ARRAY(DATA);
TEXT_IO.NEW_LINE;
CONTROL_TASK.GET_DATA;
CONTROL_TASK.ALL_DONE;
TEXT_IO.PUT_LINE("Prime numbers found: ");
PRINT_ARRAY(RESULT);
end FIND_PRIME_NUMBERS;
end PRIME;