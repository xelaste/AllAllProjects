/*---------------------------------------------------------------------*/
/*                           MAIN.C                                    */
/*This programm aims is operation with polinoms - get polinom from     */
/*standard input (read_pol) , add one polinom to another(add_pol),     */
/*subtract polinoms(sub_pol),multiply polinoms (mul_pol) and           */
/*find differential of polinom(diff_pol)                               */
/*terminating programm with command HALT                               */
/*Function of interaction with user are in the file Main.C             */
/*Function of calculation are in the Polinom.C                         */
/*Specifications of function can be found in polinom.h                 */
/*---------------------------------------------------------------------*/
#include <stdio.h>
#include <conio.h>
#include "polinom.h"
#define Lenth_of_Command_Line 80
#define Operand_Length        10
#define PROMPT "Operation:"
enum OPERANDS {READ_POL=1,PRINT_POL,ADD_POL,MUL_POL,SUB_POL,DIFF_POL,HALT};
extern POLINOM THE_POLINOM [F-A+1];/*List of polinoms*/
/*------------------------------------------------------------------*/
void Ucase(char *L)
/*function for transform any letter in input string to Uppercase */
/*char *L input string                                           */
{
int i;
for (i=0;L[i];i++)
   if ((L[i]>='a')&&(L[i]<='z')) L[i]+='A'-'a';
}
/*-------------------------------------------------------------------*/
int Strcmp(char *S1,char *S2)
/*function for compare two strings. If there is an equations */
/*return 1 else  return 0.                                   */
/* S1,S2 input string to be compare                          */
{
int i;
for(i=0;(((S1[i])&&(S2[i]))&&(S1[i]==S2[i]));i++);
if(S1[i]!=S2[i]) return 0;
return 1;
}
/*-------------------------------------------------------------------*/
int OPERAND_(char *S)
/* function for decoding string to enum OPERAND */
/* S-string for decoding                        */
{
if (Strcmp(S,"READ_POL" ))  return READ_POL;
if (Strcmp(S,"PRINT_POL"))  return PRINT_POL;
if (Strcmp(S,"ADD_POL"   )) return ADD_POL;
if (Strcmp(S,"MUL_POL"   )) return MUL_POL;
if (Strcmp(S,"SUB_POL"   )) return SUB_POL;
if (Strcmp(S,"DIFF_POL" ))  return DIFF_POL;
if (Strcmp(S,"HALT" ))      return HALT;
return 0;
}
/*-------------------------------------------------------------------*/
void Init_String(char *S,int l)
/* Function for deleting existng string to lenth l  */
/* S string,l - lenth of string for delete          */
{
int i;
for (i=0;i<l;S[i]=0,i++);
}
/*-------------------------------------------------------------------*/
void GetNames(char *COMMAND_LINE,char *Name,int Num)
/* Function for getting names of polinom from the command line   */
/* COMMAND_LINE - name for decoding                              */
/* Name string for storing names                                 */
/* Num number of names to get                                    */
{
int i,j;
for(i=0;i<Num;i++)
  {
  for(j=0;COMMAND_LINE[j]==' ';j++);
  if(COMMAND_LINE[j]) Name[i]=COMMAND_LINE[j];
  LEFT(COMMAND_LINE,j+1);
  }
}

/*-------------------------------------------------------------------*/
void main ()
{
int i,OPERAND=0;
char COMMAND_LINE[Lenth_of_Command_Line];
char Instruction[Operand_Length],Name[4]={0,0,0,0};
init_polinoms();/*put zero to all polinoms */
Init_String(Instruction,Operand_Length);
do
 {
  printf(PROMPT);
  for(i=0;((COMMAND_LINE[i]=getchar())!='\n')&&(i<Lenth_of_Command_Line);i++);
  if (i>=Lenth_of_Command_Line) COMMAND_LINE[i-1]=0; /* mark end of string*/
     else                       COMMAND_LINE[i]=0;   /*                   */
  sscanf(COMMAND_LINE,"%s",&Instruction);
  Ucase(Instruction);
  LEFT(COMMAND_LINE,LEN (Instruction)+1);
  OPERAND=OPERAND_(Instruction);
  switch (OPERAND)
  {
  /* Get polinom from standard input */
  case READ_POL : GetNames(COMMAND_LINE,Name,1);
		  Ucase(Name);
		  if(read_pol(COMMAND_LINE,Name[0]))
		     printf("Polinom %s accepted\n",Name);
		     else
		     printf("Wrong definition of Polinom %s\n",Name);
		  break;
  /*Print polinom */
  case PRINT_POL: GetNames(COMMAND_LINE,Name,1);
		  Ucase(Name);
		  print_pol(Name[0]);
		  break;
  /* add one polinom to another and if name of third polinom inputed  */
  /* store result in third polinom else print it                      */
  case ADD_POL  : GetNames(COMMAND_LINE,Name,3);
		  if(Name[2]==0) Name[2]=' ';
		  Ucase(Name);
		  Call_Operand(Name[0],Name[1],Name[2],add_pol);
		  break;
  /* multiply  polinoms ,operating like addition                   */
  case MUL_POL  : GetNames(COMMAND_LINE,Name,3);
		  if(Name[2]==0) Name[2]=' ';
		  Ucase(Name);
		  Call_Operand(Name[0],Name[1],Name[2],mul_pol);
		  break;
  /* subtract polinoms                  */
  case SUB_POL  : GetNames(COMMAND_LINE,Name,3);
		  if(Name[2]==0) Name[2]=' ';
		  Ucase(Name);
		  Call_Operand(Name[0],Name[1],Name[2],sub_pol);
		  break;
  /*find differential of first polinom and store result in second */
  case DIFF_POL : GetNames(COMMAND_LINE,Name,2);
		  Ucase(Name);
		  Call_Operand(Name[0],Name[1],Name[2],diff_pol);
		  break;
  /* Terminate programm */
  case HALT     : break;
  default       : printf("No such command %s\n",Instruction);break;

  }
 Init_String(Instruction,LEN(Instruction));
 Init_String(Name,LEN(Name));
 }
while (OPERAND!=HALT);
}
/*----------------------------------------------------------------------*/
