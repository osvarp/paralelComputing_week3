#include<iostream>
#include<vector>
#include<assert.h>
#include<pthread.h>

#include<chrono>
#include<random>

using namespace std;
#define rep(i,strt,end) for(int i=strt;i<int(end);++i)

std::mt19937 mrandom( std::chrono::steady_clock::now().time_since_epoch().count() );


void print_vec(const vector<int> &v ){ rep(i,0,v.size())cout << v[i] << ' ';cout << '\n';}
void print_mat(const vector<vector<int>> &m){rep(i,0,m.size())print_vec(m[i]);}


vector<vector<int>> rcreate(int n,int m){
	vector<vector<int>> mt(n,vector<int>(m));
	rep(i,0,n)rep(j,0,m)mt[i][j]=mrandom()&1;
	return mt;
}



const bool use_pthread=0;

struct tdata{
	vector<vector<int>>*m1,*m2,*res;
	int sign;
};

void *  work_work(void * arg){
	tdata *dat=(tdata*)arg;
	rep(i,0,dat->m1->size())rep(j,0,(*dat->m1)[i].size())(*dat->res)[i][j]=(*dat->m1)[i][j]+(*dat->m2)[i][j]*(dat->sign);
	if(use_pthread)pthread_exit(NULL);
}

int main(){
	int n=1000;
	vector<vector<int>> m1=rcreate(n,n),m2=rcreate(n,n),mad(n,vector<int>(n)),mre(n,vector<int>(n));
	
	pthread_t thrd[2];
	tdata tdat[2];
	tdat[0]={&m1,&m2,&mad,1}; tdat[1]={&m1,&m2,&mre,-1};
	
	if(use_pthread){
		rep(i,0,2)pthread_create(&thrd[i],NULL,work_work,(void*)&tdat[i]);
		rep(i,0,2)pthread_join(thrd[i],NULL);
	} else rep(i,0,2)work_work((void*)&tdat[i]);
	
	// cout <<"m1\n";print_mat(m1);cout <<"m2\n";print_mat(m2);
	// cout << "suma " << endl; print_mat(mad); cout << "resta " << endl; print_mat(mre);

	return 0;
}
