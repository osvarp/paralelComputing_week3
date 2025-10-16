/*
Fecha: 10/10/2025
Autor: Oscar Vargas Pabon

Actividad 2

g++ actividad2.cpp pretty_io.cpp table.cpp -o act2.exe
g++ actividad2.cpp pretty_io.cpp table.cpp -o act2.out
*/
#include"table.h"
#include"pretty_io.h"
#include"seq_search.cpp"


int main(){
	std::array<int,2> bnd={4,4};
	
	// Note: the case "EABCM#GDKFILNOJH" is ending on
	// A*_2 but not on the others
	Table tbl=read_table(bnd);
	int r_bfs=bfs(tbl); std::cout <<"bfs "<<r_bfs<<std::endl;
	int r_as1=aStar_1(tbl); std::cout <<"A*1 "<<r_as1<<std::endl;
	int r_as2=aStar_2(tbl); std::cout <<"A*2 "<<r_as2<<std::endl;
	
	return 0;
}