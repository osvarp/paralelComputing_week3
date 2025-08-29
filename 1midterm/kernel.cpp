/*
Autor: Oscar Vargas Pabon
*/
#include "kernel.h"
Kernel::Kernel(const std::vector<std::vector<int>> &mt, bool nrm ){
	this->normalize=nrm; this->krnl=mt; this->step=mt.size()/2;
}
void Kernel::init(){this->acum=this->cnt=0;}
void Kernel::add(int i,int j,int vl){this->acum+=this->krnl[i][j]*vl;++this->cnt;}
void Kernel::neut(int i,int j){return;}
int Kernel::calculate(){return static_cast<int>(double(this->acum)/double(this->cnt));}