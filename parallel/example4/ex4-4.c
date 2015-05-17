#include<stdio.h>
#include"mpi.h"

int main(int argc, char *argv[])
{
    int i,j,N=4,M=5;
    double A[N][M],B[N-2][M-2];
    MPI_Status status;
    MPI_Datatype type;
    MPI_Aint ex;

    MPI_Init(&argc, &argv);
    for (i=0;i<N;i++)
	for (j=0;j<M;j++)
	    A[i][j]=10*i+j;
    printf("A=\n");
    for(i=0;i<N;i++)
    {
	for(j=0;j<M;j++)
    	    printf("%d ",(int)A[i][j]);
	printf("\n");
    }
    MPI_Type_vector(N-2,M-2,M,MPI_DOUBLE, &type);
    MPI_Type_commit(&type);
    MPI_Sendrecv(A[1]+1,1,type, 0, 111,
	    B,(N)*(M),MPI_DOUBLE,0,111,
	    MPI_COMM_SELF,&status);
    MPI_Type_free(&type);
    printf("B=\n");
    for(i=0;i<N-2;i++)
    {
	for(j=0;j<M-2;j++)
	    printf("%d ",(int)B[i][j]);
	printf("\n");
    }
    MPI_Finalize();
    return 0;
}
