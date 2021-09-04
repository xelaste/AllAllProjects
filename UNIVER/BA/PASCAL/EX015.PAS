program ex015;
{ This program will accept two whole positive numbers from keyboard and
  will try fill chessboard of given size from the point that accepted numbers
  define by knight movies.If it was a succses filled board will be printed
  otherwise errorr message occure                                            }
const
  BoardSize     = 5;
  PossibleMovies= 8;
type
 jump = record
             X:integer;
             Y:integer;
        end;
 option=array [1..PossibleMovies] of jump;
 matrixe=array[1..boardSize,1..boardSize] of integer;
 LineType=array[1..5] of char;
var
result:boolean;
Y,X,    {coordinates of starting points}
counter {counter of movies}
:integer;
JumpList:option;{array where relative coordinates will store}
ChessBoard:matrixe;
(*************************   Function  *************************)
function NextMove(Y0,X0:integer;var Y,X:integer;var Jumplist:option;Num:integer):boolean;
{this function will find next point the knight will move
 X0,Y0 current place of knight;
 X,y   place where knight should move,
 JumpList  size of jump by coordinates x and y }
begin
X:=Jumplist[Num].x+X0;Y:=JumpList[Num].y + Y0;
NextMove:=(X in [1..boardSize]) and (Y in [1..boardSize]);
end;(*NextMove*)
(*----------------------------------------------------------------*)
procedure linedraw (first,last:char;item:LineType); {procedure that drawing a line}
var i:integer;
begin
writeln;
write(first);
for i:=1 to (boardsize-1) do write(item);
writeln('ÄÄÄÄ',last);
end;(*linedraw*)
(*-----------------------------------------------------------*)
procedure PrintMatrixe(var Board:matrixe;y0,x0:integer);
{Procedure will print filled chesboard}
var
i,j: {running indexes}
integer;
begin
writeln;
writeln(
'Chessboard of size ',boardsize:2,' x ',boardsize:2,' filled by knight movies from the point: ',y0:2,' ',x0:2);
linedraw('Ú','¿','ÄÄÄÄÂ');{first line}
for i:=1 to boardsize do
   begin
    if i>1 then linedraw('Ã','´','ÄÄÄÄÅ');{intermediate line}
    write('³');
    for j :=1 to boardsize do write(board[i,j]:4,'³');{printing item from table}
   end;
linedraw('À','Ù','ÄÄÄÄÁ');{closing table}
end;(*PrintMatrixe*)
(*--------------------------------------------------------------*)
procedure putzero(var board:matrixe);
var i,j:integer;
begin
for i:=1 to boardsize do
    for j:=1 to boardsize do board[i,j]:=0;
end;(*putzero*)
(*--------------------------------------------------------------*)
function AcceptStartPosition(var lin,col:integer):boolean;
const terminator=99;
begin
(* Accept line *)
lin:=0;col:=0;
while (not (lin in [1..boardsize])) and (lin<>terminator)  do
       begin
       Writeln('Accept line number from 1 to ',boardsize:2,' ,',terminator,' to quit');
       read (lin);
       if (not (lin in [1..boardsize])) and (lin<>terminator) then writeln('Invalid line number');
       end;
(* Accept column  *)
while (col<>terminator) and (lin<>terminator) and (not (col in [1..boardsize])) do
      begin
      Writeln('Accept column number from 1 to ',boardsize:2,' ,',terminator,' to quit');
      read(col);
      if (not (col in [1..boardsize])) and (col<>terminator) then writeln('Invalid column number');
      end;
AcceptStartPosition:=(lin in [1..boardsize]) and (col in [1..boardsize]);
end;(*AcceptStartPosition*)
(*----------------------------------------------------------------*)
function fillboard(lin,col,Num:integer;var board:matrixe):boolean;
var result:boolean;{check if it was success to fill chessboard}
nextlin,{coordinates of the next position}
nextcol,{                                }
i
:integer;
begin
board[lin,col]:=Num;                                  {mark current cell}
if Num=(boardsize*boardsize) then fillboard:=true else{is it the last sell?}
   begin                                              {if it is that return true}
   i:=0;                                              {else look for the next cell}
   result:=false;
   repeat
        i:=i+1;{increasing index by one}
        if NextMove(lin,col,nextlin,nextcol,Jumplist,i)
           and (board[nextlin,nextcol]=0)              {search free cell}
           then
           result:=fillboard(nextlin,nextcol,num+1,board);
   until result or (i=8);
   if not result then board[lin,col]:=0;{it was impossible to to fill chessboard from this point}
   fillboard:=result;
  end;
end;(*fillboard*)
(*---------------------------------------------------------------*)
begin (*main program*)
if AcceptStartPosition(Y,X) then
   begin
   putzero(ChessBoard);
{   ÚÄÄÄÄÄÂÄÄÄÄÄÂÄÄÄÄÄÂÄÄÄÄÄÂÄÄÄÄÄ¿
    ³     ³ 2,-1³     ³  2,1³     ³   This table show the possible knight
    ÃÄÄÄÄÄÅÄÄÄÄÄÅÄÄÄÄÄÅÄÄÄÄÄÅÄÄÄÄÄ´   movies from the cell 0,0
    ³ 1,-2³     ³     ³     ³  1,2³
    ÃÄÄÄÄÄÅÄÄÄÄÄÅÄÄÄÄÄÅÄÄÄÄÄÅÄÄÄÄÄ´
    ³     ³     ³  0,0³     ³     ³
    ÃÄÄÄÄÄÅÄÄÄÄÄÅÄÄÄÄÄÅÄÄÄÄÄÅÄÄÄÄÄ´
    ³-1,-2³     ³     ³     ³ -1,2³
    ÃÄÄÄÄÄÅÄÄÄÄÄÅÄÄÄÄÄÅÄÄÄÄÄÅÄÄÄÄÄ´
    ³     ³-2,-1³     ³ -2,1³     ³
    ÀÄÄÄÄÄÁÄÄÄÄÄÁÄÄÄÄÄÁÄÄÄÄÄÁÄÄÄÄÄÙ
}
   jumplist[1].x:=-2;jumplist[1].y:= 1; {List of possible jumps from             }
   jumplist[2].x:=-1;jumplist[2].y:= 2; {the any point.Every item in the array   }
   jumplist[3].x:= 1;jumplist[3].y:= 2; {jumplist include two integer defining     }
   jumplist[4].x:= 2;jumplist[4].y:= 1; {size of jump by to coordinate.There are }
   jumplist[5].x:= 2;jumplist[5].y:=-1; {eight possible jumps from each point    }
   jumplist[6].x:= 1;jumplist[6].y:=-2; {(without pay attention to border points }
   jumplist[7].x:=-1;jumplist[7].y:=-2; {                                        }
   jumplist[8].x:=-2;jumplist[8].y:=-1; {                                        }

   if fillboard (Y,X,1,Chessboard) then PrintMatrixe(chessboard,y,x)
      else writeln
      ('It is impossible to cover given chessboard from the line ',y,' and the column ',x);
   end;
end.(* main program*)