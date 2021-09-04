#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <alloc.h>
#include "const.h"
#include "msg.h"
/*---------prototyping-----------*/
void help_line(char *str);
void frame (int x1, int x2, int y1, int y2);
void fcls(void);
char *keep_area(int top_lin,int top_col, int bot_lin,int bot_col);
void restore_area(int top_col,int top_lin,int bot_col,int bot_lin,char *area);
void fprint_msg(int col,int lin,char *msg,char atribute);
void fmatrice(int x1,int y1);
void ferror_msg(char *msg);
void putmarker(int x,int y,char mark);
int  fchoise(int str_col,int str_lin,int lst_col,int lst_lin,int *row,int *col);
void fwindow (int x1, int x2, int y1, int y2, char *title, char *Line);
int getField(char *buffer, int len, int isNumeric, int col, int line);
/*------------------------------------------------------------------------*/
void fmatrice(int x1,int y1)
{
   int y_help,i=0;
   char matrice[] [WIDE+1]={MATRICE_0,MATRICE_1, MATRICE_2,
			    MATRICE_3,MATRICE_4, MATRICE_5,
			    MATRICE_6,MATRICE_7, MATRICE_8,
			    MATRICE_9,MATRICE_10, MATRICE_11,
			    MATRICE_12, MATRICE_13};

   y_help=y1;
   for (i=0;*matrice[i]!='\0';i++)
      {
       fprint_msg(x1,y_help,matrice[i],ATR);
       y_help++;
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
char *keep_area(int top_col,int top_lin, int bot_col,int bot_lin)
{
     int size_area=2*(bot_lin - top_lin+1)*(bot_col - top_col+1),
	 i=0,hlp_col;
     char *pwind;
     char far *bgnwind;
     flushall();
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
		   pwind[i++]=*bgnwind;
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
     flushall();
     while(top_lin<=bot_lin)
	  {
	   pscr=BGN_SCR;
	   pscr +=  PLACE(top_col,top_lin);
	   for(hlp_col = top_col;hlp_col<=bot_col;hlp_col++,area++,pscr++)
		{
		 *pscr++ = (char far) *area++;
		 *pscr = (char far) *area;
		}
	   top_lin++;
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
     *psR++ = ATR;	    *psL++ = ATR;
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
void  fprint_msg(int col,int lin,char *msg,char atribute)
{
     int i=0;
     char far *letter=BGN_SCR;
     letter+=PLACE(col,lin);
     for(i=0;msg[i]!=0;i++)
	{*letter++=msg[i];
	 *letter++=atribute;
	}
}
/*------------------------------------------------------------------------*/
int fchoise(int str_col,int str_lin,int lst_col,int lst_lin,int *row,int *col)
{
     int help_col=str_col,help_lin=str_lin,terminator=0;
     char expr[]=WAS_ERROR;
     (*row)=0;(*col=0);
     putmarker(help_col,help_lin,MARKER);
     do
      {
	    switch(terminator)
		 {
		  case RIGHT : if(help_col < lst_col)
			       {
				putmarker(help_col,help_lin,FILLER_0);
				help_col+=HOR_STEP;
				(*col)++;
				putmarker(help_col,help_lin,MARKER);
			       }
			       break;
		  case LEFT :  if(help_col > str_col)
				{
				putmarker(help_col,help_lin,FILLER_0);
				help_col-=HOR_STEP;
				(*col)--;
				putmarker(help_col,help_lin,MARKER);
				}
				break;
		  case UP : if(help_lin > str_lin)
				{
				putmarker(help_col,help_lin,FILLER_0);
				help_lin-=VER_STEP;
				(*row)--;
				putmarker(help_col,help_lin,MARKER);
				}
				break;

		  case DOWN : if(help_lin < lst_lin)
				{
				putmarker(help_col,help_lin,FILLER_0);
				help_lin+=VER_STEP;
				(*row)++;
				putmarker(help_col,help_lin,MARKER);
				}
				break;

		  default : if(terminator!=ESC && terminator!=ENTER &&
							    terminator!=0)
						  {
						   ferror_msg(expr);
						   help_line(UNITS_SELECT);
						  }
		  break;
		 }
	     }
       while((terminator=getch())!=ESC&&terminator!=ENTER);
       putmarker(help_col,help_lin,FILLER_0);
       return terminator;
  }
/*------------------------------------------------------------------------*/
 void putmarker(int x,int y,char mark)
{
      gotoxy(x,y);
      putch(mark);
      putch('\b');
}
/*------------------------------------------------------------------------*/
void  ferror_msg(char *msg)
{
     int col1,lin1,col2,lin2;
     char *buffer;
     col1=LEFT_COL-1;col2=LEFT_COL + HOR_SIZE;
     lin1=TOP_LINE-1;lin2=TOP_LINE+VER_SIZE;
     buffer=keep_area(col1,lin1,col2,lin2);
     frame(col1,col2-1,lin1,lin2-1);
     fprint_msg(MSG_COL,MSG_LINE,msg,ATR_REVERSE);
     help_line(ERROR_MSG);
     getch();
     col1=LEFT_COL-1;col2=LEFT_COL + HOR_SIZE;
     lin1=TOP_LINE-1;lin2=TOP_LINE+VER_SIZE;
     restore_area(col1,lin1,col2,lin2,buffer);

}
/*------------------------------------------------------------------------*/
void help_line(char *str)
{
     char far *pscr = BGN_SCR;
     int x1 = 1,  y1 = SCR_BOT;

     pscr += 2 * (y1-1) * COLUMN_NUMBER;
     while(pscr < END_SCR)
	 {
	 *pscr++ = FILLER_0;
	 *pscr++ = ATR_REVERSE;
	 }
     fprint_msg(x1, y1, str,ATR_REVERSE);
}
/*---------------------------------------------------------------------*/
void  fwindow (int x1, int x2, int y1, int y2, char *title, char *Line)
{
     frame(x1,x2-1,y1,y2-1);
     fprint_msg((x1 + DIF_COL), (y1 + DIF_LINE+1),  title, ATR);
     help_line(Line);
}
/*-----------------------------------------------------------------------*/
int getField(char *buffer, int len, int isNumeric, int col, int line)
{
     char c;
     int i=0, swEsc = NO_ESC;

     gotoxy(col,line);
     c=getch();
     while(c!=ENTER &&	c!=ESC	&& i <= len)
	     {
	     if(c== BACKSPACE && i!=0)
		     {
		     buffer--;
		     col--;
		     putch(FILLER_0);
		     }

	     else
		     {
		      if((isNumeric== NUMERIC && c>='0' && c<='9') ||
		      (isNumeric!= NUMERIC))
			     {
			      *buffer++ = c;
			      i++;
			      putch(c);
			      col++;
			     }
		     }
	     gotoxy(col, line);
	     c = getch();
	     }
     if(c!= ESC)
	     *buffer = '\0';
     else
	     {
	     swEsc = YES_ESC;
	     free(buffer);
	     }
     return(swEsc);
}
/*************************************************************************/
