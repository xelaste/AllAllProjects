/**************************************************************************/
/*  FUNCTION FOR PROECT.          „ƒ‘ šˆ‰Œ—           */
#include <conio.h>
#include <stdio.h>
#include <alloc.h>
#include "const.h"

/*-----------------------------------------------------------------------*/
int getField(char *buffer, int len, int isNumeric, int col, int line)
{
char c;
int i=0, swEsc = NO_ESC, bcol = col;

gotoxy(col,line);
c=getch();
while(c!=ENTER &&  c!=ESC  && i <= len)
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
	      /*	 if (++col == COLOMN)
			       {
			       col = bcol;
			       line++;
			       }*/
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
/*************************************************************************/