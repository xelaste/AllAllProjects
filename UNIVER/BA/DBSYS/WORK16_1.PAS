type
ItemPointer=^Item;
Item=record N:integer;
            next:ItemPointer;
     end;
relation=record First:ItemPointer;
                Arity :integer;
         end;
RelationPointer=^relation;
(*------------------------------------------------*)
function Belongto(Num:integer;The_relation:relation):Boolean;
var
X:ItemPointer;
begin
X:=The_relation.First;
if X<>nil
   then
   while (X<>nil) and (X^.N<>Num) do X:=X^.next;
if X<>nil then Belongto:=True else Belongto:=False;
end;
(*------------------------------------------------*)
procedure Insert(var Head:ItemPointer;Num:Integer);
Var
X:ItemPointer;
begin
new(X);
X^.Next:=Nil;
X^.N:=Num;
if (Head=Nil) then Head:=X
              else
              begin
              X^.next:=Head;
              Head:=X;
              end;
end;
(*------------------------------------------------*)
function InterSection(A:relation;B:relation):RelationPointer;
var
X:ItemPointer;
C  :RelationPointer;
begin
new(C);
C^.First:=Nil;
C^.Arity:=0;
while (X<>nil) do
      begin
      if belongto(X^.N,B) then
                          begin
                          C^.Arity:=C^.Arity+1;
                          insert(C^.First,X^.N);
                          end;
      X:=X^.Next;
      end;
if(C^.Arity=0) then begin
                    dispose (c);
                    C:=Nil;
                    end;
InterSection:=C;
end;
