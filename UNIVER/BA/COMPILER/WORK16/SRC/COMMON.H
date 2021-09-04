/*-----------------------------------------------------------------------
             C O M P I L E R  O F  T I N Y   L A N G U A G E
developed by Stekolchik Alexander 1998.
Module file COMMON.H common constants and definitions
       related files 
       TQC.C       main function
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
       SEMANTIC.C semantic functions
---------------------------------------------------------------------------*/

#ifndef __COMMON_H
#define __COMMON_H
#define FILE_NAME_LENTH          40
#define CopyRight "Compiler project. Developed by Alexander Stekolchik.1998"
#define AllRight  "OK! There was found none error in the source code !!!\n"
#define INPUT_EXTENTION ".tin"
#define LIST_EXTENTION  "lst"
#define QUAD_EXTENTION  "qud"
#define INTEGER         "Integer"
#define REAL            "Real"
#define MULTIPLY        "Multiply"
#define DIVIDE          "Divide"
#define GRT             "Great than"
#define LSS             "Less than"
#define EQL             "Equal"
#define NEQL            "Not equal"
#define EmptyString          ""
#define MaxIdLen            20
#define AtrStrLen           30
#define MsgLn                150
#define NSTATES 65
#define NSYMBS  12
#define NTERM   30
#define NTERM_IN_LIST 7

#define DelMsg               memset(msg,'\0',MsgLn)
#define PrintMessage(fp)     fprintf(fp,"%s",msg)
#define PrintMsgAndClear(fp) PrintMessage(fp);DelMsg
typedef enum {FALSE,TRUE} BOOL;
typedef char *DataType;
typedef enum {tBegin,tDo,tElse,tEnd,tFi,tIf,tInt,tOd,tPrint,tProg,
	      tRead,tReal,tThen,tVar,tWhile,tId,tNum,tRelop,tPlus,tMinus,
	      tMulop,tAssignop,tLpar,tRpar,tComma,tEndOfProgram,
	      tColon,tSemicolon,tEmpty,tIllegal,tEof,tOther} tokentype;
typedef struct _TokenTag {
			   tokentype T;
			   char Lexeme[MaxIdLen+1];
			   char Atribute[AtrStrLen+1];
			 } token;

typedef enum {S0,S1,S2,S3,S4,S5,S6,S7,S8,S9,
	      S10,S11,S12,S13,S14,S15,S16,S17,S18,S19,
	      S20,S21,S22,S23,S24,S25,S26,S27,S28,S29,
	      S30,S31,S32,S33,S34,S35,S36,S37,S38,S39,
	      S40,S41,S42,S43,S44,S45,S46,S47,S48,S49,
	      S50,S51,S52,S53,S54,S55,S56,S57,S58,S59,
	      S60,S61,S62,S63,S64} ParserStateType;

typedef enum  {Program,Declarations,StmtList,DeclList,Type,Statement,
	       Expression,BoolExp,Term,Factor,mM,mN} SymbolType;

#endif
