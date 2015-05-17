#include <iostream>
#include <mpi.h>
using namespace std;

int main(int argc,char **argv)
{
	int rank,size;
	int n=100000000;
	double h=1.0/(double)n;
	int root=0;
	double total;
	double x;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	double sum=0.0;
	for(int i=rank;i<n;i=i+size){
		x=(i+0.5)*h;
		sum+=4.0*h/(1.0+x*x);
	}
	MPI_Reduce(&sum,&total,1,MPI_DOUBLE,MPI_SUM,root,MPI_COMM_WORLD);
	
	if(rank==root)
		cout<<"pi is approximated by: "<<total<<endl;
	MPI_Finalize();
	return 0;
}
