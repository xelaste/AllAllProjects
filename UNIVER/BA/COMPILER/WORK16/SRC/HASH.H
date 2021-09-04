/*-----------------------------------------------------------------------
             C O M P I L E R  O F  T I N Y   L A N G U A G E
developed by Stekolchik Alexander 1998.
Module file HASH.H definitions and constants for hashing table.
       related files 
       TQC.C       main function
       COMMON.H    common header file
       SCANNER.H  lexical analizer definitions and constants
       TLA.C      lexical analizer functions
       GSTACK.H  stack definitions and declarations
       GSTACK.C  common stack operation function
       HASH.C   hashtable functions
       STKENTRY H  parser stack definitions and declarations
       STKENTRY.C  parser stack function
       PARSER.H   parser header file
       PARS_TAB.C  definitions of LALR actions table and goto table
       PARSER.C    parser operation function
       SEMANTIC.H semantic actions constants
       SEMANTIC.C semantic functions
---------------------------------------------------------------------------*/
#ifndef __HASH_T_
#define __HASH_T_
#define HASHSIZE 101
#define PRIME    31
typedef struct _hash_node *hashptr;
typedef struct _hash_node
		{
		void *body;
		char *name;
		hashptr next;
		} hashnode;
void inithash (void);
void *lookup (char *s);/*/check if there is occurence of s */
void *install(void *body,char *s); /* install new node in hash table */
#endif
/* __hash.h__  */