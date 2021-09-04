#include <iostream.h>
#include <math.h>
#define D 0.0001
#define X01 1.965
#define X02 3
main()
{
float curr,next,help;
cout<<"\n*******(-(Xn-1)*(Xn-1)/10) ***********";
next=X01;
do
  {
  curr=next;
  next=acos(-curr*curr/10);
  cout<<"\n"<<curr,"5,2";
  if (fabs(curr-next)<=D) cout<<"\n"<<next,"5,2";
  }
while ((fabs(curr-next))>D);
cout<<"\n******** Xn=û-10*cos((Xn-1)) ***********";
next=X02;
do
 {
  curr=next;
  next=sqrt(-10*cos(curr));
  cout<<"\n"<<curr,"5,2";
  if (fabs(curr-next)<=D) cout<<"\n"<<next,"5,2";
  }
while ((fabs(curr-next))>D);
}