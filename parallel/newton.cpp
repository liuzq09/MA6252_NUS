#include <iostream>
#include <cmath>
using namespace std;

double init_f(double &x)
{
double s=0.0;
s=3*x*x-exp(x);
return s;
}

double deriv_f(double &x)
{
double s=0.0;
s=6*x-exp(x);
return s;
}

double newton_f(double &x)
{
double s=0.0;
s=x-init_f(x)/deriv_f(x);
return s;
}

int main()
{
double err=1.0;
double x0=1.0,x1=0.0;
while(err>0.000001)
{
x1=newton_f(x0);
err=fabs(x1-x0);
x0=x1;
}
cout<<x1<<endl;
return 0;
}
