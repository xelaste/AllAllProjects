--**********************************************************************
package body TREES is
type NODE is
     record
     THE_ITEM: ITEM;
     PARENT  : TREE;
     LEFT    : TREE;
     RIGHT   : TREE;
     end record;
--===================================================================
function NEW_TREE(NEW_ITEM:ITEM) return TREE is
begin
return NEW NODE'(NEW_ITEM,NULL_TREE,NULL_TREE,NULL_TREE);
end NEW_TREE;
--===================================================================
procedure INSERT (ROOT:TREE;NEW_ITEM:ITEM) is
PREV,
CURRENT:TREE;
ON_THE_CHILD:CHILD;
begin
CURRENT:=ROOT;
while CURRENT/=NULL_TREE loop
      PREV:=CURRENT;
      if NEW_ITEM<CURRENT.THE_ITEM 
         then CURRENT:=CURRENT.LEFT; 
              ON_THE_CHILD:=LEFT;  
         else CURRENT:=CURRENT.RIGHT;
              ON_THE_CHILD:=RIGHT;
         end if;         
end loop;
if ON_THE_CHILD=RIGHT 
   then PREV.RIGHT:=new NODE'(NEW_ITEM,PREV,NULL_TREE,NULL_TREE);
   else PREV.LEFT :=new NODE'(NEW_ITEM,PREV,NULL_TREE,NULL_TREE);
end if;   
end INSERT;
--===================================================================
function THE_TREE_IS_NULL(ROOT:TREE) return BOOLEAN is
begin
return ROOT=NULL_TREE;
end THE_TREE_IS_NULL;
--===================================================================
function SEARCH  (ROOT:TREE;THE_ITEM:ITEM) return TREE is
CURRENT:TREE:=ROOT;
begin
while CURRENT/=NULL_TREE and then CURRENT.THE_ITEM/=THE_ITEM loop
      if THE_ITEM<CURRENT.THE_ITEM 
         then CURRENT:=CURRENT.LEFT; 
         else CURRENT:=CURRENT.RIGHT;
      end if;     
end loop;
if CURRENT=NULL_TREE then raise NODE_DOES_NOT_EXIST; end if;
return CURRENT;
end SEARCH;
--===================================================================
procedure TREE_TRIP (ROOT:TREE) is
begin
if ROOT/=NULL_TREE 
   then TREE_TRIP(ROOT.LEFT);
        PRINT_ITEM(ROOT.THE_ITEM);
        TREE_TRIP(ROOT.RIGHT);     
end if;
end TREE_TRIP;
--===================================================================
function  GET_ITEM (NODE:TREE) return ITEM is
begin
return NODE.THE_ITEM;
end GET_ITEM;
--===================================================================
end TREES;
