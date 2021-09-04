#include <iostream.h>
#include <iomanip.h>
#define SIZE 10
#define DEGREE 4
class Point {public:float x,y;};
main ()
{
int counter=0,i,j,i_max=0,first,last,size;
float x0=0,y0,Li;
Point INPUT[SIZE];
cout<<"\nEntry the size of the table \n";
cin>>size;
cout<<"\nEntry the table of points\n";
while (counter<size)
{cin>>INPUT[counter].x;cin>>INPUT[counter++].y;};
cout<<"\nEntry the point , 99 to end\n";
cout<<"X0=";cin>>x0;
if (size>(DEGREE+1)) while (x0>INPUT[i_max++].x);
if (i_max<=(DEGREE/2)) {first=0;last=DEGREE;}
	else if ((size-i_max)>(DEGREE/2))
			  {first=i_max-DEGREE;last=i_max+DEGREE;}
		  else {first=size-DEGREE;last=size;};
while (x0!=99)
{
y0=0;
for (i=first;i<=last;i++)
	 {Li=1;
	  for (j=first;j<=last;j++)
	  if (i!=j) Li*=(x0-INPUT[j].x)/(INPUT[i].x-INPUT[j].x);
	  y0+=Li*INPUT[i].y;
	 }
cout<<"Y0="<<setw(5)<<setprecision(5)<<y0<<'\n';
cout<<"\nX0=";cin>>x0;
}
return (0);
}
