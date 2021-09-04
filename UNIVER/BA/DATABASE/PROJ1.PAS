program proj1;
(*----------------------------------------*)
const
  MaxInputSize   = 200;
  MinSelectSize  = 16  ;{The Min Array size for process by SELECT procedure}
  type
  InputArray = array[1..MaxInputSize] of integer;
  FileOfInteger=file of integer;
  FileTableItem=record
                     FileName:string;
                     FileSize:integer
                end;
  TableOfFiles=array[1..9] of FileTableItem;
  var
  InputFile:FileOfInteger;
  FileList:TableofFiles; {List of input files}
  i,         {index}
  FileType   {what type of file in process}
  :integer;
  Counter    {Operation counter for compare Algorithms selectsort and quicksort}
  :longint;
  EntryArray:InputArray; {Array to be sorted}
(*------functiuon and procedure -----------------------------------------*)
procedure PrintArray(var PrintArray:InputArray;NumOfItem:integer);
          {pinting first NumOfItem in the given array of integer}
     var
     i {counter}
     :integer;
     begin
     writeln;
     for i:=1 to NumOfItem
          do begin
             write (PrintArray[i]:4,' ');
             if (i mod 15=0) then writeln;{new line after each 15 items}
             end;
     writeln;writeln;
     end;
(*------------------------------------------------------------*)
procedure LoadFile(var InputFile:FileOfInteger;var EntryArray:InputArray);
(*Procedure for loading InputFile to the Entry Array*)
var
counter:integer;
begin
reset(InputFile);
counter:=0;
 while (not eof(InputFile)) and (counter<MaxInputSize) do
       begin
           read(inputFile,EntryArray[counter+1]);
           counter:=counter+1;
       end;
 end;
(*------------------------------------------------------------*)
function Insert_Sort(SubArray:InputArray;first:integer;last:integer;place:integer;
                    var NumOp:longint):integer;
(*Function for sorting SubArrays less then 15 items and searching the value of given place *)
(*  used in procedure SELECT                                             *)
var
  {first: place of the first item of the SubArray in the InputArray
   last : place of the last item of the SubArray in the InputArray
   place: the absolute place in subarray for placeth item
   NumOp: counter operation number}
   key,  {help variable}
   i,j   {indexes      }
   :integer;
begin
    for j:=first+1 to last do
        begin
        i:=j-1;
        key:=SubArray[j];
        NumOp:=NumOp+3;
        while (i>first-1) and (SubArray[i]>key) do
              begin
              SubArray[i+1]:=SubArray[i];
              i:=i-1;
              NumOp:=NumOp+3;
              end;
              SubArray[i+1]:=key;
              NumOp:=NumOp+1;
        end;
        NumOp:=NumOp+1;
        Insert_Sort:=SubArray[place];
end;
(*------------------------------------------------------------*)
function SelectPartition(var SubArray:InputArray;        {array to be divided}
                             first:integer;last:integer; {first and last items in subarray}
                             pivot_value:integer;        {value arround him array should be divided}
                             NumOP:longint               {counter operation number}
                             ):integer;
(*procedure for dividing given array by two subarrays arround the median*)
         var   {item arround him the array should be divided}
         j,i,  {indexes}
         key,  {help variable}
         first_item
        :integer;
   begin
       i:=first;j:=last;
       NumOp:=NumOp+2;
       while (i<j) do
             begin
             while (SubArray[j]>=pivot_value) and (j>first)
             do begin j:=j-1;NumOp:=NumOp+3; end;
             while (SubArray[i]<pivot_value) and (i<last)
             do begin i:=i+1;NumOp:=NumOp+3; end;
             if (i<j) then  {exchanging values SubArray[i]<--->SubArray[j]}
                      begin
                      key:=SubArray[i];
                      SubArray[i]:=SubArray[j];
                      SubArray[j]:=key;
                      NumOp:=NumOp+4;
                      end
                      else NumOp:=NumOp+1;
             end;
         NumOp:=NumOp+1;
         SelectPartition:=j;
   end;
(*------------------------------------------------------------*)
function Partition(var SubArray:InputArray;first:integer;last:integer;
                   var NumOP:longint):integer;
(*procedure for dividing given array by two subarrays arround the first item*)
         var
         {NumOP       :counter of operation}
         j,i,        {indexes}
         pivot_value,{value arround him subbarray should be divided}
         key  {help variable}
         :integer;
   begin
       i:=first;j:=last;pivot_value:=SubArray[first];
       NumOp:=NumOp+3;
       while (i<j) do
             begin
             NumOp:=NumOp+1;
             while (SubArray[j]>=pivot_value) and (j>first) do
             begin j:=j-1; NumOp:=NumOp+3; end;
             while ((SubArray[i]<pivot_value) and (i<last)) do
             begin i:=i+1;NumOp:=NumOp+3; end;
             if (i<j) then
                      begin
                      key:=SubArray[i];
                      SubArray[i]:=SubArray[j];
                      SubArray[j]:=key;
                      NumOp:=NumOp+4;
                      end
                      else NumOp:=NumOp+1;
             end;
         NumOp:=NumOp+1;
         Partition:=j;
   end;
(*------------------------------------------------------------*)
function SELECT(SubArray:InputArray;first:integer;last:integer;place:integer;
                var NumOP:longint):integer;
         {procedure that loking for median in the given subarray
          if there are less than MinSelectSize items it the subarray if are not procedure calling herself recursively}
  var
    {NumOP       :counter of operation}
    ArrayOfMedian:InputArray;{array for storing medians of fifes of items }
    i,j,                     {indexes}
    last_item,{index for sign last item in the subarray of fife items}
    md_of_md,{median of medians}
    md_place {place of median of median}
    :integer;
    begin
        i:=first;{starting the variables}
        j:=0;
        NumOp:=NumOp+2;
        if (last-first+1<MinSelectSize) {then sort it}
           then begin SELECT:=Insert_Sort(SubArray,first,last,first+place-1,NumOP);
                      NumOp:=NumOp+6;
                end
                else begin {look for the median and go to suit subarray}
                while (i<=last) do
                      begin
                      j:=j+1;
                      NumOp:=NumOp+2;
                      if (i+4<=last)
                      then last_item:=i+4  {checking border conditions}
                      else last_item:=last;
                      NumOp:=NumOp+2;
                      {finding medians fifes of items}
                      ArrayOfMedian[j]:=Insert_Sort(SubArray,i,last_item,(i+last_item) div 2+(i+last_item) mod 2,NumOP);
                      i:=i+5;
                      NumOp:=NumOp+2;
                      end;
                      {find median of medians}
                      md_of_md:=SELECT(ArrayOfMedian,1,j,j div 2+j mod 2,NumOp);
                      {divide given subarray arround median of medians}
                      md_place:=Selectpartition(SubArray,first,last,md_of_md,NumOp);
                      NumOp:=NumOp+5;
                      if (md_place=place+first-1) then SELECT:=md_of_md;
                      if (md_place<place+first-1) {recursive call}
                      then SELECT:=SELECT(Subarray,md_place,last,place+first-md_place,NumOp);
                      if (md_place>place+first-1)
                      then SELECT:=SELECT(Subarray,first,md_place,place,NumOp);
                      NumOp:=NumOp+5;
                end;
    end;
(*-------------------------------------------------------------*)
procedure SelectQuickSort (var Unsorted:InputArray;first:integer;last:integer;
                           var NumOp:longint);
          var
          (*Unsorted array to be sorted                                        *)
          (*first,last - items between them SelectQuickSort process input array*)
          {NumOP       :counter of operation}
          Pivot_Item, {the item for dividing entry array to sub arrays}
          Pivot_Index, {the place of pivot for dividing array}
          middle     , {the middle of the subarray}
          key {help variable}
          :integer;
          begin
             middle:=(first+last) div 2 +  (first+last) mod 2-first+1;
             {the middle of the given substring relatively to first item}
             if first<last
             then begin
             Pivot_Item:=SELECT(Unsorted,first,last,middle,NumOp);
             Pivot_Index:=SelectPartition(Unsorted,first,last,Pivot_item,NumOp);
             SelectQuickSort(Unsorted,first,Pivot_Index,NumOp);
             SelectQuickSort(Unsorted,Pivot_Index+1,last,NumOp);
             NumOp:=NumOp+12;
             end;
          end;
(*---------------------------------------------------------------------*)
procedure QuickSort (var Unsorted:InputArray;first:integer;last:integer;
                     var NumOp:longint);
          var
          (*Unsorted array to be sorted                                        *)
          (*first,last - items between them SelectQuickSort process input array*)
          {NumOP       :counter of operation}
          Pivot_Item, {the item for dividing entry array to sub arrays}
          Pivot_Index, {the place of pivot for dividing array}
          key {help variable}
          :integer;
          begin
             if first<last
             then begin
                  Pivot_Index:=Partition(Unsorted,first,last,NumOP);
                  QuickSort(Unsorted,first,Pivot_Index,NumOP);
                  QuickSort(Unsorted,Pivot_Index+1,last,NumOP);
                  NumOP:=NumOp+4;
                  end
             else NumOP:=NumOp+1;
          end;
(**************************************************************)
begin {main program}
   FileList[1].FileName:= 'sort50.dat' ;FileList[2].FileName:= 'nsort50.dat';
   FileList[1].FileSize:= 50;           FileList[2].FileSize:= 50;
   FileList[3].FileName:= 'bsort50.dat';FileList[4].FileName:= 'sort100.dat';
   FileList[3].FileSize:= 50;           FileList[4].FileSize:= 100;
   FileList[5].FileName:='nsort100.dat';FileList[6].FileName:='bsort100.dat';
   FileList[5].FileSize:=100;           FileList[6].FileSize:=100;
   FileList[7].FileName:='sort200.dat' ;FileList[8].FileName:='nsort200.dat';
   FileList[7].FileSize:=200           ;FileList[8].FileSize:=200;
   FileList[9].FileName:='bsort200.dat';FileList[9].FileSize:=200;
   for i:=1 to 9 do
   begin
       Assign(InputFile,FileList[i].FileName);
       FileType:=i mod 3;
       writeln;writeln;
       case FileType of
            0:writeln('Backsorted file , file size is: ',FileList[i].FileSize:4);
            1:writeln('Sorted file , file size is: ',FileList[i].FileSize:4);
            2:writeln('Unsorted file , file size is: ',FileList[i].FileSize:4);
       end;
       {SELECTQUICKSORT operate}
       Counter:=0;
       LoadFile(InputFile,EntryArray);
       writeln('Input File: ',FileList[i].FileName:10);
       Printarray(EntryArray,FileList[i].FileSize);
       writeln('SELECTQUICKSORT');
       write('===============');
       SelectQuickSort(EntryArray,1,FileList[i].FileSize,Counter);
       Printarray(EntryArray,FileList[i].FileSize);
       writeln ('SELECTQUICKSORT. Number of operation is ',Counter);
       writeln ('**********************************************');
       {Operate quicksort}
       LoadFile(InputFile,EntryArray);
       writeln;
       writeln('QUICKSORT');
       write('=========');
       Counter:=0;
       QuickSort(EntryArray,1,FileList[i].FileSize,Counter);
       Printarray(EntryArray,FileList[i].FileSize);
       writeln ('QuickSort. Number of operation is ',Counter);
       writeln ('**********************************************')
       end;
end.
(*--------------------------------------------------------------------*)
