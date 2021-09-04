program  ex012 ;
(*The programm will accept sequence of whole numbers and print it        *)
(*by eights in a line. Inspite of this it will be founds the how many    *)
(*input numbers are average of previous numbers and how meny numbers     *)
(* are the sum of two previous, and also it will be found max number and *)
(*his position.                                                          *)
const
    line_len=8;(*The lenth of line to be printing*)
var
   CurrNo,    (*current numbers*)
   prevNo1,   (*previous number*)
   prevNo2,   (*The number before previous*)
   maxNo ,    (* The biggest number*)
   posMax,    (*Position of the biggest number*)
   AvNo  ,    (*How many input numbers are average of previous numbers*)
   SumNo ,    (*How many numbers are the sum of two previous*)
   Sum   ,    (*Sum of numbers*)
   i          (*Current position*)
   :integer;
begin
   AvNo :=0;  (*                    *)
   SumNo:=0;  (* starting of numbers*)
   Sum  :=0;  (*                    *)
   i    :=0;  (*                    *)
   prevNo1:=0;(*                   *)
   prevNo2:=0;(*                   *)
   read(CurrNo); (*first reading*)
   if eof then write(' The input file is empty!!!')
          else
          begin
              maxNo:=CurrNo;
              i:=1;
              writeln('The elements of the input sequence are:');
              while not eof do
                    begin
                    if maxNo<currNo then           (* Calculating of*)
                                    begin          (* maximum number*)
                                    maxNo:=CurrNo ;(*               *)
                                    posMax:=i;     (*               *)
                                    end;           (*               *)

                    if i>1 then                           (*if the number is average of previouses*)
                    if CurrNo=sum/(i-1) then AvNo:=AvNo+1;(*numbers if it is increasing counter by 1*)

                    if i>=3 then                                  (*if the number is the sum of two previouses*)
                    if prevNo1+prevNo2=CurrNo then sumNo:=sumNo+1;(*if it is increasing counter by 1*)

                    if i mod line_len = 0 then writeln(CurrNo:6) else write(currNo:6);
                    (*writing numbers by eight number in a line *)

                    prevNo2:=prevNo1;
                    prevNo1:=CurrNo;
                    sum:=sum+Currno;
                    read(currNo);
                    i:=i+1;
                    end;
          writeln('');(*open new line*)
          writeln('');(*open new line*)
          writeln('The maximum value is:',MaxNo:4,
                            ' and it is in position ', posMax:2);
          writeln('');(*open new line*);
          writeln('The number of elements that equal the average of all the elements');
          writeln('which precede them is ',Avno:4);
          writeln('');(*open new line*);
          writeln('The number of elements that equal the sum of two precedents is ',sumNo:4);
          end;
end.
























(