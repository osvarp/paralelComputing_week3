/*
Autor:Oscar Vargas Pabon

ggs hermanos
*/

#include <vector>
#include <iostream>
#include <utility>
#include <omp.h>
#include<functional>
#include <chrono>
#include <random>
std::mt19937 rng( std::chrono::steady_clock::now().time_since_epoch().count() );

void bubble_lin(std::vector<int> &vc){
	bool flg=1;while(flg){
		flg=0;
		for(int i=1;i<int(vc.size());++i)if(vc[i-1]>vc[i]){
			flg=1; std::swap(vc[i-1],vc[i]);
		}
	}
}
void bubble_omp(std::vector<int> &vc){
	bool flg=1;while(flg){
		flg=0;
		#pragma omp parallel for
		for(int i=1;i<int(vc.size());i+=2)if(vc[i-1]>vc[i]){
			flg=1; std::swap(vc[i-1],vc[i]);
		}
		#pragma omp parallel for
		for(int i=2;i<int(vc.size());i+=2)if(vc[i-1]>vc[i]){
			flg=1; std::swap(vc[i-1],vc[i]);
		}
	}
}

std::vector<int> merge(const std::vector<int>&v1,const std::vector<int>&v2){
	std::vector<int> res(v1.size()+v2.size());
	int i1=0,i2=0,ir=0;
	while(i1<int(v1.size())&&i2<int(v2.size())){
		if(v1[i1]>v2[i2]) res[ir++]=v2[i2++];
		else res[ir++]=v1[i1++];
	}
	while(i1<int(v1.size()))res[ir++]=v1[i1++];
	while(i2<int(v2.size()))res[ir++]=v2[i2++];
	return res;
};

std::vector<int> msort_lin(const std::vector<int> &vc){
	if(int(vc.size())==1)return vc;
	int m=vc.size()/2;
	return merge(
		msort_lin(std::vector<int>(vc.begin(),vc.begin()+m)),
		msort_lin(std::vector<int>(vc.begin()+m,vc.end()))
		);
	
}
std::vector<int> msort_omp(const std::vector<int> &vc){
	if(int(vc.size())==1)return vc;
	int m=vc.size()/2;
	std::vector<int> l,r;
	#pragma omp parallel sections
	{
		#pragma omp section
		l=msort_omp(std::vector<int>(vc.begin(),vc.begin()+m));
		#pragma omp section
		r=msort_omp(std::vector<int>(vc.begin()+m,vc.end()));
	}
	return merge(l,r);
}

void qsort_lin(std::vector<int>&vc){
	std::function<void(int,int)>aux_qsort=[&](int l,int r){
		if(l+1>=r)return;
		int q1=l,q2=r,obj=vc[l+ rng()%(r-l)];
		for(int i=l;i<r;++i)if(vc[i]<obj)std::swap(vc[i],vc[q1++]);
		for(int i=l;i<r;++i)if(vc[i]>obj)std::swap(vc[i],vc[--q2]);
		aux_qsort(l,q1); aux_qsort(q2,r);
	};aux_qsort(0,vc.size());
}

void qsort_omp(std::vector<int>&vc){
	std::function<void(int,int)>aux_qsort=[&](int l,int r){
		if(l+1>=r)return;
		int q1=l,q2=r,obj=vc[l+ rng()%(r-l)];
		for(int i=l;i<r;++i)if(vc[i]<obj)std::swap(vc[i],vc[q1++]);
		for(int i=l;i<r;++i)if(vc[i]>obj)std::swap(vc[i],vc[--q2]);
		#pragma omp parallel sections
		{
			#pragma omp section
			aux_qsort(l,q1);
			#pragma omp section
			aux_qsort(q2,r);
		}
	};aux_qsort(0,vc.size());
}

int main(){
	int n;std::cin>>n;
	std::vector<int> vo(n),ot;
	for(int &ac:vo)std::cin>>ac;
	std::function<void(std::string,std::vector<int>)> prnt=[&](std::string cad,std::vector<int> vec){
		std::cout << "["<<cad << "]";
		for(int ac:vec)std::cout << ' ' << ac;
		std::cout << '\n';
	};
	//bubble
	ot=vo;bubble_lin(ot);prnt("bubble_lin",ot);
	ot=vo;bubble_omp(ot);prnt("bubble_omp",ot);
	// msort
	ot=msort_lin(vo);prnt("msort_lin",ot);
	// ot=msort_omp(vo);prnt("msort_omp",ot);
	// qsort
	ot=vo;qsort_lin(ot);prnt("qsort_lin",ot);
	ot=vo;qsort_omp(ot);prnt("qsort_omp",ot);
	return 0;
}