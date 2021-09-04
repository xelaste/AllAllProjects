/*  FUNCTION FOR PROECT.     MAIN MENU.            */
#include "const.h"
#include "msg.h"
/*------------------------------------------------------*/
void main_menu(void)
{
char *title,  *help, *str;
char attribute;
int x1, y1, x2, y2;

fcls();
title = MAIN_MENU_TITLE;
help  = HELP_SELECT;
x1 = LEFT_CORNER_COLUMN;
y1 = LEFT_CORNER_LINE;
x2 = RIGHT_CORNER_COLUMN;
y2 = RIGHT_CORNER_LINE;
fwindow(x1,x2,y1,y2, title, help);
x1 = COLUMN_INSIDE;
y1 += 4;
str = MAIN_MENU_1;
attribute = ATR;
fprint_msg(x1, y1, str, attribute);
y1++;
str = MAIN_MENU_2;
fprint_msg(x1, y1, str, attribute);
y1++;
str = MAIN_MENU_3;
fprint_msg(x1, y1, str, attribute);
y1++;
str = MAIN_MENU_4;
fprint_msg(x1, y1, str, attribute);
}