#include<stdio.h>
#include"mpi.h"

int main(int argc, char *argv[])
{
    int i,j,N=4,M=5;
    double A[N][M],B[M][N];
    MPI_Status status;
    MPI_Datatype type1,type2;
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
    MPI_Type_vector(M,1,N,MPI_DOUBLE, &type1);
    MPI_Type_extent(MPI_DOUBLE, &ex);
    MPI_Type_create_hvector(N,1,ex,type1,&type2);
    MPI_Type_free(&type1);
    MPI_Type_commit(&type2);
    MPI_Sendrecv(A,N*M,MPI_DOUBLE, 0, 111,
	    B,1,type2,0,111,
	    MPI_COMM_SELF,&status);
    MPI_Type_free(&type2);
    printf("B=\n");
    for(i=0;i<M;i++)
    {
	for(j=0;j<N;j++)
	    printf("%d ",(int)B[i][j]);
	printf("\n");
    }
    MPI_Finalize();
    return 0;
}
