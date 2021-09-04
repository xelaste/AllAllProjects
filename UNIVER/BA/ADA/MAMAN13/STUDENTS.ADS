package STUDENTS is
type STUDENT is private;
type PHONE_NUMBER is range 0..999999999;
type ID_NUMBER    is range 0..999999999;
type STUDENT_NAME is new STRING(1..20);
type STUDENT_ADDRESS is new STRING(1..30);
function "<" (LEFT,RIGHT:STUDENT) return BOOLEAN;
function "=" (LEFT,RIGHT:STUDENT) return BOOLEAN;
procedure SET_STUDENT (THE_STUDENT:in out STUDENT;
                       THE_ID:ID_NUMBER;
                       THE_NAME:STUDENT_NAME;
                       THE_ADDRESS:STUDENT_ADDRESS;
                       THE_PHONE:PHONE_NUMBER);
procedure PRINT_STUDENT(THE_STUDENT:STUDENT);
private
type STUDENT is record
     ID       :ID_NUMBER:=0;
     NAME     :STUDENT_NAME:=(others=>' ');
     ADDRESS  :STUDENT_ADDRESS;
     PHONE    :PHONE_NUMBER:=0;
end record;
end STUDENTS;