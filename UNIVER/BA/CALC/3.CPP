#include <iostream.h>
#include <math.h>
#include <iomanip.h>
#define D 0.000001
float NormaOfVector(float *Vector,int size);
main ()
{
float NXk=0,*b,*x,*xk;
int i,j,k=0,**M;
int h=0;
cout<<"Entry size of the matrixe \n";
cin>>h;
M=new int *[h];
b=new float [h];
x=new float [h];
xk=new float [h];
cout<<"Entry the matrixe  A\n";
for (i=0;i<h;M[i++]=new int [h]);
for (i=0;i<h;i++)
	 {
	 for(j=0;j<h;cin>>M[i][j++]);
	 x[i]=0;xk[i]=0;b[i]=0;
	 }
cout<<"Entry vector B\n";
for (i=0;i<h;cin>>b[i++]);
do
{
for (i=0;i<h;x[i]=xk[i],i++);
for (i=0;i<h;i++)
	  {xk[i]=0;
		for (j=0 ;j<h;j++)if (i!=j) xk[i]-=x[j]*M[i][j];
		xk[i]=(xk[i]+b[i])/M[i][i];
	  }
for (i=0;i<h;x[i]-=xk[i],i++);
NXk=NormaOfVector(x,h);
cout<<'\n'<<setw(4)<<++k;
for (i=0;i<h;cout<<setprecision(8)<<setw(12)<<xk[i++]);
}
while (NXk>D);
return 0;
}
//********************************************************
float NormaOfVector(float *Vector,int size)
{float max;
 int i;
 max=fabs(Vector[0]);
 for (i=1;i<size;i++)
	  if (max<fabs(Vector[i]))max=fabs(Vector[i]);
 return max;
}
