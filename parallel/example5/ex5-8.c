#include<stdlib.h>
#include<stdio.h>
#include"mpi.h"
int main(int argc, char *argv[])
{
    int myrank, nprocs;
    int *sendbuf,*recvbuf;
    int i;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    sendbuf = (int *)malloc(nprocs * sizeof(int));
    recvbuf = (int *)malloc(nprocs * sizeof(int));
    for(i=0;i<nprocs;i++)
	sendbuf[i]=myrank;

    MPI_Alltoall(sendbuf, 1, MPI_INT, recvbuf, 1, MPI_INT, MPI_COMM_WORLD);
    for(i=0;i<nprocs;i++){
	printf("On process %d,recvbuf[%d] receive from processor %d\n",myrank,i,recvbuf[i]);
    }
    MPI_Finalize();
    return 0;
}

