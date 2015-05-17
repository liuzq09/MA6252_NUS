#include<stdio.h>
#include"mpi.h"
int main(int argc, char *argv[])
{
    int N = 1024;
    int myrank, nprocs, src, dest, tag;
    MPI_Request request[2];
    MPI_Status status;
    double A[N],B[N],sum;
    int i;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    for (i=0;i<N;i++)
	A[i]=(double)myrank;
    
    src = myrank - 1;
    if(src<0)
       src = nprocs - 1;
    dest = myrank + 1;
    if(dest>=nprocs)
	dest = 0;    
//  Create persistent communication requests
    tag = 111;
    MPI_Send_init( A, N, MPI_DOUBLE, dest, tag,
	    MPI_COMM_WORLD, request);
    MPI_Recv_init(B, N, MPI_DOUBLE, src, tag,
	    MPI_COMM_WORLD, request+1);
//   Start communications
    MPI_Startall(2, request);

//  Wait for completion of recv.
    MPI_Wait(request+1, &status);

    sum = 0.0;
    for (i=0;i<N;i++)
	sum = sum + B[i];
    printf("Process %d ,values = %f\n",myrank, (double)sum/N);
// Wait for completion of send.
    MPI_Wait(request, &status);

//   Start communications again;
    MPI_Startall(2, request);
//  Wait for completion of recv.
    MPI_Wait(request+1, &status);

    sum = 0.0;
    for (i=0;i<N;i++)
        sum = sum + B[i];
    printf("Process %d ,values = %f\n",myrank, (double)sum/N);
// Wait for completion of send.
    MPI_Wait(request, &status); 

    MPI_Finalize();
    return 0;
}
