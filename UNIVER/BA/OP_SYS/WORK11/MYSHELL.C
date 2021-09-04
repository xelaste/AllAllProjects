#define halt "quit"
#define CmdLen 80
#define BufLen 20
#define DELIMITER ' '
void main()
 { 
  char instr[CmdLen], *cmd[BufLen],buffer[BufLen];
  int i=0,j,k,l,pid,status;
  printf("\n");
  do 
  {
  printf("%d ? ",++i);
  for (j=0;j<CmdLen;instr[j]=0,j++);
/* Accept command line */
  for (j=0;(j<CmdLen-1)&&((instr[j]=getchar())!='\n');j++);
  instr[j]=0;
  if(strcmp(instr,halt))
    {
     j=0;
     l=0;
  /* now store all arguments passed to the program */  
  while (j<strlen(instr))
       {
       for (k=0;k<BufLen;buffer[k]=0,k++);
       for (k=0;k<BufLen&&j<strlen(instr)&&instr[j]!=DELIMITER;k++,j++)
	buffer[k]=instr[j];
        cmd[l]=(char*)malloc(strlen(buffer)+1);
        strcpy(cmd[l],buffer);
        l++;
        j++;
        }
     cmd[l]=0;      
     pid=fork();
     if(pid==0)
      {
       /* its the child process */          
       execvp(cmd[0],cmd);
       printf("\nError in exec the %s of master program\n",cmd[0]);
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
  }
  while (strcmp(instr,halt));
 }
