#include<stdio.h>
int main(){
	// pone primero Line 1. luego Line 2.
	printf("Line 1 ..\n");
	// fflush(stdout);
	// el fflush hace que se vacie el buffer del stdout antes de la
	// linea del write. Esto hace que escriba al archivo justo entre
	// estas dos lineas
	write(1,"Line 2 \n",7);
	
	return 0;
}