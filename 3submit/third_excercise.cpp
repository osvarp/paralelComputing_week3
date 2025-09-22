/*
Autor: Oscar Vargas Pabon
*/

#include <mpi.h>
#include <iostream>

const int template_limit=1000;
int a[template_limit],b[template_limit];

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);
    int world_rank; MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size; MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	for(int i = 0 ; i < template_limit ; ++i )a[i]=world_rank;
	int snd=(world_rank+1)%world_size;
	MPI_Send(a, template_limit, MPI_INT, snd, 0, MPI_COMM_WORLD);
	std::cout << "Process " << world_rank << " sent array to process " << snd << std::endl;
	int rcv=(world_rank+world_size-1)%world_size;
	MPI_Status status; MPI_Recv(b,template_limit,MPI_INT,rcv,0,MPI_COMM_WORLD,&status);
    std::cout << "Process " << world_rank << " Received array b[0]= " << b[0] << std::endl;

    MPI_Finalize();
    return 0;
}