#include <stdlib.h>
#include <iostream.h>
#include <iomanip.h>
#define N 4
int M [N][N]; 
int L [N*N];
int EXIST_ITEM (int *ARRAY,int ITEM)
{
int i=0;
while ((i<N*N)&&(ITEM!=ARRAY[i])&&(ARRAY[i]>0)){i++;}
return ARRAY[i];
}
void PRINT_ARRAY(int *L)
{
int MAGIC=0;
int j=0,i=0,SL[N],SC[N],SD1=0,SD2=0;
for (i=0;i<N;i++)
	 for (j=0;j<N;j++)
	 M[i][j]=L[N*i+j];
for (i=0;i<N;i++)
	 {
	 SD1+=M[i][i];
	 SD2+=M[N-i][i];
	 SC[i]=(SL[i]=0);
	 for (j=0;j<N;SL[i]+=M[i][j],SC[i]+=M[j][i],j++);
	 }
MAGIC=(SD1==SD2);//check diagonals
if (MAGIC)
	{MAGIC=0;
	 i=0;
	 while (!MAGIC) MAGIC=(SD1==SL[i++]);
	}
//check lines
if (MAGIC)
	{MAGIC=0;
	 i=0;
	 while (!MAGIC) MAGIC=(SD1==SC[i++]);
	}
//check column
if (MAGIC)
	{
	for (i=0;i<N;i++)
		 {
		  cout<<'\n';
		  for(j=0;j<N;cout<<setw(3)<<M[i][j],j++);
		 }
   exit;
	}
}
void FILL_ARRAY (int *ARRAY,int k)
{
int i;
cout<<k;
if (k==N*N)
	 PRINT_ARRAY(ARRAY);
	 else
	 for (i=1;i<=N*N;i++)
	{if (!(EXIST_ITEM(ARRAY,i)))
			{ARRAY[k]=i;
			 FILL_ARRAY(ARRAY,k+1);
			 ARRAY[k]=0;
			}
	}
}
void main ()
{
int i=0;
for (i=0;i<N*N;L[i]=0,i++);
FILL_ARRAY(L,0);
}