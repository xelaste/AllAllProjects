/**************************************************************************/
/*                           M A I N                                      */
#include "const.h"
#include "msg.h"
#include "struct.h"
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <alloc.h>
#include "declarat.h"
struct unit  units[TIME_UNITS][DAY_UNITS][MAX_UNITS];
struct entry courses[MAX_COURSES];
struct entry teacher[MAX_TEACHERS];
struct entry groups[MAX_GROUPS];
int listlen_units=0;
int listlen_courses=0;
int listlen_teachers=0;
int listlen_groups=0;
/*--------------------------------------------------------------*/
main()
{
     char terminator=0;
     fcls();
     loadfiles();
     main_menu();
     while(terminator!=ESC)
	{
	help_line(MENU_SELECT);
	terminator=getch();
	switch (terminator)
	      {
	      case '1' : unit();
		       break;
	      case '2' : list();
		       break;
/*            case '3' : report()
		       break;*/
	      default : if (terminator!=ESC)
			  ferror_msg(WAS_ERROR);
			break;
	      }
	 }
     fcls();
 /*  savefiles()*/
}
/*-------------------------------------------------------------------------*/
void unit(void)
{
     int Time, Day, c, was_esc=0;
     char *area;

     area = keep_area(MATRICE_START_COL, MATRICE_START_LINE, MATRICE_END_COL, MATRICE_END_LINE);
     fmatrice(MATRICE_START_COL, MATRICE_START_LINE);
     while(was_esc!=ESC)
	     {
	      help_line(UNITS_SELECT);
	      was_esc = fchoise(START_COL, START_LINE, LAST_COL, LAST_LINE, &Time, &Day);
	     if(was_esc != ESC)
		  units_manager(Time,  Day);
	     }
     restore_area(MATRICE_START_COL, MATRICE_START_LINE, MATRICE_END_COL, MATRICE_END_LINE, area);
}
/*-----------------------------------------------------------------------*/
void list (void)
{
     char terminator;
     char *buffer=keep_area(LIST_LEFT_COL,LIST_TOP_LINE,LIST_RIGHT_COL,LIST_BOTTOM_LINE);
     list_menu();
     while((terminator=getch())!=ESC)
	switch (terminator)
	     {
	      case '1' : courses_list();
		       break;
	      case '2' : teachers_list();
		       break;
	      case '3' : groups_list();
		       break;
	     default : ferror_msg(WAS_ERROR);
			break;
	     }
      restore_area(LIST_LEFT_COL,LIST_TOP_LINE,LIST_RIGHT_COL,LIST_BOTTOM_LINE,buffer);
}
/*------------------------------------------------------------------------*/
void loadfiles(void)
{
clean_units();
}



