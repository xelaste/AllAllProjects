/*-----------------------------------------------------------------------
             C O M P I L E R  O F  T I N Y   L A N G U A G E
developed by Stekolchik Alexander 1998.
Module file HASH.C hashtab  operation functions.
       related files
       TQC.C       main function
       COMMON.H    common header file
       SCANNER.H  lexical analizer definitions and constants
       TLA.C      lexical analizer functions
       GSTACK.H  stack definitions and declarations
       GSTACK.C  common stack operation function
       HASH.H   hashtable header file
       STKENTRY H  parser stack definitions and declarations
       STKENTRY.C  parser stack function
       PARSER.H   parser header file
       PARS_TAB.C  definitions of LALR actions table and goto table
       PARSER.C    parser operation function
       SEMANTIC.H semantic actions constants
       SEMANTIC.C semantic action functions
---------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <alloc.h>
#include <process.h>
#include "hash.h"
static hashptr hashtab[HASHSIZE];
/*---------------------------------------------------------*/
void inithash (void)
/* primary initialization of hash table */
{
int i;
for(i=0;i<HASHSIZE;hashtab[i]=NULL,i++);
}
/*--------------------------------------------------------*/
unsigned hash(char *s)
/* compute hashvalue of string s */
/* return hashvalue of string  s */
{
unsigned hashval;
for (hashval=0;*s;s++)
     hashval=*s+PRIME*hashval;
return hashval % HASHSIZE;
}
/*-------------------------------------------------*/
void *lookup (char *s)
/* check if there is occurence of s in the hashtable               */
/* return the body of the found node or null if there was not found*/
{
hashptr np;
for (np=hashtab[hash(s)];np!=NULL;np=np->next)
     if (!strcmp(s,np->name)) return np->body;
return NULL;
}
/*------------------------------------------------*/
void *install(void *body,char *s)
/*install new node in hash table                  */
/*parameters body ,s data for new node            */
/*return new node or null if there was an error   */
/*------------------------------------------------*/
{
hashptr np=NULL;
unsigned hashval;
np=(hashptr) malloc(sizeof(hashnode));
if(np==NULL || (np->name=strdup(s))==NULL){
   printf("malloc failed \n");
   exit(1);
  } 
np->body=(body==NULL?np->name:body);
hashval=hash(s);
np->next=hashtab[hashval];
hashtab[hashval]=np;
return np;
}
/*----------------------------------------------------------------*/
