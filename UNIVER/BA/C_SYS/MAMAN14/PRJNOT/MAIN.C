/*********/
/* DAMKA */  /* Main function of the game - interface and game cycles */
/*********/

#include "main.h"

main()
{
   FILE *fp;                   /* for log file and board saving file */
   char c,                     /* auxiliary variable for inputed chars */
	i,j;                   /* looping variables */

   clrscr();
   head=(pointer)malloc(sizeof(Tnode));      /* head of minimax tree */
   head->b=(Bblock*)malloc(sizeof(Bblock));  /* main root board - exists always */
   head->next=NULL;

   printf("For new game - type 'n', for suspended game continuing - 'c'>");
   c=getch();
   while ((c!='n') && (c!='c') && (c!='N') && (c!='C'))
	 {
	 printf("\a\nFor new game - type 'n', for suspended game continuing - 'c'>");
	 c=getch();
	 }
   initialize(head->b->board);
   if ( c=='n' || c=='N' )
	  filep=fopen("log.txt","w");
   else                                     /* c=='c' or c=='C'*/
	 {
	  fp=fopen("save.dat","rb");
	  if(!fp) {                         /* opening error */
		puts("\n\aCan't open data file. New game is loaded");
		filep=fopen("log.txt","w");
		}
	  else  {                           /* the file exists */
		fread(&head->b->board, sizeof(char), sizeof(boardt), fp);
		fclose(fp);
		filep=fopen("log.txt","a"); /* append log to the old one */
		}
	  };

   for(;;)
    /* i.e. there are figures on the board and not stale-mate situation */

      {
      board_draw() ;                    /* board printing */

      if (move_of_pl())                 /* player's move. 1 if exit is inputed */
	  {
	   fclose(filep);

/* saving the game in the file query: */

	   printf("\nSave the game to the future?");
	   c=getch();
	   while ((c!='y') && (c!='n'))
		 {
		  printf("\a\n'y' or 'n' : ");
		  c=getch();
		 }
	   if (c=='n') {
		 fclose(filep);
		 return 0;
		 }
	   else {
		fp=fopen("save.dat","wb");
		fwrite(&head->b->board, sizeof(char), sizeof(boardt), fp);
		fclose(filep);
		fclose(fp);
		return 0;
		}
	  }

/* COMPUTER'S MOVE: */

	  buildtree(head,0);      /* min-max tree building */
	  head=bestbranch();      /* move realization */
	  head=killtree(head);    /* kill minmax tree */

/* End of the game? */

	  if (stalemate && count_figures(head->b->board,1))
	      {
	       printf ("\nStale-mate situation. Computer has been blocked.\n") ;
	       fclose(filep);
	       return 0;
	      }
	  else if (!count_figures(head->b->board,1))
	      {
	       printf ("\nGAME IS OVER. YOU ARE A WINNER!\n") ;
	       fclose(filep);
	       return 0;
	       }
	  else if (!count_figures(head->b->board,0))
	      {
	       board_draw() ;         /* board print */
	       printf ("\nGAME IS OVER. COMPUTER IS A WINNER.\n") ;
	       fclose(filep);
	       return 0;
	      }

      }                               /* end of main game loop */
}
