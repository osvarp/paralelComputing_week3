#include <iostream>
#include "plate.h"


int str_to_int(char *str){
	int res=0;
	for(int i=0;'0'<=str[i]&&str[i]<='9';++i)res=res*10+str[i]-'0';
	return res;
}


int main(int argc, char *argv[]){
	int n=256,m=256;
	if(argc>=2)n=str_to_int(argv[1]);
	if(argc>=3)m=str_to_int(argv[2]);
	
	std::vector<std::vector<double>> plt=simul(n,m,{n/2,m/2});
	
	return 0;
}