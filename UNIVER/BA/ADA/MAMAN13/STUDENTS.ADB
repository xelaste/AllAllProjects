--********************************************************************
with TEXT_IO;
package body STUDENTS is
--=================================================
function "<" (LEFT,RIGHT:STUDENT) return BOOLEAN is
begin
return (LEFT.ID<RIGHT.ID);
end "<";
--===============================================================
function "=" (LEFT,RIGHT:STUDENT) return BOOLEAN is
begin
return (LEFT.ID=RIGHT.ID);
end "=";
--================================================================
procedure SET_STUDENT (THE_STUDENT:in out STUDENT;
                       THE_ID:ID_NUMBER;
                       THE_NAME:STUDENT_NAME;
                       THE_ADDRESS:STUDENT_ADDRESS;
                       THE_PHONE:PHONE_NUMBER) is
begin                       
THE_STUDENT.ID     :=THE_ID;
THE_STUDENT.NAME   :=THE_NAME;
THE_STUDENT.ADDRESS:=THE_ADDRESS;
THE_STUDENT.PHONE  :=THE_PHONE;
end SET_STUDENT;
--================================================================
procedure PRINT_STUDENT(THE_STUDENT:STUDENT) is 
begin
TEXT_IO.NEW_LINE;
TEXT_IO.PUT (ID_NUMBER'IMAGE(THE_STUDENT.ID)&" ");
TEXT_IO.PUT (STRING(THE_STUDENT.NAME)&" "); 
TEXT_IO.PUT (STRING(THE_STUDENT.ADDRESS)&" ");
TEXT_IO.PUT (PHONE_NUMBER'IMAGE(THE_STUDENT.PHONE));
end PRINT_STUDENT;
--=================================================================
end STUDENTS;
--******************************************************************