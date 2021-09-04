--*************************************************************************
package LINKED_POLYNOM is
type POLYNOM is private;
function GET_POLYNOM return POLYNOM;
procedure PRINT_POLYNOM (HEAD:POLYNOM);
function "+" (LEFT,RIGHT:POLYNOM) return POLYNOM;
function "*" (LEFT,RIGHT:POLYNOM) return POLYNOM;
function "-" (LEFT,RIGHT:POLYNOM) return POLYNOM;
function "=" (LEFT,RIGHT:POLYNOM) return BOOLEAN;
FUNCTION DIFFERENTIAL_OF (EXPRESSION:POLYNOM) return POLYNOM; 
private
type NODE;
type ACCESS_NODE is access NODE;
type POLYNOM is new ACCESS_NODE;
end LINKED_POLYNOM; 
--***********************************************************************