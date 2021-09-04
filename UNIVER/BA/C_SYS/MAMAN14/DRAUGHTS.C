/*------------------------------------------------------------------------*/
/*                                DRAUGHTS.C                              */
/*------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include<conio.h>
#include<alloc.h>
#include <string.h>
#include "DRAUGHTS.H"
#define LOGFILE "BOARD.SAV"
static char IMAGE_LIST[][4][4]={{"ллл","   "," w "," W "},
				{"ллл","   "," b "," B "},
				{"ллл","   ","   ","   "}};
static struct MOVE BestVar[MAXPLY + 1][MAXPLY + 1];  /* the best variation */
static struct MOVE Killer[ MAXPLY + 1 ][ 2 ];        /* Killer moves       */
static char buf[ 80 ];

void NewGame (struct BOARD *B);
int IsInList( struct MOVE *list, int num_moves, struct MOVE m );
void initboard (struct Square Board[MAXBDSIZE+2][MAXBDSIZE+2],
		int *WP,int *BP);
void showboard (struct Square Board[MAXBDSIZE+2][MAXBDSIZE+2]);
int GenMoves(struct BOARD B,struct MOVE *list,int row, int col);
int GenJumps(struct BOARD B,struct MOVE *list, color player,
					       int row, int col);
BOOL CanJump( struct BOARD B ,color player, int row, int col );
void MakeMove(struct BOARD *B, struct MOVE *m);
void UnMakeMove(struct BOARD *B,struct MOVE *m);
BOOL CompMoves( struct MOVE m1, struct MOVE m2 );
void MemSwap( void *a, void *b, int size );
void *memcpy (void *dest, const void *src, size_t n);
int SortMoves( struct MOVE list[], int num_moves );
int KillerSortMoves(struct MOVE list[],int num_moves,int ply);
BOOL Quiescent(struct MOVE m,int limit, int num_moves, int ply);
void PreEvaluate(struct BOARD *B);
BOOL SaveToFile (struct BOARD B);
BOOL LoadFromFile(struct BOARD *B);
/*-----------------------------------------------------------------------*/
/*function for initializing checkers board                               */
/*-----------------------------------------------------------------------*/
void initboard (struct Square Board[MAXBDSIZE+2][MAXBDSIZE+2],
		int *WP,int *BP)
/*parameters Board - board to be initilazed */
/*           WP,BP - numbers of black and white pieces*/
{
BOOL OK;
int i,j;
for (i=0;i<MAXBDSIZE+2;i++)
    for (j=0;j<MAXBDSIZE+2;j++)
	{
	OK=TRUE;
	Board[i][j].row=i;
	Board[i][j].col=j;
	Board[i][j].IsValid=FALSE;
	Board[i][j].Piece.Value=empty;
	Board[i][j].Piece.Side =unknown;
	if ((i==0)||(i==MAXBDSIZE+1)) OK=FALSE;
	   else
	   if (((j==0)||(j==MAXBDSIZE+1)||((i+j)%2!=0))) OK=FALSE;
	if (OK) /* Inside Board and valid square */
	  {
	   Board[i][j].IsValid=TRUE;
	   if (i<=3)
	      {
	      Board[i][j].Piece.Value=man;
	      Board[i][j].Piece.Side =white;
	      (*WP)++;
	      }
	      else if (i>=6) {
			     Board[i][j].Piece.Value=man;
			     Board[i][j].Piece.Side =black;
			     (*BP)++;
			     }
	  }
	}
}
/*---------------------------------------------------------------------*/
/*  function for show given position onto board                        */
/*  parameters  Board - boardto be shown                               */
/*---------------------------------------------------------------------*/
void showboard (struct Square Board[MAXBDSIZE+2][MAXBDSIZE+2])
{
int i,j;
char c='A';
clrscr();
for(i=MAXBDSIZE+1;i>=0;i--)
   {
   printf("\n");
   for(j=0;j<MAXBDSIZE+2;j++)
      {
      if ((i>0&&i<MAXBDSIZE+1)&&(j>0&&j<MAXBDSIZE+1))
	 printf("%3s",IMAGE(Board[i][j].IsValid,Board[i][j].Piece.Value,
			    Board[i][j].Piece.Side));
	 else
	      /*print frame and labels */
	      {if(i==0&&j==0) printf("Ш");
	       if(i==0&&j==MAXBDSIZE+1) printf("М");
	       if(i==MAXBDSIZE+1&&j==0) printf("Щ");
	       if(i==MAXBDSIZE+1&&j==MAXBDSIZE+1) printf("Л");
	       if((i==0||i==MAXBDSIZE+1)&&j>0&&j<MAXBDSIZE+1) printf("ЭЭЭ");
	       if((j==MAXBDSIZE+1||j==0)&&i>0&&i<MAXBDSIZE+1) printf("К");
	       }
      }
   if (i>0&&i<MAXBDSIZE+1) printf(" %d",i);
   }
printf("\n");
for (i=0;i<MAXBDSIZE+1;i++)
    if(i>0) printf(" %c ",c+i-1);
      else printf(" ");
}
/*--------------------------------------------------------------------*/
BOOL DefineKingTrips(struct BOARD B,int row,int col,struct TRIP *I1,
						    struct TRIP *I2)
{
int x,y;
I1->x1=I1->x2=I2->x1=I2->x2=col;
I1->y1=I1->y2=I2->y1=I2->y2=row;
for(x=col-1,y=row-1;B.Board[y][x].Piece.Value==empty&&
		 B.Board[y][x].IsValid;x--,y--)
		 {
		 I1->x1=x;
		 I1->y1=y;
		 }
for(x=col+1,y=row+1;B.Board[y][x].Piece.Value==empty&&
		 B.Board[y][x].IsValid;x++,y++)
		 {
		 I1->x2=x;
		 I1->y2=y;
		 }

for(x=col-1,y=row+1;B.Board[y][x].Piece.Value==empty&&
		 B.Board[y][x].IsValid;x--,y++)
		 {
		 I2->x1=x;
		 I2->y1=y;
		 }
for(x=col+1,y=row-1;B.Board[y][x].Piece.Value==empty&&
		 B.Board[y][x].IsValid;x++,y--)
		 {
		 I2->x2=x;
		 I2->y2=y;
		 }
if((I1->x1-I1->x2)||(I2->x1-I2->x2)) return TRUE; else return FALSE;
}
/*--------------------------------------------------------------*/
void SetMove(int Or,int Oc,int Dr,int Dc,int Cr,int Cc,piecetype Capture,
	     BOOL Crown,struct MOVE *m)
{
 m->org.row =Or;
 m->org.col =Oc;
 m->dest.row=Dr;
 m->dest.col=Dc;
 m->capt.row=Cr;
 m->capt.col=Cc;
 m->Capture =Capture;
 m->Crown   =Crown;
}
/*--------------------------------------------------------------*/
/* generates the list of moves for a given player at a row, col */
/* returns the number of legal moves found                      */
/*--------------------------------------------------------------*/
int GenMoves(struct BOARD B,struct MOVE *list,int row, int col)
{
   int NumMoves;
   int what;
   int trow1 = row+1,tcol1=col+1,trowm1=row-1,tcolm1=col-1;
   int i,j;
   struct TRIP T1,T2;
   NumMoves = 0;
   what=WHAT(B.Board[row][col].Piece.Side,B.Board[row][ col].Piece.Value);
   if(what == BLACKMAN )
      {
      if(B.Board[trowm1][tcolm1].Piece.Value==empty
	 &&B.Board[trowm1][tcolm1].IsValid)
	 {
	 SetMove(row,col,trowm1,tcolm1,0,0,empty,((row==2)&&(what==BLACKMAN)),
		 list);
	 ++NumMoves;
	 ++list;
	 }
      if  (B.Board[trowm1][tcol1].Piece.Value==empty
	 &&B.Board[trowm1][tcol1].IsValid)
	 {
	 SetMove(row,col,trowm1,tcol1,0,0,empty,((row==2)&&(what==BLACKMAN)),
		 list);
	 ++NumMoves;
	 ++list;
	 }
      }

   if(what==WHITEMAN )
      {
      if (B.Board[trow1][tcolm1].Piece.Value == empty
	&&B.Board[trow1][tcolm1].IsValid)
	 {
	 SetMove(row,col,trow1,tcolm1,0,0,empty,
	 ((row==B.BoardSize-1)&&(what==WHITEMAN)),list);
	 ++NumMoves;
	 ++list;
	 }
      if  (B.Board[trow1][tcol1].Piece.Value == empty
	 &&B.Board[trow1][tcol1].IsValid)
	 {
	 SetMove(row,col,trow1,tcol1,0,0,empty,
	 ((row==B.BoardSize-1)&&(what==WHITEMAN)),list);
	 ++NumMoves;
	 ++list;
	 }
      }
   if(what==WHITEKING || what == BLACKKING)
     {
     if(DefineKingTrips(B,row,col,&T1,&T2))
       {
       for(i=0;(T1.x1+i<=T1.x2)&&(T1.x1!=T1.x2);i++)
	  {
	  if ((T1.x1+i)!=col)
	     SetMove(row,col,T1.y1+i,T1.x1+i,0,0,empty,FALSE,list);
	     list++;
	     NumMoves++;
	  }
       for(i=0;(T2.x1+i<=T2.x2)&&(T2.x1!=T2.x2);i++)
	  {
	  if ((T2.x1+i)!=col)
	     SetMove(row,col,T2.y1-i,T2.x1+i,0,0,empty,FALSE,list);
	     list++;
	     NumMoves++;
	  }
       }
     }
   return( NumMoves );
}
/*-------------------------------------------------------------*/
/*make move m at board B;do not show                           */
/*update weight of the position                                */
/* B board                                                     */
/* m move for doing                                            */
/*-------------------------------------------------------------*/
void MakeMove(struct BOARD *B,struct MOVE *m)
{
  struct Square *osqu, *dsqu, *csqu;
  osqu = &B->Board[m->org.row][m->org.col];
  dsqu = &B->Board[m->dest.row][m->dest.col];
  csqu = &B->Board[m->capt.row][m->capt.col];

    B->Material[osqu->Piece.Side]-=
    B->SValue[m->org.row][m->org.col][osqu->Piece.Side]
				     [osqu->Piece.Value];


  dsqu->Piece.Side=osqu->Piece.Side;
  dsqu->Piece.Value=osqu->Piece.Value;
  osqu->Piece.Value=empty;
  osqu->Piece.Side=unknown;

  if( m->Crown)  dsqu->Piece.Value=king;
    B->Material[dsqu->Piece.Side]+=
    B->SValue[m->dest.row][m->dest.col][dsqu->Piece.Side]
				       [dsqu->Piece.Value];
  if( m->Capture!=empty)
    {
    B->Material[csqu->Piece.Side]-=
    B->SValue[m->capt.row][m->capt.col][csqu->Piece.Side][csqu->Piece.Value];
    if(csqu->Piece.Side==black)        B->NumBlackPieces--;
      else if(csqu->Piece.Side==white) B->NumWhitePieces--;
    csqu->Piece.Value = empty  ;
    csqu->Piece.Side  = unknown;
    }

}
/*-------------------------------------------------------------------*/
/*make move and show position after it                               */
/*B Board                                                            */
/*m move                                                             */
/*-------------------------------------------------------------------*/
void MakeActualMove(struct BOARD *B, struct MOVE m)
{
 MakeMove(B,&m);
 showboard(B->Board);
}

/*------------------------------------------------------------------*/
/*Generates list of movies that should capture                      */
/*B Board (position)                                                */
/*list pointer to list of possible movies                           */
/*player which side check                                           */
/*row,col if there is a capture from given position                 */
/*return number of found movies                                     */
/*------------------------------------------------------------------*/
int GenJumps(struct BOARD B,struct MOVE *list, color player,
					       int row, int col)
{
   struct TRIP T1,T2;
   int NumMoves=0;
   int what;
   int trow1=row+1,trowm1=row-1;
   int tcol1=col+1,tcolm1=col-1;
   int x11,y11,x12,y12,x21,x22,y21,y22;  /*end of king trips */
   what=WHAT(B.Board[row][col].Piece.Side,B.Board[row][ col].Piece.Value);
   if(what==BLACKMAN )
      {
      if(B.Board[trowm1][tcolm1].Piece.Side==OPLAYER)
	 {
	 if(B.Board[trowm1-1][tcolm1-1].Piece.Value==empty
	    &&B.Board[trowm1-1][tcolm1-1].IsValid)
	    {
	     SetMove(row,col,trowm1-1,tcolm1-1,trowm1,tcolm1,
		    B.Board[trowm1][tcolm1].Piece.Value,
		    ((row==3)&&(what==BLACKMAN)),list);
	    ++NumMoves;
	    ++list;
	    }
	 }
      if(B.Board[trowm1][tcol1].Piece.Side==OPLAYER)
	 {
	 if (B.Board[trowm1-1][tcol1+1].Piece.Value==empty
	   &&B.Board[trowm1-1][tcol1+1].IsValid)
	    {
	     SetMove(row,col,trowm1-1,tcol1+1,trowm1,tcol1,
		    B.Board[trowm1][tcol1].Piece.Value,
		    ((row==3)&&(what==BLACKMAN)),list);
	    ++NumMoves;
	    ++list;
	    }
	 }
      }

   if( what == WHITEMAN )
      {
      if(B.Board[trow1][tcol1].Piece.Side == OPLAYER )
	 {
	 if (B.Board[trow1+1][tcol1+1].Piece.Value==empty
	   &&B.Board[trow1+1][tcol1+1].IsValid)
	    {
	     SetMove(row,col,trow1+1,tcol1+1,trow1,tcol1,
		    B.Board[trow1][tcol1].Piece.Value,
		    ((row==B.BoardSize-2)&&(what==WHITEMAN)),list);
	    ++NumMoves;
	    ++list;
	    }
	 }
      if( B.Board[trow1][tcolm1].Piece.Side == OPLAYER )
	 {
	 if (B.Board[trow1+1][tcolm1-1].Piece.Value == empty
	   &&B.Board[trow1+1][tcolm1-1].IsValid)
	    {
	    SetMove(row,col,trow1+1,tcolm1-1,trow1,tcolm1,
		   B.Board[trow1][tcolm1].Piece.Value,
		   ((row==B.BoardSize-2)&&(what==WHITEMAN)),list);
	    ++NumMoves;
	    ++list;
	    }
	 }
      }

  if(what==WHITEKING||what==BLACKKING)
     {
     if (DefineKingTrips(B,row,col,&T1,&T2))
	{
	x11=T1.x1;y11=T1.y1;
	x12=T1.x2;y12=T1.y2;
	x21=T2.x1;y21=T2.y1;
	x22=T2.x2;y22=T2.y2;
	if(B.Board[y11-1][x11-1].Piece.Side==OPLAYER)
	  if (B.Board[y11-2][x11-2].Piece.Value == empty
	     &&B.Board[y11-2][x11-2].IsValid)
	     {
	      SetMove(row,col,y11-2,x11-2,y11-1,x11-1,
		      B.Board[y11-1][x11-1].Piece.Value,FALSE,list);
	      ++NumMoves;
	      ++list;
	     }
	if(B.Board[y12+1][x12+1].Piece.Side==OPLAYER)
	  if (B.Board[y12+2][x12+2].Piece.Value==empty
	     &&B.Board[y12+2][x12+2].IsValid)
	     {
	      SetMove(row,col,y12+2,x12+2,y12+1,x12+1,
		      B.Board[y12+1][x12+1].Piece.Value,FALSE,list);
	      ++NumMoves;
	      ++list;
	     }
	if(B.Board[y21+1][x21-1].Piece.Side==OPLAYER)
	  if (B.Board[y21+2][x21-2].Piece.Value == empty
	     &&B.Board[y21+2][x21-2].IsValid)
	     {
	      SetMove(row,col,y21+2,x21-2,y21+1,x21-1,
		      B.Board[y21+1][x21-1].Piece.Value,FALSE,list);
	      ++NumMoves;
	      ++list;
	     }
	if(B.Board[y22-1][x22+1].Piece.Side==OPLAYER)
	  if (B.Board[y22-2][x22+2].Piece.Value==empty
	     &&B.Board[y22-2][x22+2].IsValid)
	     {
	      SetMove(row,col,y22-2,x22+2,y22-1,x22+1,
		      B.Board[y22-1][x22+1].Piece.Value,FALSE,list);
	      ++NumMoves;
	      ++list;
	     }
	 }
     }
return( NumMoves );
}
/*---------------------------------------------------------------------*/
/*check if there are movies with capture from given position           */
/*B position                                                           */
/*player who is a player                                               */
/* row,col coordinate point for check if zero check all                */
/*return true if found false if not                                    */
/*---------------------------------------------------------------------*/
BOOL CanJump( struct BOARD B ,color player, int row, int col )
{
   int what;
   int trow1 = row + 1, trowm1 = row - 1;
   int tcol1 = col + 1, tcolm1 = col - 1;
   struct TRIP T1,T2;
   int x11,y11,x12,y12,x21,x22,y21,y22;  /*end of king trips */
   if (!row || row > B.BoardSize)
      return FALSE;

   what = WHAT(B.Board[row][col].Piece.Side,B.Board[row][col].Piece.Value);

   if( what == BLACKMAN )
      {
      if(B.Board[trowm1][tcolm1].Piece.Side == OPLAYER )
	 {
	 if( B.Board[trowm1-1][tcolm1-1].Piece.Value == empty
	   &&B.Board[trowm1-1][tcolm1-1].IsValid)
	    return( TRUE );
	 }

      if( B.Board[trowm1][tcol1].Piece.Side==OPLAYER)
	 {
	 if(B.Board[trowm1-1][tcol1+1].Piece.Value == empty
	  &&B.Board[trowm1-1][tcol1+1].IsValid)
	    return( TRUE );
	 }
      }

   if( what == WHITEMAN )
      {
      if( B.Board[trow1][tcol1].Piece.Side == OPLAYER )
	 {
	 if(B.Board[trow1+1][tcol1+1].Piece.Value == empty
	  &&B.Board[trow1+1][tcol1+1].IsValid)
	    return( TRUE );
	 }

      if( B.Board[trow1][tcolm1].Piece.Side == OPLAYER )
	 {
	 if(B.Board[trow1+1][tcolm1-1].Piece.Value == empty
	  &&B.Board[trow1+1][tcolm1-1].IsValid)
	    return( TRUE );
	 }
      }

 if(what==WHITEKING||what==BLACKKING)
     {
     if (DefineKingTrips(B,row,col,&T1,&T2))
	{
	x11=T1.x1;y11=T1.y1;
	x12=T1.x2;y12=T1.y2;
	x21=T2.x1;y21=T2.y1;
	x22=T2.x2;y22=T2.y2;
	if(B.Board[y11-1][x11-1].Piece.Side==OPLAYER)
	  if (B.Board[y11-2][x11-2].Piece.Value == empty
	     &&B.Board[y11-2][x11-2].IsValid)
	     {
	     return TRUE;
	     }
	if(B.Board[y12+1][x12+1].Piece.Side==OPLAYER)
	  if (B.Board[y12+2][x12+2].Piece.Value==empty
	     &&B.Board[y12+2][x12+2].IsValid)
	     {
	     return TRUE;
	     }
	if(B.Board[y21+1][x21-1].Piece.Side==OPLAYER)
	  if (B.Board[y21+2][x21-2].Piece.Value == empty
	     &&B.Board[y21+2][x21-2].IsValid)
	     {
	     return TRUE;
	     }
	if(B.Board[y22-1][x22+1].Piece.Side==OPLAYER)
	  if (B.Board[y22-2][x22+2].Piece.Value==empty
	     &&B.Board[y22-2][x22+2].IsValid)
	     {
	     return TRUE;
	     }
	 }
     }

   return(FALSE);
}
/*------------------------------------------------------------------------*/
/*return position to state before move m was made                         */
/* B - position                                                           */
/* m - move for canceling                                                 */
/*------------------------------------------------------------------------*/
void UnMakeMove(struct BOARD *B,struct MOVE *m)
{
   color player;
   struct Square *osqu, *dsqu, *csqu;
   osqu = &B->Board[m->org.row][m->org.col];
   dsqu = &B->Board[m->dest.row][m->dest.col];
   csqu = &B->Board[m->capt.row][m->capt.col];
   player=dsqu->Piece.Side;

   B->Material[dsqu->Piece.Side] -=
   B->SValue[m->dest.row][m->dest.col][dsqu->Piece.Side][dsqu->Piece.Value];

   osqu->Piece.Value=dsqu->Piece.Value;
   osqu->Piece.Side=dsqu->Piece.Side;
   dsqu->Piece.Value=empty;
   dsqu->Piece.Side=unknown;

   if( m->Crown ) --(osqu->Piece.Value);
   B->Material[osqu->Piece.Side] +=
   B->SValue[m->org.row][m->org.col][osqu->Piece.Side][osqu->Piece.Value];
   if( m->Capture != empty )
      {
      csqu->Piece.Value=m->Capture;
      csqu->Piece.Side=OPLAYER;
      B->Material[csqu->Piece.Side]+=
      B->SValue[m->capt.row][m->capt.col][csqu->Piece.Side][csqu->Piece.Value];
      }
}
/*----------------------------------------------------------------------*/
/*build list of all possible movies for given position and if it needed */
/*only for given point                                                  */
/*B position                                                            */
/*list pointer to list of movies                                        */
/*player - which side check                                             */
/*row,col point for check if zero check all                             */
/*ply depth of searching for update tables of optimal movies            */
/*return number of found movies                                         */
/*----------------------------------------------------------------------*/
int Lmg(struct BOARD B ,struct MOVE *list,
			color player, int row, int col, int ply)
{
   int num, NumMoves=0, HasAJump= FALSE;;

   if( row )          /* examine jumps from this square */
      {
      NumMoves = GenJumps(B, &list[ NumMoves ], player, row, col );
      if(!NumMoves) NumMoves=GenMoves( B,&list[ NumMoves ],row,col);
      }
   else               /* find all legal moves */
      {
      for( row = 1; row <= B.BoardSize; ++row )
	 {
	 for( col = 1; col <=B.BoardSize; ++col )
	    {
	    if( B.Board[row][col].Piece.Side == player )
	       {
	       if( (num = GenJumps(B, &list[ NumMoves ],
				    player, row, col )) != 0 )
		  {
		  HasAJump = TRUE;
		  NumMoves += num;
		  }
	       if( !HasAJump )
		  {
		  NumMoves += GenMoves( B,&list[ NumMoves ], row, col );
		  }
	       }
	    }
	 }
      }

   if( B.KillerFlag )
      {
      NumMoves = KillerSortMoves(list, NumMoves, ply );
      }
   else
      {
      NumMoves = SortMoves( list, NumMoves );
      }
   return( NumMoves );
}
/*-----------------------------------------------------------------*/
/* check if move m1 equal to m2                                    */
/*return true if equal else return false                           */
/*-----------------------------------------------------------------*/
BOOL CompMoves( struct MOVE m1, struct MOVE m2 )
{
   if( m1.org.row == m2.org.row && m1.org.col==m2.org.col)
      {
      if( m1.dest.row == m2.dest.row && m1.dest.col == m2.dest.col )
         {
	 if( m1.Capture == m2.Capture )
            {
	    if( m1.Capture != empty )
               {
	       if( m1.capt.row == m2.capt.row )
                  {
		  if( m1.capt.col == m2.capt.col )
                     {
		     if( m1.Crown == m2.Crown )
                        {
                        return( TRUE );
                        }
                     }
                  }
               }
            else
               {
	       if( m1.Crown == m2.Crown )
		  {
		  return( TRUE );
		  }
               }
            }
         }
      }
   /* all members of 'm1' and 'm2' should be equivalent, except */
   /* the last member, 'value', which is of size int, so its left out */
   return( FALSE );
}
/*---------------------------------------------------------------------*/
/**********************************************
 sorts the moves list
 **********************************************/

int SortMoves( struct MOVE list[], int num_moves )
{
int i,j;
   for(  i = 0; i < num_moves; ++i )
      {
      if( list[ i ].Capture == empty )
	 break;
      }

   for(  j = i + 1; j < num_moves; ++j )
      {
      if( list[ j ].Capture != empty )
	 {
	 MemSwap( &list[ i ], &list[ j ], sizeof( struct MOVE ) );
	 ++i;
	 }
      }

   /* if there is a jump, trim off all non-jump moves */
   if( list[ 0 ].Capture != empty )
      {
      while( list[ num_moves - 1 ].Capture == empty )
	 --num_moves;
      }

   return( num_moves );
}
/*----------------------------------------------------------------*/
/*exchange memory contest between areas that  a and b point to    */
/*size byte memory of b to a and v.v.                             */
/*----------------------------------------------------------------*/
void MemSwap( void *a, void *b, int size )
{
int i;
char tmp;
char *first=(char *)a,*second=(char *)b;
for(i=0;i<size;i++,first++,second++)
   {
    tmp=*first;
    *first=*second;
    *second=tmp;
   }
}
/*----------------------------------------------------------------*/
/*copy n byte of memory from area begining frim src to dest       */
/*----------------------------------------------------------------*/
void *memcpy (void *dest, const void *src, size_t n)
{
int i;
char *first=(char *)dest,*second=(char *)src;
for(i=0;i<n;first++,second++,i++)
	    *first=*second;
return dest;
}

/*--------------------------------------------------------------------*/
/*check if m is in list of movies list  and if it is return it's place*/
/*list list of movies                                                 */
/*m move for searching                                                */
/*num_moves lenth of list                                             */
/*if was found nothing return -1                                      */
/*--------------------------------------------------------------------*/
int IsInList( struct MOVE *list, int num_moves, struct MOVE m )
{
   int i;
   for( i = 0; i < num_moves; ++i )
      {
      if(CompMoves(*list,m))
	 return(i);
	 list++;
      }
   return( -1 );
}
/*---------------------------------------------------------------------*/
/*function for sort movies considering previous iteration of searching */
/*list list of movies to be sorted                                     */
/*num_moves lenth of list                                              */
/*ply iteration depth                                                  */
/*---------------------------------------------------------------------*/
int KillerSortMoves(struct MOVE list[],int num_moves,int ply)
{
   struct MOVE *mptr, *endptr, *mptr2;
   int j;
  /* evaluate each move */
   for( mptr = list, endptr = mptr + num_moves; mptr < endptr; mptr++ )
      {
      if( mptr->Capture != empty )
	 mptr->Value = 5000;  /*first movies with capture*/
      else
	 mptr->Value = 0;

      if( (j = IsInList( Killer[ ply ], 2, *mptr )) >= 0 )
	 {
	 mptr->Value += Killer[ ply ][ j ].Value;
	 /*add value from previous iteration */
	 }
      }

  /* sort the list in descending order */
   for( mptr = list, endptr = mptr + num_moves; mptr < endptr - 1; mptr++)
      {
      for( mptr2 = mptr + 1; mptr2 < endptr; mptr2++ )
	 {
	 if( mptr2->Value > mptr->Value )
	    {
	    MemSwap( mptr, mptr2, sizeof(struct MOVE));
	    }
	 }
      }

   /* if there is a jump, trim off all non-jump moves */
   mptr = &list[num_moves-1];
   if( list[ 0 ].Capture != empty )
      {
      while( (mptr--)->Capture == empty )
	 --num_moves;
      }

   return( num_moves );
}
/*----------------------------------------------------------------------*/
/*check if we get to the last iteration or made MAXPLY checks of movies */
/*m move if there is a capture return true                              */
/*limit max depth of iteration                                          */
/*num_moves if there is only one move return true                       */
/*ply depth of the iteration                                            */
/*----------------------------------------------------------------------*/
BOOL Quiescent(struct MOVE m,int limit, int num_moves, int ply)
 {
   if( ply == MAXPLY - 1 )
      return( TRUE );
      else
      {
      if( limit > 0 || m.Capture != empty || num_moves == 1 )
	 return( FALSE );
	 else
	 return( TRUE );
	 }
 }
/*----------------------------------------------------------------------*/
/*insert move to the table of the best movies for this iteration        */
/*m move to be inserted                                                 */
/*ply number of iteration                                               */
/*----------------------------------------------------------------------*/
void UpdateBestVariation(struct MOVE m, int ply )
{
   int t1 = ply + 1;
   struct MOVE *mptr1, *mptr2;
   memcpy( &BestVar[ply][ply], &m, sizeof(struct MOVE));
   for ( mptr1 = &BestVar[t1][t1], mptr2 = &BestVar[ply][t1];
      mptr1->org.row; mptr1++, mptr2++)
      memcpy(mptr2, mptr1, sizeof(struct MOVE));

   mptr2->org.row=0;
   BestVar[ t1 ][ t1 ].org.row=0;
}
/*------------------------------------------------------------------------*/
/*insert move to KillerTable (table for best movies of previous iteration)*/
/*m move to insert                                                        */
/*ply number of iteration                                                 */
/*------------------------------------------------------------------------*/
void UpdateKillerTable( struct MOVE *m, int ply )
{
   static int i;
   m->Value = 1;
   if( (i = IsInList( Killer[ ply ], 2, *m)) != -1 )
      {
      if( ++Killer[ ply ][ i ].Value > 1000 )
	 Killer[ ply ][ i ].Value = 1000;
      }
   else           /* add it to the Killer table */
      {
      if( Killer[ ply ][ 0 ].Value <= Killer[ ply ][ 1 ].Value )
         {
	 memcpy( &Killer[ ply ][ 0 ], m, sizeof(struct MOVE));
         }
      else
	 {
	 memcpy( &Killer[ ply ][ 1 ], &m, sizeof(struct MOVE ) );
	 }
      }
}


/*----------------------------------------------------------------------*/
/*check if there is only move for the position B                        */
/*B position                                                            */
/*player which side to check                                            */
/*row col destination point                                             */
/*if there is only move do it and return true                           */
/*----------------------------------------------------------------------*/
BOOL OnlyOneMove( struct BOARD *B,color player,int *row,int *col )
{
   int RetVal = FALSE;
   struct MOVE *list = malloc(MAXMOVES*sizeof(struct MOVE));
   int NumMoves = 0;

   while ( (NumMoves = Lmg(*B,list,player,*row,*col,0)) == 1 )
      {
      MakeActualMove(B,list[0]);
      RetVal = TRUE;
      if(list[0].Capture != empty && !list[ 0 ].Crown &&
	 CanJump(*B,player,list[0].dest.row,list[0].dest.col) )
	{
	*row = list[ 0 ].dest.row;
	*col = list[ 0 ].dest.col;
	}
      else
         goto END_ONLYONE;
      }

END_ONLYONE:
   free(list);
   if (NumMoves > 1) /* In case where there is one required jump, but */
      return FALSE;  /* then two possible jumps after that, return FALSE */
   return   RetVal;
}
/*----------------------------------------------------------------------*/
/*calculate the weight of the position B before start evaluate best move*/
/*----------------------------------------------------------------------*/
void PreEvaluate(struct BOARD *B)
{
   int i, j, SIDE,inside;
   piecetype Piece;
   color     Side;
   int tBSizeDiv2 = B->BoardSize >> 1;  /* (BoardSize / 2)*/

   /*********************************************************
   This code gets a rough idea as to who is ahead in Material.
   **********************************************************/
   B->Material[white  ] = 0;
   B->Material[black  ] = 0;
   B->Material[unknown] = 0;

   B->Man[unknown][man]  =0;
   B->Man[unknown][king] =0;
   B->Man[unknown][empty]=0;

   B->Man[white][man]=100;
   B->Man[white][king]=140;
   B->Man[white][empty]=0;

   B->Man[black][man]  =100;
   B->Man[black][king] =140;
   B->Man[black][empty]=0;

   for( i = 1; i <= B->BoardSize; ++i )
      {
      for( j = 1; j <= B->BoardSize; ++j )
	 {
	 Side = B->Board[i][j].Piece.Side ;
	 Piece= B->Board[i][j].Piece.Value;
	 B->Material[Side] += B->Man[Side][Piece];
	 }
      }
   /****************************************************
   Now adjust the Material weights based on who is ahead.
   This is to encourage the fellow who is winning to exchange pieces
   and the fellow who is behind to not exchange pieces.
   If Material is dead even then you shouldn't try to force exchanges
   just on general principles.
   *****************************************************/
   if( B->Material[white] >= B->Material[black] )
      {
	 --B->Man[white][man];
	 --B->Man[white][king];
      }
   else
     {
	 --B->Man[black][man];
	 --B->Man[black][king];
     }
   /****************************************************
   Examine each and every square and calculate the bonus values.
   *****************************************************/
   for( i = 1; i <= B->BoardSize; ++i )
      {
      for( j = 1; j <= B->BoardSize; ++j )
	 {
	 inside = (j > 1 && j < B->BoardSize) ? 1 : 0;
	 B->SValue[i][j][white][man] =B->Man[white][man] + inside;
	 B->SValue[i][j][white][king]=B->Man[white][king] + inside;

	 B->SValue[i][j][black][man] =B->Man[black][man] + inside;
	 B->SValue[i][j][black][king]=B->Man[black][king] + inside;

	 /* bonus points for central squares */
	 if( abs( tBSizeDiv2 - i ) < 2 && abs( tBSizeDiv2 - j )  < 3 )
	    {
	    ++B->SValue[i][j][white][man];
	    ++B->SValue[i][j][white][king];
	    ++B->SValue[i][j][black][man];
	    ++B->SValue[i][j][black][king];
	    }

	 /* bonus for non-Crown piece advancement */
	 if( i > 2 )
	    {
	    B->SValue[i][j][white][man] += i - 2;
	    }

	 if( i <B->BoardSize - 2 )
	    {
	    B->SValue[i][j][black][man]+=B->BoardSize-i-1;
	    }

	 if(i== 1)           ++B->SValue[i][j][white][man];
	 if(i==B->BoardSize) ++B->SValue[i][j][black][man];
	 }
      }

   B->Material[white]   = 0;
   B->Material[black]   = 0;

   for( i = 1; i <= B->BoardSize; ++i )
      {
      for( j = 1; j <= B->BoardSize; ++j )
	 {
	 Side = B->Board[i][j].Piece.Side ;
	 Piece= B->Board[i][j].Piece.Value;
	 B->Material[Side]+=B->SValue[i][j][Side][Piece];
	 }
      }
}

/*-------------------------------------------------------------------------*/
/*This function evaluate the best move in the position B for current player*/
/*Quality of position define parmeters alpha and beta                      */
/*where alpha is the worst move cost and beta is upper level for move cost */
/*we are looking for movies with max cost for player and min cost for      */
/*opponent  (calling with parameters alpha'=-beta,beta'=-alpha)             */
/*the best movies inserted to the BestVar table of movies                  */
/*B - current position                                                     */                                                                           
/*alpha,beta-levels of movies cost(val)                                    */
/*player-for him we looking for move                                       */
/*row,col-evaluate if we make move from specific point                     */
/*limit - max depth of recursion                                           */
/*ply   - depth of current call                                            */
/*-------------------------------------------------------------------------*/
int Evaluate(struct BOARD *B,
	     int alpha, int beta, color player,int row, int col,
					       int limit, int ply)
{
   struct MOVE *list;
   struct MOVE *mptr, *endptr;
   int NumMoves, val;
   int num_back = 0;
   int retval = 0;
   int t1 = WIN - 2 - ply;
   int plyp1 = ply + 1;
   list =(struct MOVE *)malloc(MAXMOVES*sizeof(struct MOVE));
   if((NumMoves = Lmg(*B, list, player, row, col, ply )) == 0)
      {
      retval = LOSS + ply;
      goto END_EVALUATE;
      }
   if( Quiescent(*list,limit,NumMoves, ply)) /*end of recursion */
      {
      retval = (B->Material[player]-B->Material[OPLAYER]+(NumMoves>3?1:0));
      goto END_EVALUATE;
      }
   for(mptr=list,endptr=mptr+NumMoves;mptr<endptr&&alpha<t1;mptr++)
      {
      MakeMove(B, mptr);

      if( mptr->Capture != empty)
         {
	 if( !(mptr->Crown)&&CanJump(*B,player,mptr->dest.row,mptr->dest.col))
	    /*capture more than one piece*/
	    {
	    val=Evaluate(B,alpha,beta,player,mptr->dest.row,mptr->dest.col,
							      limit, plyp1);
            }
         else
            {
	    val = Evaluate(B,-beta,-alpha,OPLAYER,0,0,limit,plyp1) * -1;
	    }
         }
         else
            {
            if( limit == 0 || NumMoves == 1 )
               {
	       val=Evaluate(B,-beta,-alpha,OPLAYER,0,0,limit,plyp1)*-1;
	       }
	    else
	       {
	       val=Evaluate(B,-beta,-alpha,OPLAYER,0,0,limit ? limit-1 : 0,
							       plyp1)*-1;
               }
            }
	 UnMakeMove(B,mptr);

         if( val > alpha )
            {
            if( val >= beta )
               {
		  if( B->KillerFlag )
		     UpdateKillerTable( mptr, ply );
                  retval =  beta ;
                  goto END_EVALUATE;
               }
         else
            {
            alpha = val;
            ++num_back;
	    UpdateBestVariation(*mptr,ply);
            }
	 }
	 BestVar[plyp1][plyp1].org.row=0;
      }
   retval = alpha;
END_EVALUATE:

   free(list);
   return   retval;
}
/*-----------------------------------------------------------------*/
/*reply to human move if it is imposible return false              */
/*B position after human move                                      */
/*-----------------------------------------------------------------*/
BOOL ComputersTurn(struct BOARD *B)
{
   color player=B->Computer;
   int iter, i, val, row = 0, col = 0;
   int alpha = -MAXINT, beta = MAXINT;

   memcpy(B->SavedBoard, B->Board,
	 (MAXBDSIZE+2)*(MAXBDSIZE+2)*sizeof(struct Square));

   if( !OnlyOneMove(B,B->Computer,&row,&col))
      {
      PreEvaluate(B);
      /* clear out the best-variation table */
      for(i=0;i<= MAXPLY;++i)
	 {
	 BestVar[ i ][ i ].org.row=0;
	 BestVar[ 0 ][ i ].org.row=0;
	 }

      /* clear out the Killer table */
      for( i = 0; i <= MAXPLY; ++i )
	 {
	 Killer[ i ][ 0 ].org.row=  0;
	 Killer[ i ][ 0 ].Value  = -1;
	 }

      for(iter=B->IterFlag?1:B->SearchDepth; iter<=B->SearchDepth; ++iter)
	 {

	 val = Evaluate(B, alpha, beta, B->Computer, row, col, iter, 0 );
	 if (iter==1&&val==LOSS)
	    {
	    B->The_Winer=OPLAYER;
	    return FALSE;
	    }
	 if( val >= beta )
	    {
	    val = Evaluate(B, alpha, MAXINT, B->Computer, row, col, iter, 0 );
	    }
	 else
	    {
	    if( val <= alpha )
	       {
	       val = Evaluate(B,-MAXINT,beta,B->Computer,row,col,iter,0);
	       }
	    }
	 alpha = val - 12;
	 beta  = val + 12;

	 /* seed the killer table with the best variation */
	 for( i = 0; BestVar[ 0 ][ i ].org.row; ++i )
	    {
	    memcpy(&Killer[i][0],&BestVar[0][i],sizeof(struct MOVE));
	    Killer[ i ][ 0 ].Value = 1;
	    /* eliminate the other killer move */
	    Killer[ i ][ 1 ].Value = -1;
	    Killer[ i ][ 1 ].org.row=0 ;
	    }

	 /* clear the rest of the killer table */
	 do
	    {
	    Killer[ i ][ 0 ].org.row=0;
	    Killer[ i ][ 1 ].org.row=0;
	    }
	 while( i++ < MAXPLY );
	 }

      for (i=0;B->Board[BestVar[0][i].org.row]
		       [BestVar[0][i].org.col].Piece.Side==B->Computer;++i)
	 {
	 MakeActualMove(B,BestVar[0][i]);
	 }
      }
   return TRUE;
}
/*------------------------------------------------------------------------*/
/*make human move from point FROM to point TO                             */
/*if impossible return false                                              */
/*B position                                                              */
/*from,to - move                                                          */
/*------------------------------------------------------------------------*/
BOOL UsersTurn(struct BOARD *B,struct POINT from,struct POINT to)
{
   struct MOVE m;
   color player=B->Human;
   int NumMoves,i;
   int retval = FALSE;
   struct MOVE *list =(struct MOVE *)malloc(sizeof(struct MOVE)*MAXMOVES);
   BOOL OldKillerFlag=B->KillerFlag;/* do not sort with previous move */
   B->KillerFlag=FALSE;
   B->JumpAgain = FALSE;
   B->LastDest.row=from.row;
   B->LastDest.col=from.col;


   NumMoves = Lmg(*B,list,B->Human, B->LastDest.row,B->LastDest.col,0);
   for(i=0;i<NumMoves;i++)
      printf("\n%d %d %d %d %d",list[i].org.col,list[i].org.row,
				list[i].dest.col,list[i].dest.row);
   if(NumMoves==0)
     {
     B->The_Winer=OPLAYER;
     retval=FALSE;
     }
   m.org.row =from.row;
   m.org.col =from.col;
   m.dest.row=to.row;
   m.dest.col=to.col;
   if (abs(m.org.row - m.dest.row) == 2)
      {
      m.capt.row=(m.org.row + m.dest.row)/2;
      m.capt.col=(m.org.col + m.dest.col) /2 ;
      m.Capture =CON(B->Board,m.capt);
      }
   else
      {
      m.Capture = empty;
      }

   if(CON(B->Board,m.org)==man && WHO(B->Board,m.org)==B->Human
			       && m.dest.row ==B->BoardSize )
      m.Crown = TRUE;
   else
      m.Crown = FALSE;

   if( IsInList( list, NumMoves, m ) >= 0 )
      {
      MakeActualMove(B, m );
      if( m.Capture != empty && !m.Crown )
	 {
	 if((B->JumpAgain=CanJump(*B,B->Human,m.dest.row,m.dest.col))!=0)
	   {
	    B->LastDest.row=m.dest.row;
	    B->LastDest.col=m.dest.col;
	    }
	 else
	    {
	    B->LastDest.row=0;
	    B->LastDest.col=0;
	    }
	 }
      retval = TRUE;
      }
   free(list);
   B->KillerFlag=OldKillerFlag;
   return retval;
}
/*------------------------------------------------------------------*/
/*start new game for board B                                        */
/*------------------------------------------------------------------*/
void NewGame (struct BOARD *B)
{
B->SearchDepth=DEPTH;
B->IterFlag=TRUE;
B->KillerFlag=TRUE;
B->BoardSize=MAXBDSIZE;
B->JumpAgain=FALSE;
B->Human   =white;
B->Computer=black;
B->The_Winer=unknown;
B->LastDest.row=0;
B->LastDest.col=0;
B->LastDest.Piece.Value=empty;
B->LastDest.Piece.Side =unknown;
initboard(B->Board,&B->NumBlackPieces,&B->NumWhitePieces);
}
/*--------------------------------------------------------*/
/*exchange sides between computer and human               */
/*--------------------------------------------------------*/
void ExChangeSide (struct BOARD *B)
{
color temp;
temp=B->Human;
B->Human=B->Computer;
B->Computer=temp;
}
/*----------------------------------------------------------*/
/*  function for saving existing position to file           */
/*  B existing BOARD to save                                */
/*----------------------------------------------------------*/
BOOL SaveToFile(struct BOARD B)
{
BOOL retval=FALSE;
FILE *fp;
fp=fopen(LOGFILE,"wb");
if (fp==NULL) retval=FALSE;
   else
       {
	fwrite(&B,sizeof(B),1,fp);
	fclose(fp);
	retval=TRUE;
       }
return retval;
}
/*----------------------------------------------------------*/
/*  function for loading saved position to file             */
/*  B existing BOARD to save                                */
/*----------------------------------------------------------*/
BOOL LoadFromFile(struct BOARD *B)
{
BOOL retval=FALSE;
FILE *fp;
fp=fopen(LOGFILE,"rb");
if (fp==NULL) retval=FALSE;
   else
       {
	fread(B,sizeof((*B)),1,fp);
	fclose(fp);
	retval=TRUE;
       }
return retval;
}
