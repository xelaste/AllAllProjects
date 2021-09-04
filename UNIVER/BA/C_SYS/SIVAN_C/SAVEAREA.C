
#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <alloc.h>

#define ATR (7)
#define SPACE  (' ')
#define FILLER_1 42
#define FILLER_0 32
#define SCR_WDT  (80)
#define SCR_MODE (0xb000)
#define BGN_SCR  (MK_FP(SCR_MODE,0))
#define END_SCR  (MK_FP(SCR_MODE,4000))
#define PLACE(X,Y)(2*((Y-1)*SCR_WDT+(X-1)))
/*---------prototyping-----------*/
void fcls(void);
char * keep_area(int top_col,int top_lin, int bot_col,int bot_lin);
void restore_area(int top_col,int top_lin,int bot_col,int bot_lin,char *area);
/*------------------------------------------------------------------------*/
main()
{int x1,y1,x2,y2;
 char *buffer;
 printf("\nenter coordinates pointers " );
 scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
 buffer=keep_area(x1,y1,x2,y2);
 getch();
 restore_area(x1, y1, x2, y2, buffer);
}
/*------------------------------------------------------------------------*/
void fcls(void)
{
 char far *scr_point=BGN_SCR;
 for (scr_point=BGN_SCR;scr_point <= END_SCR;scr_point++)
     {
      *scr_point++=FILLER_0;
      *scr_point=ATR;
     }
}
/*-----------------------------------------------------------------------*/
char *keep_area(int top_col,int top_lin, int bot_col,int bot_lin)
     {
     int size_area=(bot_lin - top_lin+1)*(bot_col - top_col+1),
	 i=0,hlp_col;
     char *pwind;
     char far *bgnwind;
     if((pwind=malloc(size_area * (sizeof(char))))!=NULL)
       {
	 while ((top_lin)<=(bot_lin))
	    {
		  bgnwind=BGN_SCR;
		  bgnwind+=PLACE(top_col,top_lin);
	       for(hlp_col=top_col;hlp_col<=bot_col;hlp_col++)
		  {
		   pwind[i++]=*bgnwind;
		   *bgnwind++=FILLER_0;
		   *bgnwind++=ATR;
		  }
	      top_lin++;
	    }
	return(pwind);
       }
      else
       {
	printf("\n not enough memory");
	return(NULL);
       }
     }
/*-----------------------------------------------------------------------*/
void restore_area(int top_col,int top_lin,int bot_col,int bot_lin, char *area)
{
     int hlp_col;
     char far *pscr;
     while(top_lin<=bot_lin)
	  {
	   hlp_col=top_col;
	   pscr=BGN_SCR;
           pscr +=  PLACE(top_col,top_lin);
	   while(hlp_col <= bot_col)
		{
		 *pscr++ = *area++;
		 *pscr++=ATR;
		 hlp_col++;
		}
	   top_lin++;
	   }
     free(area);
 }
/*-----------------------------------------------------------------------*/
