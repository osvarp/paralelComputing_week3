/*
Autor: Oscar Vargas Pabon
*/

#ifndef KERNEL_H
#define KERNEL_H
#include<vector>

class Kernel{
	std::vector<std::vector<int>> krnl; bool normalize;

	int acum,cnt;
public:

	int step;

	Kernel()=default;;
	Kernel(const std::vector<std::vector<int>> &, bool );
	void init();
	void add(int,int,int);
	void neut(int,int);
	int calculate();
};

#endif