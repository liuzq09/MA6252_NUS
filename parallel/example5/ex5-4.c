/* stride >=5*/
#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include"mpi.h"
int main(int argc, char *argv[])
{
    int nprocs, myrank;
    int a[5];
    int i,root=0;
    int *rbuf;
    int stride=5, *displs, *rcounts;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    rbuf = (int *)malloc(nprocs*stride*sizeof(int));
    displs = (int *)malloc(nprocs * sizeof(int));
    rcounts = (int *)malloc(nprocs * sizeof(int));
    bzero(rbuf,sizeof(rbuf));
    for(i=0;i<nprocs;i++){
	displs[i]=i*stride;
	rcounts[i]=5;
    }
    for(i=0;i<5;i++)
	a[i]=myrank;
    MPI_Gatherv(a,5,MPI_INT,rbuf,rcounts,displs,
	    MPI_INT,root,MPI_COMM_WORLD);
    if(myrank == root){
    	for(i=0;i<stride*nprocs;i++){
    	    printf("%d ",rbuf[i]);
    	    if((i+1)%stride==0&&i>0)
		printf("\n");
    	}
    }
    free(rbuf);
    free(displs);
    free(rcounts);
    MPI_Finalize();
    return 0;
}


