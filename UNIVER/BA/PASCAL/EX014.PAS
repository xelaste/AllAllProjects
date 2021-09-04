program ex014;
(*Program will accept matrixe [Height x Width] of whole positive numbers from*)
(*1 to Width x Height and will look for the longest sequence of numbers N[i,j]*)
(*that (N[i,j]-N[m,n]=1) and (abs(i-m)<=1) and (abs(j-n)<=1)*)
const
 Maxheight=100;{The upper limit of matrixe height}
 Maxwidth =100;{The upper limit of matrixe width}
 inputfilename='m14.dat';
type
  Widthrange =1..Maxwidth ;         {column index range}
  Heightrange=1..Maxheight;         {line   index range}
  SentenceLenth  =1..55;                {lenth of sentences will printed on the screen}
  NumbeRange=1..Maxheight*Maxwidth; {range of possible input numbers}
  Numbers  = array [Heightrange,Widthrange] of NumbeRange;
  checkNum = array [NumbeRange] of boolean;
  Sentence = array [SentenceLenth] of char;{String for storing sentences for printing}
var
  MaxLen,{variable for storing lenth of sequenceses}
  IMax,JMax,{coordinates of item that is a head of longest sequence}
  RealWidth,RealHeight,
  i,j,(*indexes*)
  next_i,next_j,(*index of the next item in current sequence*)
  len (*line of current sequence*)
  :integer;
  Table:Numbers;(*matrix for scanning*)
(**************************************************************)
procedure putfalse (var checkinput:checknum);
var i:integer;
begin
for i:=1 to Maxheight*Maxwidth do checkinput[i]:=false;
end(*putfalse*);
(**********************************************************************)
function FileExists(FileName: string): Boolean;

  (*note this procedure is copied from help of TurboPascal*)

  {Returns True if file exists; otherwise,
    it returns False. Closes the file if
    it exists. }
  var
    f: file;
  begin
    {$I-}
    Assign(f, FileName);
    Reset(f);
    Close(f);
    {$I+}
    FileExists := (IOResult = 0) and
     (FileName <> '');
  end;  { FileExists }
(**********************************************************************)
procedure ErrorProcess(var Loopcontrol:boolean;warning:sentence);
{pocedure that will put false to control variabes and print suit warning
LoopControl - boolean variable for controlling current loop,
warning - Error message}
begin
writeln;
writeln(warning);
loopcontrol    :=false;
end;
(**********************************************************************)
function EntryMatrixe(var InputTable:numbers;var height,width:integer):boolean;
(*function for accepting table of numbers from data file*)
var
entryfile:text;
WasNum:checknum;
i,j, {indexes}
itemcounter:integer; {variable for counting accepting values}
DataisCorrect:boolean;
begin
putfalse(WasNum);
DataisCorrect:=true;i:=0;j:=0;itemcounter:=0;(*starting variables*)
assign(entryfile,inputfilename);
if FileExists(inputfilename) then
   begin
   reset(entryfile);
   if not eof(entryfile)
          then readln(entryfile,height,width)
          else ErrorProcess(DataisCorrect,'*****************File of Data is empty ****************');
   end
   else ErrorProcess(DataisCorrect,       '**************File of Data does not exists ************');
if DataisCorrect then
   if (width<=0) or (width>Maxwidth) or (height<=0) or (height>Maxheight) then
      begin
      ErrorProcess(DataisCorrect,         '*****************Invalid dimensions********************');
      writeln('Hight of matrix=',height:4,' and should be from 1 to ',Maxheight:4);
      writeln('Width of matrix=',width:4,' and should be from 1 to ',Maxwidth:4)  ;
      end;
while DataisCorrect and (i<height) do
   begin
       i:=i+1;
       j:=0;
       while DataisCorrect and (j<width) do
          begin
             j:=j+1;
             read(entryfile,InputTable[i,j]);
             if (InputTable[i,j]<=0) or (InputTable[i,j]>width*height) then
                begin
                 ErrorProcess(DataisCorrect,'*********************Inavlid input*********************');
                 writeln('Input number is ',InputTable[i,j]:4,' and should be from 1 to ',width*height:4);
                end
             else if WasNum[InputTable[i,j]] then
                     {ErrorProcess(DataisCorrect,'Repeated values!! Input number is ',InputTable[i,j]:4);}
                  else
                      begin                         (*There were not   *)
                      WasNum[InputTable[i,j]]:=true;(*any problems with*)
                      itemcounter:=itemcounter+1;   (*accepted value   *)
                      end;
          end;
  end;
if DataisCorrect then {checks if the date file contained nessecary number of items}
   if (itemcounter=height*width) then EntryMatrixe:=true else
     {ErrorProcess(DataisCorrect,'File of data include only ',itemcounter:4,' item it should be ',height*width:4;}

EntryMatrixe:=DataisCorrect;{return value of function}
end;(*EntryMatrixe*)
(**************************************************************)
function nextitem (var matrix:numbers;cur_i,cur_j:integer;var next_i,next_j:integer):boolean;
(*This function will find next item in sequence if it found it return true *)
(*matrix-array we are scanning at,                                         *)
(*cur_i,cur_j current coordinates in array                                 *)
(*next_i,next_j coordinates of the next item                               *)
var
Max_i,Max_j,(*upper limits for searching*)
Min_i,Min_j (*lower limits for searching*)
:integer;
founded:boolean;(*if next item is found*)
begin
founded:=false;
if cur_i>=RealHeight then Max_i:=cur_i else Max_i:=cur_i+1;(*using global variables   *)
if cur_j>=RealWidth  then Max_j:=cur_j else Max_j:=cur_j+1;(*realheight and real width*)
if cur_i<=1 then Min_i:=1 else Min_i:=cur_i-1;
if cur_j<=1 then Min_j:=1 else Min_j:=cur_j-1;
next_i:=Min_i;
While (next_i<=Max_i) and (not founded) do
      begin
      next_j:=Min_j;
      While (next_j<=Max_j) and (not founded) do
            begin
            if Matrix[next_i,next_j]=Matrix[cur_i,cur_j]+1
            then founded:=true
            else next_j:=next_j+1;
            end;
      if not founded then next_i:=next_i+1;
      end;
nextitem:=founded;
end;(*nextitem*)
(**************************************************************************)
procedure printsequence(var table:numbers;i,j:integer);
(*procedure for printing the given sequence from input tables*)
const itemperline=16;
var
counter:integer;{variable for counting values}
begin
counter:=0;
repeat
     counter:=counter+1;
     if counter mod itemperline = 0 then writeln(table[i,j]:5)
     else write(table[i,j]:5)
until (not nextitem(table,i,j,i,j));
end;(*printsequence*)
(*****************************************************************)
begin (*main program*)
  if EntryMatrixe (table,RealHeight,RealWidth) then
  begin
  Maxlen:=0;i:=0;j:=0;(*initializing of variables*)
   while (i<RealHeight) and (Maxlen<RealHeight*RealWidth) do
   begin
      i:=i+1;j:=0;
      while (j<RealWidth) and (Maxlen<RealHeight*RealWidth) do
          begin
          j     :=j+1;
          len   :=0;
          next_i:=i;
          next_j:=j;
          repeat
          len:=len+1;
          until not nextitem(table,next_i,next_j,next_i,next_j);
          if len>Maxlen then begin
                                  Maxlen:=len;
                                  Imax  :=i;
                                  Jmax  :=j
                              end;
          end;
   end;
  writeln;
  writeln('The longest sequence in the given matrixe is: ');
  writeln('==============================================');
  printsequence(table,Imax,Jmax);
  end;
 end.
