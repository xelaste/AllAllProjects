#include <stdio.h>
#include <conio.h>
#define STATES_NUMBER 8
#define SIZE_OF_ABC   5
#define EOL          '\n'
#define FALSE         0
#define TRUE          1
/*kind of characters can be inputed*/
typedef enum {DIGIT,POINT,SIGN,EXP,OTHER} LETTERS;
/* possibal states of automata */
typedef enum {FIRST,WHOLE,DECIMAL,NEG,POWER,POWER_SIGN,ISFLOAT,IS_NOT_FLOAT}
	     STATES;
LETTERS check_input(char ch);
/*function for check what is the inputed character */
/*
This function will get from standart input string of characters
and check if the head of string is the floating point number
The program algorith based at automata
*/
int isfloat (void);
/*------------------------------------------*/
void main ()
{
int result;
result=isfloat();
if (result) printf("There is float number followed by string\n");
	    else  printf("There is not float number followed by string\n");
}
/*-----------------------------------------*/
int isfloat (void)
{
char ch;
LETTERS INPUT;
STATES THE_STATE=FIRST, /* the first state of automata*/
DELTA [STATES_NUMBER][SIZE_OF_ABC];/*the moving function*/
/*FIRST */
DELTA[FIRST][DIGIT]=WHOLE;
DELTA[FIRST][SIGN] =NEG  ;
DELTA[FIRST][POINT]=DELTA[FIRST][EXP]=DELTA[FIRST][OTHER]=IS_NOT_FLOAT;
/* NEG */
DELTA[NEG][POINT]=DELTA[NEG][EXP]=DELTA[NEG][SIGN]=IS_NOT_FLOAT;
DELTA[NEG][OTHER]=IS_NOT_FLOAT;
DELTA[NEG][DIGIT]  =WHOLE;
/* WHOLE */
DELTA[WHOLE][DIGIT]=WHOLE;
DELTA[WHOLE][POINT]=DECIMAL;
DELTA[WHOLE][EXP]  =POWER;
DELTA[WHOLE][SIGN] =DELTA[WHOLE][OTHER]=IS_NOT_FLOAT;
/* DECIMAL */
DELTA[DECIMAL][DIGIT]=ISFLOAT;
DELTA[DECIMAL][SIGN]=DELTA[DECIMAL][EXP]=DELTA[DECIMAL][POINT]=IS_NOT_FLOAT;
DELTA[DECIMAL][OTHER]=IS_NOT_FLOAT;
/* POWER */
DELTA[POWER][DIGIT]=ISFLOAT;
DELTA[POWER][SIGN]=POWER_SIGN;
DELTA[POWER][POINT]=DELTA[POWER][EXP]=DELTA[POWER][OTHER]=IS_NOT_FLOAT;
/*POWER_SIGN*/
DELTA[POWER_SIGN][DIGIT]=ISFLOAT;
DELTA[POWER_SIGN][SIGN]=IS_NOT_FLOAT;
DELTA[POWER_SIGN][POINT]=DELTA[POWER_SIGN][EXP]=IS_NOT_FLOAT;
DELTA[POWER_SIGN][OTHER]=IS_NOT_FLOAT;
/* ISFLOAT */
DELTA[ISFLOAT][DIGIT]=DELTA[ISFLOAT][SIGN]=DELTA[ISFLOAT][EXP]=ISFLOAT;
DELTA[ISFLOAT][POINT]=DELTA[ISFLOAT][OTHER]=ISFLOAT;
/* IS_NOT_FLOAT */
DELTA[IS_NOT_FLOAT][DIGIT]=DELTA[IS_NOT_FLOAT][SIGN]=IS_NOT_FLOAT;
DELTA[IS_NOT_FLOAT][EXP]=IS_NOT_FLOAT;
DELTA[IS_NOT_FLOAT][POINT]=DELTA[IS_NOT_FLOAT][OTHER]=IS_NOT_FLOAT;
while ((ch=getchar())!=EOL)
       {INPUT=check_input(ch);
       THE_STATE=DELTA[THE_STATE][INPUT];
       }
return (THE_STATE==ISFLOAT) ? TRUE : FALSE;
}
/*------------------------------------*/
LETTERS check_input(char ch)
{
LETTERS LETTER;
return ((ch-'0')>=0&&(ch-'9')<=0) ? DIGIT :
(ch=='.') ? POINT :
((ch=='e')|| (ch=='E')) ? EXP :
(ch=='-') ? SIGN : OTHER;
}