#include<stdio.h>
#include<string.h>
#include"mpi.h"
int main(int argc, char *argv[])
{
    int myrank,count;
    char message[20];
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    if(myrank == 0){
	strcpy(message,"Hello,there");
	MPI_Send(message,strlen(message)+1, MPI_CHAR, 1, 99,MPI_COMM_WORLD);
    }
    else if (myrank == 1){
	MPI_Recv(message, 20, MPI_CHAR, 0, 99, MPI_COMM_WORLD, &status);
//        printf("MPI_TAG_UB=%d\n",MPI_TAG_UB);
//	MPI_Get_count(&status,MPI_CHAR, &count);
//	printf("count = %d\n",count);
	printf("Received: %s \n ",message);
//	printf("Status: Source=%d,Tag=%d\n",status.MPI_SOURCE, status.MPI_TAG);
    }
    MPI_Finalize();
    return 0;
}

