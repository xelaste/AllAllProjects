/*-----------------------------------------------------------------------
             C O M P I L E R  O F  T I N Y   L A N G U A G E
developed by Stekolchik Alexander 1998.
Module file PARSER.H constants and definitions for parser and parser tables
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
       PARS_TAB.C  definitions of LALR actions table and goto table
       PARSER.C    parser operation function
       SEMANTIC.H semantic actions constants
       SEMANTIC.C semantic functions
---------------------------------------------------------------------------*/

#ifndef __PARSER_H_
#define __PARSER_H_
#include "stkentry.h"
#define ParserError "Because of parser error skip "
#define MaxPrsErr 4
typedef enum {SHIFT,REDUCE,ACCEPT,ERROR} ActionType;
typedef struct _action_table_entry *ActTableEntryPtr;
typedef struct _action_table_entry
 {
 ActionType act; /*action to perform (shift/reduce/accept/error) */
 tokentype tok;
 union {
	struct for_reduce{
	      /*symbol to put onto the stack after reduce */
	      SymbolType newsymb;
	      int Rule;
	      int reduce_nsymb;
		  /* number of symbols to reduce from the stack */
	      void (*func)(StackEntryPtr,NonTermPtr);
		  /*Semantic action to perform */
	      } for_reduce ;
	      ParserStateType shift_goto;/*state to enter if shift */
      } action_data;
 } ActionTableEntry;
#define action(entry)         (entry).act
#define shift_to(entry)       (entry).action_data.shift_goto
#define new_sym(entry)        (entry).action_data.for_reduce.newsymb
#define symb_to_reduce(entry) (entry).action_data.for_reduce.reduce_nsymb
#define sem_func(entry)       (entry).action_data.for_reduce.func
#define Rule(entry)           (entry).action_data.for_reduce.Rule
#endif