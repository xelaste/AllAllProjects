#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <"const.h">
#define ATT_NORMAL  (7)
#define BLANK 42
#define STAR 32
#define SCR_MODE (0xb000)
#define BGN_SCR  (MK_FP(SCR_MODE,0))
#define END_SCR  (MK_FP(SCR_MODE,4000))
/*---------prototyping-----------*/
void cls(void);
/*------------------------------------------------------------------------*/
main()
{
 cls();
}
/*------------------------------------------------------------------------*/
void cls(void)
{
 char far *scr_point=BGN_SCR;
 for (scr_point=BGN_SCR;scr_point <= END_SCR;scr_point++)
     {
      *scr_point++=BLANK;
      *scr_point=ATR;
     }
}
/**************************************************************************/