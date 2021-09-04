/*********************************************************************/
#include <conio.h>
#include "const.h"
#include "msg.h"
/*#include "struct.h"*/
/*------------------------------------------------------------*/
void dellistentry(struct entry *pentry)
{
char c;
char *str;
int x =40, y = SCR_BOT;

str = DEL_QUESTION;
help_line(str);
gotoxy(x,y);
c=getch();
if(c=='Y' || c=='y')
	{
	while((pentry -> code) != '0')
		*pentry++ = *(pentry +1);
	return;
	}
else
	return;
}
/***************************************************************************/