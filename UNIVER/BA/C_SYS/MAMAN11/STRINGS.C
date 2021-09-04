/*
The program input string substring character and integer and
checking function for string manipulating
*/
#include <stdio.h>
#include <conio.h>
#define FALSE 0
#define TRUE  1
/*function suffixes looking for all apearnces of c in str and
printing  suffixes of str those begining from c
*/
int suffixes (char str[],char c);
/*printing string from given position */
void print_from_position(char str[],int pos);
int LENTH_OF_STRING(char str[]);/* return lenth of string */
int strrevstr(char s1[],char s2[]);
/* rotates given string by i position , forward if i>0 and back if i<0*/
void rotate_string(char str[],int i);
void main ()
{
char str1[21],str2[11],ch[1];
int Num=0;
printf("\nInput the first string: ");
scanf ("%20s",str1);
printf("Input the second string: ");
scanf ("%10s",str2);
printf("Input the character: ");
scanf ("%1s",ch);
printf("Input the integer: ");
scanf("%d",&Num);
/*--------------------------------------*/
printf("\n %d",suffixes(str1,ch[0]));
/*--------------------------------------*/
if (strrevstr(str1,str2)) printf("\n %s","TRUE");
    else printf("\n %s","FALSE");
/*--------------------------------------*/
rotate_string(str1,Num);
printf("\n%s",str1);
/*--------------------------------------*/
}
/*-------------------------------------------------*/
void print_from_position(char str[],int pos)
{
int i;
for (i=pos;str[i]!=0;putch(str[i++]));
}
int suffixes (char str[],char c)
{
int N=0,i;
for (i=0;str[i]!=0;i++)
    {if (str[i]==c)
	{printf("\n");
	print_from_position(str,i);
	N++;
	}
    }
return N;
}
/*--------------------------------------------------*/
void rotate_string(char str[],int i)
{
char ch1,ch2;
int j,DELTA;
if (i>0) DELTA=-1; else DELTA=1;
for (;i>0;i+=DELTA)
    {
    ch1=str[0];
    for (j=0;str[j+1]!=0;j++)
	 {
	 ch2=str[j+1];
	 str[j+1]=ch1;
	 ch1=ch2;
	 }
    str[0]=ch1;
    }
}
/*-----------------------------------------------------------*/
int LENTH_OF_STRING(char str[])
{
int L=0;
for (L=0;str[L]!='\0';L++);
return L;
}
/*------------------------------------------------------------*/
int strrevstr(char s1[],char s2[])
{
int i,j,l;
l=LENTH_OF_STRING(s2)-1;
for(i=0;s1[i]!='\0';i++)
   {if (s1[i]==s2[l])
       {
       for (j=0;(l-j>=0)&&(s1[i+j]==s2[l-j]);j++);
       if (j>l) return TRUE;
       }
   }
return FALSE;
}