#include<iostream>
#include<vector>

int main(){
	int n; std::cin>>n;
	std::vector<int> arr(n);
	for(int&act:arr)std::cin>>act;
	
	int res=0;for(int act:arr)res+=act;
	std::cout << "Respuesta <"<<res<<">(lin)\n";
	return 0;
}