#include <const.h>
#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <alloc.h>
#include <const.h>
#include <msg.h>
/*--------prototyping----------*/
void putmarker(int x,int y,char mark);
int fchoise(int str_col,int str_lin,int lst_col,int lst_lin,int *row,int *col);
char *keep_area(int top_lin,int top_col, int bot_lin,int bot_col);
void restore_area(int top_col,int top_lin,int bot_col,int bot_lin,char *area);
void  fprint_msg(int col,int lin,char *msg,char atribute);
void fmatrice(int x1,int y1);
void ferror_msg(char *msg);
/*----------------------------------------------------------*/
main()
{int a,b,act_number,start_col,start_line,last_col,last_line,time,day;
 char *buffer;
 scanf("%d%d",&a,&b);
 buffer=keep_area(a,b,a+WIDE-1,b+HEIGHT-1);
 getch();
 fmatrice(a,b);
 start_col=a+START_HOR_STEP;
 start_line=b+START_VER_STEP;
 last_col=start_col + (WORK_DAY_NUMBER-1) * HOR_STEP;
 last_line=start_line+(LESSON_NUMBER-1)*VER_STEP;
 act_number=fchoise(start_col,start_line,last_col,last_line,&time,&day);
 printf("\n%d",act_number);
 getch();
 restore_area(a,b,a+WIDE-1,b+HEIGHT-1,buffer);
}
/*--------------------------------------------------------------------*/
