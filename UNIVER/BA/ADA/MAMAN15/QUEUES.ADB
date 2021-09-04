--===================================================
package body QUEUES is
---------------------------------------
EMPTY_QUEUE:constant QUEUE:=null;
type NODE is record
DATA:ITEM;
NEXT:QUEUE:=EMPTY_QUEUE;
end record;
---------------------------------------
protected body SPOOL is
---------------------------------------
 entry CLEAR when TRUE is
 begin
 QUEUE_COUNT:=0;
 FIRST:=EMPTY_QUEUE;
 LAST :=EMPTY_QUEUE;
 end CLEAR;
---------------------------------------------
 entry ADD(NEW_ITEM:ITEM) when QUEUE_COUNT<MAX is 
 begin
 if QUEUE_COUNT=0 
    then FIRST:= new NODE;
         LAST:=FIRST;
    else 
         LAST.NEXT:=NEW NODE;
         LAST:=LAST.NEXT;
  end if;       
 LAST.DATA  :=NEW_ITEM;
 QUEUE_COUNT:=QUEUE_COUNT+1;
 end ADD;
-------------------------------------------    
 entry REMOVE (X:out ITEM) when QUEUE_COUNT>0 is
 begin
 X:=FIRST.DATA;
 FIRST:=FIRST.NEXT;
 QUEUE_COUNT:=QUEUE_COUNT-1;
 end REMOVE;
-------------------------------------------
 procedure PRINT (X:in ITEM) is
 begin
 PUT(X);
 end PRINT; 
-------------------------------------------
 function LENTH_OF return INTEGER is
 begin
 return QUEUE_COUNT;
 end LENTH_OF;
-----------------------------------------------
end SPOOL;
end QUEUES;  
