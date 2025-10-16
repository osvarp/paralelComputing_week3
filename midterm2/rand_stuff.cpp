/*
Fecha: 10/10/2025
Autor: Oscar Vargas Pabon

Para mis pruebas
*/
#include"rand_stuff.h"
Generator::Generator():Generator(std::chrono::steady_clock::now().time_since_epoch().count()) {};
Generator::Generator(int seed){
	sd=seed;rng=std::mt19937(seed);
}

#include<functional>
#include<assert.h>
//#include<iostream>
bool is_perm(const std::vector<int> &p){
	std::vector<int> fq(p.size(),0);
	for(int ac:p)if(ac>=0&&ac<int(p.size()))++fq[ac];
	bool rs=1;for(int ac:fq)rs=rs&&ac;
	return rs;
}

std::vector<int> Generator::gen(int sz){
	std::vector<int> bit(sz+1,0);
	std::function<void(int,int)> b_upd=[&](int x,int vl){
		for(;x<=sz;x+=x&(-x))bit[x]+=vl;
	};
	std::function<int(int)> b_qu=[&](int x){
		int res=0;for(;x;x-=x&(-x))res+=bit[x];
		return res;
	};
	int lgi=1;while((1<<lgi)<=sz)++lgi;//lgi:=\lfloor log_2(sz)\rfloor
	std::function<int(int)> binlift=[&](int obj){
		// https://codeforces.com/blog/entry/61364
		//O(lg n)
		int ind=0;for(int e=lgi;e>=0;--e){

			int neo=ind+(1<<e);
			//std::cout << lgi<<" ____ "<< obj << "; " << neo << "???" <<ind << std::endl;
			if(neo<=sz&&bit[neo]<obj)obj-=bit[neo],ind=neo;
		}
		return ind+1;
	};
	for(int i=0;i<sz;++i)b_upd(i+1,1);
	std::vector<int> res(sz);for(int i=0;i<sz;++i){
		int spc=sz-i; int chs=rng()%spc;
		res[i]=binlift(chs+1);
		//std::cout<< b_qu(res[i]) << " _ " << b_qu(res[i]-1) << std::endl;
		//std::cout <<i<<"-> "<<spc << " ; " << chs << "- > "<<res[i]<<std::endl;
		b_upd(res[i],-1);
		--res[i];
	}
	assert(is_perm(res));
	return res;
}


int Generator::get_seed(){return sd;}
