
/********************************************************************\
 hello_mpi.cpp
 -------------
 This example is used to illustrate the use of several fundamental
 MPI routines
 
 To compile, use:  mpic++ -o hello_mpi hello_mpi.cpp
 
 To run, use:      mpirun -np 64 -hostfile hostfile hello_mpi
 (Note: You must have the file, "hostfile", in the same directory as
 the executable.)
 \********************************************************************/

#include <iostream>
#include "mpi.h"

using namespace std;

int main (int argc, char *argv[]) {
    char name[100];
    cin >> name;
    MPI_Init(&argc, &argv);
    
    // Time at start of processing
    double start_time = MPI_Wtime();
    
    // Process id number
    int id;
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    
    // Number of processes
    int numberOfProcesse;
    MPI_Comm_size(MPI_COMM_WORLD,&numberOfProcesse);
    
    // Processor name and size of processor name
    char hostName[MPI_MAX_PROCESSOR_NAME];
    int nameSize;
    MPI_Get_processor_name(hostName, &nameSize);
    
    // Send
    for (int i = 0; i < numberOfProcesse; i++)
    {
        MPI_Send(&name, 101, MPI_CHAR, i, 1, MPI_COMM_WORLD);
    }
    
    // Only root prints this
    if (id == 0)
    {
        cout << "There are " << numberOfProcesse << " processes running!" <<  endl;
    }
    
    char recvName[100] = "Empty Message (shouldn`t see this.)";
    MPI_Recv(&recvName, 101, MPI_CHAR, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    
    // Every one print this
    cout << "Hello, " << recvName << "! - from process #" << id << endl;
    
    
    
    
    
    // Root prints runtime
    if (id == 0)
    {
        double run_time = (MPI_Wtime() - start_time) * MPI_Wtick();
        // cout << "Processing time for process " << id << " = " <<  run_time << " seconds" << endl;
    }
    
    MPI_Finalize();
}
