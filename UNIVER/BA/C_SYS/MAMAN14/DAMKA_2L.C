/*********/
/* DAMKA */             /* Project - mamman 14 */
/*********/

/* main unit */

#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <alloc.h>

#define SIZEBOARD 8
#define SIZE SIZEBOARD+2
#define USER_SOLDIER 1
#define USER_QUEEN 2
#define COMP_SOLDER -1
#define COMP_QUEEN -2
#define PROHIBITED 3

char board[SIZE][SIZE]; /* main global array, containing the board */

void initialize(char array[SIZE][SIZE]);     /* board initialization */
void board_draw(void);               /* board print */
int threat (char line, char col);    /* threat to a soldier exists? */
char move_of_pl(FILE* filep);        /* accepts a move from the user */
char eat_by_sol(char from_c,char from_l,char to_c,char to_l);
           /* returns 0 if eating by soldier is possible, else - 1 */
char eat_by_q(char from_c,char from_l,char to_c,char to_l);
int protect(char line,char col);     /* current soldier protects an other one? */
int post_move (char col, char line, char m_col, char m_line, char pointer[2]);
                                     /* realizes possible moves */
int sold_test (char col, char line, char bstmv[4]); /* tests soldier move */
int queen_test (char col, char line, char bstmv[4]); /* tests queen move */
int minimax (FILE* filep);
void copy (char array1[SIZE][SIZE], char array2[SIZE][SIZE]);
void switchb(char array[SIZE][SIZE]);

/*******************************************************************/
void copy (char array1[SIZE][SIZE], char array2[SIZE][SIZE])
{
   char i,j;
   for (i=0; i<=SIZEBOARD+1; i++)
       for (j=0; j<=SIZEBOARD+1; j++)
            array2[i][j]=array1[i][j];
}
/*******************************************************************/
/* Eating by the soldier is legal? */
/* Four parameters are the coordinates, the last ones - the destination */

char eat_by_sol(char from_c,char from_l,char to_c,char to_l)
{
       if ( (from_c-to_c)==2 || (from_c-to_c)==-2 ) /* skip one figure? */
          if (board[to_l][to_c]==0)            /* destination is empty ? */
			if (board[(from_l+to_l)/2][(from_c+to_c)/2] <= -1)
                                               /* we eat computer's figure */
                 return 0;                     /* legal eating */
       return 1;                               /* illegal */
}
/*******************************************************************/
/* Eating by queen is legal? On the contrary with the version for soldiers,
   this procedure modifies the board (removes eaten figures).
   Four parameters are the coordinates, the last two - the destination. */

char eat_by_q(char from_c,char from_l,char to_c,char to_l)
{
     char unit_c, unit_l,                  /* for single move holding */
     temp, i, j;                           /* looping and auxiliary variables */
     unit_c = (to_c-from_c)/abs(to_c-from_c);
     unit_l = (to_l-from_l)/abs(to_l-from_l);

     if (board[to_l][to_c]!=0) return 1;   /* destination is not empty ? */
     if (abs(from_c-to_c)==abs(from_c-to_c))
           {                               /* does the move along diagonal? */
           for(i=from_l+unit_l, j=from_c+unit_c; board[i][j]==0;i=i+unit_l, j=j+unit_c)
                                           /* (skip blanks) */
               if (i==to_l) return 1;      /* not eating - error */
           if (board[i][j]>=USER_SOLDIER) return 1;   /* not computer's figure - error */
           board[i][j]=0;                  /* computer's figure removing */
           for(; board[i][j]==0 && i!=to_l; i=i+unit_l, j=j+unit_c);
                                           /* (skip blanks) */
           if (i!=to_l) return 1;          /* The second figure! - error */
                                           /* modifications on the board: */
           temp=board[from_l][from_c];
           board[from_l][from_c]=0;
           board[to_l][to_c]=temp;
           return 0;
           }
     else return 1;                        /* if not along diagonal */
}
/*******************************************************************/
/* Get next move from the user */

char move_of_pl(FILE *filep)
{
   int i, j, k ;         /* looping var's */
   char c[128],          /* temporal container for a command */
        temp,            /* temporal container for a figure */
        flag=1,          /* =1 if there is an error in the input */
        col, line,       /* auxiliary var's, holding column and line */
        sign_c,sign_l,   /* for direction of move */
        aux[SIZE][SIZE];
                         /* auxiliary array for previous board configuration holding */

   while(flag)           /* i.e. while input is erroneous (flag initially is 1) */
   {
SWCH:  printf("Input your next move in the form: xNyM (a move or one figure eating)");
       printf("or in the \nform: xNyMzL...,where x,y,z...-letters; N,M,L...-numbers");
	   printf(" (few figures eating.)\nType 'exit' for quit or 'switch' for players' places interchanging) > ");
       scanf ("%s",c) ;

	   if(!stricmp(c,"exit")) return(1);

	   if(!stricmp(c,"switch"))
				{
				switchb(board);
				board_draw();
				goto SWCH;
				}
       for(i=0; c[i]; i++);
       if ((i%2)||(i<4)) printf("\aError in input!\n");
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
                if((c[j]<USER_SOLDIER) || (c[j]>8))
                     {
                      printf ("There is no such move!\n\a") ;
                      break;
                      }
                 }

/* checking of move validity: */

            if (j==i)     /* input is correct syntactically */
                    switch (board[c[1]][c[0]])
                    {
                    case USER_SOLDIER:
/* SOLDIER: */
                         if (i>4)   /* few soldiers eating? */
                            {
                               char err=0;
                               for(j=0; j<=SIZEBOARD+1; j++)

/* let us make a copy of board to recover initial state if will be an error: */

                                   for(k=0; k<=SIZEBOARD+1; k++)
                                         aux[j][k]=board[j][k];

/* Eating by eating. If error - exit */

                               for(j=0; j<=i-3 && !err; j=j+2)
                                   {
                                   err=eat_by_sol(c[j],c[j+1],c[j+2],c[j+3]);
                                   temp=board[c[j+1]][c[j]];
                                   board[c[j+1]][c[j]]=0;
                                   board[c[j+3]][c[j+2]]=temp;
                                   board[(c[j+1]+c[j+3])/2][(c[j]+c[j+2])/2]=0;
                                   }
                               if (err)

/* if it was an error then recover board using its copy in aux */

                                  {
                                    copy(aux, board);
                                    printf("Error in input!\a\n");
                                    break;
                                   }
                                else

/* no error. board has been already modified: */

                                    {
                                     flag=0;
                                     break;
                                    }
                             }
                         else   /* i=4 ,i.e. simple move or simple eating */
                               {
                               if (board[c[3]][c[2]]!=0)
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
                                          temp=board[c[1]][c[0]];
                                          board[c[1]][c[0]]=0;
                                          board[c[3]][c[2]]=temp;
                                          board[(c[1]+c[3])/2][(c[0]+c[2])/2]=0;
                                          flag=0;
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
                                        temp=board[c[1]][c[0]];
                                        board[c[1]][c[0]]=0;
                                        board[c[3]][c[2]]=temp;
                                        flag=0;
                                        break;
                                        }
                                  }
                    case 2:
/* QUEEN: */

                          if ((board[c[3]][c[2]]!=0)||
           /* destination is empty? */
                               (abs(c[0]-c[2])!=abs(c[1]-c[3])))
           /* does the move along diagonal? */
                                    {
                                     printf("Invalid move for a queen!\a\n");
                                     break;
                                     }
           /* single move in appropriate direction: */
                           sign_c=(c[2]-c[0])/abs(c[2]-c[0]);
                           sign_l=(c[3]-c[1])/abs(c[3]-c[1]);
                           for(k=c[1]+sign_l,j=c[0]+sign_c;board[k][j]==0 && k!=c[3];k=k+sign_l,j=j+sign_c);
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
                                   temp=board[c[1]][c[0]];
           /* move realization: */
                                   board[c[1]][c[0]]=0;
                                   board[c[3]][c[2]]=temp;
                                   flag=0;
                                   break;
                                   }
                               }
                           else
           /* figures on the way: eating or error */
                               {
                               char err=0;
                               for(j=0; j<=SIZEBOARD+1; j++)

           /* let us make a copy of board to recover initial state if will be an error: */

                                   for(k=0; k<=SIZEBOARD+1; k++)
                                         aux[j][k]=board[j][k];
           /* Eating by eating. If error - exit */

                               for(j=0; j<=i-3 && !err; j=j+2)
                                      err=eat_by_q(c[j],c[j+1],c[j+2],c[j+3]);
                               if (err)

           /* if it was an error then recover board using its copy in aux */
                                  {
                                    copy(aux,board);
                                    printf("Error in input!\a\n");
                                    break;
                                   }
                                else
           /* no error. board has been already modified */
                                    {
                                     flag=0;
                                     break;
                                    }
                               }
                    case -1:
                    case -2:
                          printf ("Error! an attempt to move a computer's figure!\a\n") ;
                          break ;

/* Not existing soldier move attempt: */

                    case 0:
                    case PROHIBITED:
                          printf ("Error! You want to move not existing figure!\a\n") ;
                          break ;
                    };   /* end switch */
       }
   }  /* end while */
   if (c[i-1]==1)
/* queen appearence: */
      board[c[i-1]][c[i-2]] = 2 ;
   fprintf(filep,"User's move is     : %c%d-%c%d\n",c[0]+96,c[1],c[2]+96,c[3]);
   board_draw() ;           /* print */
   return(0);
}

/*******************************************************************/
/* Threat to be eaten by a soldier? */

int threat (char line, char col)
{
/* 4 configurations: */

   if( (board[line-1][col-1]>=USER_SOLDIER &&
        board[line-1][col-1]!=PROHIBITED &&
        board[line+1][col+1]==0)
        ||
       (board[line-1][col+1]>=USER_SOLDIER &&
        board[line-1][col+1]!=PROHIBITED &&
        board[line+1][col-1]==0)
        ||
       (board[line+1][col-1]>=USER_SOLDIER &&
        board[line+1][col-1]!=PROHIBITED &&
        board[line-1][col+1]==0)
        ||
       (board[line+1][col+1]>=USER_SOLDIER &&
        board[line+1][col+1]!=PROHIBITED &&
        board[line-1][col-1]==0))
/* i.e. there is a threat from one of four sides */

        if (board[line][col]==-1) return 10;   /* computer's soldier */
              else return 20;
    else return 0;
}

/*******************************************************************/
/* Does one soldier has been defended by the other one? */

int protect(char line,char col)
{
    if (board[line-1][col-1]<=USER_SOLDIER &&
        board[line+1][col+1]!=PROHIBITED &&
        board[line+1][col+1]>=USER_SOLDIER)
                if(board[line-1][col-1]==-1) return 10; /* soldier */
                                        else return 20;
    if (board[line-1][col+1]<=USER_SOLDIER &&
        board[line+1][col-1]!=PROHIBITED &&
        board[line+1][col-1]>=USER_SOLDIER)
                if(board[line-1][col+1]==-1) return 10; /* soldier */
                                        else return 20;
    if (board[line+1][col-1]<=USER_SOLDIER &&
        board[line-1][col+1]!=PROHIBITED &&
        board[line-1][col+1]>=USER_SOLDIER)
                 if(board[line+1][col-1]==-1) return 10; /* soldier */
                                         else return 20;
    if (board[line+1][col+1]<=USER_SOLDIER &&
        board[line-1][col-1]!=PROHIBITED &&
        board[line-1][col-1]>=USER_SOLDIER)
                if(board[line+1][col+1]==-1) return 10;  /* soldier */
                                        else return 20;
   return (0) ; /* not defender */
}

/*******************************************************************/
/*  Examining of move quality after the move */

int post_move (char col, char line, char m_col, char m_line, char pointer[2])
{
   int v=0 ;
   char t1 = board[line][col] ; /* š‰† ††…™ Œ‰‰‡ ˜…‹† */
   char t2=100 ;
   char a, b ;

   board[line][col] = 0 ;

   t2 = board[m_line][m_col] ;  /* š‰† Œ‹€™ Œ‰‰‡ ˜…‹† */
   board[m_line][m_col] = 0 ;

   if (pointer[0]==USER_SOLDIER || pointer[0]==8)     /* ‰‰” ˜…ˆ ˜š…‰ …ˆ ‰…–‰— ˜…ˆ */
      v = v + 1 ;

   if (pointer[1]==USER_SOLDIER)                 /* š‰€ƒ‹ ,„…™€˜ „˜…™ Š…šŒ ,„˜…‡€ „Œ‰‹€ */
      v = v + 2 ;

   if (t1==-1 && pointer[1]==8)       /* ˜š…‰ ™—… ƒ’‰ €‰„ „‹Œ„ š˜…™ */
      v = v + 15 ;

   v = v - threat (pointer[1], pointer[0]) ;     /* ? š‰ƒ‚ „Œ‰‹€ š‹‘ €„ */
   v = v + protect (pointer[1], pointer[0]) ;   /* ? ˜‡€ Œ‰‰‡Œ „‚„ „……„ „†…†š„ €„ */

                     /* ƒ…—„ ƒ–Œ ‡…Œ„ š€ ˜†‡„ */
   board[m_line][m_col] = t2 ;
   board[line][col] = t1 ;

   return (v) ;
}

/*******************************************************************/
/* Evaluation of soldier's move */

int sold_test (char col, char line, char bstmv[4])
{
   char move[2] ;
   int v, bstval=-100 ;
   char a, b, c ;
   char m_col, m_line ;

   for (a=col-1 ; a<=col+1 ; a+=2)
      for (b=line-1 ; b<=line+1 ; b+=2) {
         v = -100 ;
         m_col = col ;
         m_line = line ;
         if (b<line) {

/* Eating back is possible? */

            if ((c=board[b][a])>=USER_SOLDIER && c!=PROHIBITED)
               if (board[b-1][a+a-col]==0) {
                  move[0]=a+a-col ;
                  move[1]=b-1 ;
                  if (c==USER_SOLDIER) v=20;
                       else v=40;
                  m_col = a ;
                  m_line = b ;
                  }
            }
         else
            switch (c=board[b][a]) {      /* nearest square checking */
               case 0:                    /* empty */
                  move[0]=a ;
                  move[1]=b ;
                  v = b ;
                  break;
               case USER_SOLDIER:
               case 2:
                  if (board[b+1][a+a-col]==0) {    /* eating forward */
                     move[0]=a+a-col ;
                     move[1]=b+1 ;
                     if (c==USER_SOLDIER) v=23;
                        else   v=43;
                     m_col = a ;
                     m_line = b ;
                     }
                  break ;
               default : v = -100 ;
               }

         if (v > -100) {
            v = v + threat(line,col) ;    /* plus balls if become defender */
            v = v - protect(line,col) ;   /* minus balls if defends */

                    /* after move: */
            v = v + post_move (col, line, m_col, m_line, move) ;
            }

         if (v > bstval) {    /* The best move has been saved */
            bstval = v ;
            bstmv[0] = move[0] ;
            bstmv[1] = move[1] ;
            bstmv[2] = m_col ;
            bstmv[3] = m_line ;
            }
         }

   return (bstval) ;
}

/*******************************************************************/
/* Evaluation of queen's move */

int queen_test (char col, char line, char bstmv[4])
{
   char move[2] ;
   int v, bstval=-100 ;
   char a, b, c, cut ;
   char m_col, m_line ;
   char dc, dl ;

   for (dc=-1 ; dc<=1 ; dc+=2)
      for (dl=-1 ; dl<=1 ; dl+=2)
         for (a=col+dc, b=line+dl, cut=0 ;
                 (!cut) && a>=1 && a<=8 && b>=1 && b<=8 ; a+=dc, b+=dl) {

            v = -100 ;
            m_col = col ;
            m_line = line ;
            switch (c=board[b][a]) {
               case 0:
                  move[0]=a ;
                  move[1]=b ;
                  v = 9-b ;      /* back */
                  break ;
               case USER_SOLDIER:
               case 2:   /* eating */
                  if (board[b+dl][a+dc]==0) {
                     move[0]=a+dc ;
                     move[1]=b+dl ;
                     v = (c==1) ? 23 : 43 ;
                     m_col = a ;
                     m_line = b ;
                     cut=1 ;
                     }
                  break ;
               case -1:
               case -2:
               case PROHIBITED:
                  cut = 1 ;
                  break ;
               }

            if (v > -100) {
               v = v + threat(line,col) ;
               v = v - protect(line,col) ;
               v = v + post_move (col, line, m_col, m_line, move) ;
               }

            if (v > bstval) {
               bstval = v ;
               bstmv[0] = move[0] ;
               bstmv[1] = move[1] ;
               bstmv[2] = m_col ;
               bstmv[3] = m_line ;
               }
            }

   return (bstval) ;
}

/*******************************************************************/
/* board printing procedure */

void board_draw()
{
   int i,j;
   printf("\n\xA9");
   printf (" a  b  c  d  e  f  g  h") ;
   printf(" \xAA\n");
   for (i=1 ; i<=SIZEBOARD ; i++)
     {
      if (i%2) printf ("%d   ",i);
          else printf("%d",i);
        for (j = i%2+1 ; j<=8 ;j=j+2)
            {
            switch (board[i][j])
                   {
                    case  0 : { textattr(WHITE*16);
                                cprintf("%c%c%c",32,32,32);
                                break; };
                    case -1 : { textattr(WHITE*16+RED);
                                cprintf(" %c ",30);
                                break; };
                    case -2 : { textattr(WHITE*16+RED);
                                cprintf(" %c ",234);
                                break; };
                    case  USER_SOLDIER : { textattr(WHITE*16+BLUE);
                                cprintf(" %c ",127);
                                break; };
                    case  2 : { textattr(WHITE*16+BLUE);
                                cprintf(" %c ",234);
                                break; }
                    }
             if ((i%2)&&(j==8)) printf("");
             else printf("   ");
             }
      printf ("%d\n",i);
      }
   printf("\xC0");
   printf (" a  b  c  d  e  f  g  h") ;
   printf(" \xD9\n");
}
/*******************************************************************/

void initialize(char array[SIZE][SIZE])
{
   char *pnt;
   int i,j;

/* prohibited squares: */

   for (i=1; i<=SIZEBOARD; i=i+2)
      for (j=1; j<=SIZEBOARD; j=j+2)
		 array[i][j]=PROHIBITED;
   for (i=2; i<=SIZEBOARD; i=i+2)
      for (j=2; j<=SIZEBOARD; j=j+2)
		 array[i][j]=PROHIBITED;

/* border */

   for (j=0; j<=SIZEBOARD+1; j++) {
		array[0][j]=PROHIBITED;        /* horizontal borders */
		array[9][j]=PROHIBITED;
        }
   for (i=1; i<=SIZEBOARD; i++) {
		array[i][0]=PROHIBITED;        /* vertical borders */
		array[i][9]=PROHIBITED;
        }

/* computer's soldiers: */

   for (i=1; i<=3 ;i=i+2)
      for (j=2; j<=SIZEBOARD ; j=j+2)
		 array[i][j] = -1 ;
   for (j=1; j<=SIZEBOARD; j=j+2)
		 array[2][j] = -1;

/* empty squares: */

   for (j=1; j<=SIZEBOARD; j=j+2)
		 array[4][j]=0;
   for (j=2; j<=SIZEBOARD; j=j+2)
		 array[5][j]=0;

/* player's soldiers: */

   for (i=6; i<=SIZEBOARD ;i=i+2)
      for (j=1; j<=SIZEBOARD ; j=j+2)
		 array[i][j] = 1 ;
   for (j=2; j<=SIZEBOARD; j=j+2)
		 array[7][j] = 1;
}

/*******************************************************************/

main()
{
   FILE *filep, *fp;
   char c,
        i,j,
        count1, count2;

   clrscr();
   printf("For new game - type 'n', for suspended game continuing - 'c'>");
   c=getch();
   while ((c!='n') && (c!='c') && (c!='N') && (c!='C'))
         {
         printf("\a\nFor new game - type 'n', for suspended game continuing - 'c'>");
         c=getch();
         }
   initialize(board);
   if ((c=='n') ||(c=='N'))
         filep=fopen("log.txt","w");
   else             /* c=='c' or c=='C'*/
         {
          fp=fopen("save.dat","rb");
          if(!fp) {                        /* opening error */
                puts("\n\aCan't open data file. New game is loaded");
                filep=fopen("log.txt","w");
                }
          else  {                           /* the file exists */
                fread(&board, sizeof(char), SIZEBOARD*SIZEBOARD, fp);
                fclose(fp);
                filep=fopen("log.txt","a"); /* append log to the old one */
                }
          };

   for(;;)
/* i.e. there are figures on the board and not stale-mate situation */
      {
      board_draw() ;         /* board print */
      if (move_of_pl(filep)) /* player's move. 1 if exit is inputed */
          {
           fclose(filep);
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
                fwrite(&board, sizeof(char), SIZEBOARD*SIZEBOARD, fp);
                fclose(filep);
                fclose(fp);
                return 0;
                }
          }
      if(minimax(filep))        /* computer's move */
          {
           count1=count2=0;          /* figures counter */
           for(i=1;i<=SIZEBOARD;i++)      /* figures number checking */
              for(j=1;j<=SIZEBOARD;j++)
                if (board[i][j]<=-1) count1++;
                else if (board[i][j]>=USER_SOLDIER) count2++;
           if (count1!=0 && count2!=0)
                 {
                  printf ("Stale-mate situation. Computer has been blocked.\n") ;
                  fclose(filep);
                  return 0;
                 }
           }
      count1=count2=0;          /* figures counter */
      for(i=1;i<=SIZEBOARD;i++)      /* figures number checking */
         for(j=1;j<=SIZEBOARD;j++)
            if (board[i][j]<=-1) count1++;
            else if (board[i][j]>=USER_SOLDIER) count2++;
      if (count1==0)
         {
          printf ("GAME IS OVER. YOU ARE WINNER!\n") ;
          fclose(filep);
          return 0;
         }
      else if (count2==0)
          {
           printf ("GAME IS OVER. COMPUTER IS WINNER.\n") ;
           fclose(filep);
           return 0;
          }
      } /* end of main game cycle */
}

/*******************************************************************/
int minimax(FILE *filep)
/* The best move of Computer: */

{
   char temp, c,
        mov[4],
        next_move[6],
        line,
        flag1, flag2,
        col;
   int val, nxtval ;

      for (flag1=flag2=0, nxtval=-100, line=1 ; line<=8 ; ++line)
         for (col=1 ; col<=8 ; ++col)
            if ((c=board[line][col])<=-1) {
               flag1=1;
               if (c==-1)        /* soldier */
                    val=sold_test(col,line,mov);
               else              /* queen */
                    val=queen_test(col,line,mov);
               if (nxtval<val) {
                  nxtval=val ;
                  next_move[0] = col;
                  next_move[1] = line ;
                  next_move[2] = mov[0] ;
                  next_move[3] = mov[1] ;
                  next_move[4] = mov[2] ;
                  next_move[5] = mov[3] ;
                  }
               }
            else if (c>=1)
               ++flag2 ;
      if (nxtval == -100) return 1; /* Stale-mate situation */

      if (flag1 && flag2)
      {

/* move realization: */
         temp = board[next_move[1]][next_move[0]] ;
         board[next_move[1]][next_move[0]] = 0 ;
         board[next_move[3]][next_move[2]] = temp ;

         c = board[next_move[5]][next_move[4]] ;
         board[next_move[5]][next_move[4]] = 0 ;
         if (c>=1)                      /* user's soldier eating */
            --flag2 ;
         if (next_move[3]==8)           /* computer's soldier becomes a queen */
            board[next_move[3]][next_move[2]] = -2 ;
                                        /* Printing and log making */
         printf ("Computer's move is : %c%d-%c%d\n",next_move[0]+96,next_move[1],next_move[2]+96,next_move[3]);
         fprintf (filep,"Computer's move is : %c%d-%c%d\n",next_move[0]+96,next_move[1],next_move[2]+96,next_move[3]);
      }
      return 0;
}
/*******************************************************************/
void switchb(char array[SIZE][SIZE])
{
   char temp[SIZE][SIZE],i,j;
   initialize(temp);
   for (i=1; i<=SIZEBOARD; i++)
	   for (j=1; j<=SIZEBOARD; j++)
		switch (array[i][j])
			{
			case -1: temp[SIZEBOARD+1-i][SIZEBOARD+1-j]=1;
					 break;
			case -2: temp[SIZEBOARD+1-i][SIZEBOARD+1-j]=2;
					 break;
			case USER_SOLDIER: temp[SIZEBOARD+1-i][SIZEBOARD+1-j]=-1;
					break;
			case 2: temp[SIZEBOARD+1-i][SIZEBOARD+1-j]=-2;
					break;
			default: temp[SIZEBOARD+1-i][SIZEBOARD+1-j]=array[i][j];  /* empty squares */
			}
   copy(temp,array);
}