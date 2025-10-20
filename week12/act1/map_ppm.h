/*
Autor: Oscar Vargas Pabon
*/
#ifndef MAP_PPM_H
#define MAP_PPM_H

#include "fmap.h"
#include "map_pgm.h"
#include<array>

class ppmMap : public fMap {
	int width,height,max_color;
	std::array<pgmMap,3> mp;
public:
	ppmMap();
	void read_from( FILE* ) override;
	void write_to(FILE*) override;
	ppmMap* apply_kernel( Kernel * ) override;
};

#endif