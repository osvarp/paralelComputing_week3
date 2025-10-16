/*
Fecha: 10/10/2025
Autor: Oscar Vargas Pabon

Clase tablero. Para manejar mis operaciones de tipo tablero
*/
#ifndef TABLE_H
#define TABLE_H

#include<vector>
#include<string>
#include<array>
#include<utility>

const std::vector<std::array<int,2>> mov={{-1,0},{1,0},{0,-1},{0,1}};

const char cent_piece='#',frst_char='A';

class Table{
private:
	std::vector<int> p;
	std::array<int,2> bnd;//p\in\mathfrac{Z}^{bnd[0]\times bnd[1]}
	std::array<int,2> init;//mat[x][y]=='#'
	int stat;//stationary elements stat:=\sum(p[i]==i)
	int sm_dst;//sum of manhattan distances to its apropriate place

	std::array<int,2> real_index(int ind)const;
	int unreal_index(const std::array<int,2> &ind )const;
	void recalc_stat();
	int dst_to_ok(int ind)const;
	void recalc_sm_dst();
public:
	static int manh_dst(const std::array<int,2> &i1,const std::array<int,2> &i2);
	
	Table();
	Table(const std::array<int,2>&bbnd);
	Table(const std::array<int,2>&bbnd,const std::string &str);
	Table(const std::array<int,2>&bbnd,const std::vector<int> &pp);

	bool posible_move(const std::array<int,2>&delta)const;
	Table move( const std::array<int,2>&delta )const ;

	
	std::string to_str() const ;
	std::array<int,2> get_bnd() const;
	int get_stat()const;
	int get_sm_dst()const;
	std::array<int,2> get_init()const;
	std::vector<int> get_p()const;

	bool operator <(const Table &ot)const{return p<ot.p;}
	bool operator ==(const Table &ot)const{return p==ot.p;}
};

#endif // TABLE_H