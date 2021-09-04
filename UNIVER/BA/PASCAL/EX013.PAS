program  ex013 ;
(*The programm will accept  whole numbers and print  the palindrom        *)
(*has been recieved from them .Inspite of this it will be found   how many*)
(*circles need for converting initial number to palindrom and print's it. *)
(*It will check causes of overflow too and print suit message if took place*)

var
   CurrNo,    (*current numbers*)
   CnvNo,     (*number for converting*)
   Hlp,       (*help number for calculating*)
   i          (*loop counter*)
   :integer;
   overflow:boolean;
(*************************************************************)
function power (num,n:integer):integer;
(*raising value num to positive power n*)
 var i,
 result:integer;
 begin
 result:=1;
 for  i:=1 to n do result:=result*num;
 power:=result;
 end;(*power*)
(*************************************************************)
function DigitNumber(Num:integer):integer;
(*The function will find number of digit in the Num*)
 var
 counter:integer;
 begin
    counter:=0;
    repeat
         counter:=counter+1;
         Num:=Num div 10
    until Num=0;
  DigitNumber:=counter;
 end; (*DigitNumber*)
(*************************************************************)
function ConvertNumber(Num:integer):integer;(*function that converting number*)
 var
      sum (*variable that will collect digit and form converted number*)
         :integer;
 begin
     sum:=0;
     repeat
     sum:=sum*10+Num mod 10;
     Num:=Num div 10;
   until Num = 0;
   ConvertNumber:=sum;
 end;(*ConvertNumber*)
(*************************************************************)
function CheckNum(Num:integer):boolean;
(*function will check if converted number will greater than maxint*)
var
  Maxdigit,(*digit number of maxint*)
  DigNum,  (*digit number of Num*)
  i,       (*counter*)
  digit1, (*variable for storing digits from maxint*)
  digit2  (*variable for storing digits from Num*)
  :integer;
  result:boolean;(*check if there are digits in Num bigger than maxint*)
begin
  MaxDigit:=DigitNumber(maxint);
  DigNum:=DigitNumber(num);
  if DigNum<MaxDigit then CheckNum:=True (*if number digits in num < than *)
                                         (* in maxint then return true    *)
     else
(*check until  digit of num will be > then digit of maxint or vice versa*)
     begin
       digit1:=0;digit2:=digit1;
       i:=0;
       result:=False;
       while   (not result) and (i<=MaxDigit) and (digit1=digit2) do
        begin
        i:=i+1;
        digit1:=(maxint div (power(10 ,MaxDigit-i))) mod 10;(*i-th digit from begining of maxint*)
        digit2:=Num mod 10;(*i-th digit from end of num*)

        if digit1>digit2 then result:=true
                         else
                         if digit1=digit2 then Num:=Num div 10;
        end;
        CheckNum:=result;
      end;
end;(*CheckNum*)
(****************************************************)
begin (*main program start*)
 read (Currno);
 if eof
 then
    begin
    writeln;
    writeln('****************File of Data is empty**************');
    end
 else
    begin
    writeln;
    writeln('Initial Number ** Palindrom ** Circles number ** ');
    writeln('=================================================');
    while not eof do
     begin
       CnvNo:=0;       {                         }
       i    :=0;       {Initializing of variables}
       Hlp  :=CurrNo;  {                         }
       repeat
           overflow:=(maxint-Hlp<CnvNo) or (not CheckNum(Hlp+CnvNo));
           if not overflow then
              begin
              Hlp:=Hlp+CnvNo;
              CnvNo:=ConvertNumber(Hlp);
              i:=i+1;
              end;
       until (CnvNo=Hlp) or overflow;
       if overflow then
          writeln(' ':5,CurrNo:5,' overflow ':18,' ':10,i:3)
          else
          writeln(' ':5,CurrNo:5,' ':10,Hlp:5,' ':13,i:3);
       read(CurrNo);
     end;
   end;
end.