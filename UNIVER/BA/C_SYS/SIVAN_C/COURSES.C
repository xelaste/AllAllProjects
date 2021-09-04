/************************************************************************/
#include "const.h"
#include "msg.h"
/*#include "struct.h"*/
#include <conio.h>
#include <stdio.h>
/*------------------------------------*/
void show_list(struct entry *list,int listlen,int i);
/*-------------------------*/
void courses_list(void)
{
char str[]=UPDATE;
char title[] = TITLE_CODE_NAME;

int listlen = 0;
int i=0;
fwindow(LIST_X1, LIST_X2, LIST_Y1, LIST_Y2,title, str);
show_list(courses,listlen,i);
}
/*----------------------------------------------------------------*/
void show_list(struct entry *list,int listlen,int i)
{
int x=LIST_X1 +DIF_COL, y = LIST_Y1+DIF_LINE+1;
while(y<LIST_Y2-1)
   {
   if(i<=listlen)
	{
	gotoxy(x,y);
	printf("%d",list[i].code);
	printmsg(x+10, y, list[i].name);
	i++;
	}
   else
	{
	gotoxy(x,y);
	printf(EMPTY);
	}
   y++;
   }
}