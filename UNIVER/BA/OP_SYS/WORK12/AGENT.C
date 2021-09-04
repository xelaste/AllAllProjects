/* ________________________________________________________________________

    MODULE  AGENT.C
      of the program AGENTS.C.    Second module of 2.

      Related Files:       agent.h      -  Global Constants.
                           father.c     -  module 1.
                           agents.doc   -  Doc file.

      Description:         Here are all the function needed to
                           perform the work of the agents.




__________________________________________________________________________ */

#include <stdio.h>
#include <memory.h>
#include <time.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "agent.h"

static int Fsem=0;


cloipc ()/* remove semaphore ids and structures */
{
semctl(Fsem,0,IPC_RMID,0);
}

/* Routine  : To perform "semop" on a semaphore. If val is 1
   increment semval by 1; if val is -1 suspend process until
   semval is 1 and then decrement it by absolete value of val */
int csemop(int semid,int val)
{
struct sembuf sval;
sval.sem_num=0;
sval.sem_op=val;
sval.sem_flg=0;
if(semop(semid,&sval,1)==ERROR) return 0;
return 1;
}
/* Routine to do up (V) operation;unlock (release semaphore) */
int up (int semid)
{
 return csemop(semid,1);
}

/* Routine to do down (P) operation;lock (get semaphore) */
int down (int semid)
{
 return csemop(semid,-1);
}

int allipc() /* Routine for create a semaphor */
{
int pid=getpid();
if ((Fsem=semget( (key_t) pid,1,IPC_CREAT | 
                                IPC_EXCL | 0664))==ERROR) return 0;
return up(Fsem);
}

int go_agent( agent_name )      /* sends agent to work */
char *agent_name;
{
   int n,
       i,
       amount,
       pid,
       retry=0;
   while ( ( pid = fork() ) == ERROR && ++retry < RETRY )
            sleep(SLEEP);
   if ( pid == 0 )
   {
      for( i = 0; i < OPERATIONS ; ++i )
     {
         amount = gen_rand( MAX_OPER );
         if(!down(Fsem))/* close semapfor to file */
             fatal_error("Semafor","C'ant perform semaphore operation");
         if ( update( amount,ACCOUNT ) == ERROR )
                 fatal_error( ACCOUNT,"C'ant Update Account File");
         if (!up(Fsem))/*open semaphor to file */
             fatal_error("Semafor","C'ant perform semaphore operation");
          
         if ( log( amount,agent_name ) == ERROR )
                    fatal_error( agent_name,"C'ant log operations");
         if ( ( n = rand() % MAX_SLEEP ) != 0 )
                   sleep( n );
      }
      printf("Agent %s : Succefull!\n",agent_name );
      exit( 0 );  /* Son normally exits here! */
   }
   return( pid );
}


/* Agent.c - Page 2 */

int gen_rand( range )  /* Generates random numbers between -rang and +range */
int range;         /* exept 0, if range = 0 - init generation */
{
   int n,sign;
   static int init=0;

    if ( init++ == 0 )
      srand( time( NULL ) % getpid() );
  
   while( ( n = rand() ) == 0 );
   sign = (n/1111) % 2;
   n = ( (n/1117) % range ) + 1;

   if ( sign == 0 )
      return( n );
   else return( 0 - n );
}


int update( amount,account )  /* Updates account using amount. Returns new sum */
int amount;
char *account;            /* File name */
{
   FILE  *fp;
   int n;
  
   char buf[ BUFFER ];

   memset (buf, '\0',  BUFFER);

   if ( !(fp = fopen( account , "r"))) 
      return( ERROR );

   fscanf (fp, "%s", buf);
   fclose( fp );

   if ( amount != 0 )  printf(".");

   if (!( fp = fopen( account,"w" ))) 
      return( ERROR );

   fprintf( fp,"%d", n = atoi(buf) + amount );
   fclose( fp );

   return( n + amount );                   /* New sum in account */
}


int log( amount,log_file )               /* Appends amount to log_file */
int amount;
char *log_file;
{
   FILE *fp;

   if ((fp = fopen( log_file,"a")) == NULL ) 
                                  return( ERROR );
   fprintf( fp,"%d\n",amount );
   fclose( fp );
   return( SUCCESS );
}


