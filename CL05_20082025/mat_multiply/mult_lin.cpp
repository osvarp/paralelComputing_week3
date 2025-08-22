#include<iostream>
#include<vector>
#include<assert.h>

std::vector<std::vector<int>> mat_mult(
		std::vector<std::vector<int>>&a,
		std::vector<std::vector<int>>&b,
		int n_thread=6
		){
	// computo c=a*b
	assert(!b.empty());
	int n=a.size(),m=b.size(),p=b[0].size();
	// a\in R^{nXm} ; b\in R^{mXp} ; c\in R^{nXp} ;
	std::vector<std::vector<int>> c(n,std::vector<int>(p,0));
	for(int i=0;i<n;++i)for(int j=0;j<p;++j)for(int k=0;k<m;++k)c[i][j]+=a[i][k]*b[k][j];
	return c;
}

std::vector<std::vector<int>> read_mat(){
	int n,m;std::cin>>n>>m;
	std::vector<std::vector<int>> mat(n,std::vector<int>(m));
	for(std::vector<int>&rw:mat)for(int&ac:rw)std::cin>>ac;
	return mat;
}



int main(){
	std::vector<std::vector<int>> a=read_mat(),b=read_mat(),c;
	c=mat_mult(a,b);
	
	for(std::vector<int>&rw:c){
		for(int&ac:rw)std::cout << ac << ' ';
		std::cout << '\n';
	}
	
	return 0;
}