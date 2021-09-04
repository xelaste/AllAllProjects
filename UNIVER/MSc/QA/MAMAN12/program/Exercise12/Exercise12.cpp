#include <stdio.h>
#include <time.h>

int const max_words_in_input_line = 40 ;
int const max_word_length = 80 ;

char table [max_words_in_input_line][max_word_length];
char buffer [max_word_length];

int row =0 ;   /* current row to be filled in the table */

int i,j ;    /* counters */

char c;   /* current character read from the input */

char const blank = ' ';
//char buffer[2000]; 
void main()
{
   
  time_t seconds;
  seconds = time ( 0 );
  printf ("%lu000 ms since January 1, 1970",seconds  );
  
  
	do
      {
       /*  Skipping blanks  */ 
       do 
             c = getchar() ;
       while ( c == blank ) ; 

       if ( c != '\n')
          {
            /* And now read the next word and put it into the table :  */
            j = 0;
            while ( (c != blank)  &&  (c != '\n') )
                  {
                   
                   table[row][j] = c ;
				   c = getchar() ;
                   j++ ;
                  }
            table[row][j] = '\0' ;
            row++ ;
          }
     }
   while ( c != '\n') ;
  
  /* all other rows in the table remain empty :  */ 
  for (i = row; i < max_words_in_input_line; i++)
        table[i][0] = '\0';

  
 
  printf ("Total number of non-empty words in the input line:  %d\n" , row );

  for (i = 0; i < max_words_in_input_line; i++)
       {
       if ( table[i][0] == '\0' )                    /* the word in this row is empty */
            {
			//printf("Empty word \n");
             continue;
             }

       /* for non-empty-word: copy it into the buffer, and then print */
       for (j = 0; j <= max_word_length; j++)            
          {
           buffer[j] = table[i][j];
           if (table[i][j] == '\0' )
               break ;
           }

        printf ("%s\n", buffer);
        }

    printf(" DONE !!! \n"); 
} /* end of main */
