/*-----------------------------------------------------------------------
             C O M P I L E R  O F  T I N Y   L A N G U A G E
developed by Stekolchik Alexander 1998.
Module file PARS_TAB.C parser action table and goto function
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
       PARSER.C    parser operation function
       SEMANTIC.H semantic actions constants
       SEMANTIC.C semantic functions
---------------------------------------------------------------------------*/
#include <stdio.h>
#include <alloc.h>
#include "parser.h"
/*---------------------------------*/
void f1(StackEntryPtr septr,NonTermPtr ntptr);
/*void f2(StackEntryPtr septr,NonTermPtr ntptr);*/
void f3(StackEntryPtr septr,NonTermPtr ntptr);
void f4(StackEntryPtr septr,NonTermPtr ntptr);
void f5(StackEntryPtr septr,NonTermPtr ntptr);
void f6(StackEntryPtr septr,NonTermPtr ntptr);
void f7(StackEntryPtr septr,NonTermPtr ntptr);
/*void f8(StackEntryPtr septr,NonTermPtr ntptr);*/
void f9(StackEntryPtr septr,NonTermPtr ntptr);
void f10(StackEntryPtr septr,NonTermPtr ntptr);
void f11(StackEntryPtr septr,NonTermPtr ntptr);
void f12(StackEntryPtr septr,NonTermPtr ntptr);
void f13(StackEntryPtr septr,NonTermPtr ntptr);
void f14(StackEntryPtr septr,NonTermPtr ntptr);
void f15(StackEntryPtr septr,NonTermPtr ntptr);
void f16(StackEntryPtr septr,NonTermPtr ntptr);
void f17(StackEntryPtr septr,NonTermPtr ntptr);
void f18(StackEntryPtr septr,NonTermPtr ntptr);
void f19(StackEntryPtr septr,NonTermPtr ntptr);
void f20(StackEntryPtr septr,NonTermPtr ntptr);
void f21(StackEntryPtr septr,NonTermPtr ntptr);
void f22(StackEntryPtr septr,NonTermPtr ntptr);
void f23(StackEntryPtr septr,NonTermPtr ntptr);
void f24(StackEntryPtr septr,NonTermPtr ntptr);
/*---------------------------------*/
/* action part of the pars_table   */
/*---------------------------------*/
ActionTableEntry pars_table[NSTATES][NTERM_IN_LIST];
/*-------------------------------------------------------*/
/* Initialize Parse table                                */
/*-------------------------------------------------------*/
void SetParsTable(void)
{
ActTableEntryPtr pAct;
int i,j;
for(i=S0;i<NSTATES;i++)
   for(j=0;j<NTERM_IN_LIST;j++){
       pars_table[i][j].tok=tOther;
       action(pars_table[i][j])=ERROR;
       sem_func(pars_table[i][j])=NULL;
   }
/*-- S0  -- the start state of the parser*/
/* Program->.Program */

pAct=&pars_table[S0][0];
(*pAct).tok=tProg;shift_to(*pAct)=S2;action(*pAct)=SHIFT;

/*-- S1  --*/
/* Program->Program.*/

pAct=&pars_table[S1][0];
(*pAct).tok=tEndOfProgram;action(*pAct)=ACCEPT;

/*-- S2  --*/
/* Program->Prog.id;Declarations begin StmtList end */

pAct=&pars_table[S2][0];
(*pAct).tok=tId;shift_to(*pAct)=S3;action(*pAct)=SHIFT;

/*-- S3  --*/
/* Program->Prog id.;Declarations begin StmtList end */

pAct=&pars_table[S3][0];
(*pAct).tok=tSemicolon;action(*pAct)=SHIFT;shift_to(*pAct)=S4;

/*-- S4  --*/
/* Program->Prog id;.Declarations begin StmtList end */

pAct=&pars_table[S4][0];
(*pAct).tok=tVar;action(*pAct)=SHIFT;shift_to(*pAct)=S6;

/*-- S5  --*/
/* Program->Prog id; Declarations.begin StmtList end */

pAct=&pars_table[S5][0];
(*pAct).tok=tBegin;action(*pAct)=SHIFT;shift_to(*pAct)=S7;

/*-- S6  --*/
/* Declarations -> var.DeclList */

pAct=&pars_table[S6][0];
(*pAct).tok=tId;action(*pAct)=SHIFT;shift_to(*pAct)=S9;

/*-- S7  --*/
/* Program->Prog id;Declarations begin.StmtList end */
/* StmtList->.                                      */

pAct=&pars_table[S7][0];
(*pAct).tok=tOther;action(*pAct)=REDUCE;symb_to_reduce(*pAct)=0;
Rule(*pAct)=8;new_sym(*pAct)=StmtList;/*sem_func(*pAct)=f8;*/

/*-- S8  --*/
/* Declarations -> var DeclList.; */
/* DeclList ->DeclList.,id:Type */

pAct=&pars_table[S8][0];
(*pAct).tok=tSemicolon;action(*pAct)=SHIFT;shift_to(*pAct)=S11;pAct++;
(*pAct).tok=tComma;action(*pAct)=SHIFT;shift_to(*pAct)=S12;

/*-- S9  --*/
/* DeclList ->  id.:Type */

pAct=&pars_table[S9][0];
(*pAct).tok=tColon;action(*pAct)=SHIFT;shift_to(*pAct)=S13;

/*-- S10  --*/
/* Program  -> Prog id;Declarations begin StmtList.end */
/* StmtList -> StmtList .mM Statement;                 */
/* mM ->                                               */
pAct=pars_table[S10];
(*pAct).tok=tEnd;action(*pAct)=SHIFT;shift_to(*pAct)=S14;pAct++;
pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=mM;symb_to_reduce(*pAct)=0;
Rule(*pAct)=23;sem_func(*pAct)=f23;

/*-- S11 --*/
/* Declarations -> var DeclList;. */

pAct=&pars_table[S11][0];
(*pAct).tok=tOther;action(*pAct)=REDUCE;symb_to_reduce(*pAct)=3;
new_sym(*pAct)=Declarations;Rule(*pAct)=2;

/*-- S12  --*/
/* DeclList ->  DEclList ,.id:Type */

pAct=&pars_table[S12][0];
(*pAct).tok=tId;action(*pAct)=SHIFT;shift_to(*pAct)=S21;

/*-- S13  --*/
/* DeclList ->  id:.Type */

pAct=&pars_table[S13][0];
(*pAct).tok=tInt;action(*pAct)=SHIFT;shift_to(*pAct)=S23;pAct++;
(*pAct).tok=tReal;action(*pAct)=SHIFT;shift_to(*pAct)=S24;

/*-- S14 --*/
/* Program->Prog id;Declarations begin StmtList end. */

pAct=&pars_table[S14][0];
(*pAct).tok=tOther;action(*pAct)=REDUCE;symb_to_reduce(*pAct)=7;
new_sym(*pAct)=Program;Rule(*pAct)=1;sem_func(*pAct)=f1;

/*-- S15  --*/
/* StmtList ->  StmtList Statement.; */

pAct=&pars_table[S15][0];
(*pAct).tok=tSemicolon;action(*pAct)=SHIFT;shift_to(*pAct)=S25;

/*-- S16  --*/
/* Statement->id.:=Expression; */

pAct=&pars_table[S16][0];
(*pAct).tok=tAssignop;action(*pAct)=SHIFT;shift_to(*pAct)=S26;

/*-- S17  --*/
/* Statement-> print .Expression; */

pAct=&pars_table[S17][0];
(*pAct).tok=tId;action(*pAct)=SHIFT;shift_to(*pAct)=S30;pAct++;
(*pAct).tok=tNum;action(*pAct)=SHIFT;shift_to(*pAct)=S31;pAct++;
(*pAct).tok=tLpar;action(*pAct)=SHIFT;shift_to(*pAct)=S32;pAct++;
(*pAct).tok=tMinus;action(*pAct)=SHIFT;shift_to(*pAct)=S56;pAct++;

/*-- S18  --*/
/*  Statement-> read.id  */
pAct=&pars_table[S18][0];
(*pAct).tok=tId;action(*pAct)=SHIFT;shift_to(*pAct)=S33;

/*-- S19  --*/
/* Statement-> if .BoolExp mM then mN StmtList else mM StmtList fi */

pAct=&pars_table[S19][0];
(*pAct).tok=tId;action(*pAct)=SHIFT;shift_to(*pAct)=S30;pAct++;
(*pAct).tok=tNum;action(*pAct)=SHIFT;shift_to(*pAct)=S31;pAct++;
(*pAct).tok=tLpar;action(*pAct)=SHIFT;shift_to(*pAct)=S32;pAct++;
(*pAct).tok=tMinus;action(*pAct)=SHIFT;shift_to(*pAct)=S56;pAct++;

/*-- S20  --*/
/* Statement-> while mM. BoolExp do mM StmtList od */

pAct=&pars_table[S20][0];
(*pAct).tok=tId;action(*pAct)=SHIFT;shift_to(*pAct)=S30;pAct++;
(*pAct).tok=tNum;action(*pAct)=SHIFT;shift_to(*pAct)=S31;pAct++;
(*pAct).tok=tLpar;action(*pAct)=SHIFT;shift_to(*pAct)=S32;pAct++;
(*pAct).tok=tMinus;action(*pAct)=SHIFT;shift_to(*pAct)=S56;

/*-- S21  --*/
/*  DeclList -> DeclLIst , id.:Type  */

pAct=&pars_table[S21][0];
(*pAct).tok=tColon;action(*pAct)=SHIFT;shift_to(*pAct)=S37;pAct++;

/*-- S22 --*/
/* DeclList -> id:Type. */

pAct=pars_table[S22];
pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=DeclList;symb_to_reduce(*pAct)=3;
Rule(*pAct)=4;sem_func(*pAct)=f4;

/*-- S23 --*/
/* Type -> int. */
pAct=pars_table[S23];
pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=Type;symb_to_reduce(*pAct)=1;
Rule(*pAct)=5;sem_func(*pAct)=f5;

/*-- S24 --*/
/* Type -> real. */

pAct=pars_table[S24];
pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=Type;symb_to_reduce(*pAct)=1;
Rule(*pAct)=6;sem_func(*pAct)=f6;

/*-- S25 --*/
/* StmtList -> StmtList mM Statement;. */

pAct=pars_table[S25];
pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=StmtList;symb_to_reduce(*pAct)=4;
Rule(*pAct)=7;sem_func(*pAct)=f7;

/*-- S26  --*/
/* Statement-> id:=.Expression */

pAct=pars_table[S26];
pAct->tok=tId;action(*pAct)=SHIFT;shift_to(*pAct)=S30;pAct++;
pAct->tok=tNum;action(*pAct)=SHIFT;shift_to(*pAct)=S31;pAct++;
pAct->tok=tLpar;action(*pAct)=SHIFT;shift_to(*pAct)=S32;pAct++;
pAct->tok=tMinus;action(*pAct)=SHIFT;shift_to(*pAct)=S56;pAct++;

/*-- S27  --*/
/* Statement -> print Expression. */
/*Expression -> Expression.addop Term */

pAct=pars_table[S27];
pAct->tok=tPlus;action(*pAct)=SHIFT;shift_to(*pAct)=S39;pAct++;
pAct->tok=tMinus;action(*pAct)=SHIFT;shift_to(*pAct)=S39;pAct++;;
pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=Statement;symb_to_reduce(*pAct)=2;
Rule(*pAct)=10;sem_func(*pAct)=f10;

/*-- S28  --*/
/* Expression -> Term. */
/* Term -> Term. mulop Factor */

pAct=pars_table[S28];
pAct->tok=tMulop;action(*pAct)=SHIFT;shift_to(*pAct)=S40;pAct++;
pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=Expression;symb_to_reduce(*pAct)=1;
Rule(*pAct)=16;sem_func(*pAct)=f16;

/*-- S29  --*/
/* Term -> Factor. */

pAct=pars_table[S29];
pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=Term;symb_to_reduce(*pAct)=1;
Rule(*pAct)=18;sem_func(*pAct)=f18;

/*-- S30  --*/
/* Factor -> id. */

pAct=pars_table[S30];
pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=Factor;symb_to_reduce(*pAct)=1;
Rule(*pAct)=19;sem_func(*pAct)=f19;

/*-- S31  --*/
/* Factor -> num. */

pAct=pars_table[S31];
pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=Factor;symb_to_reduce(*pAct)=1;
Rule(*pAct)=20;sem_func(*pAct)=f20;

/*-- S32  --*/
/* Factor -> (.Expression) */

pAct=pars_table[S32];
pAct->tok=tId;action(*pAct)=SHIFT;shift_to(*pAct)=S30;pAct++;
pAct->tok=tNum;action(*pAct)=SHIFT;shift_to(*pAct)=S31;pAct++;
pAct->tok=tLpar;action(*pAct)=SHIFT;shift_to(*pAct)=S32;pAct++;
pAct->tok=tMinus;action(*pAct)=SHIFT;shift_to(*pAct)=S56;

/*-- S33  --*/
/* Statement -> read id. */

pAct=pars_table[S33];
pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=Statement;symb_to_reduce(*pAct)=2;
Rule(*pAct)=11;sem_func(*pAct)=f11;

/*-- S34 --*/
/* Statement -> if BoolExp.then mM StmtList mN else mM StmtList fi */

pAct=pars_table[S34];
pAct->tok=tThen;action(*pAct)=SHIFT;shift_to(*pAct)=S58;

/*-- S35  --*/
/* BoolExpression.relop Expression     */
/* Expression -> Expression .addop Term */

pAct=pars_table[S35];
pAct->tok=tRelop;action(*pAct)=SHIFT;shift_to(*pAct)=S43;pAct++;
pAct->tok=tPlus;action(*pAct)=SHIFT;shift_to(*pAct)=S39;pAct++;
pAct->tok=tMinus;action(*pAct)=SHIFT;shift_to(*pAct)=S39;

/*-- S36  --*/
/* Statement -> while mM BoolExp .do mM StmtList od */

pAct=pars_table[S36];
pAct->tok=tDo;action(*pAct)=SHIFT;shift_to(*pAct)=S62;

/*-- S37  --*/
/* DeclList -> DeclList , id:.Type */

pAct=pars_table[S37];
pAct->tok=tInt;action(*pAct)=SHIFT;shift_to(*pAct)=S23;pAct++;
pAct->tok=tReal;action(*pAct)=SHIFT;shift_to(*pAct)=S24;

/*-- S38  --*/
/* Statement -> id := Expression. */
/* Expression -> Expression .addop Term*/

pAct=pars_table[S38];
pAct->tok=tPlus;action(*pAct)=SHIFT;shift_to(*pAct)=S39;pAct++;
pAct->tok=tMinus;action(*pAct)=SHIFT;shift_to(*pAct)=S39;pAct++;
pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=Statement;symb_to_reduce(*pAct)=3;
Rule(*pAct)=9;sem_func(*pAct)=f9;

/*-- S39  --*/
/* Expression -> Expression addop. Term */

pAct=pars_table[S39];
pAct->tok=tId;action(*pAct)=SHIFT;shift_to(*pAct)=S30;pAct++;
pAct->tok=tNum;action(*pAct)=SHIFT;shift_to(*pAct)=S31;pAct++;
pAct->tok=tLpar;action(*pAct)=SHIFT;shift_to(*pAct)=S32;

/*-- S40  --*/
/* Term -> Term mulop. Factor */

pAct=pars_table[S40];
pAct->tok=tId;action(*pAct)=SHIFT;shift_to(*pAct)=S30;pAct++;
pAct->tok=tNum;action(*pAct)=SHIFT;shift_to(*pAct)=S31;pAct++;
pAct->tok=tLpar;action(*pAct)=SHIFT;shift_to(*pAct)=S32;

/*-- S41  --*/
/* Expression -> Expression .addop Term */
/* Factor -> (Expression.) */

pAct=pars_table[S41];
pAct->tok=tPlus;action(*pAct)=SHIFT;shift_to(*pAct)=S39;pAct++;
pAct->tok=tMinus;action(*pAct)=SHIFT;shift_to(*pAct)=S39;pAct++;
pAct->tok=tRpar;action(*pAct)=SHIFT;shift_to(*pAct)=S48;

/*-- S42  --*/
/*if BoolExp then M. StmtList N else M StmtList fi */
/* Statement -> . */

pAct=pars_table[S42];
pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=StmtList;symb_to_reduce(*pAct)=0;
Rule(*pAct)=8;/*sem_func(*pAct)=f8;*/

/*-- S43  --*/
/* BoolExp -> Expression relop. Expression */

pAct=pars_table[S43];
pAct->tok=tId;action(*pAct)=SHIFT;shift_to(*pAct)=S30;pAct++;
pAct->tok=tNum;action(*pAct)=SHIFT;shift_to(*pAct)=S31;pAct++;
pAct->tok=tLpar;action(*pAct)=SHIFT;shift_to(*pAct)=S32;pAct++;
pAct->tok=tMinus;action(*pAct)=SHIFT;shift_to(*pAct)=S56;

/*-- S44  --*/
/*Statement -> while BoolExp do. StmtList od*/
/* StmtList -> . */

pAct=pars_table[S44];
pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=StmtList;symb_to_reduce(*pAct)=0;
Rule(*pAct)=8;/*sem_func(*pAct)=f8;*/

/*-- S45  --*/
/* DeclList ->DeclList,id:Type. */
pAct=pars_table[S45];
pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=DeclList;symb_to_reduce(*pAct)=5;
Rule(*pAct)=3;sem_func(*pAct)=f3;

/*-- S46  --*/
/* Expression -> Expression addop Term. */
/* Term -> Term. mulop Factor            */

pAct=pars_table[S46];
pAct->tok=tMulop;action(*pAct)=SHIFT;shift_to(*pAct)=S40;pAct++;
pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=Expression;symb_to_reduce(*pAct)=3;
Rule(*pAct)=15;sem_func(*pAct)=f15;

/*-- S47  --*/
/* Term -> Term mulop Factor. */

pAct=pars_table[S47];
pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=Term;symb_to_reduce(*pAct)=3;
Rule(*pAct)=17;sem_func(*pAct)=f17;

/*-- S48  --*/
/* Factor-> (Expression). */

pAct=pars_table[S48];
pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=Factor;symb_to_reduce(*pAct)=3;
Rule(*pAct)=21;sem_func(*pAct)=f21;

/*-- S49  --*/
/* Statement -> if BoolExp then mM StmtList mN. else mM StmtList fi */

pAct=pars_table[S49];
pAct->tok=tElse;action(*pAct)=SHIFT;shift_to(*pAct)=S60;pAct++;

/*-- S50  --*/
/* BoolExp -> Expression relop Expression. */
/* Expression -> Expression. addop Term*/

pAct=pars_table[S50];
pAct->tok=tPlus;action(*pAct)=SHIFT;shift_to(*pAct)=S39;pAct++;
pAct->tok=tMinus;action(*pAct)=SHIFT;shift_to(*pAct)=S39;pAct++;
pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=BoolExp;symb_to_reduce(*pAct)=3;
Rule(*pAct)=14;sem_func(*pAct)=f14;

/*-- S51  --*/
/* StmtList -> StmtList .mM Statement; */
/* Statement -> while mM BoolExp do mM StmtList. od  */
/* mM ->                                             */
pAct=pars_table[S51];
pAct->tok=tOd;action(*pAct)=SHIFT;shift_to(*pAct)=S53;pAct++;
pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=mM;symb_to_reduce(*pAct)=0;
Rule(*pAct)=23;sem_func(*pAct)=f23;


/*-- S52  --*/
/* Statement -> if BoolExp then M StmtList N else M. StmtList fi */
/* StmtList -> .                                           */

pAct=pars_table[S52];
pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=StmtList;symb_to_reduce(*pAct)=0;
Rule(*pAct)=8;/*sem_func(*pAct)=f8;*/

/*-- S53  --*/
/* Statement -> while mM BoolExp do mM StmtList od. */

pAct=pars_table[S53];
pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=Statement;symb_to_reduce(*pAct)=7;
Rule(*pAct)=13;sem_func(*pAct)=f13;

/*-- S54  --*/
/* StmtList -> StmtList .mM Statement */
/* Statement -> if BoolExp then mM StmtList mN else mM StmtList. fi*/
/* mM ->                                                           */

pAct=pars_table[S54];
pAct->tok=tFi;action(*pAct)=SHIFT;shift_to(*pAct)=S55;pAct++;
pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=mM;symb_to_reduce(*pAct)=0;
Rule(*pAct)=23;sem_func(*pAct)=f23;

/*-- S55  --*/
/* Statement -> if BoolExp then mM StmtList mN else mM StmtList fi. */

pAct=pars_table[S55];
pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=Statement;symb_to_reduce(*pAct)=10;
Rule(*pAct)=12;sem_func(*pAct)=f12;

/*-- S56 --*/
/* Expression -> -.Term */

pAct=pars_table[S56];
pAct->tok=tId;action(*pAct)=SHIFT;shift_to(*pAct)=S30;pAct++;
pAct->tok=tNum;action(*pAct)=SHIFT;shift_to(*pAct)=S31;pAct++;
pAct->tok=tLpar;action(*pAct)=SHIFT;shift_to(*pAct)=S32;

/*-- S57  --*/
/* Expression -> -Term. */

pAct=pars_table[S57];
pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=Expression;symb_to_reduce(*pAct)=2;
Rule(*pAct)=22;sem_func(*pAct)=f22;

/*-- S58  --*/
/* Statement -> if BoolExp then .mM StmtList mN else mM StmtList fi */
/* mM ->                                                            */

pAct=pars_table[S58];
pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=mM;symb_to_reduce(*pAct)=0;
Rule(*pAct)=23;sem_func(*pAct)=f23;


/*-- S59  --*/
/* Statement -> if BoolExp then mM StmtList .mN else mM StmtList fi */
/* StmtList -> M StmtList Statement;                                */
/* mN ->  {on Else }                                                */
/* mM ->  {on other}                                                */

pAct=pars_table[S59];

pAct->tok=tElse;
action(*pAct)=REDUCE;new_sym(*pAct)=mN;symb_to_reduce(*pAct)=0;
Rule(*pAct)=24;sem_func(*pAct)=f24;
pAct++;pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=mM;symb_to_reduce(*pAct)=0;
Rule(*pAct)=23;sem_func(*pAct)=f23;


/*-- S60  --*/
/* Statement -> if BoolExp then mM StmtList mN else .mM StmtList fi */
/* mM ->                                                            */

pAct=pars_table[S60];
pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=mM;symb_to_reduce(*pAct)=0;
Rule(*pAct)=23;sem_func(*pAct)=f23;

/*-- S61  --*/
/* Statement-> while .mM BoolExp do StmtList mM od */
/* mM ->                                           */

pAct=pars_table[S61];
pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=mM;symb_to_reduce(*pAct)=0;
Rule(*pAct)=23;sem_func(*pAct)=f23;

/*-- S62  --*/
/* Statement-> while mM BoolExp do .mM StmtList  od */
/* mM ->                                            */

pAct=pars_table[S62];
pAct->tok=tOther;
action(*pAct)=REDUCE;new_sym(*pAct)=mM;symb_to_reduce(*pAct)=0;
Rule(*pAct)=23;sem_func(*pAct)=f23;

/*-- S63  --*/
/* StmtList -> SmtList mM. Statement; */

pAct=pars_table[S63];
(*pAct).tok=tId;action(*pAct)=SHIFT;shift_to(*pAct)=S16;pAct++;
(*pAct).tok=tPrint;action(*pAct)=SHIFT;shift_to(*pAct)=S17;pAct++;
(*pAct).tok=tRead;action(*pAct)=SHIFT;shift_to(*pAct)=S18;pAct++;
(*pAct).tok=tIf;action(*pAct)=SHIFT;shift_to(*pAct)=S19;pAct++;
(*pAct).tok=tWhile;action(*pAct)=SHIFT;shift_to(*pAct)=S61;

}


/*--------------------------------------------------------------*/
ActionTableEntry GetActTableEntry(ParserStateType S,tokentype t)
/*--------------------------------------------------*/
/* Get current state S and token t                  */
/* return action to do                              */
/*--------------------------------------------------*/
{
int i=0;
while (i<NTERM_IN_LIST) {
      if((pars_table[S][i].tok==t)||(pars_table[S][i].tok==tOther))
	 return pars_table[S][i];
      i++;
}
return pars_table[0][1];
}
/*--------------------------------------------------------*/
/*Goto part of the parse table                            */
/*--------------------------------------------------------*/
ParserStateType Goto[NSTATES][NSYMBS];
/*--------------------------------------------------------*/
void SetGotoTable(void)
{
int i,j;
for(i=0;i<NSTATES;i++)
  for(j=0;j<NSYMBS;Goto[i][j]=i,j++);/*goto to the same state as default*/
Goto[S0][Program]=S1;Goto[S4][Declarations]=S5;
Goto[S6][DeclList]=S8;Goto[S7][StmtList]=S10;
Goto[S10][mM]=S63;Goto[S13][Type]=S22;
Goto[S17][Expression]=S27;Goto[S17][Term]=S28;Goto[S17][Factor]=S29;
Goto[S19][Expression]=S35;Goto[S19][BoolExp]=S34;Goto[S19][Term]=S28;
Goto[S19][Factor]=S29;
Goto[S20][Expression]=S35;Goto[S20][BoolExp]=S36;Goto[S20][Term]=S28;
Goto[S20][Factor]=S29;
Goto[S26][Expression]=S38;Goto[S26][Term]=S28;Goto[S26][Factor]=S29;
Goto[S32][Expression]=S41;Goto[S32][Term]=S28;Goto[S32][Factor]=S29;
Goto[S37][Type]=S45;Goto[S39][Term]=S46;Goto[S39][Factor]=S29;
Goto[S40][Factor]=S47;Goto[S42][StmtList]=S59;
Goto[S43][Expression]=S50;Goto[S43][Term]=S28;Goto[S43][Factor]=S29;
Goto[S44][StmtList]=S51;Goto[S51][mM]=S63;
Goto[S52][StmtList]=S54;Goto[S54][mM]=S63;
Goto[S56][Term]=S57;Goto[S56][Factor]=S29;Goto[S58][mM]=S42;
Goto[S59][mM]=S63;Goto[S59][mN]=S49;Goto[S60][mM]=S52;
Goto[S61][mM]=S20;Goto[S62][mM]=S44;Goto[S63][Statement]=S15;

}
/*-------------------------------------------------------------------*/
ParserStateType GetGotoTableEntry(ParserStateType s,SymbolType sym)
/*--------------------------------------------------*/
/* Get current state S and nonterminal symbol sym   */
/* return state where go to                         */
/*--------------------------------------------------*/

{
return Goto[s][sym];
}
/*--------------------------------------------------------------------*/
char *Rules[25]={
     {"0. Program'->Program."},
     {"1. Program -> prog id ; Declarations begin StmtList end"},
     {"2. Declarations -> var DecList;"},
     {"3. DecList -> DecList , id: Type"},
     {"4. DecList -> id: Type"},
     {"5. Type -> int"},
     {"6. Type -> real"},
     {"7. StmtList -> SmtList mM Statement;"},
     {"8. StmtList -> "},
     {"9. Statement -> id:=Expression"},
     {"10.Statement -> print Expression"},
     {"11.Statement -> read id"},
     {"12.Statement -> if BoolExp Then mM StmtList mN else mM StmtList fi"},
     {"13.Statement -> while mM BoolExp do mM StmtList od"},
     {"14.BoolExp -> Expression relop Expression"},
     {"15.Expression -> Expression addop Term"},
     {"16.Expression -> Term"},
     {"17.Term -> Term mulop Factor"},
     {"18.Term -> Factor"},
     {"19.Factor -> id"},
     {"20.Factor -> num"},
     {"21.Factor -> (Expression)"},
     {"22.Expression -> -Term"},
     {"23.mM -> "},/* mM and mN are markers for backpatcing */
     {"24.mN -> "}
};
/*--------------------------------------------------------------------*/
void PrintRule(int Rule)
/* print rule number Rule used for debug                              */
{
printf("REDUCED %s\n",Rules[Rule]);
}
/*--------------------------------------------------------------------*/