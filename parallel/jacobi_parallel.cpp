#include <iostream>
#include <cmath>
#include <mpi.h>
using namespace std;

double u_exact(double x)
{
	double u;
	u=x*x*(x-1)*(x-1);
	return u;
}

double f(double x)
{
	double y;
	y=2*x*x+2*(x-1)*(x-1)+8*(x-1)*x;
	return y;
}

int main(int argc, char** argv)
{
	int n=101;
	double h=1.0/n;
	double *xe=new double[n+1];
	double *fe=new double[n+1];
	double *uu=new double[n+1];
	for(int i=0;i<n+1;i++){
		xe[i]=(double)i*h;
		fe[i]=h*h*f(xe[i]);
		uu[i]=u_exact(xe[i]);
	}
	double error_limit=0.000001;
	double error=1;
	double local_error=0.0;
	int iter=0;

	int rank,size;
	int local_n;
	MPI_Request request[4];
	MPI_Status status[4];
	int tag=99;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	local_n=(n-1)/size;
	double *u0=new double[local_n+2];
	double *u1=new double[local_n+2];
	for(int i=0;i<local_n+2;i++){
		u0[i]=0;u1[i]=0;
	}
	while(error>error_limit){
		error=0;
		if(rank==0){
			MPI_Isend(u0+local_n,1,MPI_DOUBLE,1,tag,MPI_COMM_WORLD,request);
			MPI_Irecv(u0+local_n+1,1,MPI_DOUBLE,1,tag,MPI_COMM_WORLD,request+1);
			for(int i=1;i<local_n;i++)
				u1[i]=0.5*(u0[i-1]+u0[i+1]-fe[i]);
			MPI_Waitall(2,request,status);
			u1[local_n]=0.5*(u0[local_n-1]+u0[local_n+1]-fe[local_n]);
			local_error=0.0;
			for(int i=1;i<local_n+1;i++){
				if(fabs(u1[i]-u0[i])>local_error)
					local_error=fabs(u1[i]-u0[i]);
				u0[i]=u1[i];
			}
		}
		else if(rank==size-1){
			MPI_Isend(u0+1,1,MPI_DOUBLE,size-2,tag,MPI_COMM_WORLD,request);
			MPI_Irecv(u0,1,MPI_DOUBLE,size-2,tag,MPI_COMM_WORLD,request+1);
			for(int i=2;i<local_n+1;i++)
				u1[i]=0.5*(u0[i-1]+u0[i+1]-fe[i+rank*local_n]);
			MPI_Waitall(2,request,status);
			u1[1]=0.5*(u0[0]+u0[2]-fe[1+rank*local_n]);
			local_error=0.0;
			for(int i=1;i<local_n+1;i++){
				if(fabs(u1[i]-u0[i])>local_error)
					local_error=fabs(u1[i]-u0[i]);
				u0[i]=u1[i];
			}
		}
		else{
			MPI_Isend(u0+1,1,MPI_DOUBLE,rank-1,tag,MPI_COMM_WORLD,request);
			MPI_Irecv(u0,1,MPI_DOUBLE,rank-1,tag,MPI_COMM_WORLD,request+1);
			MPI_Isend(u0+local_n,1,MPI_DOUBLE,rank+1,tag,MPI_COMM_WORLD,request+2);
			MPI_Irecv(u0+local_n+1,1,MPI_DOUBLE,rank+1,tag,MPI_COMM_WORLD,request+3);
			for(int i=2;i<local_n;i++)
				u1[i]=0.5*(u0[i-1]+u0[i+1]-fe[i+rank*local_n]);
			MPI_Waitall(4,request,status);
			u1[1]=0.5*(u0[0]+u0[2]-fe[1+rank*local_n]);
			u1[local_n]=0.5*(u0[local_n-1]+u0[local_n+1]-fe[local_n+rank*local_n]);
			local_error=0.0;
			for(int i=1;i<local_n+1;i++){
				if(fabs(u1[i]-u0[i])>local_error)
					local_error=fabs(u1[i]-u0[i]);
				u0[i]=u1[i];
			}
		}
		MPI_Allreduce(&local_error,&error,1,MPI_DOUBLE,MPI_MAX,MPI_COMM_WORLD);
		iter++;
		//if(rank==0)
		//	cout<<"error is: "<<error<<", and iteration is: "<<iter<<endl;
	}

	
	/*double diff=0;
	for(int i=1;i<n;i++){
		if(fabs(u0[i]-uu[i])>diff)
			diff=fabs(u0[i]-uu[i]);
	}*/
	if(rank==0)
		cout<<"error is: "<<error<<", and iteration is: "<<iter<<endl;
	MPI_Finalize();

	return 0;
}
