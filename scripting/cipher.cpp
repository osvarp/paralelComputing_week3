#include <stdio.h>

char shift( char chr, int shf ){
	const int mod=('z'-'a'+1);
	char res=chr;
	if( 'a'<=chr && chr<='z' )res=((res-'a'+shf)%mod+mod)%mod+'a';
	else if ( 'A'<=chr && chr <= 'Z')res=((res-'A'+shf)%mod+mod)%mod+'A';
	return res;
}
void crypt(int shf){
	char act=getc(stdin);
	while(act!=EOF){
		putc(shift(act,shf),stdout);
		act=getc(stdin);
	}
}

int main(){
	//llaves positivas son encriptar, negativas desencriptar
	
	//Zú iolxgju Ikygx, latioutg! [6]
	int k;scanf("%d",&k);
	crypt(k);
	return 0;
}