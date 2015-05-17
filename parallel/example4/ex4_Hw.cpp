#include <iostream>
#include <mpi.h>
using namespace std;

int main(int argc, char **argv)
{
	int M=4,N=5;
	double A[M][N],B[N],C[M],D[M];
	int len[M],disp[M];
	for(int i=0;i<M;i++){
		len[i]=1;disp[i]=i*(N+1);
	}
	for(int i=0;i<M;i++)
		for(int j=0;j<N;j++)
			A[i][j]=1.0/(1.0+i+2*j);
	MPI_Datatype type1,type2,type3;
	MPI_Status status;
	int rank;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if(rank==0){
	for(int i=0;i<M;i++){
		for(int j=0;j<N;j++)
			cout<<A[i][j]<<"\t";
		cout<<endl;
	}
	cout<<endl;
	}

	//MPI_Init(&argc,&argv);
	//MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Type_vector(1,N,1,MPI_DOUBLE,&type1);
	MPI_Type_commit(&type1);
	MPI_Type_vector(M,1,N,MPI_DOUBLE,&type2);
	MPI_Type_commit(&type2);
	MPI_Type_indexed(M,len,disp,MPI_DOUBLE,&type3);
	MPI_Type_commit(&type3);
	MPI_Sendrecv(A,N,MPI_DOUBLE,0,99,B,1,type1,0,99,MPI_COMM_WORLD,&status);
	MPI_Sendrecv(A,1,type2,0,99,C,M,MPI_DOUBLE,0,99,MPI_COMM_WORLD,&status);
	MPI_Sendrecv(A,1,type3,0,99,D,M,MPI_DOUBLE,0,99,MPI_COMM_WORLD,&status);
	if(rank==0){
	for(int j=0;j<N;j++)
		cout<<B[j]<<"\t";
	cout<<endl;
	for(int i=0;i<M;i++)
		cout<<C[i]<<endl;
	cout<<endl;
	for(int i=0;i<M;i++)
		cout<<D[i]<<endl;
	}
	MPI_Type_free(&type1);
	MPI_Type_free(&type2);

	MPI_Finalize();
	return 0;
}
