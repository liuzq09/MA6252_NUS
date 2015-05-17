#include <iostream>
#include <mpi.h>
using namespace std;

int main(int argc,char **argv)
{
	int rank,size;
	int n=100000000;
	double h=1.0/n;
	int root=0;
	double sum=0.0;
	double total;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	int r=n/size;
	//double sum=0.0;
	for(int i=0;i<r;i++)
		sum+=h*(1.0/(1.0+(double)(i+r*rank)*(double)(i+r*rank)*h*h));//why adding 0.5 or using double makes difference??
	MPI_Reduce(&sum,&total,1,MPI_DOUBLE,MPI_SUM,root,MPI_COMM_WORLD);
	
	if(rank==root){
		cout<<"pi is approximated by: "<<4*total<<endl;
		//cout<<r<<endl;
		//cout<<sum<<endl;
	}
	MPI_Finalize();
	return 0;
}
