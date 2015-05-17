#include<stdio.h>
#include"mpi.h"

int main(int argc, char *argv[])
{
    int i,j,N=5;
    double A[N][N],B[N][N];
    MPI_Status status;
    MPI_Datatype type;
    int len[N],disp[N];

    MPI_Init(&argc, &argv);
    for (i=0;i<N;i++)
	for (j=0;j<N;j++){
	    A[i][j]=10*i+j;
	}
    printf("A=\n");
    for(i=0;i<N;i++)
    {
	for(j=0;j<N;j++)
    	    printf("%d ",(int)A[i][j]);
	printf("\n");
    }
    len[0]=1;
    disp[0]=0;
    for(i=1;i<N;i++)
    {
	len[i]=len[i-1]+1;
	disp[i]=i*N;
    }
    MPI_Type_indexed(N,len,disp,MPI_DOUBLE, &type);
    MPI_Type_commit(&type);
    MPI_Sendrecv(A,1,type, 0, 111,
	    B,1,type,0,111,
	    MPI_COMM_SELF,&status);
    MPI_Type_free(&type);
    printf("B=\n");
    for(i=0;i<N;i++)
    {
	for(j=0;j<=i;j++)
	    printf("%d ",(int)B[i][j]);
	printf("\n");
    }
    MPI_Finalize();
    return 0;
}
