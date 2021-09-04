/*              SOLVE.C                */
/*
This program will get from keyboard square Matrixe M of float numbers
and vector B and resolve sytem of equations M*X=B
*/
#include <math.h>
#include <stdio.h>
#include <alloc.h>
#define N 3
#define FZERO 0.00000001
void PrintSystem (double **Matrixe,double *Vector);
void PrintVector (double *V);
void InputSystem (double **Matrixe,double *Vector);
void SwapLines (double **L1,double **L2);
int SumLines (double *L1,double *V1,double *L2,double *V2,
						       double C1,double C2);
int FindColMax (double **Matrixe,int ColNo);
void TransformMatrixe(double **Matrixe,double *V);
int ExtractSolution (double **Matrixe,double *V,double *X);
void main ()
{
double *The_Matrixe[N],The_Vector[N],Solution[N];
InputSystem(The_Matrixe,The_Vector);
printf("The system of equations is:\n");
PrintSystem(The_Matrixe,The_Vector);
printf("The transformed system of equations is:\n");
TransformMatrixe(The_Matrixe,The_Vector);
PrintSystem(The_Matrixe,The_Vector);
if (ExtractSolution (The_Matrixe,The_Vector,Solution))
   {
   printf("The solution of the given system of equations is ");
   PrintVector(Solution);
   }
   else printf("There is not any solution");
}
/*-------------------------------------------------------------*/
/* function for input matrixe from keyboard
parameters Matrixe two dimensional array for input
Vector right parts of system
*/
void InputSystem (double **Matrixe,double *Vector)
{
int i,j;
printf("\nENTER INPUT MATRIXE\n");
*Matrixe=(double *) malloc(N*N*sizeof(double));
for (i=0;i<N;i++)
    for (j=0;j<N;j++)
    scanf("%lf",&Matrixe[i][j]);
printf("ENTER VECTOR\n");
for (i=0;i<N;i++) scanf("%lf",&Vector[i]);
}
/*---------------------------------------------------------------*/
void PrintVector (double *V)
/*procedure for printing vector V */
/* V - vector to be printed */
{
int i;
for (i=0;i<N;printf("%3.2lf ",V[i]),i++);
printf("\n");
}
/*---------------------------------------------------------------*/
/* function for printing given system of equation */
void PrintSystem (double **Matrixe,double *Vector)
/* Matrixe - shorten Matrixe of equation */
/* Vector  - addition to shorten matrixe */
{
int i,j;
for (i=0;i<N;i++)
    {for(j=0;j<N;j++)
     if (j==0) printf("%3.2lf*X%-i",Matrixe[i][j],j+1);
	else   printf("%+3.2lf*X%-i",Matrixe[i][j],j+1);
     printf(" = %3.2lf\n",Vector[i]);
    }
}
/*------------------------------------------------------------*/
/* Function for swaping lines of the Matrixe */
void SwapLines (double **L1,double **L2)
/*L1,L2 lines to be swaped */
{
double *TEMP;
TEMP=*L1;
*L1=*L2 ;
*L2=TEMP;
}
/*------------------------------------------------------------*/
/* Function for calculating sum of two lines of Matrixe*/
/* L2=L1*C1+L2*C2 */
int SumLines (double *L1,double *V1,double *L2,double *V2,
						       double C1,double C2)
/*
L1,V1 - first line;L2,V2 - Second line
C1,C2 coeficients for calculating sum
*/
{
int i;
if ((C1==0)||(C2==0)) return 0;
*V2=*V1*C1+*V2*C2;
for (i=0;i<N;i++)
    L2[i]=L1[i]*C1+L2[i]*C2;
return 1;
}
/*---------------------------------------------------------------------*/
/*function searching for min in given column  */
int FindColMin (double **Matrixe,int ColNo)
/*
Matrixe - given matrixe
ColNo   - Column for search
*/
{
int i,i_Min=ColNo;
for(i=i_Min+1;i<N;i++)
i_Min=fabs(Matrixe[i_Min][ColNo])<=fabs(Matrixe[i][ColNo])?i_Min:i;
return i_Min;
}
/*------------------------------------------------------------------*/
/*function for tansform DATA matrixe to triangle form */
void TransformMatrixe(double **Matrixe,double *V)
/*
Matrixe,V full matrixe of given system of equations
*/
{
int i,j,I;
double TEMP;
for (i=0;i<N;i++)
 {
  I=FindColMin(Matrixe,i);
  if (i!=I) { /* swap lines to avoid round mistakes  */
	    SwapLines (&Matrixe[i],&Matrixe[I]);
	    TEMP=V[I];
	    V[I]=V[i];
	    V[i]=TEMP;
	    }
  for (j=i+1;j<N;j++)
      SumLines(Matrixe[i],&V[i],Matrixe[j],&V[j],-1,
						 Matrixe[i][i]/Matrixe[j][i]);
 }
}
/*-----------------------------------------------------------*/
int ExtractSolution (double **Matrixe,double *V,double *X)
/*
Matrixe - transformed system of equations
V free coefficents in the given system
X solution
*/
{
int i,j;
for (i=N-1;i>=0;i--)
	{
	X[i]=V[i];
	for (j=i+1;j<N;X[i]-=Matrixe[i][j]*X[j],j++);
	if (fabs(Matrixe[i][i])<=FZERO)
	   if (fabs(X[i])>FZERO) return 0; /* there is no solution */
	      else X[i]=0; /* there are many solutions but we use only one*/
	   else X[i]/=Matrixe[i][i]; /*only solution */
	}
return 1;
}