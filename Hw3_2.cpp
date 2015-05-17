#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <mpi.h>
using namespace std;


int main(int argc, char** argv)
{
string message[100];
for(int i=0;i<100;i++)
message[i]="message ";

int size,rank;
MPI_Status status;
MPI_Init(&argc,&argv);

MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);

if(rank!=0){
ostringstream orank;
orank<<rank;
string oranks=orank.str();
for(int i=0;i<100;i++){
char mm[50];
ostringstream oi;
oi<<i;
string ois=oi.str();
message[i]+=ois;
message[i]+=" of process ";
message[i]+=oranks;
strcpy(mm,message[i].c_str());
MPI_Send(mm,strlen(mm)+1,MPI_CHAR,0,99,MPI_COMM_WORLD);
}
}
else{
for(int i=0;i<100*(size-1);i++){
char Message[50];
MPI_Recv(Message,50,MPI_CHAR,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
cout<<"Received: "<<Message<<endl;
}
}
MPI_Finalize();
return 0;
}

