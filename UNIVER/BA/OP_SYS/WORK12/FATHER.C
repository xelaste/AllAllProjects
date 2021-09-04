/* ____________________________________________________________________

    MODULE  FATHER.C
      of the program AGENTS.C.   part 2 of 3 Files:

      Related Files:           1. agent.h   -  Global Constants.
                               2. father.c  -  main program.
                               3. agent.c   -  Agent actions.
                               4. agent.doc -  Doc file.

 Description:         Here are all the function needed to
                      initiate the work of the agents.


 External functions:    int go_agent( int p )  - Dispatch Agent p.
                        int update( int sum,char *ACCOUNT )
                                               - updates account.
                         Located in agent.c

 Documentation file:    Agent.doc

_______________________________________________________________________ */

#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>

#include "agent.h"

/* prototypes : */

int init ();
void fatal_error ();
int check_point();
int sum_up ();
extern int go_agent ();
extern int allipc ();
extern cloipc ();

/* Global Array - All Agents' names */
char agents[ MAX_AGENTS ][ NAMES_LEN ] = AGENTS;


main( ac,av )/* Reset all files,Dispatch all agents and control actions */
int ac;
char **av;
{
   int i,
       status,
       p,

       num_agents = 1;    /* default */

   int process[MAX_AGENTS];

   if ( ac == 2 )                            /* Check arguments */
            i = atoi( av[1] );
   else
        if (ac != 1) {
            fprintf (stderr, "USAGE: <name_of_the_program> [number_of_agents]\n");
            exit (1);
        }

   if (( num_agents = init( i ) ) == ERROR )
              fatal_error( "Can't Initiate Account file",ACCOUNT );

  /* Father distributes work to Sons... */

   for( i=0, p=0 ; i < num_agents; i++, p++ )
        if (( process[p] = go_agent( agents[p] )) == ERROR)
            {
               fprintf( stderr,"Agent %s Can't work\n",agents[p] );
               perror("While Fork ");
               --p;
            }
   i = p;

   while ( p >= 0 )  /* ...And waits for their succesfull return  */
   {
      wait( &status );
      if ( status != SUCCESS )
      {
          while ( p >= 0 )
            kill( process[ p-- ],SIGINT );
            cloipc();
            exit(1);
      }
      p--;
   }
   cloipc();
   if ( check_point( i ) == ERROR )
                fatal_error("Can't control Account",ACCOUNT );
}

int init( num_agents )   /* Initiate auxiliary files,returns number agents */
int num_agents;
{
   FILE *fp;
   int i;



   if ( num_agents < 1 || num_agents > MAX_AGENTS )
            num_agents = 1;
   printf("%d Agent(s). [Minimum 1, Maximum %d]\n",num_agents,MAX_AGENTS);

   for ( i = 0; i < num_agents; unlink( agents[ i++ ] ) );

   if (( fp = fopen( ACCOUNT,"w")) == NULL )
                                  return( ERROR );
   fprintf( fp,"%d\n",START_SUM );
   fclose( fp );

   if(!allipc()) return ERROR; /*create semaphore */
   return( num_agents );
}

/* Father.c - Page 3 */

int check_point( num_agents ) /* Are agents' actions consistent with account? */
int num_agents;
{
   int i, control_sum = 0, sum = START_SUM;
 
   printf("\n\n ----- Controler ----- \n");

   
   for ( i = 0; i < num_agents; ++i )
           control_sum = control_sum + sum_up( agents[i] );
  
   control_sum = sum + control_sum;
  
   if (( sum = update( 0,ACCOUNT )) == ERROR )
                                      return( ERROR );
   if  ( sum != control_sum )
   {
      fprintf( stderr,"\n Thieves in the system!\n");
      fprintf( stderr,"Controler: %d, Account: %d \n",control_sum,sum );
      exit(1);
   }
   printf("\nOperations O.K. Acount: %d\n", sum );
}



int sum_up( log_file )    /* Returns the sum of log_file */
char *log_file;
{
   FILE  *fp;
   int sum = 0,tmp_sum;

   if ( ( fp = fopen( log_file ,"r+") ) == NULL )
   {
      perror( log_file );
      printf("\nCan't Control %s agent!\n",log_file );
      return( 0 );
   }
   while ( fscanf( fp,"%d",&tmp_sum ) > 0 )
                            sum = sum + tmp_sum;
   fclose( fp );
  
   printf(" Sum of %s = %d\n",log_file,sum );
   return( sum );
}


void fatal_error( s1,s2)    /* Prints Error messages and exit(ERROR) */
char *s1,*s2;
{
   if ( s2 != NULL )
                fprintf( stderr,"%s",s2 );
   fprintf(stderr,"\nERROR! ");
   cloipc();
   perror( s1 );
   exit(1);
}

