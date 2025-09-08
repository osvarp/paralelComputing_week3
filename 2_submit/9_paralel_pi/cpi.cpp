#include<stdio.h>
#include<omp.h>

int main(){
	const int num_steps=1e9;
	const double step=1./double(num_steps);
	double sum=0,x;
	
	omp_set_num_threads(128);
	#pragma omp parallel private(x) reduction(+:sum)
	for(int i=0;i<num_steps;++i){
		x=(i+.5)*step;
		sum +=4.0/(1.+x*x);
	}
	double pi=sum*step;
	printf("The value of PI is %15.12f \n",pi);
	return 0;
}