#include<iostream>
#include<vector>
#include<tuple>

#include"borders.cpp"
#include"psum.cpp"

int main(){
	int n;std::cin>>n;
	std::vector<int> vec(n);for(int i=0;i<n;++i)std::cin>>vec[i];
	
	
	std::pair<int,int> p1=brd_lin(vec);
	std::pair<int,int> p2=brd_omp(vec);
	
	std::cout << "lin-> " << p1.first << " _ " << p1.second << std::endl;
	std::cout << "omp-> " << p2.first << " _ " << p2.second << std::endl;
	
	std::vector<int> vt=vec;
	psum_lin(vec); psum_omp(vt);
	
	std::cout<<"[lin]";for(int ac:vec)std::cout<< ' ' << ac; std::cout << std::endl;
	std::cout<<"[omp]";for(int ac:vt)std::cout<< ' ' << ac; std::cout << std::endl;
	
	return 0;
}