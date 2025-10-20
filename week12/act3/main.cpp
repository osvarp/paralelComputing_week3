/*
Autor: Oscar Vargas Pabon

Compilar
g++ -fopenmp main.cpp -o exec.exe
g++ -fopenmp main.cpp -o exec.out

Ejecutar: Asume un archivo del estilo (donde las q_i son los que pregunto si estan)
<n>
<m_1> <v_{1,1}> <v_{1,2}> ... <v_{1,m_1}>
...
<m_n> <v_{n,1}> <v_{n,2}> ... <v_{n,m_n}>

<Q>
<q_1>
...
<q_Q>

un ejemplo esta en example.txt
*/

#include<iostream>
#include<vector>
#include<algorithm>

#include<omp.h>


int main(){
	int n;std::cin>>n;
	std::vector<std::vector<int>> al(n);
	for(int i=0;i<n;++i){
		int m;std::cin>>m;
		for(int j=0;j<m;++j){
			int ac;std::cin>>ac;
			al[i].push_back(ac);
		}
	}
	for(int i=0;i<n;++i)std::sort(al[i].begin(),al[i].end());
	int q;std::cin>>q;
	std::vector<int> qu(q);for(int &ac:qu)std::cin>>ac;
	
	std::vector<std::vector<bool>>ans(q,std::vector<bool>(n));
	#pragma omp parallel for
	for(int i=0;i<q;++i){
		#pragma omp parallel for
		// std::cout << i << " __ _ _  " << std::endl;
		for(int j=0;j<n;++j) ans[i][j]=binary_search(al[j].begin(),al[j].end(),qu[i]);
	}
	
	
	std::cout << "Answer per query \n\n";
	for(std::vector<bool> &vc:ans){
		for(bool ac:vc)std::cout << ac;
		std::cout << '\n';
	}
	std::cout << '\n';
	
	return 0;
}