#include <iostream.h>
#include <iomanip.h>
#include <math.h>
#define X0 0
#define XN 1
#define F1X (x*x-1)
#define F2X (exp(x)*sin(x))
#define h 0.05
#define M 0.5
main ()
{
float x=X0,S=0,S1=0,S2=0,fx;
int i=1,i1=1,i2=1;
while(x<=XN+h/10)
{if (x<=M+h/10) S1+=i1*(fx=F1X); else S2+=i2*(fx=F2X);
S+=i*fx;
cout<<'\n'<<setw(4)<<x<<' '<<setprecision(6)<<fx;
x+=h;
if (x>M-h/10) i1=1;else if (i1!=4)i1=2; else i1=4;
if (x>XN-h/10)i2=1;else if (i2!=4)i2=4; else i2=2;
if (x>XN-h/10)i=1; else if (i!=4) i=4;  else i=2;

}
S*=(h/3);S1*=(h/3);S2*=(h/3);
cout<<"\nS="<<setprecision(6)<<S;
cout<<"\nS1="<<setprecision(6)<<S1;
cout<<"\nS2="<<setprecision(6)<<S2;
return(0);
}