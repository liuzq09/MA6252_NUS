#include<stdio.h>
#include"mpi.h"
int main(int argc, char *argv[])
{
    double A[3]={1.0, 1.0,1.0};
    int B[5]={123, 123, 123, 123, 123};
    char C[7]={15, 15, 15, 15, 15, 15, 15};
    int lens[3]={1,1,1};
    MPI_Aint displs[3];
    int count,elements;
    MPI_Status status;
    MPI_Datatype types[3];
    MPI_Datatype newtype;

    MPI_Init(&argc, &argv);

    MPI_Type_contiguous(3, MPI_DOUBLE, types);
    MPI_Type_contiguous(5, MPI_INT, types+1);
    MPI_Type_contiguous(7, MPI_CHAR, types+2);

    MPI_Address(A,displs);
    MPI_Address(B,displs+1);
    MPI_Address(C,displs+2);
    printf("displs[0]=%d, displs[1]=%d,displs[2]=%d\n",displs[0],displs[1],displs[2]);
    MPI_Type_struct(3,lens,displs,types,&newtype);
    MPI_Type_commit(&newtype);
    MPI_Sendrecv_replace(MPI_BOTTOM, 1, newtype, 0, 0, 0, 0, 
	    MPI_COMM_SELF,&status);
    MPI_Get_count(&status, newtype, &count);
    MPI_Get_elements(&status, newtype, &elements);
    printf("Count = %d, Elements = %d\n",count, elements);
    MPI_Type_free(&newtype);
    MPI_Finalize();
    return 0;
}
