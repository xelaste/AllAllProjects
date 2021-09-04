/*-----------------------------------------------------------------------
             C O M P I L E R  O F  T I N Y   L A N G U A G E
developed by Stekolchik Alexander 1998.
Module file STKENTRY.C  parser stack functions 
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
       PARSER.H   parser header file
       PARS_TAB.C  definitions of LALR actions table and goto table
       PARSER.C    parser operation function
       SEMANTIC.H semantic actions constants
       SEMANTIC.C semantic action functions
---------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <alloc.h>
#include <process.h>
#include "gstack.h"
#include "stkentry.h"

static StackNodePtr top=NULL;
static StackEntryPtr alloc_entry(void);
/*---------------------------------------------------------------*/
void PrintEntryImage(StackEntry  se)
/* function prints context of the stack entr se used for debug   */
{
char *SymbolImage[]={"Program","Declarations","StmtList","DeclList","Type",
		     "Statement","Expression","BoolExp","Term","Factor",
		     "mM","mN"};

 switch(se.type){
      case TERMINAL    : printf(" tr %s ",((TermPtr)se.entry)->Lexeme);
			 break;
      case NON_TERMINAL: printf(" ntr %s ",
				SymbolImage[((NonTermPtr)se.entry)->Symb]);
			 break;
      case STATE       : printf(" State S%d ",((StateSPtr)se.entry)->state);
			 break;
      default          : break;
  }
}
/*---------------------------------------------------------------*/
void PushEntry(StackEntryType type, void *body)
/*push entry to the stack                                        */
/*get type of entry - type and context body                      */
/*---------------------------------------------------------------*/
{
 StackEntryPtr new_entry;
 new_entry=alloc_entry();
 new_entry->type=type;
 new_entry->entry=body;
 push(&top,new_entry);
}
/*---------------------------------------------------------------*/
StackEntryPtr PopEntry(void)
/* pop entry from the stack  return the top entry of the stack   */
/*---------------------------------------------------------------*/
{
 StackEntryPtr next_entry;
 next_entry=pop(&top);
 if(next_entry==NULL)
   {
   fprintf(stderr,"Stack underflow.\n");
   exit(3);
   }
 return next_entry;
}
/*---------------------------------------------------------------*/
void FreeStackEntry(StackEntryPtr eptr)
{
if (eptr!=NULL) free (eptr);
}
/*---------------------------------------------------------------*/
void DiscardStack(void)
/* free memory ocupied by stack                                  */
/*---------------------------------------------------------------*/
{
 StackEntryPtr eptr;
 while (top) {eptr=pop(&top); FreeStackEntry(eptr);}
}
/*---------------------------------------------------------------*/
void *TopEntry(void)
/* get top entry from the stack without poping it                */
/*---------------------------------------------------------------*/
{
StackEntryPtr eptr;
if(top!=NULL) {eptr=top->body;
	       return eptr->entry;
	       }
return NULL;
}
/*---------------------------------------------------------------*/
static StackEntryPtr alloc_entry()
/* allocating memory for new entry return pointer to new entry   */
/*---------------------------------------------------------------*/
{
StackEntryPtr new_entry;
new_entry=(StackEntryPtr)calloc(1,sizeof(StackEntry));
if(new_entry==NULL){
		   fprintf(stderr,"Cannot allocate new stack entry.\n");
		   exit(2);
		   }
return new_entry;
}
/*---------------------------------------------------------------------*/
