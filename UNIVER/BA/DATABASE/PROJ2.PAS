program proj2;
(***********************************************************************************)
(* program for managing list performers and theirs projects                        *)
(* input : lines of query or lines of operation                                    *)
(* type of input lines                                                             *)
(*  N Job1 251 25.0 P3 - insert new project for performer P3 ,                     *)
(*  Name of project -Job1 , Id - 251 , cost 25.0                                   *)
(*  F P3 - performer P3 finished project, he worked, project should be deleted     *)
(*  DA P3 - Delete performer P3 and all his projects                               *)
(*  ? P3 JOB1 if Job1 belongs to P3 and what is his status :active or waiting      *)
(*  ? P3 What project is the current project of P3                                 *)
(*  ? M What Project has the Maximum cost                                          *)
(*  ? M P3 - The Max Cost Project of P3                                            *)
(* output : query answers  and messages about deleting or inserting items          *)
(***********************************************************************************)
const
NewProject ='N';(* The first characters in the input *)
ProjectOver='F';(* line , defines what given line    *)
DeleteAll  ='D';(* means                             *)
Query      ='?';(*                                   *)
FindMax    ='M';(*                                   *)
NameLenth=10;{The lenth of perfomer Id or project name}
PerformerPrefix='P'; {after this character performer id begining}
ControlCh=[Chr(13),chr(10)];{characters end of line}
EmptyCh=' ';
EmptyName='          ';
type
kind=(job,supervisor);{which kind of data we work project or performer}
color=(black,red);    {color of tree item in red-black tree}
Cost=real;
Name=Array[1..NameLenth] of char;
ProjectSpot=^project;      {pointer to project item}
performerSpot=^performer;  {pointer to performer item}
SearchtreeSpot=^Searchtree;{pointer to red-black tree item; may be tree of performers}
                           {or tree of project depend on kind of data                }
performer=record  {performer Item}
          Id       :name;
          HeapSpot :SearchtreeSpot;{pointer to root of project tree of the performer}
          StackSpot:ProjectSpot;   {pointer to head of project stack of the performer}
          end;
project=record    {Project item}
        Id         :integer;
        ProjectName:name;
        ProjectCost:cost;
        next           :ProjectSpot;{used for building project stack}
        prev           :ProjectSpot;{used for building project stack}
     end;
Searchtree=record  {The main unit of data used for built red-black search tree}
           key:name;
           itemcolor:color;
           prev :SearchtreeSpot; {pointer to parent}
           right:SearchtreeSpot; {pointer to right child}
           left :SearchtreeSpot; {pointer to left child}
           TheMostCostProject:projectspot;{pointer to the most cost project in subtree}
           case keyValue : kind of
                           job       :(Project   :ProjectSpot);
                           supervisor:(Performer :PerformerSpot);
           end;
(************** F U N C T I O N s  A N D   P R O C U D E R E S **************)
procedure ReadName(var inf:text;var Name:name);
(*procedure for reading string name from the input file*)
var
i:integer;{index for count characters}
begin
i:=0;
name:=EmptyName;
if not (eoln(inf) or eof(inf)) then
   repeat
   i:=i+1;
   read(inf,Name[i]);
   Name[i]:=UpCase(Name[i]);(*switch to upper case*)
   until eoln(inf) or eof(inf) or (Name[i]=EmptyCh) or (i=NameLenth);
end; {readName}
(*-------------------------------------------------------------------------*)
procedure Read2Eoln(var inf:text);
{procedure for readin characters those left in the line}
var ch:char;
begin while not eoln(inf) do read(inf,ch); end;
(*-------------------------------------------------------------------------*)
procedure read2thenextchar(var inf:text;var ch:char);
(*read all spaces to next character that is not space*)
begin
ch:=EmptyCh;
repeat if not eoln(inf) then read(InF,ch) until (ch<>Emptych) or eoln(inf);
end; (* read2thenextchar *)
(*------------------------------------------------------------------------*)
procedure readline (var inf:text;var project:Project;var performer:name);
(*read line of new project from input file *)
var
ch   {character from input file}
:char;
i :integer;{help variable index for array}
begin
 ReadName(inf,project.ProjectName);
 read(InF,project.Id);
 read(InF,project.ProjectCost);
 while Ch<>PerformerPrefix do read(Inf,Ch);
 ReadName(inf,performer);
 read2eoln(inf);            {read to the end of line and}
 read(inf,ch);read(inf,ch); {signs end of line too}
end;{procedure readline}
(*------------------------------------------------------------------------*)
procedure UpdateMax(item:SearchTreeSpot;TypeOfItem:kind);
(* choose The most cost project from Childs maxprojects or from item max project  *)
(* and go to parent item , do it until coming to root or max did not change       *)
(* called whith delete tree and rotation procedures                               *)
Var
NewMax:projectspot;
begin
newmax:=nil;
while (item<>nil) and (item^.TheMostCostProject<>newmax) do
  begin
  case typeOfItem of  (* new max <----item max project *)
     job       :NewMax:=item^.project;
     supervisor:NewMax:=item^.performer^.HeapSpot^.TheMostCostProject;
     end;{case}
     if (item^.left<>nil) and (NewMax^.ProjectCost<item^.left^.TheMostCostProject^.projectcost)
        then NewMax:=item^.left^.TheMostCostProject;
     if (item^.right<>nil) and (NewMax^.ProjectCost<item^.right^.TheMostCostProject^.projectcost)
        then NewMax:=item^.right^.TheMostCostProject;
        if (NewMax<>item^.TheMostCostProject)  {The max changed}
           then
           begin
           if NewMax<>nil then item^.TheMostCostProject:=NewMax;
           item:=item^.prev;
           end;
  end;
end;{UpdateMax}
(*------------------------------------------------------------------------*)
procedure LeftRotate(var treeroot:SearchtreeSpot;Item:SearchtreeSpot;TypeOfItem:kind);
(* Changing tree structure move right child to be parent and parent to be left child *)
var
help:SearchtreeSpot;
begin
if Item^.right<>nil
then
begin
help:=Item^.right;
Item^.right:=Help^.left;
if help^.left<>nil then Help^.left^.prev:=item;
Help^.prev:=Item^.prev;
if Item^.prev<>nil {if there is not root of tree}
   then if Item=Item^.prev^.left then Item^.prev^.left:=help
                                  else Item^.prev^.right:=help
   else TreeRoot:=Help;
Item^.prev:=help;
Help^.left:=item;
end;
UpdateMax(help,TypeOfItem);
end;{LeftRotate}
(*------------------------------------------------------------------------*)
procedure RightRotate(var treeroot:SearchtreeSpot;Item:SearchtreeSpot;TypeOfItem:kind);
(* Changing tree structure move left child to be parent and parent to be right child *)
var
help:SearchtreeSpot;
begin
if item^.left<>nil
then
begin
Help      :=Item^.left;
Item^.left:=Help^.right;
if help^.right<>nil then help^.right^.prev:=Item;
Help^.prev:=Item^.prev;
if Item^.prev<>nil
   then if Item=Item^.prev^.left then Item^.prev^.left:=help
                                 else Item^.prev^.right:=help
   else TreeRoot:=Help;
Item^.prev:=help;
Help^.right:=Item;
end;
UpdateMax(help,TypeOfItem);
end; {RightRotate}
(*------------------------------------------------------------------------*)
procedure RBInsertFixUp(var TreeRoot:SearchtreeSpot;Item:SearchtreeSpot;TypeOfItem:kind);
(* Restore Red Black properties after inserting new item into the tree     *)
var
help:SearchtreeSpot;
begin
while (Item^.prev<>nil) and (Item^.prev^.ItemColor=red) do
      begin
      if Item^.prev=Item^.prev^.prev^.left
         then
         begin
         help:=Item^.prev^.prev^.right; {the uncle of item}
         if help^.ItemColor=red
(* the first case uncle and parent are red                       *)
(* move red up by changing color of parent uncle  end grandfather*)
            then
            begin
            Item^.prev^.Itemcolor:=black;
            help^.ItemColor:=black;
            Item^.prev^.prev^.itemcolor:=red;
            Item:=Item^.prev^.prev;
            end
            else
            begin
            if item=Item^.prev^.right
               then
(* the second case uncle is black parent is red  item is right child *)
(* move to third case by doing rotation                              *)
               begin
               item:=Item^.prev;
               leftrotate(treeroot,item,typeofitem);
               end;
(* the third case uncle is black parent is red item is left child*)
(* change parents and grandfather color and then rotation        *)
            Item^.prev^.itemcolor:=black;
            Item^.prev^.prev^.itemcolor:=red;
            Rightrotate(treeroot,Item^.prev^.prev,typeofitem);
            end
         end {then Item^.prev=Item^.prev^.prev^.left}
(*---------------------------------------------------------------------------*)
(* Exchange left and right                                                   *)
         else {Item^.prev=Item^.prev^.prev^.right}
           begin
           help:= Item^.prev^.prev^.left; {the ancle of item}
           if help^.ItemColor=red
              then
              begin
              Item^.prev^.Itemcolor:=black;
              help^.ItemColor:=black;
              Item^.prev^.prev^.itemcolor:=red;
              Item:=Item^.prev^.prev;
              end
              else
              begin
              if item=Item^.prev^.left
                 then
                 begin
                 item:=Item^.prev;
                 rightrotate(treeroot,item,typeofitem);
                 end;
              Item^.prev^.itemcolor:=black;
              Item^.prev^.prev^.itemcolor:=red;
              leftrotate(treeroot,Item^.prev^.prev,typeofitem);
              end
         end; {else Item^.prev=Item^.prev^.prev^.left}
      end; {(Item^.prev<>nil) and (Item^.prev^.color=red) }
TreeRoot^.ItemColor:=black;
end; {RBInsertFixUp}
(*------------------------------------------------------------------------*)
procedure InsertItem(var Treeroot,NewItem:SearchtreeSpot;
                     MaxCostProject:ProjectSpot;TypeOfItem:kind);
(*insert new item to the given tree and update MaxCostProject of previous items*)
Var
(*TreeRoot pointer to root of tree*)
(*NewItem Item to be inserted     *)
(*MaxCostProject - New value for Max cost project *)
(*TypeofItem: what kind of data we are working    *)
prev,current:SearchtreeSpot;
begin
prev:=nil;
current:=treeroot;
while current<>nil do
 begin
 prev:=current;
 if current^.TheMostCostProject^.projectcost<MaxCostProject^.projectcost then  current^.TheMostCostProject:=MaxCostProject;
 if current^.key>=NewItem^.key then current:=current^.left else current:=current^.right;
 end;
 NewItem^.prev :=prev;
 NewItem^.right:=nil;
 NewItem^.left :=nil;
 NewItem^.ItemColor:=red;
 NewItem^.TheMostCostProject:=MaxCostProject;
 if prev=nil then treeroot:=NewItem
             else if prev^.key>=NewItem^.key
                     then prev^.left :=newitem else prev^.right:=newitem;
 RBInsertFixUp(Treeroot,NewItem,TypeOfItem);
end;{procedure InsertItem}
(*------------------------------------------------------------------------*)
function TreeSearch(root:SearchtreeSpot;key:name):SearchtreeSpot;
(*find given key in the tree return nil if not found or pointer to corespond item*)
begin
while not ((root=nil) or (root^.key=key)) do if root^.key>=key then root:=root^.left else root:=root^.right;
TreeSearch:=root;
end;{function TreeSearch}
(*------------------------------------------------------------------------*)
function ExtractMin(root:SearchtreeSpot):SearchtreeSpot;
(*finding the minimal key in the tree*)
begin
while root^.left<>nil do root:=root^.left;
ExtractMin:=root;
end;{function ExtractMin}
(*------------------------------------------------------------------------*)
function TreeSuccesor(root:SearchtreeSpot):SearchtreeSpot;
(*Search for the item followes given item *)
begin
if root^.right<>nil
   then  TreeSuccesor:=ExtractMin(root^.right)
   else
   begin
   while (root^.prev<>nil) and (root=root^.prev^.right) do root:=root^.prev;
   TreeSuccesor:=root^.prev;
   end;
end;{TreeSuccesor}
(*------------------------------------------------------------------------*)
function CheckColor(Item:SearchtreeSpot):color;
begin
if item=nil then CheckColor:=black else CheckColor:=Item^.Itemcolor;
end;{CheckColor}
(*------------------------------------------------------------------------*)
procedure RBDeleteFixUp(Var TreeRoot:SearchtreeSpot;Item,ParentOfItem:SearchtreeSpot;TypeOfItem:kind);
(* Restore Red-Black tree properties after operation DELETE *)
var
dummy,(* Change Nil items                *)
brother:SearchtreeSpot;(*brother of item *)
begin
new(dummy);Dummy^.left:=Dummy;Dummy^.right:=Dummy;Dummy^.prev:=ParentOfItem;
Dummy^.ItemColor:=black;
while (item<>treeroot) and (checkcolor(Item)=black) do
      begin
      if item=ParentOfItem^.left
         then
         begin
         brother:=Item^.prev^.right;
         if brother=nil then brother:=dummy;
         if CheckColor(brother)=red
            then
(* case 1 brother of item is red  - exchange color and rotation       *)
            begin
            brother^.ItemColor      :=black;
            brother^.prev^.ItemColor:=red;
            LeftRotate (TreeRoot,ParentOfItem,TypeOfItem);
            brother:=ParentOfItem^.right;
            Dummy^.prev:=ParentOfItem;
            if brother=nil then brother:=dummy;
            end; (* CheckColor(brother)=red *)
         if (CheckColor(Brother^.left)=black) and (CheckColor(Brother^.right)=black)
             then begin
(* case 2 brothers childs are black   change color and go up to parent *)
                  Brother^.ItemColor:=red;
                  Item:=ParentOfItem;
                  ParentOfItem:=ParentOfItem^.prev;
                  Dummy^.prev:=ParentOfItem;
                  Dummy^.ItemColor:=black; {if brother=dummy then color dummy should not be changed}
                  end
             else begin
(* case 3 right child of brother is black and brother is black - rotation move to case 4*)
                  if CheckColor(brother^.right)=black
                     then
                     begin
                     Brother^.left^.ItemColor:=black;
                     Brother^.ItemColor:=red;
                     RightRotate(TreeRoot,Brother,TypeOfItem);
                     brother:=ParentOfItem^.right;
                     if brother=nil then brother:=dummy;
                     end;
(* Case 4 left child of brother is black and brother is black                           *)
                   Brother^.ItemColor:=ParentOfItem^.ItemColor;
                   ParentOfItem^.ItemColor:=black;
                   Brother^.right^.ItemColor:=black;
                   LeftRotate(TreeRoot,ParentOfItem,TypeOfItem);
                   Item:=TreeRoot;
                   end;
         end (* x=parentOfItem^.left *)
(*-------------------------------------------------------------------*)
(*exchange left and right like cases up to line                      *)
         else (* x=parentOfItem^.right *)
         begin
         brother:=ParentOfItem^.left;
         if brother=nil then brother:=dummy;
         if checkcolor(brother)=red
            then
            begin
            brother^.itemcolor:=black;
            brother^.prev^.ItemColor:=red;
            rightRotate (TreeRoot,ParentOfItem,TypeOfItem);
            Dummy^.prev:=ParentOfItem;
            brother:=ParentOfItem^.left;
            if brother=nil then brother:=dummy;
            end; (* CheckColor(brother)=red *)
         if (CheckColor(Brother^.left)=black) and (CheckColor(Brother^.right)=black)
             then begin
                  Brother^.ItemColor:=red;
                  Item:=ParentOfItem;
                  ParentOfItem:=ParentOfItem^.prev;
                  Dummy^.prev:=ParentOfItem;
                  Dummy^.ItemColor:=black;  {if brother=dummy then color dummy should not be changed}
                  end
             else begin
                  if CheckColor(Brother^.left)=black
                     then
                     begin
                     Brother^.right^.ItemColor:=black;
                     Brother^.ItemColor:=red;
                     LeftRotate(TreeRoot,Brother,TypeOfItem);
                     brother:=ParentOfItem^.left;
                     if brother=nil then brother:=dummy;
                     end;(* else brother^.left and brother^.right=black *)
                   Brother^.ItemColor:=ParentOfItem^.ItemColor;
                   ParentOfItem^.ItemColor:=black;
                   Brother^.left^.ItemColor:=black;
                   rightRotate(TreeRoot,ParentOfItem,TypeOfItem);
                   Item:=TreeRoot;
                   end;
         end (* else x=parentOfItem^.left *)
      end;(*while (item<>treeroot) and (CheckColor(Item)=black)*)
Item^.Itemcolor:=black;
dispose(dummy);{free memory}
end; {RBDeleteFixUp}
(*------------------------------------------------------------------------*)
procedure DeleteTree(Var TreeRoot:SearchtreeSpot;root:SearchtreeSpot;TypeOfItem:kind);
(* Delete item from tree                                *)
(* TreeRoot root of the tree , root: item to be deleted *)
var
help ,                 {Item to be removed from tree}
child:SearchtreeSpot; {child of help}
begin
(*if last item then exit*)
if (root^.right=nil) or (root^.left=nil) (*if root has not childs items*)
   then help:=root
   else
   begin
   help:=TreeSuccesor(root);
   root^.key:=help^.key;
   case TypeOfItem of  {copy data depends on type of item: project or performer}
        job       :root^.project:=help^.project;
        supervisor:root^.performer:=help^.performer;
   end;{case}
   {After copying data TheMostCostProject changed then update it up from the root}
   UpdateMax(root,TypeOfItem);
   end;
(* connect help childs to his parent and update maxcostproject *)
if help^.left=nil then child:=help^.right else child:=help^.left;
if child<>nil then child^.prev:=Help^.prev;
if help^.prev=nil
   then treeroot:=child
   else
   begin
   if help=help^.prev^.left then help^.prev^.left:=child
                            else help^.prev^.right:=child;
   UpdateMax(help^.prev,TypeOfItem);
   end;
if Help^.Itemcolor=black then RBDeleteFixUp(TreeRoot,child,help^.prev,TypeOfItem);
dispose(help);
end;{DeleteTree}
(*-------------------------------------------------------------------------*)
procedure AddProject2performer(var PerformerItem:SearchTreespot;project:projectspot);
(* adding new project to performer :to project heap and project stack*)
var
item:SearchTreeSpot;
begin
(*insert to stack*)
project^.prev:=nil;
project^.next:=PerformerItem^.performer^.stackspot;
PerformerItem^.performer^.stackspot^.prev:=project;
PerformerItem^.performer^.stackspot:=project;
(*insert to tree*)
new (item);
item^.project:=project;
item^.key:=project^.ProjectName;
Item^.TheMostCostProject:=project;
InsertItem(PerformerItem^.performer^.HeapSpot,item,project,job);
UpdateMax(PerformerItem,Supervisor);(* Update TheMostCostProject *)
end;{procedure AddProject2performer}
(*------------------------------------------------------------------------*)
procedure AddNewProject(var TreeRoot:SearchtreeSpot;var InputFile:text;loading:boolean);
(* called when first character in the line is 'N'-new project *)
var
CurrentItem :SearchtreeSpot;   (* performer *)
CurrentProjectSpot:ProjectSpot;(* New Project *)
PerformerId:name;
begin
 new(CurrentProjectSpot);(*reserve memory for new project*)
 readline(InPutFile,CurrentProjectSpot^,PerformerId);
 CurrentItem:=TreeSearch(TreeRoot,PerformerId);
 if CurrentItem=nil
 Then
 begin
 new(CurrentItem);new(CurrentItem^.performer);
 CurrentItem^.key:=PerformerId;
 CurrentItem^.performer^.id:=PerformerId;
 CurrentItem^.performer^.HeapSpot:=nil;
 CurrentItem^.performer^.StackSpot:=nil;
 InsertItem(TreeRoot,CurrentItem,CurrentProjectSpot,supervisor);
 end;
 AddProject2Performer(CurrentItem,CurrentProjectSpot);
 if not loading
    then
    begin
    writeln('New project: ',CurrentProjectSpot^.projectName,EmptyCh,
                          'ProjectId: ',CurrentProjectSpot^.Id,EmptyCh,
                          'ProjectCost: ',CurrentProjectSpot^.projectCost:5:2,EmptyCh,'inserted.');
    writeln('Performer  : P',PerformerId);
   end;
end;{AddNewProject}
(*------------------------------------------------------------------------*)
procedure File2Tree(var TreeRoot:SearchtreeSpot);
(*read file of data to memory and organize data  in tree*)
var
InputFile:text;
CurrentProjectSpot:ProjectSpot;
PerformerId:name;
begin
assign(InputFile,'REPDR01.TXT');
reset(InPutFile);
Writeln('Load data file into memory');
while not eof(InputFile) do AddNewProject(TreeRoot,InputFile,1=1);
close(InputFile);
end; {file2tree}
(*-----------------------------------------------------------------------*)
procedure performer2file(Root:SearchtreeSpot;var out:text);
(*write all projects of the performer as lines into output file*)
var
spot:projectspot;
begin
if root<>nil then
             begin
             spot:=root^.performer^.StackSpot;
             while spot^.next<>nil do spot:=spot^.next;{go to end of stack}
             while spot<>nil do {from end to head of stack}
             begin
             writeln(out,Spot^.projectname:NameLenth,emptych,Spot^.Id:4,emptych,
             Spot^.projectcost:5:2,emptych,'P',root^.Performer^.id:NameLenth);
             spot:=spot^.prev;
             end;
             performer2file(Root^.left,out);
             performer2file(Root^.right,out);
             end;
end;  (*Performer2File *)
(*-----------------------------------------------------------------------*)
procedure Tree2file(TreeRoot:SearchtreeSpot);
(*save updated data to file at end of job with program*)
var
OutputFile:text;
begin
assign(OutputFile,'REPDR01.TXT');
rewrite(OutPutFile);
performer2file(TreeRoot,OutPutFile);
close(OutPutFile);
end; (* Tree2file *)
(*------------------------------------------------------------------------*)
procedure DeleteCurrentProject (Performer:PerformerSpot);
(* delete Finished project if first character in input line is 'F' *)
var
treeItem:SearchTreeSpot;
begin
if performer^.StackSpot<>nil
   then
   begin
   TreeItem:=TreeSearch(Performer^.HeapSpot,Performer^.StackSpot^.projectname);
   DeleteTree(Performer^.HeapSpot,TreeItem,job);
   performer^.StackSpot:=performer^.StackSpot^.next;
   performer^.StackSpot^.prev:=nil;
   writeln('The project ',TreeItem^.project^.projectname,' performer ',Performer^.id);
   writeln('is finished and deleted from system');
   dispose(TreeItem^.project); (*free memory*)
   end;
end;  (* DeleteCurrentProject *)
(*------------------------------------------------------------------------*)

procedure PerformerQuery(var inputfile:text;PerformerTreeRoot:SearchtreeSpot);{Performer current project}
var                                          {if project belong to performer}
Projectname:Name;
CurrentProjectSpot:ProjectSpot;
PerformerId:name;
CurrentItem:SearchtreeSpot;
ProjectItem:SearchtreeSpot;
ch:char;
begin
ReadName (inputfile,PerformerId);
ReadName (inputfile,projectname);
read2eoln(inputfile);
CurrentItem:=Treesearch(PerformerTreeRoot,performerID);
if CurrentItem<>nil
   then
   If Projectname=EmptyName
      then
      begin
      writeln('The current project of the performer ',PerformerPrefix,performerID);
      writeln('Name: ',CurrentItem^.Performer^.StackSpot^.projectName,
      emptyCh,'Id: ',CurrentItem^.Performer^.StackSpot^.id,emptych,
      'cost: ',CurrentItem^.Performer^.StackSpot^.projectcost:5:2);
      end {then If Projectname=EmptyName}
      else
      begin
      ProjectItem:=Treesearch(CurrentItem^.Performer^.heapspot,projectname);
      if ProjectItem<>nil
         then if ProjectItem^.project=CurrentItem^.Performer^.StackSpot
                 then writeln('The project ',projectname,' is ',
                      'current project of ',PerformerPrefix,PerformerId)
                 else writeln('The project ',projectname,' is ',
                              'waiting project of ',PerformerPrefix,PerformerId)
         else writeln('The project ',projectname,' do not belong to ',
                       PerformerPrefix,PerformerId);
      end {else If Projectname=EmptyName}
   else writeln ('Perfomer ',PerformerPrefix,performerId,' does not exist !!!');
end;(* PerformerQuery *)
(*------------------------------------------------------------------------*)
procedure MaxFindQuery(var InputFile:text;PerformerTreeRoot:SearchtreeSpot);
{Find maxcost project for performer or at all}
var
Projectname:Name;
CurrentProjectSpot:ProjectSpot;
PerformerId:name;
CurrentItem:SearchtreeSpot;
ProjectItem:SearchtreeSpot;
ch:char;
begin
read2thenextchar(InputFile,ch);
if ch=PerformerPrefix
   then
   begin
   readname(inputfile,performerID);
   read2eoln(inputfile);
   CurrentItem:=Treesearch(PerformerTreeRoot,performerID);
   CurrentProjectSpot:=CurrentItem^.performer^.Heapspot^.TheMostCostProject;
   if CurrentItem<>nil
      then writeln('The most cost project of ',PerformerPrefix,performerid,
           ' is ',CurrentProjectSpot^.projectName,' cost: ',
           CurrentProjectSpot^.projectcost:5:2)
      else writeln ('Perfomer ',PerformerPrefix,performerId,' does not exist !!!');
   end  {then ch=PerformerPrefix}
   else {ch=PerformerPrefix}
   begin
   read2eoln(inputfile);
   CurrentProjectSpot:=PerformerTreeRoot^.TheMostCostProject;
   if PerformerTreeRoot<>nil
      then writeln('The most cost project is ',CurrentProjectSpot^.projectname,
           ' cost ',CurrentProjectSpot^.projectcost:5:2)
      else writeln('Stack is empty');
   end; {else ch=PerformerPrefix}
end; (*{MaxFindQuery}*)
(*------------------------------------------------------------------------*)
procedure EndProject(var InputFile:text;var PerformerTreeRoot:SearchtreeSpot);
(* Current project of the performer is finished and therefore should be deleted *)
var
PerformerId:name;
CurrentItem:SearchtreeSpot;
ch:char;
begin
read2thenextchar(InputFile,ch);
if ch=PerformerPrefix
   then
   begin
   ReadName (inputfile,PerformerId); ;
   read2eoln(inputfile);
   CurrentItem:=Treesearch(PerformerTreeRoot,performerID);
   if CurrentItem<>nil
      then
      begin
      DeleteCurrentProject(CurrentItem^.performer);
      if CurrentItem^.performer^.StackSpot=nil {if pervormer has not projects delete him}
         then begin
              deletetree(PerformerTreeRoot,CurrentItem,supervisor);
              writeln('Performer ',PerformerPrefix,PerformerID,' and all his projects are deleted');
              end
              else UpdateMax(CurrentItem,supervisor);
      end;
   end;{if then ch=PerformerPrefix}
end; {EndProject}
(*------------------------------------------------------------------------*)
procedure Deleteperformer(var InputFile:text;var PerformerTreeRoot:SearchtreeSpot);
(* called if first characters  in the input line is 'DA' *)
(* deletes all projects of the given performer and performer item to *)
var
PerformerId:name;
CurrentItem:SearchtreeSpot;
ch:char;
begin
   Read2TheNextChar(InputFile,ch);
   if ch=PerformerPrefix
      then
      begin
      ReadName (inputfile,PerformerId);
      read2eoln(inputfile);
      CurrentItem:=Treesearch(PerformerTreeRoot,PerformerID);
      if CurrentItem<>nil
         then
         begin
         while  CurrentItem^.performer^.StackSpot<>nil do
         DeleteCurrentProject(CurrentItem^.performer);
         writeln('Performer ',PerformerPrefix,PerformerID,' and all his projects are deleted');
         deletetree(PerformerTreeRoot,CurrentItem,supervisor);
         end
      else writeln('Performer ',PerformerPrefix,PerformerId,' does not exist');
      end;{ch=PerformerPrefix}
end; {Deleteperformer}
(*=================== * T H E  M A I N  P R O G R A M * ==================*)
var
InputFile:text;
PerformerTreeRoot:SearchtreeSpot;
ch:char;
CommandString:array [1..2] of char;
begin
PerformerTreeRoot:=nil;
file2tree(PerformerTreeRoot); {load data}
writeln('**************************************************');
Assign(InputFile,'');
reset(InputFile);
while not eof(InputFile) do
 begin
  CommandString:='  ';Ch:=EmptyCh;
  repeat read(InputFile,CommandString[1]) until not (CommandString[1] in controlch);
  read(InputFile,CommandString[2]);
  CommandString[1]:=UpCase(CommandString[1]);CommandString[2]:=UpCase(CommandString[2]);
  case CommandString[1] of
       NewProject :AddNewProject(PerformerTreeRoot,InputFile,1=2);
       ProjectOver :EndProject(InputFile,PerformerTreeRoot);
       DeleteAll   :if CommandString[2]='A' then Deleteperformer(InputFile,PerformerTreeRoot);
       Query       :begin
                    read2thenextchar(InputFile,ch);
                    case ch of
                         performerprefix:PerformerQuery(inputfile,PerformerTreeRoot);
                         FindMax        :MaxFindQuery(InputFile,PerformerTreeRoot);
                         end;
                     end; {Query}
      else  if not eof(inputfile) then writeln('INVALID COMMAND');
  end;{case}
 end;{While not eof }
close(InputFile);
tree2file(PerformerTreeRoot); {save data}
end. {the main}