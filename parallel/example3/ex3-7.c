/*blocking message passing, jqchen March 15, 2013*/
#include<stdio.h>
#include<stdlib.h> // for malloc
#include "mpi.h"
int main(int argc, char *argv[])
{
    int i,bufsize,N=1024*10;
    int myrank, nprocs,src, dest,tag;
    MPI_Status status;
    double A[N],B[N],sum;
    double *buf;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
    for(i=0;i<N;i++)
	A[i]=(double)myrank;

    MPI_Pack_size(N,MPI_DOUBLE, MPI_COMM_WORLD, &bufsize);
//    MPI_Type_size(MPI_DOUBLE,&bufsize);  
//    bufsize = N*bufsize;
    bufsize = MPI_BSEND_OVERHEAD+bufsize;//定义缓冲方式所需额外开销
    buf=(double *)malloc(bufsize);
    MPI_Buffer_attach(buf,bufsize);
    src = myrank-1;
    if(src<0)
	src=nprocs-1;
    dest = myrank+1;
    if(dest>=nprocs)
	dest = 0;
    
    tag =111;
    MPI_Bsend(A, N, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
    MPI_Recv(B, N, MPI_DOUBLE, src,  tag, MPI_COMM_WORLD, &status);
    sum = 0.0;
    for (i=0;i<N;i++)
	sum =sum +B[i];

    printf("Process %d ,values = %f\n",myrank, (double)sum/N);
    MPI_Buffer_detach(&buf, &bufsize);
    free(buf);  
    MPI_Finalize();
    return 0;
}
