/*---------------------------------------------------------------------
MODULE PREDPARS.C
       related files Main.C - main function module
		     Lexcalc.c - Lexical analyzer function.
		     PredPars.c - predictive parser functions
		     Lexcalc.h - definition header file
		     expr.cal  - file of data
       Description:  here  are all the function needed to perform
		     Predictive parsing.
/*-----------------------------------------------------------------------*/
/*                    GRAMMAR FOR CALCULATOR LANGUAGE
* stmt     --><expr=expr><tEND>
* expr     --><-Sum><expr_tail>||<Sum><expr_tail>
* expr_tail--><+Sum><expr_tail>||<-Sum><expr_tail>||nothing
* Sum      --><MulDiv><Sum_tail>
* Sum_tail --><*MulDiv><Sum_tail>||</Mul><Sum_tail>||nothing
* Mul      -->(expr)||NUM||VAR
/*------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <alloc.h>
#include "lexcalc.h"
extern char *IMAGE (token t);
extern List L;
ListP pTokenList=&L; /*pointer to current token in the list */
void stmt (void);
void expr (void);
void expr_tail (void);
void sum  (void);
void sum_tail(void);
void muldiv (void);
static void syntax_error(char *message,token t);
int line_num=1;
static token next_tok=tEMPTY;
static int WasError=0;
/*------------------------------------------------------------*/
static void syntax_error(char *message,token t)
{
 fprintf(stderr,"\nUnexpected input - %s %s",message,IMAGE(t));
 WasError++;
}
/*-------------------------------------------------------------*/
token scanner (void)
{
token retval;
if (pTokenList==NULL)
    {
    line_num++;
    return tSCANOF;
    }
retval=pTokenList->T;
pTokenList=pTokenList->next;
return retval;
}
/*-------------------------------------------------------------*/
token next_token(void)
{
if(next_tok==tEMPTY)
	next_tok=scanner();
return next_tok;
}
/*-------------------------------------------------------------*/
void match(token tok)
{
if(next_tok==tEMPTY)
   next_tok=scanner();
   if(next_tok!=tok)
     syntax_error(" read token",next_tok);
     next_tok=tEMPTY;
}
/*------------------------------------------------------------------*/
void stmt(void)
{
ListP Prev;
expr();
match(tRELOP);
expr();
match(tEND);
match(tSCANOF);
if(!WasError)
  {
  printf("\nStatement is OK\n");
  pTokenList=&L;
  while(pTokenList!=NULL)
       {
       printf("%s",pTokenList->Lexeme);
       Prev=pTokenList;
       pTokenList=pTokenList->next;
       if(Prev!=&L) free(Prev);
       }
  }
}
/*--------------------------------------------------------------------*/
void expr(void)
{
token t=next_token();
if (t==tMINUS) match(tMINUS);
 sum();
 expr_tail();
}
/*--------------------------------------------------------------------*/
void expr_tail (void)
{
token t=next_token();
if (t==tPLUS||t==tMINUS)
   {
   if (t==tPLUS) match(tPLUS);
      else       match(tMINUS);
   sum();
   expr_tail();
   }
}
/*---------------------------------------------------------------------*/
void sum  (void)
{
muldiv();
sum_tail();
}
/*---------------------------------------------------------------------*/
void sum_tail(void)
{
token t=next_token();
if (t==tMUL||t==tDIV)
   {
   if (t==tDIV) match(tDIV);
      else      match(tMUL);
   muldiv();
   sum_tail();
   }
}
/*---------------------------------------------------------------------*/
void muldiv (void)
{
token t=next_token();
switch (t)
   {
   case tlBRACKET:match(tlBRACKET);
		  expr();
		  match(trBRACKET);
		  break;
   case tNUM     :match(tNUM);
		  break;
   case tVAR     :match(tVAR);
		  break;
   default       :syntax_error(" number or expression or x expected",t);
   }

}
/*-------------------------------------------------------------------*/
