/*********/
/* DAMKA */     /* function generate which builds a level in minmax tree */
/*********/

#include "main.h"

void *generate(boardt brd, char level)
/* generates all possible moves on the board according to level:
     for player - odd levels (excluding 0) or even levels for computer */

{
   pointer first=NULL;          /* nodes */
   pointleave firl=NULL;        /* leaves */

   char i,j,l,
	sign,     /* range -1 or 1; sign for even and odd layers in the tree */
	dir,back; /* range -1 or 1; count four different directions on board */

   pos_eat[0]=pos_eat[1]=0;   /* for removing figure in the penalty case */
   if (level%2)	sign=1;
	else 	sign=-1;

   for (i=1; i<=BOARDSIZE; i++)                  /* lines */
      for (j=1; j<=BOARDSIZE; j++)               /* columns */
	 {
	  if (brd[i][j]==COMP_SOLDIER*sign)
		 {
/* MOVING: */      for(dir=-1; dir<=1; dir+=2)   /* left and right */
		      if (brd[i+sign][j+dir]==EMPTY)
			    {
			     if(level==DEPTH_MIN_MAX-1)
				firl=addnode(firl,brd,level);
			     else
				first=addnode(first,brd,level);
			     if(level==1) /* we need to hold the move name */
				{
				first->b->move[0]=j;
				first->b->move[1]=i;
				first->b->move[2]=j+dir;
				first->b->move[3]=i+sign;
				}
/* for all but the last level update the board: */
			     if(level < DEPTH_MIN_MAX-1)
				{
				first->b->board[i][j]=EMPTY;
				first->b->board[i+sign][j+dir]=COMP_SOLDIER*sign;
				}
/* becomes queen? */         if((i==7 && sign>0) || (i==2 && sign<0))
				{
				first->val+=sign*25;
				if(level < DEPTH_MIN_MAX-1)
				     first->b->board[i+sign][j+dir]=COMP_QUEEN*sign;
				}
/* near a boarder is safe */
			     if(j+dir==1 || j+dir==8)
				if(level < DEPTH_MIN_MAX-1) first->val+=sign;
						       else firl->val+=sign;
			     }
/* EATING: */      for (back=-1; back<=1; back+=2)   /* two vertical directions */
			for (dir=-1; dir<=1; dir+=2) /* two horizontal directions */
			    if ((brd[i+back][j+dir]==USER_SOLDIER*sign ||
				 brd[i+back][j+dir]==USER_QUEEN*sign) &&
				 brd[i+back*2][j+dir*2]==EMPTY)
				{
				if(level==DEPTH_MIN_MAX-1)
					firl=addnode(firl,brd,level);
				else
					first=addnode(first,brd,level);
				if(level==1) /* we need to hold the move name */
					{
					first->b->move[1]=i;
					first->b->move[0]=j;
					first->b->move[3]=i+back*2;
					first->b->move[2]=j+dir*2;
					}
				pos_eat[0]=j; pos_eat[1]=i;
/* values for eating: */        if(brd[i+back][j+dir]==USER_QUEEN*sign)
					if(level<DEPTH_MIN_MAX-1)
						first->val+=sign*30;
					    else firl->val+=sign*30;
				if(brd[i+back][j+dir]==USER_SOLDIER*sign)
					if(level<DEPTH_MIN_MAX-1)
						first->val+=sign*5;
					    else firl->val+=sign*5;
/* forward is better than backward: */
				if(back*sign>0)
					if(level<DEPTH_MIN_MAX-1)
						first->val+=sign*2;
					    else firl->val+=sign*2;
/* for all but the last level update the board: */
				if(level < DEPTH_MIN_MAX-1)
				   {
				   first->b->board[i][j]=EMPTY;
				   first->b->board[i+back][j+dir]=EMPTY;
				   first->b->board[i+back*2][j+dir*2]=COMP_SOLDIER*sign;
				   }

				/**** insert DFS for soldiers here */

/* queen? */ 			if((i+back*2==8 && sign>0 || i+back*2==1 && sign<0) &&
					brd[i+back][j+dir]==USER_SOLDIER*sign
/* for all but the last level update the board: */
						&& level < DEPTH_MIN_MAX-1)
					first->b->board[i+back*2][j+dir*2]=COMP_QUEEN*sign;
				}
		 }

	  if (brd[i][j]==COMP_QUEEN*sign)
/* QUEEN: ------------------------------------------------------------ */
	   for(back=-1; back<=1; back+=2)   /* all 4 directions */
	      for(dir=-1; dir<=1; dir+=2)
		 {
		  char k;     /* parameter: length of a move */
/* possible moves: */
		  for(k=1; brd[i+back*k][j+dir*k]==EMPTY; k++)
		      {
		      if(level==DEPTH_MIN_MAX-1)
				firl=addnode(firl,brd,level);
			     else
				first=addnode(first,brd,level);
		      if(level==1)  /* move name only for 1st level */
				{
				 first->b->move[0]=j;
				 first->b->move[1]=i;
				 first->b->move[2]=j+dir*k;
				 first->b->move[3]=i+back*k;
				 }
		      if(level < DEPTH_MIN_MAX-1) /* update board: */
				{
				first->b->board[i][j]=EMPTY;
				first->b->board[i+back*k][j+dir*k]=COMP_QUEEN*sign;
				}
		      } /* here we have come to some figure or to the board */
/* possible eatings: */
		  if((brd[i+back*k][j+dir*k]==USER_SOLDIER*sign ||
		      brd[i+back*k][j+dir*k]==USER_QUEEN*sign) &&
		      brd[i+back*(k+1)][j+dir*(k+1)]==EMPTY)
		      {
			  if(level==DEPTH_MIN_MAX-1)
				firl=addnode(first,brd,level);
			     else
				first=addnode(first,brd,level);
			  if(level==1) /* we need to hold the move name */
				{
				first->b->move[0]=j;
				first->b->move[1]=i;
				first->b->move[2]=j+dir*(k+1);
				first->b->move[3]=i+back*(k+1);
				}
			  pos_eat[0]=j;  pos_eat[1]=i;
/* values for eating: */  if(brd[i+back*k][j+dir*k]==USER_QUEEN*sign)
					if(level<DEPTH_MIN_MAX-1)
						first->val+=sign*30;
					    else firl->val+=sign*30;
			  if(brd[i+back*k][j+dir*k]==USER_SOLDIER*sign)
					if(level<DEPTH_MIN_MAX-1)
						first->val+=sign*5;
					    else firl->val+=sign*5;
/* for all but the last level update the board: */
			  if(level < DEPTH_MIN_MAX-1)
				{
				first->b->board[i][j]=EMPTY;
				first->b->board[i+back*k][j+dir*k]=EMPTY;
				first->b->board[i+back*(k+1)][j+dir*(k+1)]=COMP_QUEEN*sign;
				}

/* other eatings: */      /******* insert here dfs() *********/

			  for(l=k+2; brd[i+back*l][j+dir*l]==EMPTY; l++)
				{
				if(level==DEPTH_MIN_MAX-1)
					     firl=addnode(firl,brd,level);
				       else first=addnode(first,brd,level);

				/****** insert dfs() here ********/

				if(level==1) /* we need to hold the move name */
					{
					first->b->move[0]=j;
					first->b->move[1]=i;
					first->b->move[2]=j+dir*l;
					first->b->move[3]=i+back*l;
					}
/* values for eating: */  if(brd[i+back*k][j+dir*k]==USER_QUEEN*sign)
					if(level<DEPTH_MIN_MAX-1)
						first->val+=sign*30;
					    else firl->val+=sign*30;
			  if(brd[i+back*k][j+dir*k]==USER_SOLDIER*sign)
					if(level<DEPTH_MIN_MAX-1)
						first->val+=sign*5;
					    else firl->val+=sign*5;

/* for all but the last level update the board: */

				if(level < DEPTH_MIN_MAX-1)
					{
					first->b->board[i][j]=EMPTY;
					first->b->board[i+back*k][j+dir*k]=EMPTY;
					first->b->board[i+back*l][j+dir*l]=COMP_QUEEN*sign;
					}
				}
		      }
		 }  /* of 4 directions */
	 }  /* end of 'for' */
    if(level < DEPTH_MIN_MAX-1)
	{
	if(pos_eat[0]) first=check_eat(first, brd, sign); /* if eating has been */
	return first;
	}
    return firl;
}

