#include <iostream>
#include <cmath>
using namespace std;

double maxNorm(double *vec1, double *vec2, int n)//to calculate the maxNorm error
{
	double max=0,temp;
	for(int i=0;i<n;i++){
		temp=fabs(vec1[i]-vec2[i]);
		if(temp>max)
			max=temp;
	}
	return max;
}

int main()
{
	int n=40;//n is the total number of small intervals
	double a=1,b=2;//boundary value
	double h=1.0/n;//the computation domain is [0,1], h is the step size
	double *sol_0=new double[n-1];
	double *sol_1=new double[n-1];
	for(int i=0;i<n-1;i++)
	{
		sol_0[i]=0;sol_1[i]=0;
	}
	double diff=1;
	double errorLimit=0.00001;
	/* the following loop is the main part of the program */
	while(diff>errorLimit){
		sol_1[0]=0.5*(a+sol_0[1]);
		sol_1[n-2]=0.5*(b+sol_0[n-3]);
		for(int i=1;i<n-2;i++)
			sol_1[i]=0.5*(sol_0[i-1]+sol_0[i+1]);
		diff=maxNorm(sol_0,sol_1,n-1);
		for(int i=0;i<n-1;i++)
			sol_0[i]=sol_1[i];
	}
	/* The following is to calculate the numerical erro*/
	double error,c=b-a;
	double *sol_exact=new double[n-1];
	for(int i=0;i<n-1;i++)
		sol_exact[i]=c*(i+1)*h+a;
	error=maxNorm(sol_exact,sol_0,n-1);
	cout<<"The Max Norm Error is "<<error<<endl;
	return 0;
}
