generic
MAX:INTEGER:=100;
type ITEM is private;
with procedure PUT (X:in ITEM); 
package QUEUES is
type QUEUE is private;
     protected type SPOOL is
     entry CLEAR;
     entry ADD(NEW_ITEM:in ITEM);
     entry REMOVE(X: out ITEM);
     procedure PRINT (X:in ITEM);
     function  LENTH_OF return INTEGER;
     private
     FIRST:QUEUE;
     LAST :QUEUE;
     QUEUE_COUNT:INTEGER:=0;
end SPOOL;
private
type NODE;
type QUEUE is access NODE;
end QUEUES;