#include<iostream>
#include<vector>
#include<pthread.h>
#include<assert.h>

struct tdata{int l,r;
	std::vector<std::vector<int>>*a,*b,*c;;
};

void* work_matMul(void *arg){
	tdata *dat=(tdata*)arg;
	std::vector<std::vector<int>> &a=*(dat->a),&b=*(dat->b),&c=*(dat->c);
	for(int i=dat->l;i<dat->r;++i)for(int j=0;j<int(c[i].size());++j)for(int k=0;k<int(a[i].size());++k)c[i][j]+=a[i][k]*b[k][j];
	pthread_exit(NULL);
}

std::vector<std::vector<int>> mat_mult(
		std::vector<std::vector<int>>&a,
		std::vector<std::vector<int>>&b,
		int n_thread=6
		){
	// computo c=a*b
	assert(!b.empty());
	int n=a.size(),m=b.size(),p=b[0].size();
	// a\in R^{nXm} ; b\in R^{mXp} ; c\in R^{nXp} ;
	std::vector<std::vector<int>> c(n,std::vector<int>(p,0));
	
	
	std::vector<pthread_t> thrd(n_thread); std::vector<tdata>dat_thrd(n_thread);
	int prev=0,charge=n/n_thread,extra=n%n_thread;
	for(int i=0;i<n_thread;++i){
		int neo=prev+charge;
		if(extra)--extra,++neo;
		dat_thrd[i]={prev,neo,&a,&b,&c};
		prev=neo;
	}
	for(int i=0;i<n_thread;++i)pthread_create(&thrd[i],NULL,work_matMul,(void*)&dat_thrd[i]);
	for(int i=0;i<n_thread;++i)pthread_join(thrd[i],NULL);
	return c;
}

std::vector<std::vector<int>> read_mat(){
	int n,m;std::cin>>n>>m;
	std::vector<std::vector<int>> mat(n,std::vector<int>(m));
	for(std::vector<int>&rw:mat)for(int&ac:rw)std::cin>>ac;
	return mat;
}



int main(){
	std::vector<std::vector<int>> a=read_mat(),b=read_mat(),c;
	c=mat_mult(a,b);
	
	for(std::vector<int>&rw:c){
		for(int&ac:rw)std::cout << ac << ' ';
		std::cout << '\n';
	}
	
	return 0;
}