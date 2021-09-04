--======================================
with TEXT_IO;
with CALENDAR;
with QUEUES;
use CALENDAR;
procedure SPOOLER is
type OBJECT is
record
STR:STRING(1..3);
NUM:INTEGER;
end record;
---------------------------------------------
procedure PUT_OBJECT(O:OBJECT) is
begin
TEXT_IO.PUT_LINE(O.STR&" "&INTEGER'IMAGE(O.NUM));
end PUT_OBJECT;
---------------------------------------------
package  OBJECT_QUEUE is new QUEUES(MAX=>100,ITEM=>OBJECT,PUT=>PUT_OBJECT);
OBJECT_SPOOL:OBJECT_QUEUE.SPOOL;--define protected type for object
---------------------------------------------
task TASK_X is --task for inserting objects XXX.#
entry ADD_X;
end TASK_X;
--------------------------------------------
task TASK_Y is --task for inserting objects YYY.#
  entry ADD_Y;
end TASK_Y;
-----------------------------------------------
task PRINT is -- print current queue 
entry PRINT_OBJECT_QUEUE;
end PRINT; 
--------------------------------------------
task body TASK_X is 
X:OBJECT:=(STR=>"XXX",NUM=>0);
begin 
 accept ADD_X;
 declare 
 TIME_INTERVAL:constant DURATION:=1.0; 
 NEXT_TIME    :CALENDAR.TIME:=CALENDAR.CLOCK;
 begin
 loop
    delay NEXT_TIME-CALENDAR.CLOCK;
    X.NUM:=X.NUM+1;
    OBJECT_SPOOL.ADD(X);
    exit when X.NUM=10;
    NEXT_TIME:=NEXT_TIME+TIME_INTERVAL;
 end loop;
end; 
end TASK_X;
-----------------------------------------------
task body TASK_Y is 
 Y:OBJECT:=(STR=>"YYY",NUM=>0);
 begin 
  accept ADD_Y;
  declare 
  TIME_INTERVAL:constant DURATION:=0.5; 
  NEXT_TIME    :CALENDAR.TIME:=CALENDAR.CLOCK;
  begin
  loop
    delay NEXT_TIME-CALENDAR.CLOCK;
    Y.NUM:=Y.NUM+1;
    OBJECT_SPOOL.ADD(Y);
    exit when Y.NUM=20;
    NEXT_TIME:=NEXT_TIME+TIME_INTERVAL;
 end loop;
end; 
end TASK_Y;
-----------------------------------------------
task body PRINT is 
X:OBJECT;
begin 
  accept PRINT_OBJECT_QUEUE;
  for I in 1..30 loop
  OBJECT_SPOOL.REMOVE(X);
  OBJECT_SPOOL.PRINT (X);
  end loop;
end PRINT;
------------------------------------------------
begin 
 OBJECT_SPOOL.CLEAR;
 TASK_X.ADD_X;
 TASK_Y.ADD_Y;
 PRINT.PRINT_OBJECT_QUEUE;
end SPOOLER; 