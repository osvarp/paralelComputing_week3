#include<stdio.h>
#include<omp.h>

int main(int argc,char *argv[]){
	int n_thrd=0;
	for(int ind=0;argv[1][ind]!='\0';++ind)n_thrd=n_thrd*10+(argv[1][ind]-'0');
	
	omp_set_num_threads(n_thrd);
	#pragma omp parallel 
		printf("Hello\n");
	printf("World\n");
	return 0;
}