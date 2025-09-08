#include<stdio.h>
#include<omp.h>

int main(int argc,char *argv[]){
	int n_thrd=0;
	for(int ind=0;argv[1][ind]!='\0';++ind)n_thrd=n_thrd*10+(argv[1][ind]-'0');
	
	const int n_loop=16;
	
	omp_set_num_threads(n_thrd);
	#pragma omp parallel for
	for(int i = 0 ; i < n_loop ; ++i) printf("Hello I'm thread <%d>, running my routine iteration <%d>\n",omp_get_thread_num(),i);
	printf("World ending by pollution of ants\n");
	return 0;
}