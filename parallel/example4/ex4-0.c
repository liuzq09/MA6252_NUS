#include<stdlib.h>
#include<stdio.h>
#include"mpi.h"
int main(int argc, char *argv[])
{
    int A[100];
    int B[100],i;
    int nprocs,myrank;
    MPI_Status status;
    MPI_Datatype newtype,type[3]={MPI_INT,MPI_INT,MPI_INT};
//    int disp[]={4,12,0};
    MPI_Aint disp[]={-4,0,4};
    int len[]={1,1,1};
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    for (i=0;i<100;i++)
	A[i]=i;
    MPI_Type_struct(3,len,disp,type,&newtype);
    MPI_Type_commit(&newtype); 
    if (myrank == 0){
    //	MPI_Send(A,1,newtype,1,10,MPI_COMM_WORLD);
    	MPI_Send(A+1,1,newtype,1,10,MPI_COMM_WORLD);
    }
    else if(myrank == 1){
	MPI_Recv(B,100,MPI_INT,0,10,MPI_COMM_WORLD,&status);
	printf("B[0]=%d, B[1]=%d, B[2]=%d\n",B[0],B[1],B[2]);
    }
    MPI_Type_free(&newtype);
    MPI_Finalize();
    return 0;
}
