/*
Fecha: 10/10/2025
Autor: Oscar Vargas Pabon

Actividad 1

g++ actividad1.cpp pretty_io.cpp table.cpp -o act1.exe
g++ actividad1.cpp pretty_io.cpp table.cpp -o act1.out
*/
#include"table.h"
#include"pretty_io.h"


int main(){
	std::array<int,2> bnd={4,4};
	Table tbl=read_table(bnd);
	print_table(tbl);
	std::cout<<"________Posible movements -> "<< std::endl;
	for(int i=0;i<mv_am;++i)if(tbl.posible_move(mv_dl[i]))std::cout<<mv_tp[i]<<std::endl;
	std::cout<< "\n______Insert a movement:"<<std::endl;
	std::array<int,2> mv=read_mov();
	Table t2=tbl.move(mv);
	print_table(t2);

	return 0;
}