/*Process 0 send first, other processes receive first
 * The communication is sequentially, March 15, 2013*/
#include<stdio.h>
#include"mpi.h"
int main(int argc, char *argv[])
{
    int i,N=1024;
    int myrank, nprocs, src,dest, tag;
    MPI_Status status;
    double A[N],B[N],sum;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
    
    for(i=0;i<N;i++)
   	A[i]=(double)myrank;

    src = myrank-1;
    if (src<0)
	src = nprocs - 1;
    dest=myrank + 1;
    if (dest>=nprocs)
	dest = 0;

    tag = 111;
    if (myrank == 0){
	MPI_Send(A,N,MPI_DOUBLE, dest, tag, 
		MPI_COMM_WORLD);
	MPI_Recv(B,N,MPI_DOUBLE, src,  tag,
		MPI_COMM_WORLD, &status);
    }
    else{
	MPI_Recv(B,N,MPI_DOUBLE, src,  tag,
		MPI_COMM_WORLD, &status);
	MPI_Send(A,N,MPI_DOUBLE, dest, tag, 
		MPI_COMM_WORLD);
    }
    sum = 0.0;
    for(i=0;i<N;i++)
	sum = sum + B[i];

  printf("Process %d result %f\n",myrank, (double)sum/N);

    MPI_Finalize();
    return 0;
}
