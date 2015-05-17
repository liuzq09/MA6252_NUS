/*for tag, blocking message passing, jqchen March 15, 2013*/
#include<stdio.h>
#include "mpi.h"
int main(int argc, char *argv[])
{
    int myrank, nprocs,src, dest,tag;
    MPI_Status status;
    int a,b; 

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    MPI_Comm_size(MPI_COMM_WORLD,&nprocs);

    
    a = myrank + 10;
    b = myrank + 20;
    if (myrank==0){
	MPI_Send(&a, 1, MPI_INT, 1, 9, MPI_COMM_WORLD);
	MPI_Send(&b, 1, MPI_INT, 1, 91, MPI_COMM_WORLD);
    }
    else{
    	MPI_Recv(&b, 1, MPI_INT, 0,  91, MPI_COMM_WORLD, &status);
    	MPI_Recv(&a, 1, MPI_INT, 0,  9, MPI_COMM_WORLD, &status);
    }

    printf("Process %d ,a = %d, b = %d\n",myrank, a,b);
      
    MPI_Finalize();
    return 0;
}
