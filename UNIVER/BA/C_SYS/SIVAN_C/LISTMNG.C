/***************************************************************************/
/*                      L I S T   M A N A G E R .                          */
#include "const.h"
#include "msg.h"
#include "struct.h"
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <alloc.h>
#include "declarat.h"
int Max_list;
extern struct entry courses[MAX_COURSES];
extern struct entry teacher[MAX_TEACHERS];
extern struct entry groups[MAX_GROUPS];
extern listlen_courses;
extern listlen_teachers;
extern listlen_groups;
/*--------------------------------------------------------------*/
void courses_list(void)
{
     char *area;
     int i=0, c=0;

     Max_list = MAX_COURSES;

     area = keep_area(LIST_X1, LIST_Y1, LIST_X2, LIST_Y2);
     courses[listlen_courses].code=NULL;
     fwindow(LIST_X1, LIST_X2, LIST_Y1, LIST_Y2,TITLE_CODE_NAME,UPDATE);
     show_list(courses,listlen_courses,i);

     while(c!=ESC)
	  {
	   help_line(UPDATE);
	   c=getch();
	   if(strchr("YyNn",c)!=NULL)
	      list_manager(courses, &listlen_courses, c);
	  }
     restore_area(LIST_X1, LIST_Y1, LIST_X2, LIST_Y2,area);
}
/*----------------------------------------------------------------*/
void teachers_list(void)
{
     char *area;
     int i=0, c=0;

     Max_list = MAX_TEACHERS;

     area = keep_area(LIST_X1, LIST_Y1, LIST_X2, LIST_Y2);
     teacher[listlen_teachers].code=NULL;
     fwindow(LIST_X1, LIST_X2, LIST_Y1, LIST_Y2,TITLE_CODE_NAME,UPDATE);
     show_list(teacher,listlen_teachers,i);

     while(c!=ESC)
	  {
	   help_line(UPDATE);
	   c=getch();
	   if(strchr("YyNn",c)!=NULL)
	      list_manager(teacher, &listlen_teachers, c);
	  }
     restore_area(LIST_X1, LIST_Y1, LIST_X2, LIST_Y2,area);
}
/*----------------------------------------------------------------*/
void groups_list(void)
{
     char *area;
     int i=0, c=0;

     Max_list = MAX_GROUPS;

     area = keep_area(LIST_X1, LIST_Y1, LIST_X2, LIST_Y2);
     groups[listlen_groups].code=NULL;
     fwindow(LIST_X1, LIST_X2, LIST_Y1, LIST_Y2,TITLE_CODE_NAME,UPDATE);
     show_list(groups,listlen_groups,i);

     while(c!=ESC)
	{
	help_line(UPDATE);
	c=getch();
	if(strchr("YyNn",c)!=NULL)
	       list_manager(groups, &listlen_groups, c);
	}
     restore_area(LIST_X1, LIST_Y1, LIST_X2, LIST_Y2,area);
}
/*----------------------------------------------------------------*/
void list_manager(struct entry *list, int *listlen, int update)
{
     int Code,  i=0, c;
     struct entry *pentry_current;
     fflush(stdin);
     if(update == 'N' || update == 'n')
	     listing(list,*listlen);
     if(update == 'Y' || update == 'y')
	     {
	   do
		{
		 help_line(SELECT);
                 if((c=getch())==NULL)
		     c=getch();
		 if (c==INSERT || c==DELET)
		     {
		      Code =acceptcode();
		      pentry_current = code_exists(Code,list, *listlen);
		     }

		 switch(c)
			{
			case DELET  :if (pentry_current!= NULL)
					 {
					 dellistentry(pentry_current);
					 (*listlen)--;
					 list[(*listlen)].code=NULL;
					 show_list(list,*listlen,i);
					 }
				      else
					  ferror_msg(WAS_ERROR);
				      break;
			case INSERT : if (pentry_current== NULL)
					   if((*listlen)< Max_list)
					      {
					      addlistentry(Code,list, listlen);
					      show_list(list,*listlen,i);
					      }
					   else
					       help_line(FULL);
				      else
					  ferror_msg( WAS_ERROR);
				      break;
		       default     : if (c!=ESC)
					  ferror_msg(WAS_ERROR);
				       break;

			}
		}
	     while (c!=ESC);
	     }
}
/*-------------------------------------------------------------------*/
void show_list(struct entry *list,int listlen,int i)
{
     int x=LIST_X1 +DIF_COL, y = LIST_Y1+DIF_LINE_LIST;
     while(y<LIST_Y2-1)
	{
	if(i<listlen)
	     {
	     gotoxy(x,y);
	     printf(EMPTY);
	     gotoxy(x,y);
	     printf("%d",list[i].code);
	     fprint_msg(LIST_LINE, y, list[i].name,ATR);
	     i++;
	     }
	else
	     {
	     gotoxy(x,y);
	     printf(EMPTY);
	     }
	y++;
	}
}
/*----------------------------------------------------------------*/
void listing(struct entry *pentry,int listlen)
{
     int terminator=0,i=0;
     char expr[]=WAS_ERROR;
     do
      {
	    switch(terminator)
		 {
		  case PgUp : if(i-=SIZE_OF_PAGE <= 0)
				   {i=0;
				    show_list(pentry,listlen,i);
				   }
			       break;
		  case PgDn :  if(i+=SIZE_OF_PAGE <= listlen)
				  show_list(pentry, listlen, i);
				break;
		  default : if(terminator!=ESC && terminator!=0)
						   ferror_msg(expr);
		  break;
		 }
	     }
       while((terminator=getch())!=ESC);
  }
/*------------------------------------------------------------------------*/
int acceptlistentry(struct entry *pentry)
{
     int x1 = COLUMN_INSIDE,		   y1 = LINE_INSIDE+12,
	 x2 = COLUMN_INSIDE+NAME_LEN+40,   y2 = LINE_INSIDE+16,
	  x = COLUMN_INSIDE+DIF_COL+2,	    y = LINE_INSIDE+15;
     int was_esc,  len, isnum;
     char *area, *buffer;

     area = keep_area(x1, y1, x2, y2);
     fwindow(x1,x2,y1,y2,TITLE_CODE_NAME, MSG_ENTER);
/*   len = CODE_LEN; isnum = NUMERIC;
     buffer = malloc(sizeof(int));
     if((was_esc = getField(buffer, len, isnum, x, y))==YES_ESC)
	{restore_area(x1,y1,x2,y2,area);
	return was_esc;
	}
     pentry -> code= atoi(buffer);
     free(buffer);                */
     gotoxy(x,y);
     printf("%d", pentry -> code);
     x+=20;
     len = NAME_LEN;
     isnum=NUN_NUMERIC;
     buffer = malloc((len+1)*sizeof(char));
     was_esc = getField(buffer, len, isnum, x, y);
     if(was_esc==NO_ESC)
	     strcpy(pentry->name,buffer);
     free(buffer);
     restore_area(x1,y1,x2,y2,area);
     return was_esc;
}
/*-------------------------------------------------------------------*/
void dellistentry(struct entry *pentry)
{
     int c;

     help_line(DEL_QUESTION);
     while(strchr("YyNn", (c=getch()))==NULL);
     if(c=='Y' || c=='y')
	     {
	     while((pentry -> code) != NULL)
		     *pentry++ = *(pentry +1);
	     }
}
/*-------------------------------------------------------------------------*/
void addlistentry(int Code, struct entry *pentry, int *listlen)
{
     int  was_esc;
     struct entry *pentry_end;

     pentry_end = pentry + *listlen -1;

     while((pentry_end -> code) > Code)
	      {
	      *(pentry_end+1) = *pentry_end;
	       pentry_end--;
	      }
     pentry_end++;
     pentry_end -> code = Code;
     do
	 was_esc = acceptlistentry(pentry_end);
     while(was_esc!= NO_ESC);
     (*listlen)++;
     pentry[(*listlen)].code=NULL;
}
/*--------------------------------------------------------------------*/
struct entry *code_exists(int Code, struct entry *pentry, int listlen)
{
     int i=0;

     while(i <= listlen)
	     {
	     if(pentry -> code == Code)
		     return(pentry);
	     else
		     {
		     pentry++;
		     i++;
		     }
	     }
     if(i > listlen)
	     {
	     help_line(NO_RECORD);
	     return(NULL);
	     }
}
/*--------------------------------------------------------------------*/
int acceptcode(void)
{
     int x1 = COLUMN_INSIDE,		   y1 = LINE_INSIDE+12,
	 x2 = COLUMN_INSIDE+40, 	   y2 = LINE_INSIDE+16,
	  x = COLUMN_INSIDE+DIF_COL+2,	    y = LINE_INSIDE+15;
     int was_esc,  len, isnum, code=0;
     char *area, *buffer;

     area = keep_area(x1, y1, x2, y2);
     fwindow(x1,x2,y1,y2,TITLE_CODE,HELP_ENTER_CODE);
     len = CODE_LEN;	  isnum = NUMERIC;
     while(code==0)
     {
      buffer = malloc(sizeof(int));
      if((was_esc = getField(buffer, len, isnum, x, y))==YES_ESC)
	{restore_area(x1,y1,x2,y2,area);
	return was_esc;
	}
      else
	   {
	   restore_area(x1,y1,x2,y2,area);
	   code= atoi(buffer);
	   free(buffer);
	   return(code);
	   }
    }
}
/*****************************************************************/
