program ex016;
{ This program will process the text file and sort the words included in
  the file.
  The words that consists invalid characters will print separately.}
const
  FileName  = 'm16.dat';
  delimiter = ' '      ;
  validchar =['a'..'z'];
  controlchar=[chr(13),chr(10),delimiter];(*Group of characters that can not be accepted*)
  smallchar =chr(0);
type
 smalleters = 'a'..'z';
 setofleters = set of smalleters;
 ItemPointer=^item;
 item = record   (*the character in the current word*)
             ch:char;
             next:ItemPointer;
        end;
 nextwordpointer=^headofword;
 headofword     =record (*pointer for marking head of word and link with next word*)
                        down:ItemPointer;
                        right:nextwordpointer;
                    end;
(************** F u n c t i o n  and p r o c e d u r e s ******************)
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
(*========================================================================*)
procedure readword(var top:headofword;var inf:text;var waserror:boolean);
{this procedure will read next word from input file.
note: word is the all characters between two delimeters or
between delimiter and eof or between delimeter and eoln.}

var
{ top will store an adress of head of chain
  inf - pointer to input file
  waserror  indicate if there where illegal characters }
  curr:ItemPointer;{current record in chain}
  last:ItemPointer;{the last record in chain}
  ch  :char;       {variable for storing current character}
  waschar:boolean; {if we read character different from delimiter}
begin
  (* initializing variables *)
  waschar:=false;
  last:=nil;
  repeat
  read(inf,ch); (*reading character from input file*)
  if not (ch in controlchar)
         then begin                    (*if there is sequence of delimiters skip it*)
              if not (ch in validchar) then waserror:=true; (*validity check*)
              waschar:=true;
              new (curr);
              if top.down=nil then top.down:=curr; {begining of link}
              if last<>nil then last^.next:=curr;  {inserting       }
              last      :=curr;                    {new record      }
              curr^.next:=nil;                     {to the end of   }
              curr^.ch  :=ch ;                     {chain           }
              end;
  until ((ch=delimiter) and waschar) or eof(inf) or eoln(inf);
end;
(*-----------------------------------------------------------------*)
procedure PrintWord (head:headofword);
{printing the given word}
begin
    while head.down<>nil do begin
                         write(head.down^.ch);
                         head.down:=head.down^.next;
                             end;
end;(*Printword*)
(*-------------------------------------------------------------------*)
procedure PrintChain(head:nextwordpointer);{procedure for printing chain of words}
begin                                      {head pointer to begining of chain}
 while head<>nil do begin
                    writeln;{opening new line before next words}
                    printword(head^) ;
                    head:=head^.right;
                    end;
end;(*PrintChain*)
(*==================================================================*)
procedure Deleteword (var head:headofword);
{procedure for deleting accepted word if error occured}
var
  next
  :itempointer;
begin
    next:=head.down^.next;
    while head.down <> nil do begin
                             dispose(head.down)   ;(*freeing memory*)
                             head.down:=next      ;(*moving to next char in word*)
                             next:=head.down^.next;(*storing pointer to next char*)
                             end;
end;(*Deleteword*)
(*====================================================================*)
function compareword (head1,head2:ItemPointer):boolean;
{The function will recieve two parameters: beginings of words to be
compared and return true if first word greater than second one}
var
first,
second
:char; {variables for comparing}
begin
repeat
     if head1<>nil then first :=head1^.ch else first:=smallchar;
     if head2<>nil then second:=head2^.ch else second:=smallchar;
(*note if we are at the end of chain then correspond variable geting the smallest value*)
     head1:=head1^.next;  head2:=head2^.next;{next item in the chain}
until (first<>second) or ((head1=nil) and (head2=nil));
compareword:=(first<second) or ((first=second) and ((head1=nil) and (head2=nil)))
end;(*comparechain*)
(*------------------------------------------------------------------------*)
function findthepoint (head,new:nextwordpointer):nextwordpointer;
(*function will find the point that new record will inserted after it*)
(*if not found nil will return                                       *)
var
prev:nextwordpointer;
placeisfound:boolean;
begin
prev:=nil;
if head<>new
   then
   while (head<>nil) and compareword(head^.down,new^.down) do
      begin
      prev:=head;
      head:=head^.right;
      end;
findthepoint:=prev;
end;(*findthepoint*)
(*====================================================================*)
function filetochain(var head:nextwordpointer):boolean;
(*function for loading input file to chain of words*)
var
infile:text;  {input file}
currentword,  {pointer to current word}
thisisthepoint{pointer to the word the current word should inserted after}
:nextwordpointer;
waserror:boolean;
begin
if fileExists(FileName) then
   begin
    assign(infile,fileName);
    reset(infile);
    while not eof(infile) do
    begin
    new(currentword);
    currentword^.down:=nil;
    currentword^.right:=nil;
    waserror:=false;
    readword(currentword^,infile,waserror);
    if waserror then  begin
                      Printword(currentword^);
                      write ('is not a valid word':30);
                      deleteword(currentword^);
                      dispose(currentword);
                      end
                else begin
                     thisisthepoint:=findthepoint(head,currentword);
                     if thisisthepoint<>nil then
                        begin
                        currentword^.right  :=thisisthepoint^.right;
                        thisisthepoint^.right:=currentword;
                        end
                     else
                        begin
                        currentword^.right:=head;
                        head:=currentword;
                        end;
                     end;{else if was error}
    end;(*while not eof*)
    filetochain:=true;
  end (*if fileexist*)
else begin
     writeln('File ',Filename,' does not exist!!');
     filetochain:=false;
     end;
end;(*filetochain*)
(*************************The main program ****************************)
var
head:nextwordpointer;       {pointer to the begining of first word    }
begin (*main program*)
head:=nil;
writeln;
if filetochain(head) then PrintChain(head);
end.(*main program*)
