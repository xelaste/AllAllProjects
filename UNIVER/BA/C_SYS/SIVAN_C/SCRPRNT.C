/**************************************************************************/
/*			     M A I N					  */
#include "const.h"
#include <graphics.h>
#include <stdio.h>
#include <alloc.h>
#include <dos.h>
#include <stdlib.h>
#define   X1  1
#define   X2  80
#define   Y1  1
#define   Y2  25
char *area;
void fsave_to_file(char *arr,char *file_name,int top_lin,int bot_lin);
char *keep_area(int top_col,int top_lin, int bot_col,int bot_lin);
char far *TP_SCR() ;
/*--------------------------------------------------------------*/
  void main(int argc,char *argv[])
       { 
	 char *name;
	 int y_1=Y1 , y_2=Y2;
	 if (argc > 1)
		  name=argv[1];
	     else
		  name="screen.dat";

	 if (argc > 2)
		{
		  y_1=atoi(argv[2])?atoi(argv[2]):Y1;
		  y_2=atoi(argv[3])?atoi(argv[3]):Y2;
		}
	 y_1=(y_1>25||y_1<1)?Y1:y_1;
	 y_2=(y_2>25||y_2<1)?Y2:y_2;
	 y_2=(y_2<y_1)?Y2:y_2      ;
	 area=keep_area(X1,y_1,X2,y_2);
	 fsave_to_file(area,name,y_1,y_2);
	}
/*-------------------------------------------------------------------------*/
 void fsave_to_file(char *arr,char *file_name,int top_lin,int bot_lin)
       {
	FILE *fpout;
	char str[X2+1];
	int line_counter=0 , col_counter=0;
	fpout=fopen(file_name,"wt");
	if(fpout)
	    {
	     for (line_counter=top_lin;line_counter <= bot_lin;
		  line_counter++,col_counter=0)   
	       {
		for(col_counter=0;col_counter<X2;col_counter++ , arr++)
		 fputc(*arr++,fpout);
		 fputc('\n',fpout)  ;
		}
		 fputc('\f',fpout);
	     fclose(fpout);
	    }
	else
	   printf("\n Illegal file name %s",file_name);
      }
/*-----------------------------------------------------------------------*/
char *keep_area(int top_col,int top_lin, int bot_col,int bot_lin)
{
     int size_area=2*(bot_lin - top_lin+1)*(bot_col - top_col+1),
	 i=0,hlp_col;
     char *pwind;
     char far *bgnwind;
     flushall();
     if((pwind=malloc(size_area * (sizeof(char))))!=NULL)
       {
	 while ((top_lin)<=(bot_lin))
	    {
		  bgnwind = BGN_SCR;
		  bgnwind+=PLACE(top_col,top_lin);
	       for(hlp_col=top_col;hlp_col<=bot_col;hlp_col++)
		  {
		   pwind[i++]=*bgnwind;
		   bgnwind++;
		   pwind[i++]=*bgnwind;
		   bgnwind++;
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
char far *TP_SCR() /*--defining type of screen-----*/
 { 
   int gd,gm;
   unsigned char far *screen;
   detectgraph(&gd,&gm);
   if (gd==HERCMONO)
	 screen = MK_FP(MONOCHROME,0);
      else
	 screen = MK_FP(POLYCHROME,0);
   return screen;
  }
/*-----------------------------------------------------*/