/*---------------------------------------------------------------------
MODULE LEXALC.C
       related files Main.C - main function module
		     Lexcalc.c - Lexical analyzer function.
		     PredPars.c - predictive parser functions
		     Lexcalc.h - definition header file
		     expr.cal  - file of data
       Description:  here  are all the function needed to perform
		     Lexical analyzer.
-----------------------------------------------------------------------*/
#include <stdio.h>
#include <alloc.h>
#include "lexcalc.h"
/*-------------------------------------------------------------*/
/*  SET transition function delta                              */
/*-------------------------------------------------------------*/
char *ImageList[]={"NUM","PLUS","MINUS","MUL","DIV","lBRACKET","rBRACKET",
		   "VAR","RELOP","END","ILLEGAL","EMPTY"};
States  DELTA[NUM_OF_STATES][NUM_OF_TOKEN];
Attrib StAttr[NUM_OF_STATES];
char *IMAGE (token t) {return ImageList[t];}
/*-------------------------------------------------------------*/
void SetDelta(void)
{
int i,j;
for (i=0;i<NUM_OF_STATES;i++)
    for(j=0;j<NUM_OF_TOKEN;DELTA[i][j]=LAST,j++);

DELTA[FIRST][digit]=C; DELTA[FIRST][plus]=A;DELTA[FIRST][minus]=M;
DELTA[FIRST][mul]=N;DELTA[FIRST][div]=O;
DELTA[FIRST][lBracket]=F;DELTA[FIRST][rBracket]=G; DELTA[FIRST][relop]=H;
DELTA[FIRST][var]=J;DELTA[FIRST][end]=I;DELTA[FIRST][point]=B;

DELTA[A][plus]=B;DELTA[A][minus]=B;DELTA[A][mul]=B;DELTA[A][div]=B;
DELTA[M][plus]=B;DELTA[M][minus]=B;DELTA[M][mul]=B;DELTA[M][div]=B;
DELTA[N][plus]=B;DELTA[N][minus]=B;DELTA[N][mul]=B;DELTA[N][div]=B;
DELTA[O][plus]=B;DELTA[O][minus]=B;DELTA[O][mul]=B;DELTA[O][div]=B;

DELTA[C][digit]=C;DELTA[C][point]=D;
DELTA[D][digit]=E; DELTA[E][digit]=E;

DELTA[I][digit]=B; DELTA[I][plus]=B; DELTA[I][lBracket]=B;
DELTA[I][rBracket]=B; DELTA[I][relop]=B; DELTA[I][var]=B;
DELTA[I][end]=B;DELTA[I][point]=B; DELTA[I][minus]=B;
DELTA[I][div]=B;DELTA[I][mul]=B; DELTA[I][minus]=B;

StAttr[FIRST].Token=tEMPTY; StAttr[FIRST].OK=FALSE;
StAttr[FIRST].desc=IMAGE(tEMPTY);

StAttr[A].Token=tPLUS;StAttr[A].OK=TRUE;StAttr[A].desc=IMAGE(tPLUS);
StAttr[M].Token=tMINUS; StAttr[M].OK=TRUE; StAttr[M].desc=IMAGE(tMINUS);
StAttr[N].Token=tMUL ;StAttr[N].OK=TRUE;StAttr[N].desc=IMAGE(tMUL);
StAttr[O].Token=tDIV ;StAttr[O].OK=TRUE;StAttr[O].desc=IMAGE(tDIV);

StAttr[B].Token=tILLEGAL; StAttr[B].OK=FALSE;
StAttr[B].desc="Illegall input - have been removed from statement";

StAttr[C].Token=tNUM; StAttr[C].OK=TRUE;StAttr[C].desc="INT";

StAttr[D].Token=tILLEGAL; StAttr[D].OK=FALSE; StAttr[D].desc="BAD NUM";

StAttr[E].Token=tNUM; StAttr[E].OK=TRUE; StAttr[E].desc="FLOAT";

StAttr[F].Token=tlBRACKET; StAttr[F].OK=TRUE;
StAttr[F].desc=IMAGE(tlBRACKET);

StAttr[G].Token=trBRACKET; StAttr[G].OK=TRUE;
StAttr[G].desc=IMAGE(trBRACKET);

StAttr[H].Token=tRELOP; StAttr[H].OK=TRUE;StAttr[H].desc=IMAGE(tRELOP);

StAttr[J].Token=tVAR; StAttr[J].OK=TRUE;
StAttr[J].desc=IMAGE(tVAR);

StAttr[I].Token=tEND; StAttr[I].OK=TRUE; StAttr[I].desc=IMAGE(tEND);

}
/*-------------------------------------------------------*/
/* Function for printing current token                   */
/*-------------------------------------------------------*/
void PrintToken(char *Lexene,States State)
{
if(StAttr[State].Token!=tEMPTY)
   printf("\n%10s %10s %10s",IMAGE(StAttr[State].Token),Lexene,
					     StAttr[State].desc);
}
/*--------------------------------------------------*/
#include <string.h>
ListP InsertToken2List(States State,char *Lexeme,ListP item)
{
ListP NewItem;
if (StAttr[State].Token!=tEMPTY&&StAttr[State].Token!=tILLEGAL)
  {
  NewItem=(ListP) malloc(sizeof(List));
  NewItem->T=StAttr[State].Token;
  NewItem->Lexeme=(char *)malloc(strlen(Lexeme)+1);
  strcpy(NewItem->Lexeme,Lexeme);
  NewItem->next=NULL;
  if (item==NULL) item=NewItem;
     else         item->next=NewItem;
  return NewItem;
  }
  else return item;

}
/*---------------------------------------------------------*/
/* translate input character to match token                */
/*---------------------------------------------------------*/
terminals Char2Terminal(char ch)
{
if(ch>='0'&&ch<='9') return digit;
if(ch=='(') return lBracket;
if(ch==')') return rBracket;
if(ch=='.') return point;
if(ch=='X') return var;
if(ch=='=') return relop;
if(ch=='+') return plus;
if(ch=='*') return mul;
if(ch=='/') return div;
if(ch=='-') return minus;
if(ch==';') return end;
return other;
}
/*-----------------------------------------------------------*/
List TestExpr(char *expr)
{
States Curr=FIRST,Prev;
terminals Terminal=Char2Terminal(expr[0]);
char ch,lexeme[10];
int i=0,j,TokenCounter=0;
ListP tFirst=NULL,tLast=NULL;
SetDelta();
do
{
 for(j=0;j<10;lexeme[j]=0,j++);
 Curr=FIRST;
 j=0;
 while (Curr!=LAST)
     {
     Terminal=Char2Terminal(expr[i]);
     lexeme[j]=expr[i];
     Prev=Curr;
     Curr=DELTA[Curr][Terminal];
     if(Curr==J)
	DELTA[Prev][Terminal]=B;
     j++;
     i++;
     }
 TokenCounter++;
 if (Prev!=FIRST) {i--;lexeme[--j]=0;} /*back for one character */
 PrintToken(lexeme,Prev);
 tLast=InsertToken2List(Prev,lexeme,tLast);
 if(tFirst==NULL) tFirst=tLast;
}
while (expr[i]);
return *tFirst;
}
/*----------------------------------------------------------------*/