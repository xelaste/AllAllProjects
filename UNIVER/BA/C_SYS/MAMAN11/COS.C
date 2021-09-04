/*
The program accepting float number from keyboard and
calling to the function mycos for calculating cos of input number
*/
#include <math.h>
#include <stdio.h>
#define DELTA 1.0e-6
/*------------------------------------------------------------*/
double factorial (int Num) /*function for calculating factorial of Num*/
{
double F=1;
if (Num>=1) for (;Num>=1;F*=Num--);
return F;
}
/*-------------------------------------------------------------*/
double mycos (double x) /*function returns cos (x)*/
/* cos (x) is sum of -1^i*x^2i/i! where 0<=i<= infinity */
{
int i=0;
double SUM=0,MEMBER;
while ((MEMBER=pow(x,2*i)/factorial(2*i))>=DELTA) /*member=-1^i*x^2i/i!*/
 {
 SUM+=pow(-1,i)*MEMBER;
 i++;
 }
return SUM;
}
/*---------------------------------------------------------------------*/
void main ()
{
double x;
printf("\nInput argument value X = ");
scanf("%lf",&x);
printf("COS (%1.7f) = %1.8f",x,mycos(x));
}
