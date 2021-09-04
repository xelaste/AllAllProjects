/*-----------------------------------------------------------------------
             C O M P I L E R  O F  T I N Y   L A N G U A G E
developed by Stekolchik Alexander 1998.
Module file PARSER.C LALR parser
       related files
       TQC.C       main function
       COMMON.H    common header file
       SCANNER.H  lexical analizer definitions and constants
       TLA.C      lexical analizer functions
       GSTACK.H  stack definitions and declarations
       GSTACK.C  common stack operation function
       HASH.H   hashtable header file
       HASH.C   hashtable functions
       STKENTRY H  parser stack definitions and declarations
       STKENTRY.C  parser stack function
       PARSER.H   parser header file
       PARS_TAB.C  definitions of LALR actions table and goto table
       SEMANTIC.H semantic actions constants
       SEMANTIC.C semantic functions
---------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <alloc.h>
#include <process.h>
#include "parser.h"
extern FILE *fp,*lf;
extern char msg[MsgLn];
extern ActionTableEntry GetActTableEntry(ParserStateType S,tokentype t);
extern ParserStateType GetGotoTableEntry(ParserStateType s,SymbolType sym);
extern void SetParsTable(void);
extern void SetGotoTable(void);
extern void SetTransitionTable(void);
extern void init_quadruples(void);
extern void OutputQuadruples(void);
extern void inithash (void);
extern token *GetToken(FILE *fp,FILE *lf);
extern void PrintRule(int Rule);
void PrintEntryImage(StackEntry  se);
static int PrsErrCnt=0;
static BOOL ParseError=FALSE;
/*---------------------------------------------------------*/
extern BOOL WasSemanticError(void);
BOOL WasParseError(void){return ParseError;}
/*---------------------------------------------------------*/
static void init(void)
/*initialize parrser transitions tables,hashtables,stack   */
/*goto tables and ct                                       */
/*---------------------------------------------------------*/
{
StateSPtr sptr=NULL;
sptr=(StateSPtr)calloc(1,sizeof(StateS));
if(sptr==NULL) {
		 fprintf(stderr,"Malloc failed.\n");
		 exit(1);
	       }
SetTransitionTable();
SetParsTable();
SetGotoTable();
init_quadruples();
inithash();
sptr->state=S0;
PushEntry(STATE,sptr);
}
/*----------------------------------------------------------------*/
static void shift(TermPtr t,ActionTableEntry pte)
/*shift to the stack terminal t and new state of the parser       */
/* new state defined by action table entry pte                    */
/*----------------------------------------------------------------*/
{
TermPtr tptr;
StateSPtr sptr;
tptr=t;
sptr=(StateSPtr)calloc(1,sizeof(StateS));
if((sptr==NULL)||tptr==NULL) {
		 fprintf(stderr,"Malloc failed.\n");
		 exit(1);
	       }
sptr->state=shift_to(pte);
/* debug printf("shift state S%d terminal %s\n",sptr->state,tptr->Lexeme);*/
PushEntry(TERMINAL,tptr);
PushEntry(STATE,sptr);
}
/*----------------------------------------------------------------*/
NonTermPtr NewNonTerminal(SymbolType Symb)
/* Genereate new nonterminal symbol,input symbol Symb             */
/* return pointer to new non terminal                             */
/*----------------------------------------------------------------*/
{
NonTermPtr ntptr;
 ntptr=(NonTermPtr)calloc(1,sizeof(NonTerminalType));
 if(ntptr==NULL) {
		 fprintf(stderr,"Malloc failed.\n");
		 exit(1);
 }
 ntptr->Symb=Symb;
 ntptr->quad=0;
 strcpy(ntptr->ntValue,EmptyString);
 strcpy(ntptr->Atribute,EmptyString);
 ntptr->NextList=ntptr->TrueList=ntptr->FalseList=NULL;
return ntptr;
}
/*----------------------------------------------------------------*/
static void reduce (ActionTableEntry pte)
/*reduce  according rule that action table entry pte points to    */
/*----------------------------------------------------------------*/
{
 StackEntryPtr septr=NULL,curr_entry=NULL;
 StateSPtr sptr;
 ParserStateType s;
 NonTermPtr ntptr;
 int i,j,
 N=symb_to_reduce(pte),
 N2=2*N;
/* for debug PrintRule(Rule(pte)); */
 if (N){
	septr=(StackEntryPtr) calloc (N,sizeof(StackEntry));
	if(septr==NULL) {
			 fprintf(stderr,"Malloc failed.\n");
			 exit(1);
			}
       }
/* pop /right_side_of_prod/*2 entries from the stack */
 for (i=0,j=0;i<N2;i++){
     curr_entry=PopEntry();
     /* debug printf("pop ");PrintEntryImage(*curr_entry);printf("\n");*/
     if(i%2) {/* not state*/
	     memcpy(&(septr[j]),curr_entry,sizeof(StackEntry));
	     j++;
	     }
      if(curr_entry->type==STATE) free((StateSPtr)curr_entry->entry);
      FreeStackEntry(curr_entry);
 }
 ntptr=NewNonTerminal(new_sym(pte));
 sptr=(StateSPtr)TopEntry(); /*save state on the top  */
 s=sptr->state;              /*of the stack for subsequent goto*/

 if((sem_func(pte))!=NULL) sem_func(pte)(septr,ntptr); /* semantic action*/

 PushEntry(NON_TERMINAL,ntptr);
/* for debug printf("push ntrm %d\n",ntptr->Symb);*/
 sptr=(StateSPtr)calloc(1,sizeof(StateS));
 if(sptr==NULL) {
		 fprintf(stderr,"Malloc failed.\n");
		 exit(1);
	       }
 sptr->state=GetGotoTableEntry(s,new_sym(pte));
 PushEntry(STATE,sptr);/* push the state according to goto table */
/* for debug printf("push state S%d\n",sptr->state); */
/* just a garbage collection*/
 for(i=N-1;i>0;i--) {
     free(septr[i].entry);
 }
 if(N) free(septr);
}
/*----------------------------------------------------------------*/
TermPtr ParserErrorHandle (void)
/*Error handle function. return token from which possible         */
/*to continue parsing.Based on panic mode error handle            */
/*Therefore some tokens are skiped until needed token is read     */
/*----------------------------------------------------------------*/
{
 SymbolType symb;
 ParserStateType newS=0,s=0;
 ActionType act;
 TermPtr tok;
 StackEntryPtr septr;
 NonTermPtr ntptr;
 StateSPtr sptr;

 while (newS==s){
   septr=PopEntry();
   if(septr->type==STATE){
      newS=s=(*(StateSPtr)septr->entry).state;
      for(symb=0;symb<NSYMBS;symb++){
	 newS=GetGotoTableEntry(s,symb); /*scan goto table for           */
	 if(newS!=s) break;              /*an entry leads somewhere      */
      }					 /*from this Symb parser continue*/
   }
   free(septr->entry);
   FreeStackEntry(septr);
 }
 sptr=(StateSPtr)malloc(sizeof(StateS));
 if(sptr==NULL){
     fprintf(stderr,"Malloc failed.\n");
     exit(1);
 }
 sptr->state=s;
 PushEntry(STATE, sptr); /* push the last poped state back to the stack*/
 ntptr=NewNonTerminal(symb);

 PushEntry(NON_TERMINAL,ntptr); /* push found symbol to the stack */
 sptr=(StateSPtr)malloc(sizeof(StateS));
 if(sptr==NULL){
    fprintf(stderr, "malloc failed.\n");
    exit(1);
 }
 sptr->state=newS;
 PushEntry(STATE,sptr); /* push the GOTO state */

 /* search input for a token that have an entry in the action table*/
 /* different from ERROR  for the newS and continue .              */
 do {
      tok=GetToken(fp,lf); /* get next token */
      if (tok->T!=tEof)
	 act=action(GetActTableEntry(newS,tok->T));
	 if(act==ERROR){
	   sprintf(msg,"%s %s\n",ParserError,tok->Lexeme);
	   PrintMessage(lf);
	   PrintMsgAndClear(stderr);
	   free(tok);
	 }
    } while((act==ERROR)&&(tok->T!=tEof));
 return (tok); /* return token parser can go on from it */
}
/*---------------------------------------------------------------------*/
void parser (void)
/* The main engine of the parser.                                      */
/* call to functions that read input file making parse action  and     */
/* error handling and output result program                            */
/*---------------------------------------------------------------------*/
{
  StateSPtr sptr=NULL;
  ParserStateType s;
  TermPtr t;
  ActionType act;
  init();
  t=GetToken(fp,lf);
  printf("");
  while((t->T)!=tEof){
       sptr=(StateSPtr)TopEntry();
       s=sptr->state;
       act=action(GetActTableEntry(s,t->T));
       switch(act) {
	     case SHIFT : shift(t,GetActTableEntry(s,t->T));
			  t=GetToken(fp,lf);
			  break;
	     case REDUCE: reduce(GetActTableEntry(s,t->T));
			  break;
	     case ACCEPT: DiscardStack();
			  if(!WasParseError()&&!WasSemanticError()){
			    sprintf(msg,"\n%s",AllRight);
			    PrintMessage(lf);
			    PrintMsgAndClear(stderr);
			    OutputQuadruples();
			    }
			  return;
	     case ERROR : ParseError=TRUE;
			  PrsErrCnt++;
			  sprintf(msg,"%s","Parse error.\n");
			  PrintMessage(lf);
			  PrintMsgAndClear(stderr);
			  if (PrsErrCnt<MaxPrsErr) t=ParserErrorHandle();
			     else{
			     DiscardStack();
			     exit(1);
			     }
			  break;
	     default    :break;
       }
  }
}
/*---------------------------------------------------------------------*/
