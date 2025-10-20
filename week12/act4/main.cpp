/*
Autor: Oscar Vargas Pabon

Compilar
g++ -fopenmp main.cpp -o exec.exe
g++ -fopenmp main.cpp -o exec.out

Ejecutar: Asume un archivo del estilo
<n>
<h_1>
...
<h_n>

un ejemplo esta en example.txt
*/

#include<iostream>
#include<vector>
#include<math.h>
#include<omp.h>

const double grav=9.7;

double calc_time(double h){
	// a(t)=grav
	// v(t)=t*grav+v_0=t*grav
	// r(t)=t^2*grav/2+r_0=t^2*grav/2
	// h=t^2*grav/2
	// \sqrt{2*h/grav}=t
	return sqrt(2*h/grav);
}

int main(){
	int n;std::cin>>n;
	std::vector<double> a(n);for(double &ac:a)std::cin>>ac;
	
	#pragma parallel for
	for(int i=0;i<n;++i)a[i]=calc_time(a[i]);
	
	for(double ac:a)std::cout << ac << '\n';
	
	return 0;
}