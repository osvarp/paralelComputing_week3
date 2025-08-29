/*
Autor: Oscar Vargas Pabon
Algunas cosas son tomadas de japeto
*/
#include <iostream>
#include "kernel.h"
#include "fmap.h"
#include "map_pgm.h"
#include "map_ppm.h"
#include <string.h>
#include <mpi.h>
#include<functional>

int main(int argc, char* argv[]) {
	Kernel *blur=new Kernel({
		{1,1,1},
		{1,1,1},
		{1,1,1}
	},9),*laplace = new Kernel({
		{-1,-1,-1},
		{-1,8,-1},
		{-1,-1,-1}
	}),*sharpen = new Kernel({
		{0,-1,0},
		{-1,5,-1},
		{0,-1,0}
	});
	
	char magic[3];

	if(argc<5){
		std::cout << "missing input and output paths\n";
		std::cout << "usage:" << argv[0] << " input_image.pgm blur.pgm laplace.pgm sharpen.pgm " << std::endl;
		std::cout << "or "<< argv[0] << "input_image.ppm blur.ppm laplace.ppm sharpen.ppm" << std::endl;
		return 1;
	}
	// abrir archivo
	FILE *file = fopen(argv[1], "r");
	if (file == NULL) {
		std::cout << "Error, incorrect path or incorrect file."<< std::endl;
		return 1;
	}
	// Leer y mostrar línea por línea
	fscanf(file, "%2s", magic);  // magic number
	
	fMap *my_map;
	if(!strcmp(magic,"P3") || !strcmp(magic,"p3")) my_map=new ppmMap;
	else if(!strcmp(magic,"P2") || !strcmp(magic,"p2"))my_map=new pgmMap;
	else {
		std::cout << "Error: file type " << magic << " not recognized" << std::endl;
		return 1;
	}

	my_map->read_from(file); fclose(file);
	
	std::function<void(Kernel*,int)> paral_apply=[&my_map,&magic,&argv](Kernel*krnl,int ind){
		fMap *my_filt=my_map->apply_kernel(krnl);
		FILE *mfile = fopen(argv[ind], "w");
		if (mfile == NULL) {
			std::cout << "Error, incorrect path or incorrect file."<< std::endl;
		}

		(void) fprintf(mfile, "%s\n", magic);
		my_filt->write_to(mfile);
		(void) fclose(mfile);
	};
	
	MPI_Init(NULL,NULL);
	int rank;MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	int world_size;MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	
	if(rank==0)paral_apply(blur,2);
	if(rank==1||(rank==0&&world_size<1))paral_apply(laplace,3);
	if(rank==2||(rank==0&&world_size<2))paral_apply(sharpen,4);

	MPI_Finalize();  
	
	return 0;
}
	