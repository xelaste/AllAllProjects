/*-----------------------------------------------------------------------
             C O M P I L E R  O F  T I N Y   L A N G U A G E
developed by Stekolchik Alexander 1998.
Module file GSTACK.C common stack operation function
       related files
       TQC.C       main function
       COMMON.H    common header file
       SCANNER.H  lexical analizer definitions and constants
       TLA.C      lexical analizer functions
       GSTACK.H  stack definitions and declarations
       HASH.H   hashtable header file
       HASH.C   hashtable functions
       STKENTRY H  parser stack definitions and declarations
       STKENTRY.C  parser stack function
       PARSER.H   parser header file
       PARS_TAB.C  definitions of LALR actions table and goto table
       PARSER.C    parser operation function
       SEMANTIC.H semantic actions constants
       SEMANTIC.C semantic action functions
---------------------------------------------------------------------------*/
#include <stdio.h>
#include <alloc.h>
#include <process.h>
#include "gstack.h"
static StackNodePtr alloc_node(void);
/*-----------------------------------------------------------*/
void push(StackNodePtr *top,void *body)
/* push new node body  into the stack                         */
{
StackNodePtr NewNode;
 NewNode=alloc_node();
 NewNode->body=body;
 NewNode->next=*top;
 *top=NewNode;
}
/*------------------------------------------------------------*/
void *pop(StackNodePtr *top)
/* poping top node from the stack */
{
  void *body;
  StackNodePtr next;
  if (*top==NULL) return NULL;
  body=(*top)->body;
  next=(*top)->next;
  free(*top);
  *top=next;
  return body;
}
/*-----------------------------------------------------------*/
static StackNodePtr alloc_node(void)
/*-----------------------------------------------------------*/
/* function for creating new node for stack                  */
/* return pointer to new node or NULL if there was an error  */
/*-----------------------------------------------------------*/
{
StackNodePtr new_node;
   new_node=(StackNodePtr) malloc(sizeof(StackNode));
   if (new_node==NULL) {
      fprintf(stderr,"Failed to allocate new node.\n");
      exit(1);
      }
return new_node;
}
/*--------------------------------------------------------------------*/