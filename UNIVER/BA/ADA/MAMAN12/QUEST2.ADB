with TEXT_IO;
procedure MATRIXE is
package INTEGER_IO is new TEXT_IO.INTEGER_IO(INTEGER);
type DIMENSION is  range 1..NATURAL'LAST;
type INT_MATRIXE is array (DIMENSION range<>,DIMENSION range<>) of INTEGER;
ROW:constant DIMENSION:=3;
COL:constant DIMENSION:=4;
M:INT_MATRIXE   (1..ROW,1..COL):=((1,7,3,2),(4,5,8,3),(6,2,9,1));
TM:INT_MATRIXE (1..COL,1..ROW);
--=====================================================================
procedure TRANSFORM (SOURCE :in INT_MATRIXE;TARGET:out INT_MATRIXE) is
begin
for I in SOURCE'FIRST(1)..SOURCE'LAST(1) loop
    for J in SOURCE'FIRST(2)..SOURCE'LAST(2) loop 
        TARGET (J,I):=SOURCE(I,J);
    end loop;
end loop;    
end TRANSFORM;
--====================================================================
procedure SHOW_MATRIX(SOURCE:INT_MATRIXE) is
begin
for I in SOURCE'FIRST(1)..SOURCE'LAST(1) loop
    TEXT_IO.NEW_LINE;
    for J in SOURCE'FIRST(2)..SOURCE'LAST(2) loop
    INTEGER_IO.PUT(SOURCE(I,J));
    end loop;   
end loop;
end SHOW_MATRIX;
--********************* THE MAIN PROGRAM ******************************
begin
TRANSFORM(M,TM);
TEXT_IO.PUT("The source matrixe is: ");
SHOW_MATRIX(M);
TEXT_IO.NEW_LINE;
TEXT_IO.PUT("The transformed matrixe is: ");
SHOW_MATRIX(TM);
end MATRIXE;