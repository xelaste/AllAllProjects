/*---------------------------------------------------------------------
MODULE MAIN.C
       related files  MAIN.C  main program and function
		      Lexcalc.c - Lexical analyzer function.
		      PredPars.c - predictive parser functions
		      Lexcalc.h - definition header file
		      expr.cal  - file of data
       Description:  here  is main function for start the program.
-----------------------------------------------------------------------*/
#include <stdio.h>
#include <process.h>
#include "lexcalc.h"
List L;
extern List TestExpr(char *expr);
extern void stmt (void);
void main (int argc,char *argv[])
{
char expr[80];
int i;
FILE *Fp;

if (argc<2)
   {
   printf("\nInvalid number of arguments use predpars <file.cal>");
   exit(1);
   }

if ((Fp=fopen(argv[1],"rt"))==NULL)
   {
   printf("\nFile not found %s",argv[1]);
   exit(2);
   }
for(i=0;i<79&&!feof(Fp);expr[i]=fgetc(Fp),i++);
fclose(Fp);
expr[i-1]=0;
printf("\n%s",expr);
printf("\n     TOKEN      LEXENE  ATTRIBUTES");
printf("\n========== =========== ===========");
L=TestExpr(expr);
stmt();
}
/*----------------------------------------------------------------------*/