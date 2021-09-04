/*---------------------------------------------------------------------
MODULE LEXALC.C
       related files  LEXCALC.C  main program and function
		      Lexcalc.h - definition header file
		      expr.cal  - file of data
       Description:  here  are all the function needed to perform
		     Lexical analyzer.
-----------------------------------------------------------------------*/
#include <stdio.h>
#include "lexcalc.h"

int TestExpr(char *expr);

void main ()
{
char *INPUT="EXPR.CAL",expr[80];
int i;
FILE *Fp=fopen(INPUT,"rt");
for(i=0;i<79&&!feof(Fp);expr[i]=fgetc(Fp),i++);
fclose(Fp);
expr[i-1]=0;
printf("\n     TOKEN      LEXENE  ATTRIBUTES");
printf("\n========== =========== ===========");
TestExpr(expr);
}
/*-------------------------------------------------------------*/
/*  SET transition function delta                              */
/*-------------------------------------------------------------*/
void SetDelta(void)
{
int i,j;
for (i=0;i<11;i++)
    for(j=0;j<9;DELTA[i][j]=LAST,j++);
DELTA[FIRST][digit]=C; DELTA[FIRST][op]=A; DELTA[FIRST][lBracket]=F;
DELTA[FIRST][rBracket]=G; DELTA[FIRST][relop]=H; DELTA[FIRST][var]=J;
DELTA[FIRST][end]=I;DELTA[FIRST][point]=B;

DELTA[A][digit]=C; DELTA[A][op]   =B;
DELTA[C][digit]=C; DELTA[C][point]=D; DELTA[D][digit]=E; DELTA[E][digit]=E;

DELTA[F][lBracket]=F; DELTA[F][rBracket]=G;

DELTA[I][digit]=B; DELTA[I][op]=B; DELTA[I][lBracket]=B;
DELTA[I][rBracket]=B; DELTA[I][relop]=B; DELTA[I][var]=B;
DELTA[I][end]=B; DELTA[I][point]=B;

StAttr[FIRST].Token=tEMPTY; StAttr[FIRST].OK=FALSE;
StAttr[FIRST].desc=IMAGE(tEMPTY);

StAttr[A].Token=tOP; StAttr[A].OK=TRUE;StAttr[A].desc=IMAGE(tOP);

StAttr[B].Token=tILLEGAL; StAttr[B].OK=FALSE;
StAttr[B].desc=IMAGE(tILLEGAL);

StAttr[C].Token=tNUM; StAttr[C].OK=TRUE;StAttr[C].desc="INT";

StAttr[D].Token=tILLEGAL; StAttr[D].OK=FALSE; StAttr[D].desc="BAD NUM";

StAttr[E].Token=tNUM; StAttr[E].OK=TRUE; StAttr[E].desc="FLOAT";

StAttr[F].Token=tlBRACKETs; StAttr[F].OK=TRUE;
StAttr[F].desc=IMAGE(tlBRACKETs);

StAttr[G].Token=trBRACKETs; StAttr[G].OK=TRUE;
StAttr[G].desc=IMAGE(trBRACKETs);

StAttr[H].Token=tRELOP; StAttr[H].OK=TRUE;
StAttr[H].desc=IMAGE(tRELOP);

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
/*---------------------------------------------------------*/
/* translate input character to match token                */
/*---------------------------------------------------------*/
token Char2Terminal(char ch)
{
if(ch>='0'&&ch<='9') return digit;
if(ch=='(') return lBracket;
if(ch==')') return rBracket;
if(ch=='.') return point;
if(ch=='X') return var;
if(ch=='=') return relop;
if(ch=='+'||ch=='-'||ch=='*'||ch=='/') return op;
if(ch==';') return end;
return other;
}
/*-----------------------------------------------------------*/
int TestExpr(char *expr)
{
States Curr=FIRST,Prev;
terminals Terminal=Char2Terminal(expr[0]);
char ch,lexene[10];
int i=0,j,TokenCounter=0;
SetDelta();
do
{
 for(j=0;j<10;lexene[j]=0,j++);
 Curr=FIRST;
 j=0;
 while (Curr!=LAST)
     {
     Terminal=Char2Terminal(expr[i]);
     lexene[j]=expr[i];
     Prev=Curr;
     Curr=DELTA[Curr][Terminal];
     j++;
     i++;
     }
 TokenCounter++;
 if (Prev!=FIRST) {i--;lexene[--j]=0;} /*back for one character */
 PrintToken(lexene,Prev);
}
while (expr[i]);
return TokenCounter;
}
/*----------------------------------------------------------------*/