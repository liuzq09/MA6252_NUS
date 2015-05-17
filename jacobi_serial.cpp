#include <iostream>
#include <cmath>
using namespace std;

double u_exact(double x)
{
	double u;
	u=x*x*(x-1)*(x-1);
	return u;
}

double f(double x)
{
	double y;
	y=2*x*x+2*(x-1)*(x-1)+8*(x-1)*x;
	return y;
}

int main()
{
	int n=101;
	double h=1.0/n;
	double *xe=new double[n+1];
	double *u0=new double[n+1];
	double *u1=new double[n+1];
	double *fe=new double[n+1];
	double *uu=new double[n+1];
	for(int i=0;i<n+1;i++){
		xe[i]=(double)i*h;
		u0[i]=0;u1[i]=0;
		fe[i]=h*h*f(xe[i]);
		uu[i]=u_exact(xe[i]);
	}
	double error_limit=0.000001;
	double error=1;
	int iter=0;

	while(error>error_limit){
		error=0;
		for(int i=1;i<n;i++){
			u1[i]=0.5*(u0[i-1]+u0[i+1]-fe[i]);
			if(fabs(u0[i]-u1[i])>error)
				error=fabs(u0[i]-u1[i]);
		}
		for(int i=1;i<n;i++)
			u0[i]=u1[i];
		iter++;
		//cout<<"error is: "<<error<<", and iteration is: "<<iter<<endl;
	}
	
	double diff=0;
	for(int i=1;i<n;i++){
		if(fabs(u0[i]-uu[i])>diff)
			diff=fabs(u0[i]-uu[i]);
	}
	cout<<"error is: "<<error<<", and iteration is: "<<iter<<endl;
	cout<<"diff is: "<<diff<<", and iteration is: "<<iter<<endl;
	return 0;
}
