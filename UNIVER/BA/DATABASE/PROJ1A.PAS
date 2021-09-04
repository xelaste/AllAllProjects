program proj1a; {program create input files for testing quicksort algorithm}
(*----------------------------------------*)
const
  MaxInputSize   = 200;
  MaxInputNumber = 2000;{The max possible number in the input}
  MinSelectSize  = 16  ;{The Min Array size for process by SELECT procedure}
  type
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
  choice     {which is current file type }
  :integer;
  (*------functiuon and procedure -----------------------------------------*)
procedure CreateUnSortFile     (FileName:string;NumberOfItem:integer);
var
  OutputFile:file of integer;
  RandomNumber,
  i:integer;{index}
begin
  assign(OutputFile,FileName);
  rewrite(OutputFile);
  randomize;
  for i:=1 to NumberOfItem do
      begin
      RandomNumber:=random(MaxInputNumber);
      write(OutputFile,RandomNumber);
      end;
  close (OutputFile);
end;
(*-------------------------------------------------------------------*)
procedure CreateSortFile   (FileName:string;NumberOfItem:integer);
var
OutputFile:file of integer;
RandomNumber, {number to be writen to output file}
MaxVar,
i:integer;{index}
begin
  RandomNumber:=0;
  MaxVar:=MaxInputNumber div NumberOfItem;
  assign(OutputFile,FileName);
  rewrite(OutputFile);
  randomize;
  for i:=1 to NumberOfItem do
      begin
      RandomNumber:=random(MaxVar)+RandomNumber;
      RandomNumber:=RandomNumber+1;{if random(MaxVar)=0}
      write(OutputFile,RandomNumber);
      end;
  close (OutputFile);
end;
(*-------------------------------------------------------------------*)









procedure CreateBackSortFile (FileName:string;NumberOfItem:integer);
var
OutputFile:file of integer;
RandomNumber, {number to be writen to output file}
MaxVar,
i:integer;{index}
begin
  RandomNumber:=MaxInputNumber;
  MaxVar:=MaxInputNumber div NumberOfItem;
  assign(OutputFile,FileName);
  rewrite(OutputFile);
  randomize;
  for i:=1 to NumberOfItem do
      begin
      RandomNumber:=RandomNumber-random(MaxVar);
      RandomNumber:=RandomNumber-1;{if random(MaxVar)=0}
      write(OutputFile,RandomNumber);
      end;
  close (OutputFile);
end;
(*------------------------------------------------------------*)
begin
   FileList[1].FileName:= 'sort50.dat' ;FileList[2].FileName:= 'nsort50.dat';
   FileList[1].FileSize:= 50;           FileList[2].FileSize:= 50;
   FileList[3].FileName:= 'bsort50.dat';FileList[4].FileName:= 'sort100.dat';
   FileList[3].FileSize:= 50;           FileList[4].FileSize:= 100;
   FileList[5].FileName:='nsort100.dat';FileList[6].FileName:='bsort100.dat';
   FileList[5].FileSize:=100;           FileList[6].FileSize:=100;
   FileList[7].FileName:='sort200.dat' ;FileList[8].FileName:='nsort200.dat';
   FileList[7].FileSize:=200           ;FileList[8].FileSize:=200;
   FileList[9].FileName:='bsort200.dat';FileList[9].FileSize:=200;

   for i:=1 to 9 do begin
                    writeln(FileList[i].FileName);
                    choice:=i mod 3;
                    case choice of
                    0:CreateBackSortFile (FileList[i].FileName,FileList[i].FileSize);
                    1:CreateSortFile     (FileList[i].FileName,FileList[i].FileSize);
                    2:CreateUnSortFile   (FileList[i].FileName,FileList[i].FileSize);
                    end;
                    end;
end.
(*------------------------------------------------------------*)