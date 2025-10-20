/*
Autor: Oscar Vargas Pabon
Algunas cosas son tomadas de japeto

Compilar

g++ -fopenmp main.cpp kernel.cpp lineal/map_pgm.cpp lineal/map_ppm.cpp -o lin.out
g++ -fopenmp -pthread main.cpp kernel.cpp pthread/map_pgm.cpp pthread/map_ppm.cpp -o pthr.out
g++ -fopenmp main.cpp kernel.cpp openMp/map_pgm.cpp openMp/map_ppm.cpp -o omp.out

Execute

Requires input from stdin in the form
<n>
<in_file_1> <out_file_1> <filter_1>
...
<in_file_n> <out_file_n> <filter_n>

Example input named example.txt
*/
#include <iostream>
#include<stdio.h>
#include<functional>

#include "kernel.h"
#include "fmap.h"
#include "map_pgm.h"
#include "map_ppm.h"
#include <string.h>
#include <omp.h>

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
	
	

	/*if(argc<2){
		std::cout << "missing input and output paths\n";
		std::cout << "usage:" << argv[0] << " input_image.pgm output_image.pgm" << std::endl;
		std::cout << "or "<< argv[0] << "input_image.ppm output_image.ppm" << std::endl;
		return 1;
	}*/

	std::function<void(char*,char*,const std::string &)> one_fl=[&](char*file_name,char*print_name,const std::string &filt){
		//printf("%s %s\n",file_name,print_name);
		// abrir archivo
		FILE *file = fopen(file_name, "r");
		if (file == NULL) {
			std::cout << "Error, incorrect path or incorrect file. 1"<< std::endl;
			return 1;
		}
		// Leer y mostrar línea por línea
		char magic[3]; fscanf(file, "%2s", magic);  // magic number
		
		fMap *my_map;
		if(!strcmp(magic,"P3") || !strcmp(magic,"p3")) my_map=new ppmMap;
		else if(!strcmp(magic,"P2") || !strcmp(magic,"p2"))my_map=new pgmMap;
		else {
			std::cout << "Error: file type " << magic << " not recognized" << std::endl;
			return 1;
		}

		my_map->read_from(file); fclose(file);
		
		Kernel *my_kernel;
		
		if(filt=="blur")my_kernel=blur;
		else if(filt=="laplace")my_kernel=laplace;
		else if(filt=="sharpen")my_kernel=sharpen;
		else{
			std::cout << "Error: The filter type " << filt << " is not recognized." << std::endl;
			return 1;
		}
		
		fMap *my_filt=my_map->apply_kernel(my_kernel);
		
		file = fopen(print_name, "w");
		if (file == NULL) {
			std::cout << "Error, incorrect path or incorrect file. 2"<< std::endl;
			return 1;
		}
		(void) fprintf(file, "%s\n", magic);
		my_filt->write_to(file);
		(void) fclose(file);

		delete my_map; delete my_filt;
	};

	int t;std::cin>>t;
	omp_lock_t read_lock;
    omp_init_lock(&read_lock);
	//#pragma omp parallel 
	//{
		#pragma omp parallel for
		for(int i=0;i<t;++i){
			omp_set_lock(&read_lock);
			char inf[100],ouf[100];scanf("%s %s",inf,ouf);
			std::string fl;std::cin>>fl;
			omp_unset_lock(&read_lock);
			//printf("%s %s\n",inf,ouf);
			one_fl(inf,ouf,fl);
		}
	//}


	delete blur; delete laplace; delete sharpen;
	
	return 0;
}


