with TEXT_IO;
package body TREE is
package VALUE_IO is new TEXT_IO.INTEGER_IO(INTEGER);
procedure INSERT (ROOT:in out NODE_POINTER;NUMBER: in INTEGER) is 
CURRENT_NODE,
PREV_NODE    :NODE_POINTER;
begin
PREV_NODE:=NULL;
CURRENT_NODE:=ROOT;
WHILE CURRENT_NODE/=NULL loop
      PREV_NODE:=CURRENT_NODE;
      if NUMBER<CURRENT_NODE.VALUE 
         THEN CURRENT_NODE:=CURRENT_NODE.LEFT;
         else CURRENT_NODE:=CURRENT_NODE.RIGHT;
      end if;   
end loop;    
CURRENT_NODE:=new NODE'(PREV_NODE,null,null,NUMBER);
if PREV_NODE=null then ROOT:=CURRENT_NODE; --start tree
             elsif CURRENT_NODE.VALUE<PREV_NODE.VALUE
                   then  PREV_NODE.LEFT :=CURRENT_NODE;
                   else  PREV_NODE.RIGHT:=CURRENT_NODE;
end if;                
end INSERT;
procedure PRINT_TREE(ROOT:NODE_POINTER) is
begin
if ROOT/=null  
   then PRINT_TREE(ROOT.LEFT);
        VALUE_IO.PUT (ROOT.VALUE,3);     
        PRINT_TREE(ROOT.RIGHT); 
end if;
end PRINT_TREE;
end TREE;