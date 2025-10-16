#include "mat_op.h"
#include<assert.h>
#include <omp.h>

std::vector<std::vector<int>> mat_mult(
		std::vector<std::vector<int>>&a,
		std::vector<std::vector<int>>&b
		){
	// computo c=a*b
	assert(!b.empty());
	int n=a.size(),m=b.size(),p=b[0].size();
	// a\in R^{nXm} ; b\in R^{mXp} ; c\in R^{nXp} ;
	std::vector<std::vector<int>> c(n,std::vector<int>(p,0));
	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<n;++i){
			#pragma omp parallel
			{
			#pragma omp for
			for(int j=0;j<p;++j){
				#pragma omp parallel
				{
					int y=0;
					#pragma parallel
					for(int k=0;k<m;++k){
						y+=a[i][k]*b[k][j];
					}
					#pragma omp atomic
					c[i][j]+=y;
				}
			}
			}
		}
	}
	return c;
}

std::vector<std::vector<int>> mat_add(
		std::vector<std::vector<int>>&a,
		std::vector<std::vector<int>>&b
		){
	// computo c=a+b
	assert(!b.empty());
	assert(b.size()==a.size()&&b[0].size()==a[0].size());
	int n=a.size(),m=a[0].size();
	
	// a\in R^{nXm} ; b\in R^{nXm} ; c\in R^{nXp} ;
	std::vector<std::vector<int>> c(n,std::vector<int>(m));
	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<n;++i){
			#pragma omp parallel
			{
			#pragma omp for
			for(int j=0;j<m;++j){
				c[i][j]=a[i][j]+b[i][j];
			}
			}
		}
	}
	return c;
}
std::vector<std::vector<int>> mat_transp(
		std::vector<std::vector<int>>&a
		){
	// computo c=a^T
	assert(!a.empty());
	int n=a.size(),m=a[0].size();
	
	
	// a\in R^{nXm} ; b\in R^{nXm} ; c\in R^{nXp} ;
	std::vector<std::vector<int>> c(m,std::vector<int>(n));
	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<n;++i){
			#pragma omp parallel
			{
			#pragma omp for
			for(int j=0;j<m;++j){
				c[j][i]=a[i][j];
			}
			}
		}
	}
	return c;
}