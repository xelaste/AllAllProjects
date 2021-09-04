/**************************************************************************/
/*  FUNCTION FOR PROECT.          „ƒ‘ šˆ‰Œ—           */
#include <conio.h>
#include <stdio.h>
#include <alloc.h>

#define   CARRIAGE_RETURN   13
#define   BACKSPACE   8
#define   ESCAPE      27
#define   NUMERIC     1
#define   COLOMN      80
#define   YES_ESC     1
#define   NO_ESC      0

int getField(char *buffer, int len, int isNumeric, int col, int line);

main()
{
char *buffer;
int len, isNumeric, col,line;

printf("\nEnter len, isNumeric, col, line:\n");
scanf("%d%d%d%d", &len, &isNumeric, &col, &line);
buffer = malloc(len+1);
printf("\nswEsc is %d,  Buffer is %s  ", getField(buffer, len, isNumeric,
	  col, line), buffer);
}
/*-----------------------------------------------------------------------*/
int getField(char *buffer, int len, int isNumeric, int col, int line)
{
char c;
int i=0, swEsc = NO_ESC, bcol = col;

gotoxy(col,line);
c=getch();
while(c!=CARRIAGE_RETURN &&  c!=ESCAPE  && i <= len)
	{
	if(c== BACKSPACE && i!=0)
		{
		buffer--;
		col--;
		putch(c);
		}

	else
		{
		 if((isNumeric== NUMERIC && c>='0' && c<='9') ||
		 (isNumeric!= NUMERIC))
			{
			 *buffer++ = c;
			 i++;
			 putch(c);
			 if (++col == COLOMN)
			       {
			       col = bcol;
			       line++;
			       }
			}
		}
	gotoxy(col, line);
	c = getch();
	}
if(c!= ESCAPE)
	*buffer = '\0';
else
	{
	swEsc = YES_ESC;
	buffer-=i*sizeof(char);
	for(i=0; i!='\0'; i++)
	    *buffer++ = 0;
	*buffer = 0;
	}
return(swEsc);
}
/*************************************************************************/