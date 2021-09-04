/***************************************************************************/
/*                      U N I T S    M A N A G E R .                          */
#include "const.h"
#include "msg.h"
#include "struct.h"
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <alloc.h>
#include "declarat.h"
extern struct unit units[TIME_UNITS][DAY_UNITS][MAX_UNITS];
/*--------------------------------------------------------------*/
void units_manager(int Time, int Date)
{
     char *area;
     int  c,i=0;
     struct unit *punit_current;

     area = keep_area(LIST_X1, LIST_Y1, LIST_X2, LIST_Y2);
     fwindow(LIST_X1, LIST_X2, LIST_Y1, LIST_Y2,TITLE_UNITS,ACTION_SELECT);
     show_unit( Time,  Date, i);
     do
		{
		 help_line(ACTION_SELECT);
                 if((c=getch())==NULL)
		     c=getch();
		 switch(c)
			{
			case   PgUp : if(i-=SIZE_OF_PAGE <= 0)
							  i=0;
				    show_unit(Time,Date,i);
			       break;
			case   PgDn : if(i+=SIZE_OF_PAGE <= MAX_UNITS)
					  show_unit(Time,Date, i);
				break;
			case DELET  :  delunitentry(Time, Date);
				       show_unit(Time, Date,i);
					 break;
			case INSERT :    addunitentry(Time, Date);
					 show_unit(Time, Date,i);
					 break;
		       default     :     if (c!=ESC)
					     ferror_msg(WAS_ERROR);
					 break;
			}
		}
     while (c!=ESC);
     restore_area(LIST_X1, LIST_Y1, LIST_X2, LIST_Y2,area);
}
/*-------------------------------------------------------------------*/
void show_unit(int Time, int Date,int i_start)
{
     int x=LIST_X1 + DIF_COL, y = LIST_Y1+DIF_LINE_LIST;
     while(y<LIST_Y2-1)
	    {
	     x=LIST_X1 + DIF_COL;
	     gotoxy(x,y);
	     printf(EMPTY);
	     if( units[Time][Date][i_start].room!=HIGH_VALUE)
		 {
		 gotoxy(x,y);
		 printf("%d",units[Time][Date][i_start].room);
		 gotoxy(x+=DIF_COL_UNIT, y);
		 printf("%d",units[Time][Date][i_start].course);
		 gotoxy(x+=DIF_COL_UNIT, y);
		 printf("%d",units[Time][Date][i_start].teacher);
		 gotoxy(x+=DIF_COL_UNIT, y);
		 printf("%d",units[Time][Date][i_start].group);
		}
		 i_start++;
	    y++;
	   }
}
/*----------------------------------------------------------------*/
int acceptunitentry(struct unit *punit)
{
     int x1 = COLUMN_INSIDE,		   y1 = LINE_INSIDE+12,
	 x2 = COLUMN_INSIDE+NAME_LEN+40,   y2 = LINE_INSIDE+16,
	  x = COLUMN_INSIDE+DIF_COL+2,	    y = LINE_INSIDE+15;
     int was_esc,  len, isnum, j;
     char *area, *buffer;

     area = keep_area(x1, y1, x2, y2);
     fwindow(x1,x2,y1,y2,TITLE_UNITS, MSG_ENTER_UNITS);
     gotoxy(x,y);
     printf("%d", punit -> room);
     x+=DIF_COL_UNIT;
     len = CODE_LEN; isnum = NUMERIC;
     buffer = malloc(sizeof(int));
     for(j=1; j<NUMBER_OF_ELEMENTS && (was_esc=getField(buffer,len,isnum,x,y))!=YES_ESC; j++)
	{
	switch(j)
		{
		case 1 :  punit -> course  = atoi(buffer);
			  break;
		case 2 :  punit -> teacher = atoi(buffer);
			  break;
		case 3 :  punit -> group   = atoi(buffer);
			  break;
		}
	 x+=DIF_COL_UNIT;
	}
     restore_area(x1,y1,x2,y2,area);
     free(buffer);
     return was_esc;
}
/*-------------------------------------------------------------------*/
void delunitentry(int Time, int Date)
{
     int c, Code;
     int Index_current;

     do
	{
         help_line(CODE_ROOM);
	 Code = acceptcode();
	 if(Code > MAX_ROOM)
	      ferror_msg(TOO_MUCH);
	}
     while(Code > MAX_ROOM);
     Index_current = code_unit_exists(Time, Date, Code);
     if(Index_current < NULL)
	{
	 help_line(NO_RECORD);
	 getch();
	}
     else
	{
	 help_line(DEL_QUESTION);
	 while(strchr("YyNn", (c=getch()))==NULL);
	 if(c=='Y' || c=='y')
		  while (Index_current < MAX_UNITS)
		      {
		       units[Time][Date][Index_current] =
		       units[Time][Date][Index_current + 1];
		       Index_current ++;
		      }
	 }
}
/*-------------------------------------------------------------------------*/
void addunitentry(int Time, int Date)
{
     int c, Code, was_esc, Index_current, i;
     do
	{
         help_line(CODE_ROOM);
	 Code = acceptcode();
	 if(Code > MAX_ROOM)
	      ferror_msg(TOO_MUCH);
	}
     while(Code > MAX_ROOM);
     Index_current = code_unit_exists(Time, Date, Code);
     if(Index_current >= NULL && units[Time][Date][Index_current].room!=HIGH_VALUE)
	{
	 help_line(DUBLE_RECORD);
	 getch();
	}
     else
	 {
	  if(units[Time][Date][MAX_UNITS-1].room!=HIGH_VALUE)
		 {
		  help_line(FULL);
		  getch();
		 }
	  else
		 {
		  for(i=MAX_UNITS; i>Index_current*(-1); i--)
			 units[Time][Date][i] = units[Time][Date][i-1];
		 units[Time][Date][i].room = Code;
		 do
		       was_esc = acceptunitentry(&units[Time][Date][i]);
		 while(was_esc!= NO_ESC);
		}
	 }
}
/*--------------------------------------------------------------------*/
int code_unit_exists(int Time, int Date, int Code)
{
     int i=0;

     while(units[Time][Date][i].room <= Code)
	    {
	     if(units[Time][Date][i].room == Code)
		    return(i);
	     i++;
	    }
     return(i*=(-1));
}
/*-------------------------------------------------------------------*/
void clean_units(void)
{
int i=0, j=0, k=0;
for (k=0;k<TIME_UNITS;k++)
    for (j=0;j<DAY_UNITS;j++)
	 for (i=0;i<MAX_UNITS;i++)
		{
		 units[k][j][i].room = HIGH_VALUE;
		 units[k][j][i].teacher = HIGH_VALUE;
		 units[k][j][i].course = HIGH_VALUE;
		 units[k][j][i].group = HIGH_VALUE;
		}
}

/*****************************************************************/
