/*
Autor: Oscar Vargas Pabon

Compilar
g++ -fopenmp main.cpp -o exec.exe
g++ -fopenmp main.cpp -o exec.out

Ejecutar: Asume un archivo del estilo
<n>
<m_1> <v_{1,1}> <v_{1,2}> ... <v_{1,m_1}>
...
<m_n> <v_{n,1}> <v_{n,2}> ... <v_{n,m_n}>

un ejemplo esta en example.txt
*/

#include<iostream>
#include<vector>
#include<omp.h>


int calc_sum(const std::vector<int> &vec){ int res=0;for(int ac:vec)res+=ac;return res; }

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
	
	std::vector<int>ans(n,0);
	#pragma omp parallel for
	for(int i=0;i<n;++i)ans[i]=calc_sum(al[i]);
	
	
	std::cout << "Answer\n\n";
	for(int ac:ans)std::cout << ac << '\n';
	std::cout << '\n';
	
	return 0;
}