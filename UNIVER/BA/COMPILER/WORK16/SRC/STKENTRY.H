/*-----------------------------------------------------------------------
             C O M P I L E R  O F  T I N Y   L A N G U A G E
developed by Stekolchik Alexander 1998.
Module file STKENTRY.H definitions for the parser stack
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
       SEMANTIC.C semantic functions
---------------------------------------------------------------------------*/

#ifndef __STACK_ENTRY_H
#define __STACK_ENTRY_H
#include "gstack.h"
#include "common.h"

typedef enum {TERMINAL,NON_TERMINAL,STATE} StackEntryType;
typedef token TerminalType,*TermPtr;
typedef struct _STATE {
	       ParserStateType state;
} StateS,*StateSPtr;
typedef struct _list *LstPtr;
typedef struct _list{
	       int quad;
	       LstPtr next;
	       } ListType;

typedef struct _listhead {
	       LstPtr last;
	       LstPtr top;
	       } ListHeadType,*LstHeadPtr;

typedef struct _NonTerminal {
			     SymbolType Symb;
			     char Atribute[AtrStrLen+1];
			     char ntValue[MaxIdLen];
			     int quad;
			     LstHeadPtr NextList;
			     LstHeadPtr TrueList;
			     LstHeadPtr FalseList;
} NonTerminalType,*NonTermPtr;

typedef struct _StackEntry *StackEntryPtr;

typedef struct _StackEntry {
		StackEntryType type;
		void *entry;
	       } StackEntry;

void PushEntry(StackEntryType type, void *body);
StackEntryPtr PopEntry(void);
void FreeStackEntry(StackEntryPtr eptr);
void DiscardStack(void);
void *TopEntry(void);
#endif
