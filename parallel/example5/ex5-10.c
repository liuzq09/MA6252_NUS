#include<stdio.h>
#include<stdlib.h>
#include"mpi.h"
typedef struct{
    double real,imag;
} Complex;
void myProd(Complex *in, Complex *inout, int *len, MPI_Datatype *dptr)
{
    int i;
    Complex c;
    for(i=0;i<*len;i++){
	c.real = inout->real*in->real
	    - inout->imag*in->imag;
	c.imag = inout->real*in->imag
	    + inout->imag*in->real;
	*inout = c;
	in++;
	inout++;
    }
}
int main(int argc, char *argv[])
{
    Complex a,answer;
    MPI_Op myOp;
    MPI_Datatype ctype;
    int root =0;
    int myrank;
    Complex sanswer;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    a.real = 1.;
    a.imag = 1.;
    
    MPI_Type_contiguous(2,MPI_DOUBLE,&ctype);
    MPI_Type_commit(&ctype);

    MPI_Op_create((MPI_User_function *)myProd,1,&myOp);
    MPI_Reduce(&a,&answer,1,ctype,myOp,root,MPI_COMM_WORLD);
    if(myrank == root)
    	printf("Reduce: answer,real =%f,imag=%f\n",answer.real,answer.imag);
    MPI_Scan(&a,&sanswer, 1, ctype, myOp, MPI_COMM_WORLD);
    printf("Scan on rank %d: answer,real=%f,imag=%f\n",myrank,sanswer.real,sanswer.imag);
    MPI_Op_free(&myOp);
    MPI_Finalize();
    return 0;
}


