/*
Autor:Oscar Vargas Pabon
*/
#include<vector>
#include<omp.h>
int bst_lin(const std::vector<int> &vec,int obj){
	int l=0,r=vec.size()-1;
	while(l<=r){
		int m=(l+r)/2;
		if(vec[m]==obj)return m;
		else if(vec[m]>obj)r=m-1;
		else l=m+1;
	}
	return -1;
}

int bst_omp(const std::vector<int> &vec,int obj){
	int l=0,r=vec.size()-1,res=-1;
	int n_thr=2;
	// int n_thr=omp_get_num_procs();
	omp_set_num_threads(n_thr);
	while(l<=r&&res==-1){
		// std::cout << l << " _ " << r << "!=== " << obj << std::endl;
		int part=(r-l+1)/n_thr,ex=(r-l+1)%n_thr;
		int wl=-1,wr=-1;
		#pragma omp parallel 
		{
			int tid=omp_get_thread_num();
			int ll=(tid<=ex)?(part+1)*tid:part*tid+ex;
			int rr=ll+part+(tid<ex);
			if(rr-ll>1){
				// #pragma omp critical
				// std::cout << tid << " ???? " << ll << " _ " << rr << std::endl;
				if(vec[ll]==obj)res=ll;
				else if(vec[rr-1]==obj)res=rr-1;
				else if(vec[ll]<obj&&obj<vec[rr-1])wl=ll,wr=rr;
			}
		}
		l=wl,r=wr;
	}
	return res;
}