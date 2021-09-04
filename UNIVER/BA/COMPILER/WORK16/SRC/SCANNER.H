/*-----------------------------------------------------------------------
             C O M P I L E R  O F  T I N Y   L A N G U A G E
developed by Stekolchik Alexander 1998.
Module file SCANNER.H lexical analizer constants and definitions
       related files 
       TQC.C       main function
       COMMON.H    common header file
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

#ifndef __SCANNER_H
#define __SCANNER_H
#include "common.h"
#define NUM_OF_KEYWORDS      15
#define InputLineLen         132
#define NumberOfStates       28
typedef enum {digit,letter,plus,minus,mul,div,relop,grt,less,
	     lpar,rpar,point,colon,semicolon,comma,space,other,
	     SCANOF,invalid} abctype;

typedef enum {FIRST,A,B,C,D,E,F,F1,G,H,I,J,K,K1,L,L1,M,N,O,P,Q,
	      LAST,INVALID} statetype;

typedef struct AtribTag
	       {
		tokentype token;
		BOOL OK;
		char *Atribute;
	       } Atrib;

typedef struct sTransitionTableItemTag *psTransitionItem;
typedef struct sTransitionTableItemTag
	       {
	       statetype    S;
	       abctype t;
	       psTransitionItem next;
	       } sTransitionTableItem;
#endif