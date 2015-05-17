#include<stdio.h>
#include<string.h>
#include"mpi.h"
int main(int argc, char *argv[])
{
    int myrank,nprocs;
    int root;
    char message[20];
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    root = 0;
    if(myrank == root){
	strcpy(message,"Hello, the world!");
    }
    MPI_Bcast(message,20,MPI_CHAR, root, MPI_COMM_WORLD);
    printf("Processor %d of %d: %s\n",myrank, nprocs, message);
    MPI_Finalize();
    return 0;
}
