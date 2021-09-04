#include <stdio.h>
#include <conio.h>
#include "info.h"
/*------------------------------------------------------------------------*/
/*This program is the game checkers.It accept from keyboard next move or  */
/*command and make reply move or do correspond action                     */
/*------------------------------------------------------------------------*/
void main ()
{
struct BOARD B;
struct POINT Mlist[MoveLenth];
COMMAND_VALUE command;
BOOL refresh,GameIsOver;
char *mv;
int N,i;
NewGame(&B);   /*begining the game*/
GameIsOver=FALSE;
showboard(B.Board);
do
{
 refresh=FALSE;
 command=UserInput(&mv);/*accept next action from keyboard*/
 switch (command)
   {
   case HALT:  SaveToFile(B); /*stop the game*/
	       break;
   case HELP:  ShowHelp();   /*show possible commands and format of move*/
	       refresh=TRUE;
	       break;
   case NEW  : NewGame(&B);  /*restart game */
               refresh=TRUE;
	       break;
   case LOAD : if (LoadFromFile(&B)) refresh=TRUE;/*load old position 
	       break;                               from file       */
   case SAVE : SaveToFile(B);   /*Save current position from file */
	       break;
   case SHIFT: ExChangeSide(&B);/* exchange sides between 
				   human and machine*/
	       GameIsOver=!(ComputersTurn(&B));
	       break;
   case MOVE : N=StringToMove(mv,Mlist);/*make human move and reply */
	       if(N)
		 {
		 for(i=0;i<N-1;i++)
		 if (!UsersTurn(&B,Mlist[i],Mlist[i+1]))
		    {
		    if(B.The_Winer==unknown)
		       printf("\nInvalide move !!!");
		       break;
		    }
		    else ComputersTurn(&B);

		 if (B.The_Winer!=unknown)
		   {
		   if(B.The_Winer==B.Human)    printf("\nHuman won");
		   if(B.The_Winer==B.Computer) printf("\nComputer won");
		   printf("\nPress any key to continue");
		   GameIsOver=TRUE;
		   getch();
		   }
		}
	       else printf("\nInvalid command format");
	       break;
   default   : break;
   }
 if (GameIsOver)
    {
    NewGame(&B);
    GameIsOver=FALSE;
    }
if (refresh) showboard(B.Board);
}
while (command!=HALT);
}