#include<iostream>
#include<vector>
#include <omp.h>

int adder(const std::vector<int> &arr){
	int res=0;
	#pragma omp parallel
	{
		int rs=0;
		#pragma omp for
		for(int i=0;i<int(arr.size());++i)rs+=arr[i];
		#pragma omp atomic
		res+=rs;
	}
	return res;
}

int main(){
	int n; std::cin>>n;
	std::vector<int> arr(n);
	for(int&act:arr)std::cin>>act;
	
	int res=adder(arr);
	std::cout << "Respuesta <"<<res<<">(openMP)\n";
	return 0;
}