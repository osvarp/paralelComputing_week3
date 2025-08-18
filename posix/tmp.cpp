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
	int res;

	int the_pipe[2]; pipe(the_pipe);
	
	pid_t p1 = fork();
	if ( p1 == 0 ){
		// res = sum_arr( arr, n/2 );
		res=1;
		write(the_pipe[1], &res, 1 );

		exit(0);
	} else {
		res=0;
		// res = sum_arr( arr+n/2, n-n/2 );
		wait(NULL);
	}
	int buf;
	read(the_pipe[0], &buf, 1 );

	std::cout << "parent calc: " << res << " _child calc: " << buf << std::endl;
	close(the_pipe[0]); close(the_pipe[1]);
	res += buf;

	std::cout << "total: " << res << std::endl;
	delete arr;

	return 0;
}
