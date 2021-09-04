#include <stdio.h>
#include <dos.h>
#include <conio.h>
#define ATR (7)
#define FILLER_1 42
#define FILLER_0 32
#define SCR_MODE (0xb000)
#define BGN_SCR  (MK_FP(SCR_MODE,0))
#define END_SCR  (MK_FP(SCR_MODE,4000))
/*---------prototyping-----------*/
void fcls(void);
/*------------------------------------------------------------------------*/
main()
{
 fcls();
}
/*------------------------------------------------------------------------*/
void fcls(void)
{
 char far *scr_point=BGN_SCR;
 for (scr_point=BGN_SCR;scr_point <= END_SCR;scr_point++)
     {
      *scr_point++=FILLER_1;
      *scr_point=ATR;
     }
}
/**************************************************************************/