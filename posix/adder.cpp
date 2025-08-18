#include<iostream>
#include<unistd.h>
#include<sys/wait.h>

int sum_arr( int *arr, int n ) {
	int res = 0;
	for ( int i = 0 ; i < n ; ++i ) res += arr[i];
	return res;
}

int main( int argc, char *argv[] ) {
	int n; std::cin >> n;
	int *arr = new int[n];
	for ( int i = 0 ; i < n ; ++i ) std::cin >> arr[i];

	int p_am=n/3;

	int the_pipe[2]; pipe(the_pipe);
	
	int p_wload=n/p_am,p_eload=n%p_am;
	int prev=0;
	
	pid_t *pn = new pid_t[p_am];
	for(int i=0;i<p_am;++i){
		int neo=prev+p_wload;
		if(p_eload)--p_eload,++neo;
		
		pn[i]=fork();
		if(!pn[i]){
			int res=0;for(int i=prev;i<neo;++i)res+=arr[i];
			write(the_pipe[1],&res,1);
			exit(0);
		}
		prev=neo;
	}
	
	wait(NULL); int res=0;
	for(int i=0;i<p_am;++i){
		int buf; read(the_pipe[0],&buf,1);
		res+=buf;
	}
	
	close(the_pipe[0]); close(the_pipe[1]);

	std::cout << "total: " << res << std::endl;
	delete arr; delete pn;

	return 0;
}
