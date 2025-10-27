/*
Autor:Oscar vargas Pabon


Lo hize asi nomas porque o si no no tiene sentido la paralelizacion
*/
#include<vector>
#include<omp.h>
void psum_lin( std::vector<int> &v){ for(int i=1;i<int(v.size());++i)v[i]+=v[i-1]; }
void psum_omp(std::vector<int> &v){
	//https://en.wikipedia.org/wiki/Prefix_sum
	std::vector<int> neo(v.size());
	for(int e=1;e<int(v.size());e<<=1){
		#pragma omp parallel for
		for(int i=0;i<int(v.size());++i){
			if(i<e)neo[i]=v[i];
			else neo[i]=v[i]+v[i-e];
		}
		swap(neo,v);
	}
}