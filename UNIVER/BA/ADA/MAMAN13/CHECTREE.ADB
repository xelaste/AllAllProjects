with STUDENTS;
with TREES;
with TEXT_IO;
procedure CHECK_TREE is
package STUDENT_LIST is new TREES(ITEM=>STUDENTS.STUDENT,             
                                  "<"=>STUDENTS."<"     ,             
                                  "="=>STUDENTS."="     ,             
                                  PRINT_ITEM=>STUDENTS.PRINT_STUDENT);
INPUT:array(1..10) of STUDENTS.STUDENT;
THE_LIST:STUDENT_LIST.TREE:=STUDENT_LIST.NULL_TREE;
STOPPER:CHARACTER;
THE_STUDENT_ID:STUDENTS.ID_NUMBER; 
THE_STUDENT:STUDENTS.STUDENT;
THE_NODE:STUDENT_LIST.TREE:=STUDENT_LIST.NULL_TREE;
begin
TEXT_IO.PUT_LINE("The data file before inserting to tree");
STUDENTS.SET_STUDENT(INPUT(1),34,"Alex                ", 
                                 "Tzerniakovsky 1               ",22_8_70);      
STUDENTS.SET_STUDENT(INPUT(2),56,"Svetlana            ", 
                                 "Sprinzak 34/10                ",03_9307838);      
STUDENTS.SET_STUDENT(INPUT(3),1, "Sergey              ", 
                                 "Rosh Ain                      ",03_9333584);      
STUDENTS.SET_STUDENT(INPUT(4),3, "Ida                 ", 
                                 "Rishon                        ",03_9640684);      
STUDENTS.SET_STUDENT(INPUT(5),10,"Parmalat            ", 
                                 "Sinjera                       ",08_9253707);
STUDENTS.SET_STUDENT(INPUT(6),100,"SUM 39              ",  
                                 "Tha factory street            ",03_9302927);      
STUDENTS.SET_STUDENT(INPUT(7),21,"Meir                ", 
                                 "Kfar Saba                     ",03_5333311);      
STUDENTS.SET_STUDENT(INPUT(8),41,"Eli                 ", 
                                 "Holon                         ",09_594684);      
STUDENTS.SET_STUDENT(INPUT(9),11,"Vika                ", 
                                 "Tel Hi                        ",09_900857);      
STUDENTS.SET_STUDENT(INPUT(10),301,"Michael             ", 
                                 "Sidney                        ",03_5279737);      
for I in 1..10 loop
STUDENTS.PRINT_STUDENT(INPUT(I));
end loop;
for I in 1..10 loop
if STUDENT_LIST.THE_TREE_IS_NULL(THE_LIST) 
   then THE_LIST:=STUDENT_LIST.NEW_TREE(INPUT(I));
   else STUDENT_LIST.INSERT(THE_LIST,INPUT(I));
end if;   
end loop; 
TEXT_IO.NEW_LINE;
TEXT_IO.PUT_LINE("Press any key to continue");
TEXT_IO.GET(STOPPER);
TEXT_IO.PUT_LINE("The data file after inserting to tree");
STUDENT_LIST.TREE_TRIP(THE_LIST);
TEXT_IO.NEW_LINE;
TEXT_IO.PUT_LINE("Look for ID=11");
THE_STUDENT_ID:=11;
STUDENTS.SET_STUDENT(THE_STUDENT,
                     THE_STUDENT_ID,"                    ",
                     "                              ",0);
THE_NODE:=STUDENT_LIST.SEARCH(THE_LIST,THE_STUDENT);
THE_STUDENT:=STUDENT_LIST.GET_ITEM(THE_NODE);
STUDENTS.PRINT_STUDENT(THE_STUDENT); 
TEXT_IO.NEW_LINE;
TEXT_IO.PUT_LINE("Look for ID=99");
THE_STUDENT_ID:=99;
STUDENTS.SET_STUDENT(THE_STUDENT,
                     THE_STUDENT_ID,"                    ",
                     "                              ",0);
THE_NODE:=STUDENT_LIST.SEARCH(THE_LIST,THE_STUDENT);
THE_STUDENT:=STUDENT_LIST.GET_ITEM(THE_NODE);
STUDENTS.PRINT_STUDENT(THE_STUDENT); 

exception 
when STUDENT_LIST.NODE_DOES_NOT_EXIST=>
     TEXT_IO.NEW_LINE;
     TEXT_IO.PUT_LINE("There found none student that student.ID="&
                      STUDENTS.ID_NUMBER'IMAGE(THE_STUDENT_ID));       
end CHECK_TREE;