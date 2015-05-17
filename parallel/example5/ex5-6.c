/* stride >=10,i<10, and nprocs<10*/
#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include"mpi.h"
int main(int argc, char *argv[])
{
    int nprocs, myrank;
    int a[10][15],*sptr;
    int i,j,root=0;
    int *rbuf;
    int stride=11, *displs, *rcounts;
    MPI_Datatype stype;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    rbuf = (int *)malloc(nprocs*stride*sizeof(int));
    displs = (int *)malloc(nprocs * sizeof(int));
    rcounts = (int *)malloc(nprocs * sizeof(int));
    bzero(rbuf,sizeof(rbuf));
    for(i=0;i<nprocs;i++){
	displs[i]=i*stride;
	rcounts[i]=10-i;
    }
    for(i=0;i<10;i++)
	for(j=0;j<15;j++)
    	    a[i][j]=i;
    /*Create datatype for the column we are sending */
    MPI_Type_vector(10-myrank,1,15,MPI_INT,&stype);
    MPI_Type_commit(&stype);
    /* sptr is the address of start of "myrank" column
     */
    sptr=&a[0][myrank];
    MPI_Gatherv(sptr,1,stype,rbuf,rcounts,displs,
	    MPI_INT,root,MPI_COMM_WORLD);
    MPI_Type_free(&stype);
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


