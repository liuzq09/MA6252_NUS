/*Each process has  an array of 30 doubles.
 * For each of the 30 locations, compute the value 
 * and rank of the process containning the largest value*/
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include"mpi.h"
int main(int argc, char *argv[])
{
    double ain[30],aout[30];
    int ind[30]; 
    int myrank, minrank,minindex;
    int minval;
    struct{
	double value;
	int rank;
    } in[30], out[30];
    int i;
    int root = 0;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    for(i=0;i<30;i++)
	ain[i]=sin(i*myrank);
    for(i=0;i<30;i++){
	in[i].value=ain[i];
	in[i].rank =myrank;
    }
    MPI_Reduce(&in,&out,30,MPI_DOUBLE_INT,MPI_MAXLOC,root, MPI_COMM_WORLD);
    if(myrank == root){
	for(i=0;i<30;i++){
	    aout[i]=out[i].value;
	    ind[i]=out[i].rank;
	    printf("value[i]=%f,ind[i]=%d\n",aout[i],ind[i]);
	}
    }
    MPI_Finalize();
    return 0;
}
