/*-----------------------------------------------------------------------
             C O M P I L E R  O F  T I N Y   L A N G U A G E
developed by Stekolchik Alexander 1998.
Module file GSTACK.H stack constants and definitions
       related files 
       TQC.C       main function
       COMMON.H    common header file
       SCANNER.H  lexical analizer definitions and constants
       TLA.C      lexical analizer functions
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

#ifndef __GSTACK_H_
#define __GSTACK_H_
typedef struct _stack_node *StackNodePtr;
typedef struct _stack_node
	       {
		void *body;
		StackNodePtr next;
	       } StackNode;
void push(StackNodePtr *top,void *body);
void *pop(StackNodePtr *top);
#endif
/* __GSTACK.H__  */