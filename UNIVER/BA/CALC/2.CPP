#include <iostream.h>
#include <math.h>
#define D   0.00001
#define X0  (10*M_PI)
#define FX  (sin(X)-(X/2))
#define DFX (cos(X)-(0.5))
main ()                   
{
 float X,Xn;
 int i=0;
 Xn=X0;
 do
 {
 X=Xn;
 Xn=X-FX/DFX;
 cout<<"\n"<<i++<<" "<<X<<" "<<FX<<" "<<DFX,"2,5";
 }
 while (fabs(Xn-X)>D);
}