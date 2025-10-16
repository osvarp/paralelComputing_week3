#include<iostream>
#include<vector>
#include<random>
#include<chrono>
#include "mat_op.h"

#define rep(i,strt,end) for(int i = strt ; i !=int(end) ; (int(strt)<int(end))?++i:--i )
std::mt19937 rndom( std::chrono::steady_clock::now().time_since_epoch().count() );

std::vector<int> random_vec(int n, int lb=0,int rb=10){
	std::vector<int> vec(n);
	for(int&act:vec)act=rndom()%(rb-lb)+lb;
	return vec;
}
std::vector<std::vector<int>> random_mat(int n,int m,int lb=0,int rb=10){
	std::vector<std::vector<int>> mat(n);
	for(std::vector<int>&act:mat)act=random_vec(m,lb,rb);
	return mat;
}

void print_vec(const std::vector<int> &vec){for(int act:vec)std::cout << act << ' '; std::cout << '\n';}
void print_mat(const std::vector<std::vector<int>>&mat){for(const std::vector<int>&act:mat)print_vec(act);}

int str_to_int(char *str){
	int res=0;
	for(int i=0;'0'<=str[i]&&str[i]<='9';++i)res=res*10+str[i]-'0';
	return res;
}

int my_gen(){return rndom()%100 + 2;}

int main(int argc, char *argv[]){
	int n=my_gen(),m=my_gen(),p=1;
	if(argc>=2)n=str_to_int(argv[1]);
	if(argc>=3)m=str_to_int(argv[2]);
	
	std::vector<std::vector<int>> m1=random_mat(n,m),m2=random_mat(m,p);
	std::vector<std::vector<int>> m3=mat_mult(m1,m2);
	
	return 0;
}

