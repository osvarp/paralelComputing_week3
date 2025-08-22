#include<iostream>
#include<vector>
#include<pthread.h>

struct tdata{int l,r,*res; std::vector<int>*arr;pthread_mutex_t *mutex;};

void *work_adder(void *arg){
	tdata *dat=(tdata*)arg;
	int rs=0;for(int i=dat->l;i<dat->r;++i)rs+=(*dat->arr)[i];
	pthread_mutex_lock(dat->mutex);
	(*dat->res)+=rs;
	pthread_mutex_unlock(dat->mutex);
	pthread_exit(NULL);
}

int adder(std::vector<int>&arr,int n_thread=6){
	pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;
	int res=0;
	std::vector<pthread_t> thrd(n_thread);
	std::vector<tdata>dat_thrd(n_thread);
	
	int prev=0,charge=int(arr.size())/n_thread,extra=int(arr.size())%n_thread;
	for(tdata&act:dat_thrd){
		int r=prev+charge;
		if(extra)++r,--extra;
		act={prev,r,&res,&arr,&my_mutex};
		prev=r;
	}
	for(int i=0;i<n_thread;++i)pthread_create(&thrd[i],NULL,work_adder,(void*)&dat_thrd[i]);
	for(int i=0;i<n_thread;++i)pthread_join(thrd[i],NULL);
	pthread_mutex_destroy(&my_mutex);
	return res;
}

int main(){
	int n; std::cin>>n;
	std::vector<int> arr(n);
	for(int&act:arr)std::cin>>act;
	
	int res=adder(arr);
	std::cout << "Respuesta <"<<res<<">(pthread)\n";
	return 0;
}