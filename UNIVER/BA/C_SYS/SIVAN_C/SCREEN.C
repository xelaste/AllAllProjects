/***********************************************************************/
/*     SCREEN-FUNCTIONS FOR PROECT.Š‘Ž„ Œ’ š†…˜‡Ž„ š€  ‚‰–„      */
#include "const.h"
#include <dos.h>
#include <stdio.h>

/*--------------Prototyping------------------------------------*/
void  window (int x1, int x2, int y1, int y2);
void cls(void);
void printmsg(int col, int lin, int att, char *pstr);
void bot_line(void);
/*------------------------------------------------------------*/
main()
{
int x1, x2, y1, y2,  x3, y3, att;
char str[MAX];

printf("\nEnter coordinates:\ncol left,  col right, line left, line right:");
scanf("%d%d%d%d", &x1,&x2,&y1,&y2);
printf("\nEnter conditions for string:\ncol, line, attribute, string:\n ");
scanf("%d%d%d%s",&x3, &y3, &att, str);
cls();
window(x1, x2, y1, y2);
printmsg(x3, y3, att, str);
bot_line();
}
void  window (int x1, int x2, int y1, int y2)
{
char far *pscr = BGN_SCR;
char far *psR, far *psL;
int bgn_x = x1;

psR = pscr + 2 * (y1 * SCR_WDT + x1);
psL = pscr + 2 * (y2 * SCR_WDT + x1);
*psR++ = 0xC9;         *psL++ = 0xC8;
*psR++ = ATT;          *psL++ = ATT;
x1++;
while(x1 < x2)
	{
	*psR++ = *psL++ = 0xCD;
	*psR++ = *psL++ = ATT;
	x1++;
	}
*psR++ = 0xBB;       *psL++ = 0xBC;
*psR-- = *psL-- = ATT;
psL = pscr + 2 * ((++y1) * SCR_WDT + bgn_x);
while(y1 < y2)
	{
	psR += 2*SCR_WDT;
	*psR++ = *psL++ = 0xBA;
	*psR-- = *psL-- = ATT;
	psL += 2*SCR_WDT;
	y1++;
	}
}
/*----------------------------------------------------------------------*/
void cls(void)
{
 char far *scr_point=BGN_SCR;
 for (scr_point=BGN_SCR;scr_point <= END_SCR;scr_point++)
     {
      *scr_point++=FILLER_0;
      *scr_point=ATT;
     }
}
/*------------------------------------------------------------------------*/
void printmsg(int col, int lin, int att, char *pstr)
{
char far *pscr = BGN_SCR;

pscr += 2 * (lin * SCR_WDT + col);
while(*pstr)
     {
     *pscr++ = *pstr++;
     *pscr++ = att;
     }
}
/*------------------------------------------------------------------------*/
void bot_line(void)
{
char far *pscr = BGN_SCR;

pscr += 2 * ((SCR_BOT - 1) * SCR_WDT);
while(pscr < END_SCR)
    {
    *pscr++ = SPACE;
    *pscr++ = REVERSE;
    }
}
/*************************************************************************/