/*-----------------------------------------------------------------------
             C O M P I L E R  O F  T I N Y   L A N G U A G E
developed by Stekolchik Alexander 1998.
Module file TLA.C lexical analizer
       related files
       TQC.C       main function
       COMMON.H    common header file
       SCANNER.H  lexical analizer definitions and constants
       GSTACK.H  stack definitions and declarations
       GSTACK.C  common stack operation function
       HASH.H   hashtable header file
       HASH.C   hashtable functions
       STKENTRY H  parser stack definitions and declarations
       STKENTRY.C  parser stack function
       PARSER.H   parser header file
       PARS_TAB.C  definitions of LALR actions table and goto table
       PARSER.C    parser operation function
       SEMANTIC.H semantic actions constants
       SEMANTIC.C semantic action functions
---------------------------------------------------------------------------*/

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <process.h>
#include <alloc.h>
#include "scanner.h"
extern char msg[MsgLn];
/*-------------------------------------------------------------------------*/
char *tImageList[]={"Begin","Do","Else","End","Fi","If","Int","Od","Print",
		   "Prog","Read","Real","Then","Var","While",
		   "Id","Num","Relop","Plus","Minus","Mulop","Assignop",
		   "Left parantess","Right parantess","Comma","EndOfProgram",
		   "Colon","Semicolon","Empty","Illegal","EOF"};

char *keyword[]={"begin","do","else","end","fi","if","int","od","print",
		 "prog","read","real","then","var","while"};
Atrib StAtr[NumberOfStates];
sTransitionTableItem TransitionTable[NumberOfStates];
char *tIMAGE (tokentype t) {return tImageList[t];}
/*-------------------------------------------------*/
/* Function for checking if string s is keyword               */
/* return match token or 0 if the given string is not keyword */
/*------------------------------------------------------------*/
tokentype iskeyword(char *s)
{
tokentype i;
for(i=0;i<NUM_OF_KEYWORDS;i++)
   if (!strcmp(strlwr(s),keyword[i])) return i+1;
return FALSE;
}
/*----------------------------------------------------------*/
/* Transform Character ch to the terminal                   */
/*----------------------------------------------------------*/
abctype Char2Terminal(char ch)
{
 if(isdigit(ch)) return digit;
 if(islower(ch)) return letter;
 if(ch=='(') return lpar;
 if(ch==')') return rpar;
 if(ch=='.') return point;
 if(ch==':') return colon;
 if(ch=='=') return relop;
 if(ch=='+') return plus;
 if(ch=='*') return mul;
 if(ch=='/') return div;
 if(ch=='-') return minus;
 if(ch==';') return semicolon;
 if(ch==',') return comma;
 if(ch==' '||ch=='\t'||ch=='\n'||ch=='\0') return space;
 if(ch=='>') return grt;
 if(ch=='<') return less;
 if(ch==EOF)  return SCANOF;
 return invalid;
}
/*------------------------------------------------------*/
/* get current State of automata and accepted string and*/
/* return - token                                       */
/*------------------------------------------------------*/
token CreateToken(statetype State,char *Lexeme)
{
token NewItem;
  NewItem.T=StAtr[State].token;
  strcpy(NewItem.Lexeme,Lexeme);
  strcpy(NewItem.Atribute,StAtr[State].Atribute);
  return NewItem;
}
/*-----------------------------------------------------------*/
/* transition function of deterministic finite automata      */
/* get state S and terminal t  ,return next state of automata*/
/*-----------------------------------------------------------*/
statetype gotostate(statetype S,abctype t)
{
psTransitionItem hItem;
hItem=&TransitionTable[S];
while((hItem->t!=t)&&(hItem->t!=other)&&hItem->next!=NULL)hItem=hItem->next;
return hItem->S;
}
/*-----------------------------------------------------------*/
/* Create new transition                                     */
/*-----------------------------------------------------------*/
psTransitionItem CreateNewTransition(void)
{
return (psTransitionItem)malloc(sizeof(sTransitionTableItem));
}
/*-----------------------------------------------------------*/
/* Set transition function of automata. automata is built as */
/* linked list of states                                     */
/*-----------------------------------------------------------*/
void SetTransitionTable(void)
{
psTransitionItem hItem;

hItem=&TransitionTable[FIRST]; /* the start state of automata */
hItem->S=A;hItem->t=letter;hItem=hItem->next=CreateNewTransition();
hItem->S=B;hItem->t=digit;hItem=hItem->next=CreateNewTransition();
hItem->S=D;hItem->t=plus;hItem=hItem->next=CreateNewTransition();
hItem->S=E;hItem->t=minus;hItem=hItem->next=CreateNewTransition();
hItem->S=F;hItem->t=mul;hItem=hItem->next=CreateNewTransition();
hItem->S=F1;hItem->t=div;hItem=hItem->next=CreateNewTransition();
hItem->S=G;hItem->t=lpar;hItem=hItem->next=CreateNewTransition();
hItem->S=H;hItem->t=rpar;hItem=hItem->next=CreateNewTransition();
hItem->S=I;hItem->t=colon;hItem=hItem->next=CreateNewTransition();
hItem->S=K;hItem->t=relop;hItem=hItem->next=CreateNewTransition();
hItem->S=K1;hItem->t=grt;hItem=hItem->next=CreateNewTransition();
hItem->S=L;hItem->t=less;hItem=hItem->next=CreateNewTransition();
hItem->S=M;hItem->t=point;hItem=hItem->next=CreateNewTransition();
hItem->S=N;hItem->t=comma;hItem=hItem->next=CreateNewTransition();
hItem->S=O;hItem->t=semicolon;hItem=hItem->next=CreateNewTransition();
hItem->S=P;hItem->t=space;hItem=hItem->next=CreateNewTransition();
hItem->S=Q;hItem->t=SCANOF;hItem=hItem->next=CreateNewTransition();
hItem->S=INVALID;hItem->t=invalid;hItem->next=CreateNewTransition();
hItem->S=INVALID;hItem->t=other;hItem->next=NULL;

hItem=&TransitionTable[A];/* accept ID */
hItem->S=A;hItem->t=letter;hItem=hItem->next=CreateNewTransition();
hItem->S=A;hItem->t=digit;hItem=hItem->next=CreateNewTransition();
hItem->S=LAST;hItem->t=other;hItem->next=NULL;

hItem=&TransitionTable[B]; /* accept NUM */
hItem->S=B;hItem->t=digit;hItem=hItem->next=CreateNewTransition();
hItem->S=C;hItem->t=point;hItem=hItem->next=CreateNewTransition();
hItem->S=LAST;hItem->t=other;hItem->next=NULL;

hItem=&TransitionTable[C]; /* accept NUM */
hItem->S=C;hItem->t=digit;hItem=hItem->next=CreateNewTransition();
hItem->S=LAST;hItem->t=other;hItem->next=NULL;

hItem=&TransitionTable[D]; /* accept plus */
hItem->S=LAST;hItem->t=other;hItem->next=NULL;

hItem=&TransitionTable[E]; /* accept minus */
hItem->S=LAST;hItem->t=other;hItem->next=NULL;

hItem=&TransitionTable[F]; /* accept mul  */
hItem->S=LAST;hItem->t=other;hItem->next=NULL;

hItem=&TransitionTable[F1]; /* accept div */
hItem->S=LAST;hItem->t=other;hItem->next=NULL;

hItem=&TransitionTable[G]; /* accept lpar */
hItem->S=LAST;hItem->t=other;hItem->next=NULL;

hItem=&TransitionTable[H]; /* accept rpar */
hItem->S=LAST;hItem->t=other;hItem->next=NULL;

hItem=&TransitionTable[I]; /* accept colon */
hItem->S=J;hItem->t=relop;hItem=hItem->next=CreateNewTransition();
hItem->S=LAST;hItem->t=other;hItem->next=NULL;

hItem=&TransitionTable[J]; /* accept assign op*/
hItem->S=LAST;hItem->t=other;hItem->next=NULL;

hItem=&TransitionTable[K]; /* accept equal  */
hItem->S=LAST;hItem->t=other;hItem->next=NULL;

hItem=&TransitionTable[K1]; /* accept  grt */
hItem->S=LAST;hItem->t=other;hItem->next=NULL;

hItem=&TransitionTable[L]; /* accept less */
hItem->S=L1;hItem->t=grt;hItem=hItem->next=CreateNewTransition();
hItem->S=LAST;hItem->t=other;hItem->next=NULL;

hItem=&TransitionTable[L1]; /* accept  not equal */
hItem->S=LAST;hItem->t=other;hItem->next=NULL;


hItem=&TransitionTable[M]; /* accept point */
hItem->S=LAST;hItem->t=other;hItem->next=NULL;

hItem=&TransitionTable[N]; /* accept comma */
hItem->S=LAST;hItem->t=other;hItem->next=NULL;

hItem=&TransitionTable[O]; /* accept semicolon */
hItem->S=LAST;hItem->t=other;hItem->next=NULL;

hItem=&TransitionTable[P]; /* accept spaces and tabs and new lines */
hItem->S=P;hItem->t=space;hItem=hItem->next=CreateNewTransition();
hItem->S=Q;hItem->t=SCANOF;hItem=hItem->next=CreateNewTransition();
hItem->S=LAST;hItem->t=other;hItem->next=NULL;

hItem=&TransitionTable[Q]; /* accept eof */
hItem->S=LAST;hItem->t=other;hItem->next=NULL;

hItem=&TransitionTable[INVALID]; /* process invalid terminal */
hItem->S=INVALID;hItem->t=invalid;hItem=hItem->next=CreateNewTransition();
hItem->S=LAST;hItem->t=other;hItem->next=NULL;

/*------------------------*/
/* set states atrributes  */
/*------------------------*/

StAtr[FIRST].token=tEmpty; StAtr[FIRST].OK=TRUE;
StAtr[FIRST].Atribute=EmptyString;

StAtr[A].token=tId;   StAtr[A].OK=TRUE;StAtr[A].Atribute=EmptyString;
StAtr[B].token=tNum;  StAtr[B].OK=TRUE; StAtr[B].Atribute=INTEGER;
StAtr[C].token=tNum;  StAtr[C].OK=TRUE; StAtr[C].Atribute=REAL;
StAtr[D].token=tPlus; StAtr[D].OK=TRUE; StAtr[D].Atribute=EmptyString;
StAtr[E].token=tMinus;StAtr[E].OK=TRUE; StAtr[E].Atribute=EmptyString;
StAtr[F].token=tMulop;StAtr[F].OK=TRUE; StAtr[F].Atribute=MULTIPLY;
StAtr[F1].token=tMulop;StAtr[F1].OK=TRUE; StAtr[F1].Atribute=DIVIDE;
StAtr[G].token=tLpar; StAtr[G].OK=TRUE; StAtr[G].Atribute=EmptyString;
StAtr[H].token=tRpar; StAtr[H].OK=TRUE; StAtr[H].Atribute=EmptyString;
StAtr[I].token=tColon;StAtr[I].OK=TRUE; StAtr[I].Atribute=EmptyString;
StAtr[J].token=tAssignop;StAtr[J].OK=TRUE; StAtr[J].Atribute=EmptyString;
StAtr[K].token=tRelop;StAtr[K].OK=TRUE; StAtr[K].Atribute=EQL;
StAtr[K1].token=tRelop;StAtr[K1].OK=TRUE; StAtr[K1].Atribute=GRT;
StAtr[L].token=tRelop;StAtr[L].OK=TRUE; StAtr[L].Atribute=LSS;
StAtr[L1].token=tRelop;StAtr[L1].OK=TRUE; StAtr[L1].Atribute=NEQL;
StAtr[M].token=tEndOfProgram;StAtr[M].OK=TRUE;
			      StAtr[M].Atribute="End of program";
StAtr[N].token=tComma; StAtr[N].OK=TRUE; StAtr[N].Atribute=EmptyString;
StAtr[O].token=tSemicolon;StAtr[O].OK=TRUE;StAtr[O].Atribute=EmptyString;
StAtr[P].token=tEmpty;StAtr[P].OK=FALSE;StAtr[P].Atribute=EmptyString;
StAtr[Q].token=tEof  ;StAtr[Q].OK=FALSE;StAtr[Q].Atribute=EmptyString;

StAtr[INVALID].token=tIllegal;StAtr[INVALID].OK=FALSE;
StAtr[INVALID].Atribute="Illegal character";;
}
/*-------------------------------------------------------
function for read line from the input file
input fp pointer to input file
     ln buffer there characters are stored
     len lenth of the buffer
-------------------------------------------------------*/
void freadln(FILE *fp, char *Ln,int len)
{
int i=0;
memset(Ln,'\0',len);
for (i=0;(i<len)&&((Ln[i]=fgetc(fp))!=EOF)&&(Ln[i]!='\n');i++);
}
/*-------------------------------------------------------*/
/* Function for printing current token                   */
/*-------------------------------------------------------*/
void PrintToken(token Item,FILE *fp)
{
if(Item.T!=tEmpty&&Item.T!=tIllegal)
  fprintf(fp,
	 "%-15s %-30s %-10s\n",tIMAGE(Item.T),Item.Lexeme,Item.Atribute);
}
/*-----------------------------------------------------*/
/*Get next token from the input file                   */
/* parmeters fp - pointer to input file                */
/*           lf - pointer to list file                 */
/*return pointer to next not empty token               */
/*-----------------------------------------------------*/
token *GetToken(FILE *fp,FILE *lf)
{
char ch,lexeme[MaxIdLen+1];
int j=0;
tokentype keyword;
static int line_counter=0;
static int wc=0;
static BOOL newline=TRUE;
static char buf[InputLineLen+1]={'\0'};
statetype sCurr=FIRST,sPrev;
abctype terminal=tEmpty;
token *tptr,newtoken={tEmpty,"",""};
memset(lexeme,'\0',MaxIdLen+1);

j=0;
while((newtoken.T==tEmpty)||(newtoken.T==tIllegal)){
     if(newline){
	     newline=FALSE;
	     freadln(fp,buf,InputLineLen+1);
	     line_counter++;
	     sprintf(msg,"%4d.  %s",line_counter,buf);
	     PrintMsgAndClear(lf);
     }
     ch=buf[wc];
     wc++;
     if ((ch==EOF)||(ch=='\n')||(!buf[wc])) {newline=TRUE;wc=0;}
     terminal=Char2Terminal(ch);
     lexeme[j]=ch==EOF?' ':ch;
     if(ch=='\n') lexeme[j]=' ';
     sPrev=sCurr;
     sCurr=gotostate(sCurr,terminal);
     j++;
     if(sCurr==LAST||strlen(lexeme)>MaxIdLen) {
     if(sPrev!=FIRST) {
       if(wc) wc--;
       lexeme[--j]=0;
       }/*back for one character */
     newtoken=CreateToken(sPrev,lexeme);
     if (newtoken.T==tIllegal) {
	sprintf(msg,"Line %d %s %s\n",line_counter,
					    newtoken.Atribute,lexeme);
	PrintMessage(lf);
	PrintMsgAndClear(stderr);
	}
    sCurr=(sCurr==LAST?FIRST:sCurr);
    j=0;
    memset(lexeme,'\0',MaxIdLen+1);
    if (terminal==SCANOF) break;
    }
   }
if((keyword=iskeyword(newtoken.Lexeme))!=0) {
  newtoken.T=keyword-1;/* begin=0 */
  strcpy(newtoken.Atribute,"Keyword");
  }

tptr=(token *)malloc(sizeof(token));
if(tptr==NULL) {
		 fprintf(stderr,"Malloc failed.\n");
		 exit(1);
	       }
memcpy(tptr,&newtoken,sizeof(token));
return tptr;
}
/*-----------------------------------------------------*/
