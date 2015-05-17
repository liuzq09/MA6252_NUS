#include<stdio.h>
#include<string.h>
#include"mpi.h"
int main(int argc, char *argv[])
{
    int myrank,nprocs;
    double wt;
    double wt0;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
wt0=MPI_Wtime();
sleep(myrank);
printf("Process %d sleep %d seconds; \n",myrank, myrank);
//MPI_Barrier(MPI_COMM_WORLD);
wt=MPI_Wtime();
printf("Process %d, Wall time =%f\n",myrank, wt-wt0);
    MPI_Finalize();
    return 0;
}
