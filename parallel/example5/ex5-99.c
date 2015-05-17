#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include"mpi.h"
#define LEN 10
int main(int argc, char *argv[])
{
    int val[LEN];/*local array of values*/
    int myrank,nprocs, minrank,minindex;
    int minval;
    struct{
	int value;
	int index;
    } in, out;
    int i;
    int root = 0;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    srand((int)time(0)); 
    for(i=0;i<LEN;i++)
	val[i]=rand();
    in.value=val[0];
    in.index=0;
    /*find the local minloc*/
    for(i=1;i<LEN;i++)
	if(in.value>val[i]){
	    in.value=val[i];
	    in.index = i;
	}
    in.index=myrank*LEN +in.index;
    MPI_Reduce(&in,&out,1,MPI_2INT,MPI_MINLOC,root, MPI_COMM_WORLD);
    if(myrank == root){
	minval=out.value;
	minrank=out.index/LEN;
	minindex=out.index%LEN;
	printf("Minvalu= %d,minrank=%d,minindex=%d\n",minval,minrank,minindex);
    }
    MPI_Finalize();
    return 0;
}
