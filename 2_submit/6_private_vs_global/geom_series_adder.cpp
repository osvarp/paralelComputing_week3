#include<stdio.h>
#include<string.h>
#include<omp.h>
#include<functional>

int wrong_adder( int n, int n_thread ){
	//calculates \sum_{i=0}^{n}i using openmp and n_thread paralel threads
	int res=0;
	omp_set_num_threads(n_thread);
	#pragma omp parallel for private(res)
	for(int i = 0 ; i <= n ; ++i ) res += i;
	
	return res;
}
int true_adder(int n){return (n*(n+1))/2;}

int thrd_val[]={2,4,8,32,64},thrd_am=5;
int cnt_val[]={10,100,1000},cnt_am=3;

int main(int argc,char *argv[]){
	const int space=10;
	auto print_line=[&](){printf("+");for(int i=0;i<=thrd_am;++i){for(int j=0;j<space;++j)printf("-");printf("+");}printf("\n");};
	
	const int ref=1e3;
	printf("Expectation with %d iterations per element\n",ref);
	
	print_line();//header
	printf("|%*s|",space,"COUNT");
	for(int i=0;i<thrd_am;++i)printf("Thrd=%*d|",space-5,thrd_val[i]);
	printf("\n");
	print_line();
	
	for(int i=0;i<cnt_am;++i){
		printf("|%*d",space,cnt_val[i]);
		for(int j=0;j<thrd_am;++j){
			int bad_cnt=0;
			for(int k=0;k<ref;++k)bad_cnt+=wrong_adder(cnt_val[i],thrd_val[j])!=true_adder(cnt_val[i]);
			double val=double(bad_cnt)/double(ref);
			printf("|%*lf",space,val);
		}
		printf("|\n");
		print_line();
	}
	
	
	return 0;
}