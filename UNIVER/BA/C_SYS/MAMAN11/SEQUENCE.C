/* This program accept string from standart input and checks
if input string  is sorted string;
and prints  result of check onto screen
*/
#include <conio.h>
#include <stdio.h>
void main ()
{
char ch=0,prev=0;
enum modes {ASC,DES,UNSORT,FIRST,SECOND} the_mode=FIRST;
while ((ch=getchar())!=EOF)
{
switch (the_mode)
 {
 case FIRST  : the_mode=SECOND;
      break;
 case SECOND : if (ch>=prev) the_mode=ASC; else the_mode=DES;
      break;
 case ASC    : if (ch<prev)  the_mode=UNSORT;
      break;
 case DES    : if (ch>=prev) the_mode=UNSORT;
      break;
 case UNSORT : break;
 default:break;
 }
prev=ch;
}
switch (the_mode)
{
 case FIRST : printf("\nThe input string is empty\n");
	      break;
 case SECOND: printf("\nThe input string includes only character\n");
	      break;
 case ASC   : printf("\nThe input string is in ascending order\n");
	      break;
 case DES   : printf("\nThe input string is in descending order\n");
	      break;
 case UNSORT: printf("\nThe input string is unsorted\n");
	      break;
}
}