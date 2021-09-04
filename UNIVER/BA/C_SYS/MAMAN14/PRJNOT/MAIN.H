/*********/
/* DAMKA */             /* Main header file */
/*********/

#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <alloc.h>

#define BOARDSIZE 8
#define SIZE BOARDSIZE+2
   /* (we've included the border into the board for functions simplicity) */

   /* figures (and board's fields) have been coded by integer numbers: */
#define EMPTY 0
#define USER_SOLDIER 1
#define USER_QUEEN 2
#define COMP_SOLDIER -1
#define COMP_QUEEN -2
#define PROHIBITED 3

#define DEPTH_MIN_MAX 5              /* depth of minimax tree */

typedef char boardt[SIZE][SIZE] ;    /* board type */

typedef struct board_block{          /* removable part of a node */
	boardt board;                /* board */
	char move[4];                /* move and eating flag */
	} Bblock;

typedef struct leave{                /* leave node for minmax tree: */
	char val;                    /* value of the move */
	struct leave *next;
	} Leave;

typedef struct tnode {               /* not leave node of minmax tree: */
       char val;                     /* value of the move */
       Bblock *b;                    /* pointer to appropriate board */
       struct tnode *next;           /* to the next move of the level */
       void *son;                    /* son may point both on leaves and nodes */
       } Tnode;

typedef Tnode *pointer;              /* to not leave node of minmax tree */
typedef Leave *pointleave;           /* to leave node */

   /* --- GLOBAL VARIABLES: --- */
extern pointer head;                 /* head of minimax tree */
extern char pos_eat[2];              /* holds possible eating for possible penalty and last move */
extern FILE* filep;                  /* pointer to the report file */
extern char stalemate;
   /* ------------------------- */

extern void initialize(boardt array);
   /* board initialization */

extern void board_draw(void);
   /* board print */

extern char move_of_pl(void);
   /* accepts a move from the user */

extern char eat_by_sol(char from_c,char from_l,char to_c,char to_l);
   /* returns 0 if eating by soldier is possible, else - 1 */

extern char eat_by_q(char from_c,char from_l,char to_c,char to_l);
   /* eating by the queen is possible? */

extern void copy (boardt array1, boardt array2);
   /* array copying */

extern void switchb(boardt array);
   /* players interchanging */

extern pointer bestbranch(void);
   /* finds the best move and realize it */

extern void buildtree(pointer ptr, char depth);
   /* min-max tree building */

extern void *generate(boardt brd,char level);
   /* generate a level for min-max tree */

extern void *addnode(void *first, boardt brd, char level);
   /* adds a node with possible move to list of possible moves from some state */

extern pointer killtree(pointer head);
   /* kills minimax tree - releases memory */

extern void eat_exist(void);
   /* checks if there is possible eating for the player */

extern pointer check_eat(pointer first, boardt father, char level);
   /* checks possible eatings in minmax tree layer and modifies nodes */

extern char count_figures(boardt board, char PLAYER);
   /* counts the numbers of figures of PLAYER: COMP or USER */

extern void modify(boardt b1, boardt b2);
   /* check difference between boards and removes the figure was moved */

