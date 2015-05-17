#include<stdio.h>
#include"mpi.h"
int main(int argc, char *argv[])
{
    MPI_Aint lb,ub,ex;
    int sz;
    MPI_Aint displs[]={-4,20,0,8,12};
    int counts[]={1,1,1,1,1};
    MPI_Datatype types[]={MPI_LB,MPI_UB,MPI_DOUBLE,MPI_INT,MPI_BYTE};
    MPI_Datatype newtype;

    MPI_Init(&argc,&argv);

    MPI_Type_struct(5,counts,displs,types,&newtype);
    MPI_Type_lb(newtype,&lb);
    MPI_Type_ub(newtype,&ub);
    MPI_Type_size(newtype,&sz);
    MPI_Type_extent(newtype,&ex);
    printf("LB=%d, UB=%d, EX=%d,Size=%d\n",lb,ub,ex,sz);
    MPI_Type_free(&newtype);  
    MPI_Finalize();
    return 0;
}
