/*-----------------------------------------------------------------------
             C O M P I L E R  O F  T I N Y   L A N G U A G E
developed by Stekolchik Alexander 1998.
Module file SEMANTIC.H semantic action constants and definitions
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
       SEMANTIC.C semantic action functions
---------------------------------------------------------------------------*/

#ifndef __SEMANTIC_
#define __SEMANTIC_
#define NumberOfCommand 27
#define MAX_NUMBER 10
#define MAX_QUAD_PROGRAM_SIZE 1000
#define MAX_QUAD_ID_LEN       11
#define DummyUseParameters(x,y)    x=x;y=y
#define MallocFailed    {fprintf(stderr,"%s\n","malloc failed");exit(1);}
#define DuplicateDefinition "Duplicate definition of "
#define InvalidType         "Invalid data type "
#define UnknownId           "Unknown identifier "
#define CodeOverFlow        "Produced code overflow from buffer" 
typedef enum {IASN,IPRT,IINP,IEQL,INQL,ILSS,IGRT,IADD,ISUB,IMLT,IDIV,
	      RASN,RPRT,RINP,REQL,RNQL,RLSS,RGRT,RADD,RSUB,RMLT,RDIV,
	      ITOR,RTOI,JUMP,JMPZ,HALT,ENDQUAD=9999} Quad_Instruction;
typedef char  ArgumentType[MAX_QUAD_ID_LEN];
typedef struct _quadruple {
	       Quad_Instruction instr;
	       ArgumentType arg1,arg2,arg3;
	       } quadrupletype;
#endif

