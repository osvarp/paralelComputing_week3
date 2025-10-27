/*
Autor: Oscar Vargas Pabon

Calculating min and max in various ways
*/

#include<vector>
#include<tuple>
#include<omp.h>

int min(int x,int y){return (x>y)?y:x;}
int max(int x,int y){return (x>y)?x:y;}

std::pair<int,int> brd_lin(const std::vector<int> &v){
	int mn=v[0];for(int ac:v)if(mn>ac)mn=ac;
	int mx=v[0];for(int ac:v)if(mx<ac)mx=ac;
	return {mn,mx};
}
std::pair<int,int> brd_omp(const std::vector<int> &v){
	int mn=v[0];
	#pragma omp parallel for reduction(min: mn)
	for(int i=1;i<int(v.size());++i)mn=min(mn,v[i]);
	
	int mx=v[0];
	#pragma omp parallel for reduction(max:mx)
	for(int i=1;i<int(v.size());++i)mx=max(mx,v[i]);
	return {mn,mx};
}