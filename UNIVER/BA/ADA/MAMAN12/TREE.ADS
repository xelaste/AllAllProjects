package TREE is
type NODE;
type NODE_POINTER is access NODE;
procedure INSERT (ROOT:in out NODE_POINTER;NUMBER: in INTEGER);
procedure PRINT_TREE(ROOT:NODE_POINTER);
type NODE is 
 record
      PARENT:NODE_POINTER;
      LEFT  :NODE_POINTER;
      RIGHT :NODE_POINTER;
      VALUE :INTEGER;
 end record; 
end TREE; 