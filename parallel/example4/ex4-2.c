#include<stdio.h>
#include"mpi.h"
int main(int argc, char *argv[])
{
    MPI_Datatype types[]={MPI_DOUBLE,MPI_INT, MPI_BYTE};
    MPI_Aint displs[]={0,8,12};
    int counts[]={1,1,1};
    MPI_Datatype newtype;
    MPI_Aint LB,UB,EX;
    int SZ;

    MPI_Init(&argc, &argv);
    
    MPI_Type_struct(3,counts,displs,types,&newtype);

    MPI_Type_lb(newtype,&LB);
    MPI_Type_ub(newtype,&UB);
    MPI_Type_size(newtype, &SZ);
    MPI_Type_extent(newtype, &EX);
    printf("LB=%d, UB=%d, EX=%d,SIZE=%d\n",LB,UB,EX,SZ);
    MPI_Type_free(&newtype);
    MPI_Finalize();
    return 0;
}
