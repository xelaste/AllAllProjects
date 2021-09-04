/*-----------------------------------------------------------------------
             C O M P I L E R  O F  T I N Y   L A N G U A G E
developed by Stekolchik Alexander 1998.
Module file SEMANTIC.C semantic action functions
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
       PARSER.C    parser operation function
       SEMANTIC.H semantic actions constants
---------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <process.h>
#include <alloc.h>
#include "stkentry.h"
#include "semantic.h"
extern FILE *lf;
extern char msg[MsgLn];
extern char quadfile[FILE_NAME_LENTH];
extern void *lookup (char *s);
void *install(void *body,char *s);
quadrupletype Quadruple[MAX_QUAD_PROGRAM_SIZE];
static char *qImage[]={"IASN","IPRT","IINP","IEQL","INQL","ILSS","IGRT",
		       "IADD","ISUB","IMLT","IDIV","RASN","RPRT","RINP",
		       "REQL","RNQL","RLSS","RGRT","RADD","RSUB","RMLT",
		       "RDIV","ITOR","RTOI","JUMP","JMPZ","HALT"};
static BOOL SemError=FALSE;
static qc=1; /*counter written lines to output*/
/*---------------------------------------------------------------------*/
BOOL WasSemanticError() {return SemError;}
extern BOOL WasParseError(void);
/*---------------------------------------------------------------------*/
static char *gettmp(void)
/* Create name of temp variable                                         */
/*----------------------------------------------------------------------*/
{
 static char name[MAX_NUMBER];
 static int i=0;
       memset(name,'\0',MAX_NUMBER);
       sprintf(name,"_t%d",i++);
 return name;
}
/*-----------------------------------------------------------------------*/
void init_quadruples(void)
/* initialize buffer where produced code should be store                 */
/*-----------------------------------------------------------------------*/
{
int i;
for(i=0;i<MAX_QUAD_PROGRAM_SIZE;i++){
    Quadruple[i].instr=ENDQUAD;
    strcpy(Quadruple[i].arg1,"\0");
    strcpy(Quadruple[i].arg2,"\0");
    strcpy(Quadruple[i].arg3,"\0");
    }
}
/*----------------------------------------------------------------------*/
void OutputQuadruples(void)
/* Output translated program if there where not errors                  */
/*----------------------------------------------------------------------*/
{
int i;
FILE *qf;
qf=fopen(quadfile,"wt");
if ((qf=fopen(quadfile,"wt"))==NULL)
  {
  fprintf(stderr,"Error open output file %s\n",quadfile);
  exit(3);
  }
for(i=0;((i<qc)&&(Quadruple[i].instr!=ENDQUAD));i++){
   fprintf(qf,"%s %s %s %s\n",qImage[Quadruple[i].instr],Quadruple[i].arg1,
			       Quadruple[i].arg2,Quadruple[i].arg3);
    }

   fprintf(qf,"%s\n",CopyRight);
fclose(qf);
}
/*---------------------------------------------------------------------*/
int nextquad(void){return qc;} /* line number of the next instruction  */
/*---------------------------------------------------------------------*/
LstHeadPtr makelist(int quad)
/*create new list of jumps for backpatching from the line quad         */
/* input quad place of the jump we must fill after                     */
/* output pointer to new list                                          */
/*---------------------------------------------------------------------*/
{
LstHeadPtr lhptr;
   lhptr=(LstHeadPtr)malloc (sizeof(ListHeadType));
   if(lhptr==NULL) {
     fprintf(stderr,"Malloc failed.\n");
     exit(1);
   }
lhptr->top=(LstPtr)malloc(sizeof(ListType));
   if(lhptr->top==NULL) {
     fprintf(stderr,"Malloc failed.\n");
     exit(1);
   }
(lhptr->top)->quad=quad;
(lhptr->top)->next=NULL;
lhptr->last=lhptr->top;
return lhptr;
}
/*--------------------------------------------------------------------*/
LstHeadPtr merge(LstHeadPtr l1,LstHeadPtr l2)
/*Connect list l2 to l1 return pointer to common list                 */
/*--------------------------------------------------------------------*/
{
if(l1!=NULL){
  if(l2!=NULL){
    (l1->last)->next=l2->top;
     l1->last=l2->last;
     free(l2);
    }
 return l1;
 }
return l2;
}
/*--------------------------------------------------------------------*/
void backpatch(LstHeadPtr lhptr,int label)
/*backpatch label to all jumps that nodes of the list lhptr points to */
/*--------------------------------------------------------------------*/
{
LstPtr lsptr,garbige,topptr=(lhptr!=NULL)?lhptr->top:NULL;
for (lsptr=topptr;lsptr!=NULL;lsptr=lsptr->next,free(garbige))
    {
    strcpy(Quadruple[lsptr->quad-1].arg1,"\0");
    sprintf(Quadruple[lsptr->quad-1].arg1,"%d",label);
    garbige=lsptr;
    }
if(lhptr!=NULL) free(lhptr);
}
/*---------------------------------------------------------------------*/
void emit(Quad_Instruction instruction,char *arg1,char *arg2,char *arg3)
/*emit to buffer quad instruction with argunents arg1,arg2,arg3        */
/*---------------------------------------------------------------------*/
{
 if(!(qc<MAX_QUAD_PROGRAM_SIZE)){
    sprintf(msg,"%s\n",CodeOverFlow);
    PrintMessage(lf);
    PrintMsgAndClear(stderr);
    SemError=TRUE;
    }
 Quadruple[qc-1].instr=instruction;
 strcpy(Quadruple[qc-1].arg1,arg1);
 strcpy(Quadruple[qc-1].arg2,arg2);
 strcpy(Quadruple[qc-1].arg3,arg3);
 qc++;
}
/*-----------------------------------------------------------------------*/
/* Semantic functions for each grammar rule                              */
/*-----------------------------------------------------------------------*/
/* fi(StackEntryPtr septr,NonTermPtr ntptr)                              */
/*input septr array of nodes that reduced from the stack                 */
/* ntptr new non terminal symbol that should be pushed to the stack      */
/*-----------------------------------------------------------------------*/
void f1(StackEntryPtr septr,NonTermPtr ntptr)
/* 1.Program -> prog id ; Declarations begin StmtList end                */
{
NonTermPtr stmtlist=septr[1].entry;
backpatch(stmtlist->NextList,nextquad());
emit(HALT,EmptyString,EmptyString,EmptyString);
DummyUseParameters(septr,ntptr);
}
/*-----------------------------------------------------------------------*/
/*  2. Declarations -> var DecList;       do nothing                     */
/*void f2(StackEntryPtr septr,NonTermPtr ntptr)                          */
/*-----------------------------------------------------------------------*/
void f3(StackEntryPtr septr,NonTermPtr ntptr)
/* 3. DecList -> DecList , id: Type"                                     */
/*-----------------------------------------------------------------------*/

{
NonTermPtr type;
TermPtr id,newterm;
id=(TermPtr)(septr[2].entry);
type=(NonTermPtr)(septr[0].entry);
if (lookup(id->Lexeme)==NULL){
   strcpy(id->Atribute,type->Atribute);
   newterm=(TermPtr)malloc(sizeof(TerminalType));
   if(newterm==NULL) MallocFailed;
   memcpy(newterm,id,sizeof(*id));
   install(newterm,id->Lexeme);
   }
   else{
   sprintf(msg,"%s %s\n",DuplicateDefinition,id->Lexeme);
   PrintMessage(lf);
   PrintMsgAndClear(stderr);
   SemError=TRUE;
   }
DummyUseParameters(septr,ntptr);
}
/*-----------------------------------------------------------------------*/
void f4(StackEntryPtr septr,NonTermPtr ntptr)
/*   4. DecList -> id: Type                                              */
/*-----------------------------------------------------------------------*/
{
NonTermPtr type;
TermPtr id,newterm;
id=(TermPtr)(septr[2].entry);
type=(NonTermPtr)(septr[0].entry);
if (lookup(id->Lexeme)==NULL){
   strcpy(id->Atribute,type->Atribute);
   newterm=(TermPtr)malloc(sizeof(TerminalType));
   if(newterm==NULL){
		    printf("malloc failed\n");
		    exit(1);
		    }
   memcpy(newterm,id,sizeof(*id));
   install(newterm,id->Lexeme);
   }
   else{
   sprintf(msg,"%s %s\n",DuplicateDefinition,id->Lexeme);
   PrintMessage(lf);
   PrintMsgAndClear(stderr);
   SemError=TRUE;
   }
DummyUseParameters(septr,ntptr);
}
/*-----------------------------------------------------------------------*/
void f5(StackEntryPtr septr,NonTermPtr ntptr)
/*   5. Type -> int                                                      */
/*-----------------------------------------------------------------------*/
{
strcpy(ntptr->Atribute,INTEGER);
DummyUseParameters(septr,ntptr);
}
/*-----------------------------------------------------------------------*/
void f6(StackEntryPtr septr,NonTermPtr ntptr)
/*   6. Type -> REAL                                                     */
/*-----------------------------------------------------------------------*/
{
strcpy(ntptr->Atribute,REAL);
DummyUseParameters(septr,ntptr);
}
/*-----------------------------------------------------------------------*/
void f7(StackEntryPtr septr,NonTermPtr ntptr)
/*   7. StmtList -> StmtList mM Statement;				 */
/*-----------------------------------------------------------------------*/
{
NonTermPtr statement=(NonTermPtr)septr[1].entry,
	    mM      =(NonTermPtr)septr[2].entry,
	    stmtlist=(NonTermPtr)septr[3].entry;
backpatch(stmtlist->NextList,mM->quad);
ntptr->NextList=statement->NextList;
}
/*-----------------------------------------------------------------------*/
/*void f8(StackEntryPtr septr,NonTermPtr ntptr)                          */
/*      8. StmtList ->              					 */
/*-----------------------------------------------------------------------*/
void f9(StackEntryPtr septr,NonTermPtr ntptr)
/*   9. Statement -> id:=Expression					 */
/*-----------------------------------------------------------------------*/
{
TermPtr id=(TermPtr)(septr[2].entry),store;
NonTermPtr expression=(NonTermPtr)(septr[0].entry);
char *name=gettmp();
if((store=lookup(id->Lexeme))==NULL){
    sprintf(msg,"%s %s\n",UnknownId,id->Lexeme);
    PrintMessage(lf);
    PrintMsgAndClear(stderr);
    SemError=TRUE;
    return;
   }
/* id and expression are integers*/
if(!strcmp(store->Atribute,INTEGER)&&!strcmp(expression->Atribute,INTEGER)){
  emit(IASN,store->Lexeme,expression->ntValue,EmptyString);
  return;
  }
/* id and expressions are reals */
if (!strcmp(store->Atribute,REAL)&&!strcmp(expression->Atribute,REAL)){
   emit(RASN,store->Lexeme,expression->ntValue,EmptyString);
   return;
   }

/* id is real and expression is integer */
if (!strcmp(store->Atribute,REAL)&&!strcmp(expression->Atribute,INTEGER)){
   emit(ITOR,name ,expression->ntValue,EmptyString);
   emit(RASN,store->Lexeme,name,EmptyString);
   return;
   }

/* id is integer and expression is real */
if (!strcmp(store->Atribute,INTEGER)&&!strcmp(expression->Atribute,REAL)){
   emit(RTOI,name,expression->ntValue,EmptyString);
   emit(IASN,store->Lexeme,name,EmptyString);
   return;
   }

/* Error type */
 sprintf(msg,"%s %s %s\n",InvalidType,store->Lexeme,expression->ntValue);
 PrintMessage(lf);
 PrintMsgAndClear(stderr);
 SemError=TRUE;
 DummyUseParameters(septr,ntptr);
}
/*-----------------------------------------------------------------------*/
void f10(StackEntryPtr septr,NonTermPtr ntptr)
/*   10.Statement -> print Expression					 */
/*-----------------------------------------------------------------------*/
{
NonTermPtr expression=septr[0].entry;

if(!strcmp(expression->Atribute,INTEGER)){
  emit(IPRT,expression->ntValue,EmptyString,EmptyString);
  return;
  }
  else if(!strcmp(expression->Atribute,REAL)){
	  emit(RPRT,expression->ntValue,EmptyString,EmptyString);
	  return;
	  }
/* Error type */
 sprintf(msg,"%s %s \n",InvalidType,expression->ntValue);
 PrintMessage(lf);
 PrintMsgAndClear(stderr);
 SemError=TRUE;
DummyUseParameters(septr,ntptr);
}
/*-----------------------------------------------------------------------*/
void f11(StackEntryPtr septr,NonTermPtr ntptr)
/*   11.Statement -> read id						 */
/*-----------------------------------------------------------------------*/
{
TermPtr id=(TermPtr)septr[0].entry,store;

if ((store=(TermPtr)lookup(id->Lexeme))==NULL){
    sprintf(msg,"%s %s\n",UnknownId,id->Lexeme);
    strcpy(ntptr->ntValue,id->Lexeme);
    PrintMessage(lf);
    PrintMsgAndClear(stderr);
    SemError=TRUE;
    return;
    }
if (!strcmp(store->Atribute,INTEGER)){
   emit(IINP,store->Lexeme,EmptyString,EmptyString);
   strcpy(ntptr->ntValue,store->Lexeme);
   strcpy(ntptr->Atribute,INTEGER);
   return;
   }

if (!strcmp(store->Atribute,REAL)){
   emit(RINP,store->Lexeme,EmptyString,EmptyString);
   strcpy(ntptr->ntValue,store->Lexeme);
   strcpy(ntptr->Atribute,REAL);
   return;
   }

/* Error type */
 sprintf(msg,"%s %s \n",InvalidType,store->Lexeme);
 PrintMessage(lf);
 PrintMsgAndClear(stderr);
 strcpy(ntptr->ntValue,store->Lexeme);
 SemError=TRUE;
}
/*-----------------------------------------------------------------------*/
void f12(StackEntryPtr septr,NonTermPtr ntptr)
/*    12.Statement -> if BoolExp Then mM StmtList mN else mM StmtList fi */
/*-----------------------------------------------------------------------*/
{
NonTermPtr boolexp=(NonTermPtr)septr[8].entry,
	   mm1=(NonTermPtr)septr[6].entry,
	   stmt1=(NonTermPtr)septr[5].entry,
	   mn=(NonTermPtr)septr[4].entry,
	   mm2=(NonTermPtr)septr[2].entry,
	   stmt2=(NonTermPtr)septr[1].entry;

backpatch(boolexp->TrueList,mm1->quad);
backpatch(boolexp->FalseList,mm2->quad);
ntptr->NextList=merge(stmt1->NextList,merge(mn->NextList,stmt2->NextList));
}
/*-----------------------------------------------------------------------*/
void f13(StackEntryPtr septr,NonTermPtr ntptr)
/*    13.Statement -> while M BoolExp do M StmtList od                   */
/*-----------------------------------------------------------------------*/
{
char quad[4]={"\0"};
NonTermPtr mm1=(NonTermPtr)septr[5].entry,
	   boolexp=(NonTermPtr)septr[4].entry,
	   mm2=(NonTermPtr)septr[2].entry,
	   stmtlst=(NonTermPtr)septr[1].entry;

backpatch(stmtlst->NextList,mm1->quad);
backpatch(boolexp->TrueList,mm2->quad);
ntptr->NextList=boolexp->FalseList;
sprintf(quad,"%d",mm1->quad);
emit(JUMP,quad,EmptyString,EmptyString);
}
/*-----------------------------------------------------------------------*/
void f14(StackEntryPtr septr,NonTermPtr ntptr)
/*    14.BoolExp -> Expression relop Expression  */
/*-----------------------------------------------------------------------*/
{
char name[MAX_NUMBER],tmp[MAX_NUMBER];
NonTermPtr expr2=(NonTermPtr)septr[0].entry,
	   expr1=(NonTermPtr)septr[2].entry;
TermPtr relop=(TermPtr)septr[1].entry;
Quad_Instruction rRelop,iRelop;
strcpy(name,gettmp());strcpy(tmp,gettmp());
if(!strcmp(relop->Atribute,EQL)){rRelop=REQL;iRelop=IEQL;}
if(!strcmp(relop->Atribute,NEQL)){rRelop=RNQL;iRelop=INQL;}
if(!strcmp(relop->Atribute,GRT)){rRelop=RGRT;iRelop=IGRT;}
if(!strcmp(relop->Atribute,LSS)){rRelop=RLSS;iRelop=ILSS;}

/* expr1 and expr2 are integers*/
if(!strcmp(expr1->Atribute,INTEGER)&&!strcmp(expr2->Atribute,INTEGER)){
  emit(iRelop,tmp,expr1->ntValue,expr2->ntValue);
  ntptr->FalseList=makelist(nextquad());
  ntptr->TrueList=makelist(nextquad()+1);
  emit(JMPZ,EmptyString,tmp,EmptyString);
  emit(JUMP,EmptyString,EmptyString,EmptyString);
  return;
  }
/* expr1 and expr2 are reals */
if (!strcmp(expr1->Atribute,REAL)&&!strcmp(expr2->Atribute,REAL)){
   emit(rRelop,tmp,expr1->ntValue,expr2->ntValue);
   ntptr->FalseList=makelist(nextquad());
   ntptr->TrueList=makelist(nextquad()+1);
   emit(JMPZ,EmptyString,tmp,EmptyString);
   emit(JUMP,EmptyString,EmptyString,EmptyString);
   return;
   }

/* expr1 is a real and expr2 is an integer */
if (!strcmp(expr1->Atribute,REAL)&&!strcmp(expr2->Atribute,INTEGER)){
   emit(ITOR,name ,expr2->ntValue,EmptyString);
   emit(rRelop,tmp,expr1->ntValue,name);
   ntptr->FalseList=makelist(nextquad());
   ntptr->TrueList=makelist(nextquad()+1);
   emit(JMPZ,EmptyString,tmp,EmptyString);
   emit(JUMP,EmptyString,EmptyString,EmptyString);
   return;
   }

/* expr1 is an integer and expr2 is a real */
if (!strcmp(expr2->Atribute,REAL)&&!strcmp(expr1->Atribute,INTEGER)){
   emit(ITOR,name ,expr1->ntValue,EmptyString);
   emit(rRelop,tmp,expr2->ntValue,name);
   ntptr->FalseList=makelist(nextquad());
   ntptr->TrueList=makelist(nextquad()+1);
   emit(JMPZ,EmptyString,tmp,EmptyString);
   emit(JUMP,EmptyString,EmptyString,EmptyString);
   return;
   }

/* Error type */
 sprintf(msg,"%s %s %s\n",InvalidType,expr1->ntValue,expr2->ntValue);
 PrintMessage(lf);
 PrintMsgAndClear(stderr);
 SemError=TRUE;
 DummyUseParameters(septr,ntptr);
}
/*-----------------------------------------------------------------------*/
void f15(StackEntryPtr septr,NonTermPtr ntptr)
/*    15.Expression -> Expression addop Term                             */
/*-----------------------------------------------------------------------*/
{
char *name=gettmp();
Quad_Instruction realop,intop;
NonTermPtr expression=(NonTermPtr)septr[2].entry,
	   term=(NonTermPtr)septr[0].entry;
TermPtr addop=(TermPtr)septr[1].entry;

realop=(addop->T==tMinus)?RSUB:RADD;
intop=(addop->T==tMinus)?ISUB:IADD;

/* expression and term are integers */
if (!strcmp(expression->Atribute,INTEGER)&&!strcmp(term->Atribute,INTEGER)){
   emit(intop,name,expression->ntValue,term->ntValue);
   strcpy(ntptr->Atribute,INTEGER);
   strcpy(ntptr->ntValue,name);
   return;
   }
/* expression and factor are reals */
if (!strcmp(expression->Atribute,REAL)&&!strcmp(term->Atribute,REAL)){
   emit(realop,name,expression->ntValue,term->ntValue);
   strcpy(ntptr->Atribute,REAL);
   strcpy(ntptr->ntValue,name);
   return;
   }

/* expression is real and term is integer */
if (!strcmp(expression->Atribute,REAL)&&!strcmp(term->Atribute,INTEGER)){
   emit(ITOR,name,term->ntValue,EmptyString);
   emit(realop,name,expression->ntValue,name);
   strcpy(ntptr->Atribute,REAL);
   strcpy(ntptr->ntValue,name);
   return;
   }

/* expression is integer and term is real */
if (!strcmp(expression->Atribute,INTEGER)&&!strcmp(term->Atribute,REAL)){
   emit(ITOR,name,expression->ntValue,EmptyString);
   emit(realop,name,name,term->ntValue);
   strcpy(ntptr->Atribute,REAL);
   strcpy(ntptr->ntValue,name);
   return;
   }

/* Error type */
 sprintf(msg,"%s %s %s\n",InvalidType,expression->ntValue,term->ntValue);
 PrintMessage(lf);
 PrintMsgAndClear(stderr);
 SemError=TRUE;
 strcpy(ntptr->ntValue,name);
}
/*-----------------------------------------------------------------------*/
void f16(StackEntryPtr septr,NonTermPtr ntptr)
/*    16.Expression -> Term						 */
/*-----------------------------------------------------------------------*/
{
NonTermPtr term=(NonTermPtr)septr[0].entry;
  strcpy(ntptr->Atribute,term->Atribute);
  strcpy(ntptr->ntValue,term->ntValue);
}
/*-----------------------------------------------------------------------*/
void f17(StackEntryPtr septr,NonTermPtr ntptr)
/*    17.Term -> Term mulop Factor					 */
/*-----------------------------------------------------------------------*/
{
char *name=gettmp();
Quad_Instruction realop,intop;
NonTermPtr term=(NonTermPtr)septr[2].entry,
	   factor=(NonTermPtr)septr[0].entry;
TermPtr mulop=(TermPtr)septr[1].entry;
realop=(strcmp(mulop->Atribute,DIVIDE))?RMLT:RDIV;
intop=(strcmp(mulop->Atribute,DIVIDE))?IMLT:IDIV;

/* term and factor are integers */
if (!strcmp(term->Atribute,INTEGER)&&!strcmp(factor->Atribute,INTEGER)){
   emit(intop,name,term->ntValue,factor->ntValue);
   strcpy(ntptr->Atribute,INTEGER);
   strcpy(ntptr->ntValue,name);
   return;
   }
/* term and factor are reals */
if (!strcmp(term->Atribute,REAL)&&!strcmp(factor->Atribute,REAL)){
   emit(realop,name,term->ntValue,factor->ntValue);
   strcpy(ntptr->Atribute,REAL);
   strcpy(ntptr->ntValue,name);
   return;
   }

/* term is real and factor is integer */
if (!strcmp(term->Atribute,REAL)&&!strcmp(factor->Atribute,INTEGER)){
   emit(ITOR,name,factor->ntValue,EmptyString);
   emit(realop,name,term->ntValue,name);
   strcpy(ntptr->Atribute,REAL);
   strcpy(ntptr->ntValue,name);
   return;
   }

/* term is integer and factor is real */
if (!strcmp(term->Atribute,INTEGER)&&!strcmp(factor->Atribute,REAL)){
   emit(ITOR,name,term->ntValue,EmptyString);
   emit(realop,name,name,factor->ntValue);
   strcpy(ntptr->Atribute,REAL);
   strcpy(ntptr->ntValue,name);
   return;
   }

/* Error type */
 sprintf(msg,"%s %s %s\n",InvalidType,term->ntValue,factor->ntValue);
 PrintMessage(lf);
 PrintMsgAndClear(stderr);
 SemError=TRUE;
 strcpy(ntptr->ntValue,name);
}
/*-----------------------------------------------------------------------*/
void f18(StackEntryPtr septr,NonTermPtr ntptr)
/*    18.Term -> Factor	                    				 */
/*-----------------------------------------------------------------------*/
{
NonTermPtr factor=(NonTermPtr)septr[0].entry;
  strcpy(ntptr->Atribute,factor->Atribute);
  strcpy(ntptr->ntValue,factor->ntValue);
}
/*-----------------------------------------------------------------------*/
void f19(StackEntryPtr septr,NonTermPtr ntptr)
/*    19.Factor -> id							 */
/*-----------------------------------------------------------------------*/
{
TermPtr id=(TermPtr)septr[0].entry,store;
if((store=lookup(id->Lexeme))!=NULL){/*check if exists in symbol table */
  strcpy(ntptr->Atribute,store->Atribute);
  strcpy(ntptr->ntValue, store->Lexeme);
  }
  else{
      sprintf(msg,"%s %s\n",UnknownId,id->Lexeme);
      PrintMessage(lf);
      PrintMsgAndClear(stderr);
      SemError=TRUE;
      strcpy(ntptr->Atribute,EmptyString);
      strcpy(ntptr->ntValue, EmptyString);
      }
}
/*-----------------------------------------------------------------------*/
void f20(StackEntryPtr septr,NonTermPtr ntptr)
/*    20. Factor -> num							 */
/*-----------------------------------------------------------------------*/
{
TermPtr num=(TermPtr)septr[0].entry;
  strcpy(ntptr->Atribute,num->Atribute);
  strcpy(ntptr->ntValue,num->Lexeme);
}
/*-----------------------------------------------------------------------*/
void f21(StackEntryPtr septr,NonTermPtr ntptr)
/*    21.Factor -> (Expression)						 */
/*-----------------------------------------------------------------------*/
{
NonTermPtr lParExpressionRpar=(NonTermPtr)septr[1].entry;
  strcpy(ntptr->Atribute,lParExpressionRpar->Atribute);
  strcpy(ntptr->ntValue,lParExpressionRpar->ntValue);
}
/*-----------------------------------------------------------------------*/
void f22(StackEntryPtr septr,NonTermPtr ntptr)
/*    22. Expression -> -Term							 */
/*-----------------------------------------------------------------------*/
{
char *name;
BOOL ValidType=FALSE;
NonTermPtr term= (NonTermPtr)(septr[0]).entry;
name=gettmp();
if(!strcmp(term->Atribute,INTEGER)){
  emit(ISUB,name,"0",term->ntValue);
  ValidType=TRUE;
  }
  else if(!strcmp(term->Atribute,REAL)){
	  emit(RSUB,name,"0.0",term->ntValue);
	  ValidType=TRUE;
	 }
	else {
	      sprintf(msg,"%s %s\n",InvalidType,term->ntValue);
	      PrintMessage(lf);
	      PrintMsgAndClear(stderr);
	      SemError=TRUE;
	     }
if(ValidType){
  strcpy(ntptr->Atribute,term->Atribute);
  strcpy(ntptr->ntValue,name);
  }
  else {
	strcpy(ntptr->Atribute,EmptyString);
	strcpy(ntptr->ntValue,name);
       }
}
/*-----------------------------------------------------------------------*/
void f23(StackEntryPtr septr,NonTermPtr ntptr)
/*    23. mM ->          						 */
/*-----------------------------------------------------------------------*/
{
ntptr->quad=nextquad();
DummyUseParameters(septr,ntptr);
}
/*-----------------------------------------------------------------------*/
void f24(StackEntryPtr septr,NonTermPtr ntptr)
/*    24. mN ->          						 */
/*-----------------------------------------------------------------------*/
{
ntptr->NextList=makelist(nextquad());
emit(JUMP,EmptyString,EmptyString,EmptyString);
DummyUseParameters(septr,ntptr);
}
/*-----------------------------------------------------------------------*/
