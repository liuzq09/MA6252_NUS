#include<stdio.h>
#include<stdlib.h>
#include"mpi.h"
int main(int argc, char *argv[])
{
    int nprocs, myrank;
    int *sbuf, rbuf[5];
    int i,j,root = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    sbuf=(int *)malloc(nprocs*5*sizeof(int));
    for(i=0;i<nprocs;i++)
    	for(j=0;j<5;j++)
    	    sbuf[i*5+j]=i;
    MPI_Scatter(sbuf,5,MPI_INT, rbuf, 5, MPI_INT, root,MPI_COMM_WORLD);
    printf("processor %d of %d: %d %d %d %d %d\n",myrank, nprocs, 
	    rbuf[0],rbuf[1],rbuf[2],rbuf[3],rbuf[4]);
    free(sbuf);
    MPI_Finalize();
    return 0;
}

