/*********/
/* DAMKA */  /* Contain several auxiliary functions - comments are attached */
/*********/

#include "main.h"

/*******************************************************************/

/* G L O B A L S : */
pointer head;   	  /* pointer to the top of minimax tree */
char pos_eat[2];          /* holds one move-eating for penalty */
FILE *filep;              /* pointer to the report file */
char stalemate;           /* =1 if there is a stale-mate situation */

/*******************************************************************/
void switchb(boardt array)
/* switches players */

{
   boardt temp;
   char i,j;

   initialize(temp);
   for (i=1; i<=BOARDSIZE; i++)
	   for (j=1; j<=BOARDSIZE; j++)
		switch (array[i][j])
			{
			case COMP_SOLDIER: temp[BOARDSIZE+1-i][BOARDSIZE+1-j]=USER_SOLDIER;
				 break;
			case COMP_QUEEN: temp[BOARDSIZE+1-i][BOARDSIZE+1-j]=USER_QUEEN;
				 break;
			case USER_SOLDIER: temp[BOARDSIZE+1-i][BOARDSIZE+1-j]=COMP_SOLDIER;
				 break;
			case USER_QUEEN: temp[BOARDSIZE+1-i][BOARDSIZE+1-j]=COMP_QUEEN;
				 break;
			default: temp[BOARDSIZE+1-i][BOARDSIZE+1-j]=array[i][j];
			}
   copy(temp,array);
}
/*******************************************************************/
char eat_by_sol(char from_c,char from_l,char to_c,char to_l)
/* Eating by the soldier is legal? */
/* Four parameters are the coordinates, the last ones - the destination */

{
       if ( (from_c-to_c)==2 || (from_c-to_c)==-2 ) /* skip one figure? */
	  if (head->b->board[to_l][to_c]==EMPTY)        /* destination is empty ? */
	    if (head->b->board[(from_l+to_l)/2][(from_c+to_c)/2] <= COMP_SOLDIER)
		 return 0;                          /* legal eating */
       return 1;                                    /* illegal */
}
/*******************************************************************/
char eat_by_q(char from_c,char from_l,char to_c,char to_l)
/* Eating by queen is legal? On the contrary with the version for soldiers,
   this procedure modifies the board (removes eaten figures).
   Four parameters are the coordinates, the last two - the destination. */

{
     char unit_c, unit_l,                    /* for single move holding */
     temp, i, j;                             /* looping and auxiliary variables */
     unit_c = (to_c-from_c)/abs(to_c-from_c);
     unit_l = (to_l-from_l)/abs(to_l-from_l);

     if (head->b->board[to_l][to_c]!=0) return 1;
					     /* destination is not empty ? */
     if (abs(from_c-to_c)==abs(from_c-to_c))
	   {                                 /* does the move along diagonal? */
	   for(i=from_l+unit_l, j=from_c+unit_c;
			head->b->board[i][j]==0;
					i=i+unit_l, j=j+unit_c)
					     /* (skip blanks) */
	   if (i==to_l) return 1;            /* not eating - error */
	   if (head->b->board[i][j]>=USER_SOLDIER)
		return 1;                    /* not computer's figure - error */
	   head->b->board[i][j]=EMPTY;              /* computer's figure removing */
	   for( ;head->b->board[i][j]==EMPTY && i!=to_l; i=i+unit_l, j=j+unit_c);
					     /* (skip blanks) */
	   if (i!=to_l) return 1;            /* The second figure! - error */

/* modifications on the board: */

	   temp=head->b->board[from_l][from_c];
	   head->b->board[from_l][from_c]=EMPTY;
	   head->b->board[to_l][to_c]=temp;
           return 0;
	   }
     else return 1;                        /* if not along diagonal */
}
/*******************************************************************/
void board_draw(void)
/* board printing procedure */

{
   int i,j;
   printf("\n\xA9");
   printf (" a  b  c  d  e  f  g  h") ;
   printf(" \xAA\n");
   for (i=1 ; i<=BOARDSIZE ; i++)
     {
      if (i%2) printf ("%d   ",i);
          else printf("%d",i);
	for (j = i%2+1 ; j<=8 ;j=j+2)
            {
	    switch (head->b->board[i][j])
                   {
		    case  EMPTY : { textattr(WHITE*16);
				cprintf("%c%c%c",32,32,32);
				break; };
                    case COMP_SOLDIER : { textattr(WHITE*16+RED);
                                cprintf(" %c ",30);
                                break; };
                    case COMP_QUEEN : { textattr(WHITE*16+RED);
                                cprintf(" %c ",234);
                                break; };
		    case  USER_SOLDIER : { textattr(WHITE*16+BLUE);
                                cprintf(" %c ",127);
				break; };
		    case  USER_QUEEN : { textattr(WHITE*16+BLUE);
                                cprintf(" %c ",234);
                                break; }
                    }
	     if ((i%2)&&(j==8)) printf("");
             else printf("   ");
             }
      printf ("%d\n",i);
      }
   printf("\xC0");
   printf (" a  b  c  d  e  f  g  h") ;
   printf(" \xD9\n");
}
/*******************************************************************/
void initialize(boardt array)
/* initializing of array (board painting) */

{
   char *pnt;
   int i,j;

/* prohibited squares: */

   for (i=1; i<=BOARDSIZE; i=i+2)
      for (j=1; j<=BOARDSIZE; j=j+2)
		 array[i][j]=PROHIBITED;
   for (i=2; i<=BOARDSIZE; i=i+2)
      for (j=2; j<=BOARDSIZE; j=j+2)
		 array[i][j]=PROHIBITED;

/* border: */

   for (j=0; j<=BOARDSIZE+1; j++) {
		array[0][j]=PROHIBITED;        /* horizontal borders */
		array[9][j]=PROHIBITED;
	}
   for (i=1; i<=BOARDSIZE; i++) {
		array[i][0]=PROHIBITED;        /* vertical borders */
		array[i][9]=PROHIBITED;
	}

/* empty squares: */

   for (j=1; j<=BOARDSIZE; j=j+2) array[4][j]=EMPTY;
   for (j=2; j<=BOARDSIZE; j=j+2) array[5][j]=EMPTY;

/* soldiers: */

   for (i=1; i<=3 ;i=i+2)
      for (j=2; j<=BOARDSIZE ; j=j+2) array[i][j] = COMP_SOLDIER ;
   for (j=1; j<=BOARDSIZE; j=j+2)     array[2][j] = COMP_SOLDIER;

   for (i=6; i<=BOARDSIZE ;i=i+2)
      for (j=1; j<=BOARDSIZE ; j=j+2) array[i][j] = USER_SOLDIER ;
   for (j=2; j<=BOARDSIZE; j=j+2)     array[7][j] = USER_SOLDIER;

}
/*******************************************************************/
void copy (boardt array1, boardt array2)
/* copies array1 into array2 */

{
   char i,j;
   for (i=0; i<=BOARDSIZE+1; ++i)
       for (j=0; j<=BOARDSIZE+1; ++j)
	    array2[i][j]=array1[i][j];
}

/*******************************************************************/
void eat_exist(void)
/* checks if there is a possible eating for a player's figure */

{
   char i,j,k,
	sign,dir;
   for (i=1; i<=BOARDSIZE; i++)                /* lines */
      for (j=1; j<=BOARDSIZE; j++)             /* columns */
      {

/* Does the soldier may eat smth.? */

	   if (head->b->board[i][j]==USER_SOLDIER)
		for (sign=-1; sign<=1; sign+=2)  /* two vertical directions */
		    for (dir=-1; dir<=1; dir+=2) /* two horizontal directions */
			 if ((head->b->board[i+sign][j+dir]==COMP_SOLDIER ||
			      head->b->board[i+sign][j+dir]==COMP_QUEEN) &&
			     (head->b->board[i+sign*2][j+dir*2]==EMPTY))
			     {
			      pos_eat[0]=j;
			      pos_eat[1]=i;
			      return;
			     }

/* Does the queen may eat smth.? */

	   if (head->b->board[i][j]==USER_QUEEN)
		for (sign=-1; sign<=1; sign+=2)  /* two vertical directions */
		    for (dir=-1; dir<=1; dir+=2) /* two horizontal directions */
			 {
			 k=1;
			 while(head->b->board[i+k*sign][j+k*dir]!=PROHIBITED   &&
			       head->b->board[i+k*sign][j+k*dir]!=COMP_SOLDIER &&
			       head->b->board[i+k*sign][j+k*dir]!=COMP_QUEEN   &&
			       head->b->board[i+k*sign][j+k*dir]!=USER_SOLDIER &&
			       head->b->board[i+k*sign][j+k*dir]!=USER_QUEEN)
						k++;
/* (move along a diagonal until any figure and empty square) */

			 if((head->b->board[i+k*sign][j+k*dir]==COMP_SOLDIER ||
			     head->b->board[i+k*sign][j+k*dir]==COMP_QUEEN)  &&
/* the next square is empty? */
			    (head->b->board[i+(k+1)*sign][j+(k+1)*dir]==EMPTY))
				{
				pos_eat[0]=j;
				pos_eat[1]=i;
				return;
				}
			 }
      }       /* end of main 'for' */
}
/*******************************************************************/
char count_figures(boardt board, char PLAYER)
/* counts the numbers of figures of PLAYER: 1 - COMP or 0 - USER */

{
        char i,j,
             countus=0,
	     countco=0;

/* even and odd rows have been processed separately for effectiveness */
/* even rows: */
	for (i=1; i<SIZE; i+=2)      /* lines */
	   for (j=2; j<SIZE; j+=2)   /* columns */
	      {
	      if (board[i][j]==USER_SOLDIER || board[i][j]==USER_QUEEN)
		  countus++;
	      if (board[i][j]==COMP_SOLDIER || board[i][j]==COMP_QUEEN)
		  countco++;
	      }
/* odd rows: */
	for (i=2; i<SIZE; i+=2)      /* lines */
	   for (j=1; j<SIZE; j+=2)   /* columns */
	      {
	      if (board[i][j]==USER_SOLDIER || board[i][j]==USER_QUEEN)
		  countus++;
	      if (board[i][j]==COMP_SOLDIER || board[i][j]==COMP_QUEEN)
		  countco++;
	      }
	if(PLAYER) return countco;
	      else return countus;
}
/***************************************************************/
pointer check_eat(pointer first, boardt father, char sign)
/* checks possible eatings in minmax tree layer and modifies nodes */

{
    pointer aux=first;

    while(aux!=NULL)
	 {
	 if(count_figures(aux->b->board,0)==count_figures(father,0)
		  && count_figures(aux->b->board,1)==count_figures(father,1))
/* figures numbers were not changed: simple move */
		{
		if(aux->b->board[pos_eat[1]][pos_eat[0]]!=EMPTY)
			{
			if(aux->b->board[pos_eat[1]][pos_eat[0]]==COMP_SOLDIER*sign)
				aux->val-=sign*6;
			if(aux->b->board[pos_eat[1]][pos_eat[0]]==COMP_QUEEN*sign)
				aux->val-=sign*31;
			aux->b->board[pos_eat[1]][pos_eat[0]]=EMPTY;
			}
		else
			{
			modify(father,aux->b->board);
			aux->val-=sign*31;
			}                                 /* REPORT: */
		}
	 if(count_figures(aux->b->board,1)==0) aux->val=-50;
	 if(count_figures(aux->b->board,0)==0) aux->val=50;
	 aux=aux->next;
	 }
    return first;
}

/***************************************************************/
void modify(boardt b1, boardt b2)
/* check difference between boards and removes the figure was moved */

{
    char i, j;

    for(i=1; i<SIZE; i++)
	for(j=1; j<SIZE; j++)
		if(b1[i][j]==EMPTY && b2[i][j]!=EMPTY)
			{
			b2[i][j]=EMPTY;
			return;
			}
}
/***************************************************************/
