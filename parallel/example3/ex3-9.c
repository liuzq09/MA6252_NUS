#include<stdio.h>
#include "mpi.h"
#define TEST_AS 1
int
main(int argc, char *argv[])
{
    int i, myrank, nprocs;
    MPI_Status status;
    int a;
    double b;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    if (nprocs < 3) {
	printf("Need more processor(>=3)!\n");
	MPI_Finalize();
	return 0;
    }
    a = myrank;
    b = (double)myrank;
    if (myrank == 0)
	MPI_Send(&a, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
    else if (myrank == 1)
	MPI_Send(&b, 1, MPI_DOUBLE, 2, 0, MPI_COMM_WORLD);
    else if (myrank == 2) {
	for (i = 0; i < 2; i++) {
	    MPI_Probe(MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
	    if (status.MPI_SOURCE == 0)
                MPI_Recv(&a, 1, MPI_INT,    0, 0, MPI_COMM_WORLD, &status);
//		MPI_Recv(&a, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
	    else
                MPI_Recv(&b, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, &status);
//		MPI_Recv(&b, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
	}
	printf("a=%d, b=%f\n", a, b);
    }
//    else if (myrank == 3)
//	MPI_Send(&b, 1, MPI_DOUBLE, 2, 0, MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}
