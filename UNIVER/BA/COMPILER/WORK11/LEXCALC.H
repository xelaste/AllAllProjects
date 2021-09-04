/*-----------------------------------------------------------------------
Header file LEXCALC.H
	    of the program LEXCALC.C
	    related files  LEXCALC.C main programm and function
			   LEXCALC.H definitions
			   EXPR.CAL file of data
-------------------------------------------------------------------------*/
#ifndef _LEXCALC
#define _LEXCALC
#define NUM_OF_KIND 6
#define INPUT_LENTH 10
typedef enum {digit,op,point,lBracket,rBracket,var,relop,end,other} terminals;
typedef enum {FALSE,TRUE} BOOL;
typedef enum {tNUM,tOP,tlBRACKETs,trBRACKETs,tVAR,
	      tRELOP,tEND,tILLEGAL,tEMPTY} token;
typedef enum {FIRST,A,B,C,D,E,F,G,H,I,J,LAST} States;
char *ImageList[]={"NUM","OP","lBRACKETs","rBRACKETs",
		   "VAR","RELOP","END","ILLEGAL","EMPTY"};
typedef struct Attrib
	       {
		token Token;
		BOOL OK;
		char *desc;
	       };
struct Attrib StAttr[12];
States  DELTA[12][9];
char *IMAGE (token t) {return ImageList[t];}
#endif