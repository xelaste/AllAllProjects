generic
type ITEM is private;
with function "<" (LEFT,RIGHT:ITEM) return BOOLEAN;
with function "=" (LEFT,RIGHT:ITEM) return BOOLEAN;
with procedure PRINT_ITEM(THE_ITEM:ITEM);
package TREES is
type TREE is private;
type CHILD is (LEFT,RIGHT);
NULL_TREE: constant TREE; 
function  NEW_TREE(NEW_ITEM:ITEM) return TREE;
procedure INSERT (ROOT:TREE;NEW_ITEM:ITEM);
function  SEARCH  (ROOT:TREE;THE_ITEM:ITEM) return TREE;
function  THE_TREE_IS_NULL(ROOT:TREE) return BOOLEAN;
function  GET_ITEM (NODE:TREE) return ITEM;
procedure TREE_TRIP (ROOT:TREE);
NODE_DOES_NOT_EXIST: exception;
private
type NODE;
type ACCESS_NODE is access NODE;
type TREE is new ACCESS_NODE; 
NULL_TREE: constant TREE:=null;
end TREES;