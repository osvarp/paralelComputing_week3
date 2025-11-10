#include<iostream>
#include<vector>
#include<tuple>

#include"pbst.cpp"

int main(){
	int n;std::cin>>n;
	std::vector<int> vec(n);for(int i=0;i<n;++i)std::cin>>vec[i];
	int q;std::cin>>q;
	std::vector<int> qu(q);for(int i=0;i<q;++i)std::cin>>qu[i];
	
	std::vector<int> r_lin(q);for(int i=0;i<q;++i)r_lin[i]=bst_lin(vec,qu[i]);
	std::vector<int> r_omp(q);for(int i=0;i<q;++i)r_omp[i]=bst_omp(vec,qu[i]);
	
	std::cout<<"[lin]";for(int ac:r_lin)std::cout<< ' ' << ac; std::cout << std::endl;
	std::cout<<"[omp]";for(int ac:r_omp)std::cout<< ' ' << ac; std::cout << std::endl;
	
	return 0;
}