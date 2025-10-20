/*
Autor: Oscar Vargas Pabon
*/

#ifndef FMAP_H
#define FMAP_H

#include<stdio.h>
#include "kernel.h"

class fMap{
public:
	fMap()=default;
	virtual void read_from( FILE* )=0;
	virtual void write_to(FILE*)=0;
	virtual fMap* apply_kernel( Kernel * )=0;
};

#endif