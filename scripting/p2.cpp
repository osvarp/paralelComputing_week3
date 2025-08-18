#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<wait.h>

int main(){
	int pid; int i;
	for(i=0;i<3;++i){
		if( (pid=fork()) < 0 ) printf("Sorry...can't fork\n");
		else if(pid==0)printf("Child %d\n",i);
		else {
			// wait(nullptr);
			printf("Parent %d\n",i);
		}
	}
	exit(0);
	return 0;
}