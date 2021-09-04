/*     ACCEPTLISTENTRY         */
#include "const.h"
#include "msg.h"
#include "struct.h"
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <alloc.h>
/*-------------------------------------------*/
char *keep_area(int x1, int y1, int x2, int y2);
/*-----------------------------------------*/
int acceptlistentry(struct entry *pentry)
{
int x1 = COLUMN_INSIDE,               y1 = LINE_INSIDE+12,
    x2 = COLUMN_INSIDE+NAME_LEN+40,   y2 = LINE_INSIDE+16,
     x = COLUMN_INSIDE+DIF_COL+2,      y = LINE_INSIDE+15;
int was_esc,  len, isnum;
char *area, *buffer;
char *title = TITLE_CODE_NAME;
char *help  = MSG_ENTER;

area = keep_area(x1, y1, x2, y2);
fwindow(x1,x2,y1,y2,title, help);
len = 1;     isnum = 1;
buffer = malloc(sizeof(int));
if((was_esc = getField(buffer, len, isnum, x, y))==YES_ESC)
   {restore_area(x1,y1,x2,y2,area);
   return was_esc;
   }
pentry -> code= atoi(buffer);
free(buffer);
x+=20;
len = NAME_LEN;
isnum=0;
buffer = malloc((len+1)*sizeof(char));
was_esc = getField(buffer, len, isnum, x, y);
if(was_esc==NO_ESC)
	strcpy(pentry->name,buffer);
free(buffer);
restore_area(x1,y1,x2,y2,area);
return was_esc;
}
/*----------------------------------------------------------*/
