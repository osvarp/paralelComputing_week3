/*
Autor: Oscar Vargas Pabon
*/

#ifndef KERNEL_H
#define KERNEL_H
#include<vector>

class Kernel{
	public:
	std::vector<std::vector<int>> krnl;
	int normalize,neutral, step;

	Kernel()=default;;
	Kernel(const std::vector<std::vector<int>> &, int=1,int=0 );
};

#endif