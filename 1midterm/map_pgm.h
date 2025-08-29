/*
Autor: Oscar Vargas Pabon
*/
#ifndef MAP_PGM_H
#define MAP_PGM_H

#include "fmap.h"
#include<vector>

class pgmMap : public fMap {
	int width,height,max_color;
	
public:
	std::vector<std::vector<int>> mp;
	pgmMap();
	pgmMap( const std::vector<std::vector<int>> &,int );
	void read_from( FILE* ) override;
	void write_to(FILE*) override;
	pgmMap* apply_kernel( Kernel * ) override;
};

#endif