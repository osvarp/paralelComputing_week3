/*
Autor: Oscar Vargas Pabon
*/
#include "kernel.h"
Kernel::Kernel(const std::vector<std::vector<int>> &mt, int nrm,int neutr ){
	this->normalize=nrm; this->krnl=mt; this->step=mt.size()/2; this->neutral=neutr;
}