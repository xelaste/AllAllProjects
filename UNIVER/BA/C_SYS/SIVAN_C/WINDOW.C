/***********************************************************************/
/*     WINDOW - FUNCTION FOR PROJECT.Š‘Ž„ Œ’ š†…˜‡Ž„ š€  ‚‰–„      */
#include <dos.h>
#include <stdio.h>

#define FILLER_1 42
#define FILLER_0 32
#define SCR_MODE (0xb000)
#define BGN_SCR  (MK_FP(SCR_MODE,0))
#define END_SCR  (MK_FP(SCR_MODE,4000))

#define ATT          7
#define SCR_WDT      80
#define SCR_BOT      25

#define MAX          70
#define SPACE        ' '
#define REVERSE      112
#define DIF_COL      5
#define DIF_LIN      2
/*--------------Prototyping------------------------------------*/
void  window (int x1, int x2, int y1, int y2, char *title, char *Line);
void fcls(void);
void printmsg(int col, int lin, int att, char *pstr);
void bot_line(void);
/*-------------------------------------------------------------*/
main()
{
int x1, x2, y1, y2;
char title[MAX];
char Line[MAX];

printf("\Enter conditions:coordinates(col, line), title and notice:\n");
scanf("%d%d%d%d%s%s", &x1,&x2,&y1,&y2, title, Line);
window(x1, x2, y1, y2, title, Line);
}
/*------------------------------------------------------------------------*/
void  window (int x1, int x2, int y1, int y2, char *title, char *Line)
{
char far *pscr = BGN_SCR;
char far *psR, far *psL;
int bgn_x = x1;
int bgn_y = y1;

fcls();
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
printmsg((bgn_x + DIF_COL), (bgn_y + DIF_LIN), ATT, title);
bot_line();
x1 = 1;  y1 = SCR_BOT - 1;
printmsg(x1, y1, REVERSE, Line);
}
/*----------------------------------------------------------------------*/
void fcls(void)
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