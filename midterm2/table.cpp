/*
Fecha: 10/10/2025
Autor: Oscar Vargas Pabon

Clase tablero. Para manejar mis operaciones de tipo tablero
*/
#include"table.h"

std::array<int,2> Table::real_index(int ind)const{ return { ind/bnd[1], ind%bnd[1] }; }
int Table::unreal_index(const std::array<int,2> &ind )const{return ind[0]*bnd[1]+ind[1];}
void Table::recalc_stat(){stat=0;for(int i=0;i<bnd[0]*bnd[1];++i)stat+=p[i]==i;}
int Table::manh_dst(const std::array<int,2> &i1,const std::array<int,2> &i2){
	int res=0;for(int i=0;i<2;++i)res+=(i1[i]-i2[i])*(2*(i1[i]>i2[i])-1);
	return res;
}
int Table::dst_to_ok(int ind)const{return Table::manh_dst(this->real_index(ind),this->real_index(p[ind]));}
void Table::recalc_sm_dst(){ sm_dst=0;for(int i=0;i<bnd[0]*bnd[1];++i) sm_dst+=this->dst_to_ok(i); }

Table::Table():Table({0,0}){};

Table::Table(const std::array<int,2>&bbnd){
	bnd=bbnd;
	p=std::vector<int>(bnd[0]*bnd[1]);
	init={-1,-1};
	stat=sm_dst=0;
}
#include<iostream>
Table::Table(const std::array<int,2>&bbnd,const std::string &str) {
	std::vector<int> tmp(str.size());
	for(int i=0;i<int(str.size());++i)tmp[i]=(str[i]==cent_piece)?bbnd[0]*bbnd[1]-1:str[i]-frst_char;
	*this=Table(bbnd,tmp);
}

Table::Table(const std::array<int,2>&bbnd,const std::vector<int> &pp):Table(bbnd){
	int ind=0;p=pp;
	for(int rw=0;rw<bnd[0];++rw)for(int cl=0;cl<bnd[1];++cl){
		if(p[ind]==bnd[0]*bnd[1]-1)init={rw,cl};
		stat+=p[ind]==ind; sm_dst+=this->dst_to_ok(ind);
		++ind;
	}
}
bool Table::posible_move(const std::array<int,2>&delta)const{
	bool res=1;for(int i=0;i<2;++i){
		int neo=delta[i]+init[i];
		res=res&& neo>=0&&neo<bnd[i];
	}
	return res;
}

Table Table::move( const std::array<int,2>&delta )const{
	Table ot=*this;
	if(this->posible_move(delta)){
		std::array<int,2> neo={init[0]+delta[0],init[1]+delta[1]};
		int i1 = unreal_index(init), i2 = unreal_index(neo);
		std::swap(ot.p[i1],ot.p[i2]);ot.init=neo;

		ot.stat -= (p[i1]==i1) + (p[i2]==i2);
		ot.stat += (p[i1]==i2) + (p[i2]==i1);

		ot.sm_dst-=this->dst_to_ok(i1)+this->dst_to_ok(i2);
		ot.sm_dst+=   ot.dst_to_ok(i1)+   ot.dst_to_ok(i2);

		//ot.recalc_stat(); ot.recalc_sm_dst();
	}
	return ot;
}

std::string Table::to_str()const{
	std::string str;
	for(int i=0;i<bnd[0]*bnd[1];++i)str.push_back( (p[i]==bnd[0]*bnd[1]-1)?cent_piece:p[i]+frst_char);
	return str;
}

std::array<int,2> Table::get_bnd()const{return bnd;}
int Table::get_stat()const{return stat;}
int Table::get_sm_dst()const{return sm_dst;}
std::array<int,2> Table::get_init()const{return init;}
std::vector<int> Table::get_p()const{return p;}


