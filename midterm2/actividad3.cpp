/*
Fecha: 10/10/2025
Autor: Oscar Vargas Pabon

Actividad 3

g++ -fopenmp actividad3.cpp pretty_io.cpp table.cpp -o act3.out
*/
#include"table.h"
#include"pretty_io.h"
#include"omp_search.cpp"


int main(){
	std::array<int,2> bnd={4,4};

	const int cores=8;std::cout<<"cores " << cores << std::endl<<std::endl;

	// Note: the case "EABCM#GDKFILNOJH" is ending on
	// A*_2 but not on the others
	Table tbl=read_table(bnd);
	int r_bfs=omp_bfs(tbl,cores); std::cout <<"bfs "<<r_bfs<<std::endl;
	int r_as1=omp_aStar_1(tbl,cores); std::cout <<"A*1 "<<r_as1<<std::endl;
	int r_as2=omp_aStar_2(tbl,cores); std::cout <<"A*2 "<<r_as2<<std::endl;
	
	return 0;
}