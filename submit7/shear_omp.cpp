/*
Autor:oscar Vargas Pabon
*/
#include <vector>
#include <algorithm>
#include <functional>
#include <random>
#include <chrono>
#include <omp.h>

void sort_row(std::vector<int>&vec,bool ord){
	mt19937 rng( chrono::steady_clock::now().time_since_epoch().count() );
	auto cmn=[&ord](int x,int y){ return (ord)?x>y:x<y;};
	auto cmx=[&ord](int x,int y){ return (ord)?x<y:x>y;};
	
	function<void(int,int)> qsort=[&](int l,int r){
		int pivot=vec[rng()%(r-l) +l];
		int q1=l;for(int i=l;i<r;++i)   if(cmn(vec[i],obj))std::swap(vec[q1++],vec[i]);
		int q2=r;for(int i=r-1;i>=l;--i)if(cmx(vec[i],obj))std::swap(vec[--q2],vec[i]);
		#pragma omp parallel sections
		{
			#pragma omp section
			qsort(l,q1);
			#pragma omp section
			qsort(q2,r);
		}
	};qsort(0,vec.size());
}

void sort_col(std::vector<std::vector<int>>&mat,int cl){
	mt19937 rng( chrono::steady_clock::now().time_since_epoch().count() );
	
	function<void(int,int)> qsort=[&](int l,int r){
		int pivot=mat[rng()%(r-l) +l][cl];
		int q1=l;for(int i=l;i<r;++i)   if(mat[i][cl]<obj)std::swap(mat[q1++][cl],mat[i][cl]);
		int q2=r;for(int i=r-1;i>=l;--i)if(mat[i][cl]>obj)std::swap(mat[--q2][cl],mat[i][cl]);
		#pragma omp parallel sections
		{
			#pragma omp section
			qsort(l,q1);
			#pragma omp section
			qsort(q2,r);
		}
	};qsort(0,mat.size());
}

void shear_omp(std::vector<std::vector<int>> &mat){
	int n=mat.size();
	for(int e=1;e<n;e<<=1){
		for(int i=0;i<n;++i)sort_row(mat[i],i&1);
		for(int i=0;i<n;++i)sort_col(mat,i);
	}
}

void transp(std::vector<std::vector<int>> &mat){
	#pragma omp parallel for
	for(int i=0;i<int(mat.size());++i)for(int j=i+1;j<int(mat.size());++j){
		std::swap(mat[i][j],mat[j][i]);
	}
}
void t_shear_omp(std::vector<std::vector<int>> &mat){
	int n=mat.size();
	for(int e=1;e<n;e<<=1){
		for(int x=0;x<2;++x){
			for(int i=0;i<n;++i)sort_row(mat[i],(i&1) || x);
			transp(mat);
		}
	}
}