#include <iostream>
#include <mpi.h>
using namespace std;

int main(int argc, char** argv)
{
	int rank,size;
	int A[8]={1,2,3,4,5,6,7,8};
	int B[2]={0,0};
	MPI_Status status;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if(rank==0){
		for(int i=0;i<4;i++)
			MPI_Send(A+2*i,2,MPI_INT,i,99,MPI_COMM_WORLD);
	}
	MPI_Recv(B,2,MPI_INT,0,99,MPI_COMM_WORLD,&status);
	cout<<"process "<<rank<<" received: "<<B[0]<<"\t"<<B[1]<<endl;

	MPI_Finalize();
	return 0;
}
