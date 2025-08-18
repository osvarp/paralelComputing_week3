#include<iostream>
#include<random>
#include<chrono>

std::mt19937 mrandom( std::chrono::steady_clock::now().time_since_epoch().count() );

// no quiero numeros demasiado random
int my_random(){ return mrandom()%10; }
int main(){
	int n; std::cin>>n;
	
	std::cout << n << '\n';
	for(int i=0;i<n;++i) std::cout<<my_random()<< ' ';
	std::cout << std::endl;
	return 0;
}