/*-----------------------------------------------------------------------
   L E X I C A L   A N A L I Z E R   O F   T I N Y   L A N G U A G E
Header file TLA.H
	    of the program TLA.C
	    related files  TLA.H definitions
			   TLA.C functions;
			   *.TIN file of data
-------------------------------------------------------------------------*/
#ifndef _TLA
#define _TLA
#define NUM_OF_KEYWORDS      15
#define LEGAL_FILE_EXTENTION ".tin"
#define InputLineLen         132
#define NumberOfStates       25
#define MaxIdLen             30
#define EmptyString          ""
#define CopyRight "Compiler project. Developed by Alexander Stekolchik.1997"
typedef enum {digit,letter,plus,minus,mul,div,relop,grt,less,
	     lpar,rpar,point,colon,semicolon,comma,space,other,
	     SCANOF,invalid} terminaltype;

typedef enum {FALSE,TRUE} BOOL;

typedef enum {tBegin,tDo,tElse,tEnd,tFi,tIf,tInt,tOd,tPrint,tProg,
	      tRead,tReal,tThen,tVar,tWhile,tId,tNum,tRelop,tPlus,tMinus,
	      tMulop,tAssignop,tLpar,tRpar,tComma,tEndOfProgram,
	      tColon,tSemicolon,tEmpty,tIllegal,tEof} tokentype;

typedef enum {FIRST,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,LAST,INVALID
	     } statetype;

typedef struct AttribTag
	       {
		tokentype token;
		BOOL OK;
		char *Attribute;
	       } Attrib;

typedef struct TokenTag {
			tokentype T;
			char *Lexeme;
			char *Attribute;
			} token;

typedef struct sTransitionTableItemTag *psTransitionItem;
typedef struct sTransitionTableItemTag
	       {
	       statetype    S;
	       terminaltype t;
	       psTransitionItem next;
	       } sTransitionTableItem;
#endif