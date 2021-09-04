/* Get next move from the user */

#include "main.h"

char move_of_pl(void)
{
   int i, j, k ;         /* looping var's */
   char c[128],          /* temporal container for a command */
	temp,            /* temporal container for a figure */
	flag=1,          /* =1 if there is an error in the input */
	col, line,       /* auxiliary var's, holding column and line */
	sign_c,sign_l,   /* for direction of move */
	flag_eat_was=0;  /* sign that eating was realised */
   boardt aux;
			 /* auxiliary array for previous board configuration holding */

   while(flag)           /* i.e. while input is erroneous (flag initially is 1) */
   {
       printf("Input your next move in the form: xNyM (a move or one figure eating)");
       printf("or in the \nform: xNyMzL...,where x,y,z...-letters; N,M,L...-numbers");
       printf(" (few figures eating.)\nType 'exit' for quit or 'switch' for players' places interchanging) > ");
       scanf ("%s",c) ;

       while(!stricmp(c,"switch"))
	   {
	   switchb(head->b->board);
	   board_draw();
	   printf("Input your next move in the form: xNyM (a move or one figure eating)");
	   printf("or in the \nform: xNyMzL...,where x,y,z...-letters; N,M,L...-numbers");
	   printf(" (few figures eating.)\nType 'exit' for quit or 'switch' for players' places interchanging) > ");
	   scanf ("%s",c) ;
	   }
       if(!stricmp(c,"exit"))
			return(1);

/* initialization of possible eating checker container: */

       for(i=0; i<2; i++) pos_eat[i]=0;
       eat_exist();

/* Error in input (primary checking): */

       for(i=0; c[i]; i++);           /* the length of input */
       if (i%2 || i<4) printf("\aError in input!\n");
       else
	{

/* reducing into numeric coordinates: */

	    for(j=0; c[j]; j=j+2)
		{
		 c[j]=c[j]-96;
		 c[j+1]=c[j+1]-48;
		}

/* checking of input correctness (board bounds): */

	    for (j=0; j<i; j++)
		{
		if((c[j]<1) || (c[j]>8))
		     {
		      printf ("There is no such move!\n\a") ;
		      break;
		      }
		 }

/* checking of move validity: */

	    if (j==i)     /* input is correct syntactically */
		    switch(head->b->board[c[1]][c[0]])
		    {
		    case USER_SOLDIER:
			 if (i>4)   /* few soldiers eating? */
			    {
			       char err=0;

/* let us make a copy of board to recover initial state if will be an error: */
			       copy(head->b->board,aux);

/* Eating by eating. If error - exit */

			       for(j=0; j<=i-3 && !err; j=j+2)
				   {
				   err=eat_by_sol(c[j],c[j+1],c[j+2],c[j+3]);
				   temp=head->b->board[c[j+1]][c[j]];
				   head->b->board[c[j+1]][c[j]]=EMPTY;
				   head->b->board[c[j+3]][c[j+2]]=temp;
				   head->b->board[(c[j+1]+c[j+3])/2][(c[j]+c[j+2])/2]=EMPTY;
				   }
			       if (err)

/* if it was an error then recover board using its copy in aux */

				  {
				    copy(aux,head->b->board);
				    printf("Error in input!\a\n");
				    break;
				   }
				else

/* no error. board has been already modified: */
				   {
				     flag=0;
				     flag_eat_was=1;
				     break;
				    }
			     }
			 else   /* i=4 ,i.e. simple move or simple eating */
			       {
			       if (head->b->board[c[3]][c[2]]!=EMPTY)
				  {
				  printf("\aError! Destination must be empty!\n");
				  break;
				  };
/* possible simple eating: */
			       if((c[0]-c[2])==2 || (c[0]-c[2])==-2)
				     if (eat_by_sol(c[0],c[1],c[2],c[3]))
					  {
					  printf("Illegal eating!\a\n");
					  break;
					  }
				      else
/* simple eating realization: */
					 {
					  temp=head->b->board[c[1]][c[0]];
					  head->b->board[c[1]][c[0]]=EMPTY;
					  head->b->board[c[3]][c[2]]=temp;
					  head->b->board[(c[1]+c[3])/2][(c[0]+c[2])/2]=EMPTY;
					  flag=0;
					  flag_eat_was=1;
					  break;
					  }
/* possible simple move: */
				else
				   if(abs(c[0]-c[2])>1 || (c[1]-c[3])!=1)
				       {
					printf("Illegal move!\n\a");
					break;
					}
				   else
/* move realization: */                 {
					temp=head->b->board[c[1]][c[0]];
					head->b->board[c[1]][c[0]]=EMPTY;
					head->b->board[c[3]][c[2]]=temp;
					flag=0;
					break;
					}
				  }
		    case USER_QUEEN:

			  if ((head->b->board[c[3]][c[2]]!=EMPTY) ||
				       (abs(c[0]-c[2])!=abs(c[1]-c[3])))

/* does the move along diagonal? */

				    {
				     printf("Invalid move for a queen!\a\n");
				     break;
				    }

/* single move in appropriate direction: */

			   sign_c=(c[2]-c[0])/abs(c[2]-c[0]);
			   sign_l=(c[3]-c[1])/abs(c[3]-c[1]);
			   for(k=c[1]+sign_l,j=c[0]+sign_c;
				     head->b->board[k][j]==0 && k!=c[3];
						   k=k+sign_l,j=j+sign_c);
			   if(k==c[3])

/* we are not eating - simple move */

			      {
			       if (i>4)
				  {
				   printf("Error! Only one move is possible.\a\n");
				   break;
				  }
			       else  /* i==4 */
				  {
				   temp=head->b->board[c[1]][c[0]];
/* move realization: */
				   head->b->board[c[1]][c[0]]=EMPTY;
				   head->b->board[c[3]][c[2]]=temp;
				   flag=0;
				   break;
				   }
			       }
			   else

/* figures on the way: eating or error */

			       {
			       char err=0;
			       for(j=0; j<=BOARDSIZE+1; j++)

/* let us make a copy of board to recover initial state if will be an error: */

				   for(k=0; k<=BOARDSIZE+1; k++)
					 aux[j][k]=head->b->board[j][k];
/* Eating by eating. If error - exit */

			       for(j=0; j<=i-3 && !err; j=j+2)
				      err=eat_by_q(c[j],c[j+1],c[j+2],c[j+3]);

/* if it was an error then recover board using its copy in aux */
			       if (err)
				  {
				    copy(aux,head->b->board);
				    printf("Error in input!\a\n");
				    break;
				   }
				else
/* no error. board has been already modified: */

				    {
				     flag=0;
				     flag_eat_was=1;
				     break;
				    }
			       }
		    case COMP_SOLDIER:
		    case COMP_QUEEN:
			  printf ("Error! an attempt to move a computer's figure!\a\n") ;
			  break ;

/* Not existing soldier move attempt: */

		    case EMPTY:
		    case PROHIBITED:
			  printf ("Error! You want to move not existing figure!\a\n") ;
		    }   /* end switch */
       }
   }  /* end while */

/* User's queen appearence: */

   if(c[i-1]==1)
	{
	head->b->board[c[i-1]][c[i-2]] = USER_QUEEN ;
	fprintf(filep,"User's QUEEN appearence on:");
	fprintf(filep,"%c%d\n",c[i-2]+96,c[i-1]);
	}

   fprintf(filep,"User's move : %c%d-%c%d\n",c[0]+96,c[1],c[2]+96,c[3]);

   board_draw() ;           /* print */

/* Did player has used his possibility (if it was) of eating?
				If no - the penalty: removing of a figure */

   if(!flag_eat_was && pos_eat[0])
	  {
	   textcolor(RED);
	   cprintf("\aYou didn't realize the chance to eat by figure on ");
	   cprintf("%c%d",pos_eat[0]+96,pos_eat[1]);
	   cprintf(" - this figure is removed.");

/* log report about removing: */

	   fprintf(filep,"User didn't take a chance to eat by figure on:");
	   fprintf(filep,"%c%d",pos_eat[0]+96,pos_eat[1]);
	   fprintf(filep," and has been penaltied by this figure removing.\n");

/* penalty realization: */

	   if(head->b->board[pos_eat[1]][pos_eat[0]]!=EMPTY)
			   /* (if user didn't move figure which might eat) */
		   head->b->board[pos_eat[1]][pos_eat[0]]=EMPTY;
	   else            /* this figure moving */
		   head->b->board[c[3]][c[2]]=EMPTY;
	   }
   return 0;
}
