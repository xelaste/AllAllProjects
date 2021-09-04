/*-----------------------------------------------------------------------
MyCron.c the programs runs background and 
examines file /usr/lib/mycrontab for work to do.
If there is , the work is done.
Record structure of entry of /usr/lib/mycrontab contain 6 fields -
Minutes, Hours, Day in Month, Month, Day in week, Command, Remarks
------------------------------------------------------------------------*/
#include <time.h>
#include <stdio.h>
#define INPUTFILE "/usr/lib/mycrontab"
#define CmdLen 180
#define BufLen 20
#define DELIMITER ' '
#define WILD      "*"
void dowork(char *Work);
void readfile(int tm_min,int tm_hour,int tm_mday,int tm_mon,int tm_wday);
void main(void)
{
int i=0,sec,done=0;
time_t t; /* binary time  */
struct tm *T;/* broke down time seconds:minutes:hours:...*/
t=time(&t);
T=gmtime(&t);
sec=T->tm_sec;
while(1==1)
  {
  t=time(&t);
  T=gmtime(&t);
  if (!(T->tm_sec-sec)&&T->tm_min!=done)
     {
     i++;
     done=T->tm_min;
     printf("Minute No %d\n",i);
     readfile(T->tm_min,T->tm_hour,T->tm_mday,T->tm_mon,T->tm_wday);
     }
  }
}























/* MYCRON.C page 2 */
/*-------------------------------------------------------------*/
/* do the work from input file                                 */
/*-------------------------------------------------------------*/
void dowork(char *work)
{
int i=0,j=0,k,pid,status;
char *cmd[BufLen],buffer[CmdLen];
while (j<strlen(work)) /* parse command */ 
  {
  memset(buffer,'\0',CmdLen);
  for(k=0;k<BufLen&&j<strlen(work)&&work[j]!=DELIMITER;k++,j++)
      buffer[k]=work[j];
  cmd[i]=(char *)malloc(strlen(buffer)+1);
  strcpy(cmd[i],buffer);
  i++;
  j++;
  }
cmd[i]=0;
pid=fork();
if (pid==0)
   {
    /* its the child process */          
    execvp(cmd[0],cmd);
    printf("\nError in exec the %s of master program\n",work);
    exit(1);
    }     
  else
    {
     if (pid==-1)
        {
         printf("\nFailed to fork");
         exit(1);
         }
         else
        /*it's parent process so wait for child process to  finish*/
	      wait(&status);
     }
}






















/* MYCRON.C page 3 */
/*---------------------------------------------------------------------*/
/* read input file check time and call dowork if there is work to do   */
/* parameters   tm_min  current minute                                 */
/*              tm_hour current hour                                   */
/*              tm_mday day of month                                   */
/*              tm_mon  month                                          */    
/*              tm_wday day of week                                    */ 
/*---------------------------------------------------------------------*/
void readfile(int tm_min,int tm_hour,int tm_mday,int tm_mon,int tm_wday)
{
FILE *fp;
int i;
char work[CmdLen],Line[CmdLen],
     sMin[3],sHour[3],sDoM[3],sMon[3],sDoW[3]; 
if ((fp = fopen(INPUTFILE,"r")) == NULL)
     {
     printf("Error opening input file %s\n",INPUTFILE); 
     exit(2);
     } 
 while(!(feof(fp)))
  {
  memset(Line,'\0',CmdLen);
  memset(work,'\0',CmdLen);
  memset(sMin,'\0',3);
  memset(sHour,'\0',3);
  memset(sDoM,'\0',3);
  memset(sMon,'\0',3);
  memset(sDoW,'\0',3);
  for(i=0;(Line[i]=fgetc(fp))!='\n'&&Line[i]!=EOF;i++);/*read command line*/
  Line[i]='\0';
  sscanf(Line,"%s%s%s%s%s%s",sMin,sHour,sDoM,sMon,sDoW,work);/* parse it */
      if( (!(strcmp(sMin,WILD))||(atoi(sMin)==tm_min))&&
          (!(strcmp(sHour,WILD))||(atoi(sHour)==tm_hour))&&
          (!(strcmp(sDoM,WILD))||(atoi(sDoM)==tm_mday))&&
          (!(strcmp(sMon,WILD))||(atoi(sMon)==tm_mon))&&
          (!(strcmp(sDoW,WILD))||(atoi(sDoW)==tm_wday)))
          {
          printf("%s\n",work);
          dowork(work);
          }
     }
 fclose(fp);
}
/*---------------------------------------------------------------------*/
