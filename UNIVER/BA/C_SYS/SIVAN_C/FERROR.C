#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <alloc.h>
#include <const.h>

/*--------------Prototyping----------------*/
void  ferror_msg(char *msg);
void  frame (int x1, int x2, int y1, int y2);
void fcls(void);
char *keep_area(int top_lin,int top_col, int bot_lin,int bot_col);
void restore_area(int top_col,int top_lin,int bot_col,int bot_lin,char *area);
/*------------------------------------------------------------------------*/
main()
{char msg[]="YOU ARE  WRONG",*buffer;
 buffer=keep_area(LEFT_COL,TOP_LINE,(LEFT_COL+HOR_SIZE),(TOP_LINE+VER_SIZE));
 ferror_msg(msg);
 getch();
 restore_area(LEFT_COL,TOP_LINE,(LEFT_COL+HOR_SIZE),(TOP_LINE+VER_SIZE),buffer);
}
/*----------------------------------------------------------------------*/
void  ferror_msg(char *msg)
{int col1,lin1,col2,lin2,i=0;
 char msgln[]="PRESS ANY KEY";
 char far *letter=BGN_SCR;
 col1=LEFT_COL-1;col2=LEFT_COL + HOR_SIZE-1;
 lin1=TOP_LINE-1;lin2=TOP_LINE+VER_SIZE-1;
 frame(col1,col2,lin1,lin2);
 col1=MSG_COL;
 lin1=lin2-VER_SIZE/2;
 letter+=PLACE(col1,lin1);
 for(i=0;msg[i]!=0;i++)
    {*letter++=msg[i];
     *letter++=ATR_REVERSE;
    }
}
/*------------------------------------------------------------------------*/
void fcls(void)
{
 char far *scr_point=BGN_SCR;
 for (scr_point=BGN_SCR;scr_point <= END_SCR;scr_point++)
     {
      *scr_point++=FILLER_0;
      *scr_point=ATR;
     }
}
/*-----------------------------------------------------------------------*/
void frame (int x1, int x2, int y1, int y2)
{
char far *pscr = BGN_SCR;
char far *psR, far *psL;
int x_help;
psR = pscr + 2 * (y1 * COLUMN_NUMBER + x1);
psL = pscr + 2 * (y2 * COLUMN_NUMBER + x1);
*psR++ = TOP_LEFT_CORNER;*psL++ = DOWN_LEFT_CORNER;
*psR++ = ATR;          *psL++ = ATR;
x_help =x1++;
while(x1 < x2)
	{
	*psR++ = *psL++ = HOR_LINE;
	*psR++ = *psL++ = ATR;
	x1++;
	}
*psR++ = TOP_RIGHT_CORNER;       *psL++ = DOWN_RIGHT_CORNER;
*psR-- = *psL = ATR;
psL = pscr + 2 * ((++y1) * COLUMN_NUMBER + x_help);
while(y1 < y2)
	{
	psR += 2*COLUMN_NUMBER;
	*psR++ = *psL++ = VER_LINE;
	*psR-- = *psL-- = ATR;
        psL += 2*COLUMN_NUMBER;
	y1++;
	}
}
/*------------------------------------------------------------------------*/
char *keep_area(int top_col,int top_lin, int bot_col,int bot_lin)
     {
     int size_area=(bot_lin - top_lin+1)*(bot_col - top_col+1),
	 i=0,hlp_col;
     char *pwind;
     char far *bgnwind;
     if((pwind=malloc(size_area * (sizeof(char))))!=NULL)
       {
	 while ((top_lin)<=(bot_lin))
	    {
		  bgnwind=BGN_SCR;
		  bgnwind+=PLACE(top_col,top_lin);
	       for(hlp_col=top_col;hlp_col<=bot_col;hlp_col++)
		  {
		   pwind[i++]=*bgnwind;
		   *bgnwind++=FILLER_0;
		   *bgnwind++=ATR;
		  }
	      top_lin++;
	    }
	return(pwind);
       }
      else
       {
	printf("\n not enough memory");
	return(NULL);
       }
     }
/*-----------------------------------------------------------------------*/
void restore_area(int top_col,int top_lin,int bot_col,int bot_lin, char *area)
{
     int hlp_col;
     char far *pscr;
     while(top_lin<=bot_lin)
	  {
	   hlp_col=top_col;
	   pscr=BGN_SCR;
           pscr +=  PLACE(top_col,top_lin);
	   while(hlp_col <= bot_col)
		{
		 *pscr++ = *area++;
		 *pscr++=ATR;
		 hlp_col++;
		}
	   top_lin++;
	   }
     free(area);
 }
/*-----------------------------------------------------------------------*/
