#include<stdio.h>
#include<stdlib.h>
#include"mpi.h"
int main(int argc, char *argv[])
{
    int i,N,M;
    double A[5],B[5];
    void *buf;
    int position;
    int nprocs, myrank;
    MPI_Status status;

    buf = malloc(256);
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    if(myrank == 0){
	N=11,M=22;
	for(i=0;i<5;i++){
	    A[i]=i;
	    B[i]=-i;
	}
	position = 0;
	MPI_Pack(&N,1,MPI_INT,buf, 256,&position, MPI_COMM_WORLD);
	MPI_Pack(&M,1,MPI_INT,buf, 256,&position, MPI_COMM_WORLD);
	MPI_Pack(A,5,MPI_DOUBLE,buf,256,&position,MPI_COMM_WORLD);
	MPI_Pack(B,5,MPI_DOUBLE,buf,256,&position,MPI_COMM_WORLD);
	MPI_Send(buf,256,MPI_PACKED,1,111,MPI_COMM_WORLD);
    }
    else if(myrank == 1){
	MPI_Recv(buf, 256, MPI_PACKED, 0, 111, MPI_COMM_WORLD, &status);
	position = 0;
	/*uppack sequencially*/
	MPI_Unpack(buf,256,&position,&N,1,MPI_INT, MPI_COMM_WORLD);
	MPI_Unpack(buf,256,&position,&M,1,MPI_INT, MPI_COMM_WORLD);
	MPI_Unpack(buf,256,&position,A,5,MPI_DOUBLE, MPI_COMM_WORLD);
	MPI_Unpack(buf,256,&position,B,5,MPI_DOUBLE, MPI_COMM_WORLD);
	printf("N=%d,M=%d\n",N,M);
	printf("A={%f %f %f %f %f}\n",A[0],A[1],A[2],A[3],A[4]);
	printf("B={%f %f %f %f %f}\n",B[0],B[1],B[2],B[3],B[4]);
    }
    MPI_Finalize();
    free(buf);
    return 0;
}



