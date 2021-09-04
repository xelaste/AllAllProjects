/*-----------------------------------------------------------------------
             C O M P I L E R  O F  T I N Y   L A N G U A G E
developed by Stekolchik Alexander 1998.
Module file TQC.C  main function
       related files: 
       COMMON.H    common header file
       SCANNER.H  lexical analizer definitions and constants
       TLA.C      lexical analizer functions
       GSTACK.H  stack definitions and declarations
       GSTACK.C  common stack operation function
       HASH.H   hashtable header file
       HASH.C   hashtable functions
       STKENTRY H  parser stack definitions and declarations
       STKENTRY.C  parser stack function
       PARSER.H   parser header file
       PARS_TAB.C  definitions of LALR actions table and goto table
       PARSER.C    parser operation function
       SEMANTIC.H semantic actions constants
       SEMANTIC.C semantic action functions
---------------------------------------------------------------------------*/

#include <string.h>
#include <stdio.h>
#include <process.h>
#include "common.h"
FILE *fp,*lf,*qf;
char msg[MsgLn]={""};
char quadfile[FILE_NAME_LENTH];
extern void parser(void);
/*-----------------------------------------------------*/
void main (int argc,char **argv)
/*The main function of the program                     */
/* gets name of input file,checks it generates names of*/
/* list file and quad files                            */
/*-----------------------------------------------------*/
{
char extention[5],list[FILE_NAME_LENTH];
int i,l;
fprintf(stderr,"%s\n",CopyRight);
if (argc!=2) {fprintf(stderr,"Usage tla file_name\n"); exit(1);}
for(i=0;i<4;i++)
    extention[i]=argv[1][strlen(argv[1])-4+i];
    extention[4]='\0';
if(strcmp(INPUT_EXTENTION,strlwr(extention)))
  {
  fprintf(stderr,"\nExtention of the source file should be tin\n");
  exit(2);
  }
if((fp=fopen(argv[1],"rt"))==NULL)
  {
  fprintf(stderr,"Source file %s not found\n",argv[1]);
  exit(3);
  }
  fprintf(stderr,"\n%s\n",CopyRight);
  fprintf(stderr,"Process file  %s\n",argv[1]);

  strcpy(list,argv[1]);
  l=strlen(list);for(i=0;i<3;list[l-i-1]=0,i++);
  strcat(list,LIST_EXTENTION);

  strcpy(quadfile,argv[1]);
  l=strlen(quadfile);for(i=0;i<3;quadfile[l-i-1]=0,i++);
  strcat(quadfile,QUAD_EXTENTION);
  unlink(quadfile);
if((lf=fopen(list,"wt"))==NULL)
  {
  fprintf(stderr,"Error open list file %s \n",list);
  exit(3);
  }


  fprintf(lf,"%s\n",CopyRight);
  fprintf(lf,"Process file  %s\n",argv[1]);
  parser();
  fclose(fp);
  fclose(lf);
}
/*-------------------------------------------------------*/
