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

int main(int argc, char* argv[]) {
	Kernel *blur=new Kernel({
		{1,1,1},
		{1,1,1},
		{1,1,1}
	},1),*laplace = new Kernel({
		{-1,-1,-1},
		{-1,8,-1},
		{-1,-1,-1}
	},0),*realce = new Kernel({
		{0,-1,0},
		{-1,5,-1},
		{0,-1,0}
	},0);
	
	char magic[3];

	if(argc<2){
		std::cout << "missing input and output paths\n";
		std::cout << "usage:" << argv[0] << " input_image.pgm output_image.pgm" << std::endl;
		std::cout << "or "<< argv[0] << "input_image.ppm output_image.ppm" << std::endl;
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
	
	Kernel *my_kernel=blur;
	if (argc<5 && argv[3]=="--f" ){
		if(!strcmp(argv[4],"blur"))my_kernel=blur;
		else if(!strcmp(argv[4],"laplace"))my_kernel=laplace;
		else if(!strcmp(argv[4],"realce"))my_kernel=realce;
		else{
			std::cout << "Error: The filter type " << argv[4] << " is not recognized." << std::endl;
			return 1;
		}
	}
	
	fMap *my_filt=my_map->apply_kernel(my_kernel);
	
	file = fopen(argv[2], "w");
	if (file == NULL) {
		std::cout << "Error, incorrect path or incorrect file."<< std::endl;
		return 1;
	}
	(void) fprintf(file, "%s\n", magic);
	my_filt->write_to(file);
	(void) fclose(file);
	delete blur; delete laplace; delete realce; delete my_map; delete my_filt;
	
	return 0;
}
	