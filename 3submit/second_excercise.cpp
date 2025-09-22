/*
Autor: Oscar Vargas Pabon
*/

#include <mpi.h>
#include <iostream>
#include <string>

/*const int template_limit=1000;
int a[template_limit],b[template_limit];*/

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);
    int world_rank; MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size; MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int val=47;
	if(!world_rank) val=val*val;
	std::cout << "Process " << world_rank << " Has value " << val << std::endl;
	MPI_Bcast(&val,1,MPI_INT,0,MPI_COMM_WORLD);
    std::cout << "Process " << world_rank << std::string( (world_rank)?" Received": " Sent" )<< " value " << val << std::endl;	
	
    MPI_Finalize();
    return 0;
}