/*-----------------------------------------------------------------*/
/*                              POLINOM.C                          */
/*-----------------------------------------------------------------*/
#include "polinom.h"
#include <stdio.h>
#include <math.h>
#define PRECISION 20 /* length of number */
#define DELIMITER  ','
#define VALUE(x)  ((x)-'A')
#define IMAGE(x)  ((x)+'A')
#define FZERO 0.00000001
POLINOM THE_POLINOM [F-A+1];
void show (POLINOM P);
/*-------------------------------------------------------*/
void putzero(POLINOM P)
/* Function for start polinom P */
{
int i;
for (i=0;i<=MAX_DEGREE;P[i]=0,i++);
}
/*--------------------------------------------------------*/
void init_polinoms (void)
/*start all polinoms */
{
int  i;
for (i=A;i<=F;putzero(THE_POLINOM[i]),i++);
}
/*-------------------------------------------------------------------*/
int LEN (char *L)
/* Function for calculate length of string L */
/* return integer - lentgh of string         */
{
int i;
for (i=0;L[i];i++);
return i;
}
/*-------------------------------------------------------------------*/
void LEFT (char *str,int s)
/*Function for shift string str toward left by s characters */
/*str stirng                                                */
/*s - lenth of shifting                                     */
{
int i,L;
L=LEN(str);
for (i=0;i<L;i++)
if (i+s<L) str[i]=str[i+s];
   else      str[i]=0;
}
/*--------------------------------------------------------------*/
int Polinom_Exists (INDEX I)
/* function for checking if polinom I exists  */
/* if it is return 1 else return 0            */
{
if (I>=A&&I<=F) return 1;
   else
   {
    if (IMAGE(I)&&IMAGE(I)!=' ')
       printf("The polinom %c does not exist\n",IMAGE(I));
    return 0;
   }
}
/*-------------------------------------------------------------------*/
int Call_Operand(char P,char Q,char R,
	 int (*operand)(POLINOM P,POLINOM Q,POLINOM R))
/* Function for standard operators call                */
/* P,Q left and right parts,R result                   */
/* if opeation did not complete return 0 else return 1 */
{
POLINOM TEMP;
putzero(TEMP);
if (!(P)||!(Q))
   {
   printf("Input at least two polinom names !!!\n");
   return 0;
   }
if (Polinom_Exists(VALUE(P)))
  if (Polinom_Exists(VALUE(Q)))
    if (Polinom_Exists(VALUE(R)))
       return (*operand)(THE_POLINOM[VALUE(P)],THE_POLINOM[VALUE(Q)],
					       THE_POLINOM[VALUE(R)]);
    else if (R==' ')
	 {
	 if((*operand)(THE_POLINOM[VALUE(P)],THE_POLINOM[VALUE(Q)],TEMP))
	   printf("P(x)=");
	   show(TEMP);/*if R not inputed show result*/
	 }
	 else if(R==0)
	      (*operand)(THE_POLINOM[VALUE(P)],THE_POLINOM[VALUE(Q)],NULL);
return 1;
}
/*--------------------------------------------------------*/
int add_pol (POLINOM P,POLINOM Q,POLINOM R)
/*add polinom P to polinom Q , store result in R*/
{
int i;
for(i=0;i<=MAX_DEGREE;R[i]=P[i]+Q[i],i++);
return 1;
}
/*--------------------------------------------------------*/
int mul_pol (POLINOM P,POLINOM Q,POLINOM R)
/*multiply polinom P to polinom Q , store result in R*/
{
int i,j;
putzero(R);
for (i=0;i<=MAX_DEGREE;i++)
  {
   for(j=0;j<=MAX_DEGREE;j++)
   {
   if ((i+j>MAX_DEGREE)&&(abs(P[i]*Q[j])>FZERO))
      {
      printf("Result order %d greater than Max order %d\n",i+j,MAX_DEGREE);
      return 0;
      }
   if (i+j<=MAX_DEGREE) R[i+j]+=P[i]*Q[j];
   }
  }
return 1;
}
/*-------------------------------------------------------*/
int sub_pol (POLINOM P,POLINOM Q,POLINOM R)
/*subtract polinom P from polinom Q , store result in R*/
{
int i;
for(i=0;i<=MAX_DEGREE;R[i]=P[i]-Q[i],i++);
return 1;
}
/*-------------------------------------------------------*/
int diff_pol(POLINOM P,POLINOM R,POLINOM DUMMY)
/*find differential of P and store result in Q*/
{
int i;
putzero(R);
if (DUMMY==NULL)
   {
   for (i=0;i<MAX_DEGREE;R[i]=(i+1)*(P[i+1]),i++);
   return 1;
   }
   else return 0;
}
/*------------------------------------------------------------*/
void  print_pol (char Name)
/* print polinom Name - decode Name and call to function */
/* show                                                  */
{
if (Polinom_Exists(VALUE(Name)))
   {
   printf("%c(x)=",Name);
   show(THE_POLINOM[VALUE(Name)]);
   }
if (!(Name)||Name==' ')
   printf("Input name of polinom for print\n");
}
/*------------------------------------------------------------------*/
int read_pol  (char *Buffer,char Name)
/* read polinom Name from string Buffer    */
{
int i=0;
INDEX I;
char Number[PRECISION];
if (!(Name)||Name==' ')
   {
   printf("Input name of input polinom \n");
   return 0;
   }
I=VALUE(Name);
if (!Polinom_Exists(I)) return 0;
for (i=0;Buffer[i];Buffer[i]=(Buffer[i]==DELIMITER?' ':Buffer[i]),i++);
i=0;
putzero(THE_POLINOM[I]);
while (LEN(Buffer)>0 && i>=0)
      {
      sscanf(Buffer,"%s",Number);
      LEFT(Buffer,LEN(Number)+1);
      sscanf(Number,"%d",&i);
      if(i>MAX_DEGREE)
	{
	printf("The item order %d bigger than max order %d\n",i,MAX_DEGREE);
	return 0;
	}
      if(i>=0)
	{
	sscanf(Buffer,"%s",Number);
	LEFT(Buffer,LEN(Number)+1);
	sscanf(Number,"%lf",&THE_POLINOM[I][i]);
	}
      }
return 1;
}
/*----------------------------------------------------------------*/
void show (POLINOM P)
/*show polinom P onto standard output */
{
int i,Items_count=0;
   for (i=MAX_DEGREE;i>=0;i--)
    {
    if (P[i])
       {
       if (Items_count==0)
	  if (P[i]<0) printf("-");
	     else;
	  else if (P[i]<0) printf("-");
		  else  printf("+");
       if (i==0||fabs(P[i])!=1) printf("%3.2lf",fabs(P[i]));
       if (i>=1)
	  {
	  if (fabs(P[i])!=1) printf("*");
	  if (i==1) printf("X");
	     else printf("X^%-d",i);
	  }
       Items_count++;
       }
    }
    if (Items_count==0) printf("0.0");
    printf("\n");
}
/*-----------------------------------------------------------------*/
