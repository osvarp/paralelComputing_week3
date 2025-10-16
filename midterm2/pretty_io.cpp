/*
Fecha: 10/10/2025
Autor: Oscar Vargas Pabon

Para mis necesidades de InputOutput
*/
#include"pretty_io.h"



std::array<int,2> read_mov(){
	std::string op;std::cin>>op;
	int ind=0;while(ind<mv_am&&mv_tp[ind]!=op)++ind;
	if(ind>=mv_am){std::cerr<<"Error: Operation <"<<op<<"> not recognized."<<std::endl;throw 10101;}
	return mv_dl[ind];
}
Table read_table(const std::array<int,2>&bnd){
	std::string rw_tb;std::cin>>rw_tb;
	if(std::cin.eof())return Table({-1,-1});
	
	if(int(rw_tb.size())!=bnd[0]*bnd[1]){
		std::cerr<<"Error: The table <"<<rw_tb<<"> doesn't have the specified dimesions of ("<<bnd[0]<<","<<bnd[1]<<")."<<std::endl;
		throw 10101;
	}
	return Table(bnd,rw_tb);
}

void print_mov(const std::array<int,2>&delta){
	int ind=0;while(ind<mv_am&&mv_dl[ind]!=delta)++ind;
	if(ind>=mv_am){std::cerr<<"Error: Movement ("<<delta[0]<<","<<delta[1]<<") not recognized."<<std::endl;throw 10101;}
	std::cout<<mv_tp[ind]<<std::endl;
}
void print_table(const Table &tbl){
	std::array<int,2> bnd=tbl.get_bnd();
	std::string pret=tbl.to_str();
	int n=bnd[0],m=bnd[1],ind=0;
	for(int rw=0;rw<n;++rw){
		for(int cl=0;cl<m;++cl)std::cout<< pret[ind++] << ' ';
		std::cout << '\n';
	}
	std::cout << std::endl;
}

