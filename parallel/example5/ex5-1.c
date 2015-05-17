#include<stdio.h>
#include<stdlib.h>
#include"mpi.h"
int main(int argc, char *argv[])
{
    int nprocs, myrank;
    int a[5];
    int i,root=0;
    int *rbuf;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    rbuf = (int *)malloc(nprocs*5*sizeof(int));
    for(i=0;i<5;i++)
	a[i]=myrank;
    MPI_Gather(a,5,MPI_INT,rbuf,5,MPI_INT,root,MPI_COMM_WORLD);
    if(myrank == root){
    	for(i=0;i<5*nprocs;i++){
    	    printf("%d ",rbuf[i]);
    	    if((i+1)%5==0&&i>0)
		printf("\n");
    	}
    }
    free(rbuf);
    MPI_Finalize();
    return 0;
}


