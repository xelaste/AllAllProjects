/*-----------------------------------------------------------------------
   L E X I C A L   A N A L I Z E R   O F   T I N Y   L A N G U A G E
Module file TLA.C
	    related files  TLA.H definitions
			   TLA.C  functions;
			   *.TIN file of data
-------------------------------------------------------------------------*/
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <process.h>
#include <alloc.h>
#include "tla.h"
/*-------------------------------------------------------------------------*/
char *ImageList[]={"Begin","Do","Else","End","Fi","If","Int","Od","Print",
		   "Prog","Read","Real","Then","Var","While",
		   "Id","Num","Relop","Plus","Minus","Mulop","Assignop",
		   "Left parantess","Right parantess","Comma","EndOfProgram",
		   "Colon","Semicolon","Empty","Illegal","EOF"};

char *keyword[]={"begin","do","else","end","fi","if","int","od","print",
		 "prog","read","real","then","var","while"};
Attrib StAttr[NumberOfStates];
sTransitionTableItem TransitionTable[NumberOfStates];
char *IMAGE (tokentype t) {return ImageList[t];}
/*-------------------------------------------------*/
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

/*------------------------------------------------------------*/
/* Function for checking if string s is keyword               */
/* return match token or 0 if the given string is not keyword */
/*------------------------------------------------------------*/
tokentype iskeyword(char *s)
{
tokentype i;
for(i=0;i<NUM_OF_KEYWORDS;i++)
   if (!strcmp(s,keyword[i])) return i;
return FALSE;
}
/*----------------------------------------------------------*/
/* Transform Character ch to the terminal                   */
/*----------------------------------------------------------*/
terminaltype Char2Terminal(char ch)
{
 if(isdigit(ch)) return digit;
 if(isalpha(ch)) return letter;
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
  NewItem.T=StAttr[State].token;
  NewItem.Lexeme=(char *)malloc(strlen(Lexeme)+1);
  strcpy(NewItem.Lexeme,Lexeme);
  NewItem.Attribute=StAttr[State].Attribute;
  return NewItem;
}
/*-----------------------------------------------------------*/
/* transition function of deterministic finite automata      */
/* get state S and terminal t  ,return next state of automata*/
/*-----------------------------------------------------------*/
statetype gotostate(statetype S,terminaltype t)
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
hItem->S=F;hItem->t=div;hItem=hItem->next=CreateNewTransition();
hItem->S=G;hItem->t=lpar;hItem=hItem->next=CreateNewTransition();
hItem->S=H;hItem->t=rpar;hItem=hItem->next=CreateNewTransition();
hItem->S=I;hItem->t=colon;hItem=hItem->next=CreateNewTransition();
hItem->S=K;hItem->t=relop;hItem=hItem->next=CreateNewTransition();
hItem->S=K;hItem->t=grt;hItem=hItem->next=CreateNewTransition();
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

hItem=&TransitionTable[F]; /* accept mul or div */
hItem->S=LAST;hItem->t=other;hItem->next=NULL;

hItem=&TransitionTable[G]; /* accept lpar */
hItem->S=LAST;hItem->t=other;hItem->next=NULL;

hItem=&TransitionTable[H]; /* accept rpar */
hItem->S=LAST;hItem->t=other;hItem->next=NULL;

hItem=&TransitionTable[I]; /* accept colon and assign op*/
hItem->S=J;hItem->t=relop;hItem=hItem->next=CreateNewTransition();
hItem->S=LAST;hItem->t=other;hItem->next=NULL;

hItem=&TransitionTable[J]; /* accept colon and assign op*/
hItem->S=LAST;hItem->t=other;hItem->next=NULL;

hItem=&TransitionTable[K]; /* accept equal or grt */
hItem->S=LAST;hItem->t=other;hItem->next=NULL;

hItem=&TransitionTable[L]; /* accept different <> */
hItem->S=K;hItem->t=grt;hItem=hItem->next=CreateNewTransition();
hItem->S=LAST;hItem->t=other;hItem->next=NULL;

hItem=&TransitionTable[M]; /* accept point */
hItem->S=M;hItem->t=space;hItem=hItem->next=CreateNewTransition();
hItem->S=LAST;hItem->t=SCANOF;hItem=hItem->next=CreateNewTransition();
hItem->S=R;hItem->t=other;hItem->next=NULL;

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

hItem=&TransitionTable[R]; /* characters after end of programm */
hItem->S=LAST;hItem->t=SCANOF;hItem=hItem->next=CreateNewTransition();
hItem->S=R;hItem->t=other;hItem->next=NULL;

hItem=&TransitionTable[INVALID]; /* process invalid terminal */
hItem->S=INVALID;hItem->t=invalid;hItem=hItem->next=CreateNewTransition();
hItem->S=LAST;hItem->t=other;hItem->next=NULL;

/*------------------------*/
/* set states atrributes  */
/*------------------------*/

StAttr[FIRST].token=tEmpty; StAttr[FIRST].OK=TRUE;
StAttr[FIRST].Attribute="";

StAttr[A].token=tId;   StAttr[A].OK=TRUE; StAttr[A].Attribute=EmptyString;
StAttr[B].token=tNum;  StAttr[B].OK=TRUE; StAttr[B].Attribute="Integer";
StAttr[C].token=tNum;  StAttr[C].OK=TRUE; StAttr[C].Attribute="Real";
StAttr[D].token=tPlus; StAttr[D].OK=TRUE; StAttr[D].Attribute=EmptyString;
StAttr[E].token=tMinus;StAttr[E].OK=TRUE; StAttr[E].Attribute=EmptyString;
StAttr[F].token=tMulop;StAttr[F].OK=TRUE; StAttr[F].Attribute=EmptyString;
StAttr[G].token=tLpar; StAttr[G].OK=TRUE; StAttr[G].Attribute=EmptyString;
StAttr[H].token=tRpar; StAttr[H].OK=TRUE; StAttr[H].Attribute=EmptyString;
StAttr[I].token=tColon;StAttr[I].OK=TRUE; StAttr[I].Attribute=EmptyString;
StAttr[J].token=tAssignop;StAttr[J].OK=TRUE; StAttr[J].Attribute=EmptyString;
StAttr[K].token=tRelop;StAttr[K].OK=TRUE; StAttr[K].Attribute=EmptyString;
StAttr[L].token=tRelop;StAttr[L].OK=TRUE; StAttr[L].Attribute=EmptyString;
StAttr[M].token=tEndOfProgram;StAttr[M].OK=TRUE;
			      StAttr[M].Attribute="End of program";
StAttr[N].token=tComma; StAttr[N].OK=TRUE; StAttr[N].Attribute=EmptyString;
StAttr[O].token=tSemicolon;StAttr[O].OK=TRUE;StAttr[O].Attribute=EmptyString;
StAttr[P].token=tEmpty;StAttr[P].OK=FALSE;StAttr[P].Attribute=EmptyString;
StAttr[Q].token=tIllegal;StAttr[Q].OK=FALSE;
StAttr[Q].Attribute="There is not point at the end of program";
StAttr[R].token=tIllegal;StAttr[R].OK=FALSE;
StAttr[R].Attribute="Illegal characters after the program end";

StAttr[INVALID].token=tIllegal;StAttr[INVALID].OK=FALSE;
StAttr[INVALID].Attribute="Illegal character";;
}
/*-------------------------------------------------------*/
/* Function for printing current token                   */
/*-------------------------------------------------------*/
void PrintToken(token Item,FILE *fp)
{
if(Item.T!=tEmpty&&Item.T!=tIllegal)
  fprintf(fp,"%-15s %-30s %-10s\n",IMAGE(Item.T),Item.Lexeme,Item.Attribute);
}
/*-----------------------------------------------------*/
/*Get next token from the input file                   */
/* parmeters fp - pointer to input file                */
/*           lf - pointer to list file                 */
/*return next not empty token                          */
/*-----------------------------------------------------*/
token GetToken(FILE *fp,FILE *lf)
{
char ch,lexeme[MaxIdLen+1],*num;
int i,j=0;
tokentype keyword;
static int line_counter=1;
static char InputLine[InputLineLen+1]={'\0'};
statetype sCurr=FIRST,sPrev;
terminaltype terminal=tEmpty;
token newtoken={tEmpty,"",""};
memset(lexeme,'\0',MaxIdLen+1);
if (!strlen(InputLine)){
    strcpy(InputLine,strcat(num=itoa(line_counter),".  "));
    free(num);
    }
i=strlen(InputLine);
while((newtoken.T==tEmpty)||(newtoken.T==tIllegal)){
   ch=fgetc(fp);
   terminal=Char2Terminal(ch);
   if (InputLine[strlen(InputLine)-1]=='\n'||ch==EOF){
      InputLine[i-1]=ch==EOF?'\n':InputLine[i-1];
      fprintf(lf,"%s",InputLine);
      line_counter++;
      memset(InputLine,'\0',InputLineLen+1);
      strcpy(InputLine,strcat((num=itoa(line_counter)),".  "));
      i=strlen(InputLine);
      free(num);
      if (ch=='\n') {ch=' ';i++;}
      }
   InputLine[i-1]=lexeme[j]=ch==EOF?' ':ch;
   if(ch=='\n') lexeme[j]=' ';
   sPrev=sCurr;
   sCurr=gotostate(sCurr,terminal);
   i++;j++;
   if(sCurr==LAST||strlen(lexeme)>MaxIdLen) {
     if(sPrev!=FIRST) {
       ungetc(ch,fp);
       InputLine[--i]=0;
       lexeme[--j]=0;
       }/*back for one character */
     newtoken=CreateToken(sPrev,lexeme);
     if (newtoken.T==tIllegal) {
       fprintf(lf,"Line %d %s %s\n",line_counter-1,
				    newtoken.Attribute,lexeme);
       fprintf(stderr,"Line %d %s %s\n",line_counter-1,
					newtoken.Attribute,lexeme);
	}
    sCurr=(sCurr==LAST?FIRST:sCurr);
    j=0;
    memset(lexeme,'\0',MaxIdLen+1);
    if (terminal==SCANOF) break;
    }
   }
if((keyword=iskeyword(newtoken.Lexeme))!=0) {
  newtoken.T=keyword;
  newtoken.Attribute="Keyword";
  }
return newtoken;
}
/*-----------------------------------------------------*/
void main (int argc,char **argv)
{
char extention[5],list[40],tok[40];
int i,l;
FILE *fp,*lf,*tf;
fprintf(stderr,"%s\n",CopyRight);
if (argc!=2) {fprintf(stderr,"Usage tla file_name\n"); exit(1);}
for(i=0;i<4;i++)
    extention[i]=tolower(argv[1][strlen(argv[1])-4+i]);
    extention[4]='\0';
if(strcmp(LEGAL_FILE_EXTENTION,extention))
  {
  fprintf(stderr,"\nExtention of the source file should be tin\n");
  exit(2);
  }
if((fp=fopen(argv[1],"rt"))==NULL)
  {
  fprintf(stderr,"Source file %s not found\n",argv[1]);
  exit(3);
  }
  strcpy(list,argv[1]);
  l=strlen(list);for(i=0;i<3;list[l-i-1]=0,i++);
  strcat(list,"lst");
  strcpy(tok,argv[1]);
  l=strlen(tok);for(i=0;i<3;tok[l-i-1]=0,i++);
  strcat(tok,"tok");
  lf=fopen(list,"wt");
  tf=fopen(tok,"wt");
  fprintf(lf,"%s\n",CopyRight);
  fprintf(tf,"%s\n",CopyRight);
  fprintf(tf,"\n%-15s %-30s %s\n","TOKEN","LEXEME","ATTRIBUTE");
  fprintf(tf,"%-15s %-30s %s\n","-----","------","---------");
  SetTransitionTable();
  while(!feof(fp))
  {
  PrintToken(GetToken(fp,lf),tf);
  }
  fclose(fp);
  fclose(lf);
  fclose(tf);
}
/*-------------------------------------------------------*/
