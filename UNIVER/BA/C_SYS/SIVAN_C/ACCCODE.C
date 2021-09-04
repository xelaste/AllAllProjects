/*     ACCEPTCODE        */
#include "const.h"
#include "msg.h"
/*#include "struct.h"*/
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <alloc.h>

/*-----------------------------------------*/
int acceptcode(void)
{
int x1 = COLUMN_INSIDE,               y1 = LINE_INSIDE+12,
    x2 = COLUMN_INSIDE+40,            y2 = LINE_INSIDE+16,
     x = COLUMN_INSIDE+DIF_COL+2,      y = LINE_INSIDE+15;
int was_esc,  len, isnum, code;
char *area, *buffer;
char *title = TITLE_CODE;
char *help  = HELP_ENTER_CODE;

area = keep_area(x1, y1, x2, y2);
fwindow(x1,x2,y1,y2,title, help);
len = 1;     isnum = 1;
buffer = malloc(sizeof(int));
if((was_esc = getField(buffer, len, isnum, x, y))==YES_ESC)
   {restore_area(x1,y1,x2,y2,area);
   return;
   }
else
      {
      restore_area(x1,y1,x2,y2,area);
      code= atoi(buffer);
      free(buffer);
      return(code);
      }
}
/*----------------------------------------------------------*/
