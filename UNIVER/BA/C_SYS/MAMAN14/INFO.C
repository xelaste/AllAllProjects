#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <alloc.h>
#include "info.h"
static char *IMAGES []={"HALT","HELP","SHIFT","SAVE","LOAD","NEW","MOVE"};
static char *Menu[]={"\nHalt  - stop the game",
		     "\nHelp  - this text",
		     "\nShift - exchange sides",
		     "\nSave  - save current position to file",
		     "\nLoad  - load position from file      ",
		     "\nNew   - start new game               " ,
"\nOr input your move in format org-middle(optional)-dest: g3-h4"
		     };
/*----------------------------------------------------------------*/
void Ucase(char *L)
/*function for transform any letter in input string to Uppercase */
/*char *L input string                                           */
{
int i;
for (i=0;L[i];i++)
	if ((L[i]>='a')&&(L[i]<='z')) L[i]+='A'-'a';
}
/*-------------------------------------------------------------------*/
int LEN (char *L)
/* Function for calculate length of string L */
/* return integer - lentgh of string         */
{
int i;
for (i=0;L[i];i++);
return i;
}
/*-----------------------------------------------------------------*/
void LEFT (char *str,int s)
/*Function for shift string str toward left by s characters */
/*str stirng                                                */
/*s - lenth of shifting                                     */
{
int i,L;
L=LEN(str);
for (i=0;i<L;i++)
if (i+s<L) str[i]=str[i+s];
   else      str[i]=0;
}
/*-----------------------------------------------------------------*/
char *itoa(int N)
/*transform integer N to string s */
{
char *s;
int i,L,n=1,sign;
if((sign=N)<0) N*=(-1);
for (L=0;N>=n;n*=10,L++);/*compute number of digits*/
if (sign<=0) L++;
s=malloc(L+1);
s[L]='\0';
for(i=L-1;i>=0;i--)
   {
   s[i]=N%10+'0';
   N/=10;
   }
if(sign<0) s[0]='-';
return s;
}
/*-----------------------------------------------------------------*/
void InitString(char *S,int l)
/* Function for deleting existng string to lenth l  */
/* S string,l - lenth of string for delete          */
{
int i;
for (i=0;i<l;S[i]=0,i++);
}
/*-------------------------------------------------------------------*/
COMMAND_VALUE CVALUE (char *S)
/* transform string S to his enum value */
{
COMMAND_VALUE k;
for (k=HALT;strcmp(S,IMAGES[k])!=0&&k<MOVE;k++);
return k;
}
/*--------------------------------------------------------------------*/
char * CIMAGE (COMMAND_VALUE k)
/* transform enum k to his string image */
{
return  IMAGES[k];
}
/*---------------------------------------------------------------------*/
COMMAND_VALUE UserInput(char **command_line)
{
/*Accept user input from keyboard and decode it to command*/
/*parameter command_line get value of inputed string */
/*return accepted command                            */
char ch,line[100];
int i;
InitString(line,100);
printf("\nInput your move or word \"HELP\" for geting list of commands.");
printf("\n\\>");
for (i=0;((ch=getchar())!='\n'&&i<99);line[i]=ch,i++);
Ucase(line);
*command_line=(char *)malloc(strlen(line));
strcpy(*command_line,line);
return CVALUE(line);
}
/*---------------------------------------------------------------------*/
void ShowHelp(void)
/*this programm showing help text onto the screen */
{
COMMAND_VALUE command;
printf("\nCommand list");
for (command=HALT;command<=MOVE;command++)
    printf(Menu[command]);
printf("\nPress any key to continue");
getch();
}
/*---------------------------------------------------------------------*/
void InitPointList(struct POINT p[])
/*put zero to coordinates of the point from point list */
{
int i;
for(i=0;i<MoveLenth;p[i].col=p[i].row=0,i++);
}
/*---------------------------------------------------------------------*/
int StringToMove(char *mv,struct POINT p[])
/*transform string to move points */
/*mv string includes move         */
/*p   array of points in the move */
/*return number of points in the move*/
{
int N=0,L;
InitPointList(p);
while(*mv)
{
L=LEN(mv);
if (L>1&&mv[0]>='A'&&mv[0]<='H'&&mv[1]>='1'&&mv[1]<=MAXBDSIZE+'0')
   {p[N].col=mv[0]-'A'+1;
    p[N].row=mv[1]-'0';
    N++;
   }
   else return 0;
LEFT(mv,L<3?L:3);
}
return (N>1)?N:0;
}
/*---------------------------------------------------------------------*/