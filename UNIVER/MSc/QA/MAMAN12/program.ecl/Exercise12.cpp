#include <stdio.h>

int const max_words_in_input_line = 40 ;
int const max_word_length = 80 ;


char table [max_words_in_input_line][max_word_length];
char buffer [max_word_length];


int row =0 ;   /* current row to be filled in the table */

int i,j ;    /* counters */

char c;   /* current character read from the input */

char const blank = ' ' ;
char buf[2000];
int pos = sprintf (buf,"%d ",1);
int main()
{
   do
      {
       pos += sprintf (buf + pos ,"%d ",2);
       /*  Skipping blanks  */ 
       do {
             pos += sprintf (buf + pos ,"%d ",3); 
             c = getchar() ;
             pos += sprintf (buf + pos ,"%d ",4);
             pos += sprintf (buf + pos ,"%d ",5);
       }      
       while ( c == blank ) ; 
       pos += sprintf (buf + pos ,"%d ",6);
       if ( c != '\n')
          {
            /* And now read the next word and put it into the table :  */
            j = 0;
            pos += sprintf (buf + pos ,"%d ",7);
            while ( (c != blank)  &&  (c != '\n') )
                  {
                   pos += sprintf (buf + pos ,"%d ",8);
                   table[row][j] = c ;
				   c = getchar() ;
                   j++ ;
                   pos += sprintf (buf + pos ,"%d ",9);
                  }
            table[row][j] = '\0' ;
            row++ ;
            pos += sprintf (buf + pos ,"%d ",10);
          }
       pos += sprintf (buf + pos ,"%d ",11);
     }
   while ( c != '\n') ;
    pos += sprintf (buf + pos ,"%d ",12);  
  /* all other rows in the table remain empty :  */ 
  for (i = row,pos += sprintf (buf + pos ,"%d ",13 ); i < max_words_in_input_line; pos += sprintf (buf + pos ,"%d ",14), i++) 
  {
        table[i][0] = '\0';
  }      
  printf ("Total number of non-empty words in the input line:  %d\n" , row );
  pos += sprintf (buf + pos ,"%d ",15);
 
  for (i = 0, pos += sprintf (buf + pos ,"%d ",16); i < max_words_in_input_line; pos += sprintf (buf + pos ,"%d ",16), i++)
       {
       pos += sprintf (buf + pos ,"%d ",17);
       if ( table[i][0] == '\0' )                    /* the word in this row is empty */
            {
			//printf("Empty word \n");
            pos += sprintf (buf + pos ,"%d ",18);
            continue;
             }

       /* for non-empty-word: copy it into the buffer, and then print */
       for (j = 0, pos += sprintf (buf + pos ,"%d ",19); j <= max_word_length; pos += sprintf (buf + pos ,"%d ",19),j++)            
       {
           buffer[j] = table[i][j];
           pos += sprintf (buf + pos ,"%d ",20);
           pos += sprintf (buf + pos ,"%d ",21);
           if (table[i][j] == '\0' ) {
               pos += sprintf (buf + pos ,"%d ",22);
               break ;
           }  
           pos += sprintf (buf + pos ,"%d ",23);
       }
        pos += sprintf (buf + pos ,"%d ",24);         
        printf ("%s\n", buffer);
        pos += sprintf (buf + pos ,"%d ",25);         
        }
     pos += sprintf (buf + pos ,"%d ",26);          
    printf(" DONE !!! \n"); 
    printf(buf);
   return 0;
  } /* end of main */
