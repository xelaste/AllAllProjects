/*-----------------------------------------------------------------------
Header file LEXCALC.H
       related files  MAIN.C  main program and function
		      Lexcalc.c - Lexical analyzer function.
		      PredPars.c - predictive parser functions
		      Lexcalc.h - definition header file
		      expr.cal  - file of data
-----------------------------------------------------------------------*/
#if !defined __LEXCALC
#define __LEXCALC
#define NUM_OF_TOKEN 12
#define NUM_OF_STATES 16
#define INPUT_LENTH 10
typedef enum {digit,plus,minus,mul,div,point,lBracket,rBracket,var,
						 relop,end,other} terminals;
typedef enum {FALSE,TRUE} BOOL;
typedef enum {tNUM,tPLUS,tMINUS,tMUL,tDIV,tlBRACKET,trBRACKET,tVAR,
	      tRELOP,tEND,tILLEGAL,tEMPTY,tSCANOF} token;
typedef enum {FIRST,A,B,C,D,E,F,G,H,I,J,M,N,O,LAST} States;
typedef struct AttribTag
	       {
		token Token;
		BOOL OK;
		char *desc;
	       } Attrib;
typedef struct ListTag *ListP;
typedef struct ListTag {
			token T;
			char *Lexeme;
			ListP next;
			} List;
#endif
