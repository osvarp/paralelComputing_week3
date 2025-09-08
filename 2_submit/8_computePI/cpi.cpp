#include<stdio.h>

int main(){
	const int num_steps=1e9;
	double step=1./double(num_steps),sum=0,x;
	for(int i=0;i<num_steps;++i){
		x=(i+.5)*step;
		sum +=4.0/(1.+x*x);
	}
	double pi=sum*step;
	printf("The value of PI is %15.12f \n",pi);
	return 0;
}