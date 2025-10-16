/*
Autor:Oscar Vargas Pabon 12/10/2025


actividad 4
g++ -fopenmp actividad4.cpp pretty_io.cpp rand_stuff.cpp table.cpp -o act4.out
*/
#include<chrono>
#include<vector>
#include<new>
#include<assert.h>
#include<functional>
#include<tuple>

#include"seq_search.cpp"
#include"omp_search.cpp"

#include"pretty_io.h"
#include"rand_stuff.h"
#include"table.h"

const std::vector<int> cores={2,4,8};

const int dist_algo=3;
int (*seq_fun[])(const Table&)={bfs,aStar_1,aStar_2};
int (*omp_fun[])(const Table&,int)={omp_bfs,omp_aStar_1,omp_aStar_2};


int main(int argc,char *argv[]){
	auto get_time=[&](){return std::chrono::steady_clock::now();};
	auto get_int=[](char cad[]){
		int res=0;for(int i=0;cad[i]!='\0';++i){
			assert(cad[i]>='0'&&cad[i]<='9');
			res=res*10+(cad[i]-'0');
		}
		return res;
	};

	int type=0,seed=-1,the_size=3;
	if(argc>1)type=get_int(argv[1]);
	if(argc>2)the_size=get_int(argv[2]);
	if(argc>3)seed=get_int(argv[3]);

	std::function<std::pair<long long,int>(int,const Table&)> ask_seq=[&](int ind,const Table&tbl){
		long long tm=0; int val=-1;
		try{
			auto t_init=get_time();
			val=seq_fun[ind](tbl);
			tm=(get_time()-t_init).count();
		} catch (const std::bad_alloc&e){
			//para evitar errores cuando falla
			tm=val=-1;
		}
		return std::make_pair(tm,val);
	};
	std::function<std::pair<long long,int>(int,const Table&,int)> ask_omp=[&](int ind,const Table&tbl,int nthr){
		long long tm=0; int val=-1;
		try{
			auto t_init=get_time();
			val=omp_fun[ind](tbl,nthr);
			tm=(get_time()-t_init).count();
		} catch (const std::bad_alloc&e){
			//para evitar errores cuando falla
			tm=val=-1;
		}
		return std::make_pair(tm,val);
	};

	if(type==0){
		// Leo de stdin los tableros de tamaño 8X8
		const std::array<int,2> dim={4,4};
		Table tbl = read_table(dim);
		
		std::cout<<"Answer format (<time in miliseconds>,<answer>)"<<std::endl;
		std::cout<<"Alg order:\n1. BFS | 2. A*_1 | 3. A*_2 | <- SEQ"<<std::endl;
		std::cout<<"4. BFS | 5. A*_1 | 6. A*_2 | <- OMP\n\n"<<std::endl;

		int ind=0; const int cr=8;
		while(tbl.get_bnd()[0]!=-1){
			//std::cout<< tbl.to_str() << std::endl;
			std::vector<std::pair<long long,int>> r1,r2;
			for(int i=0;i<dist_algo;++i) r1.push_back(ask_seq(i,tbl));
			for(int i=0;i<dist_algo;++i) r2.push_back((r1[i].first==1ll)?r1[i]:ask_omp(i,tbl,cr));
			
			std::cout<<"["<<ind++<<"]"<<std::endl;
			for(std::pair<long long,int> &ac:r1)
				std::cout<<" ("<<ac.first<<";"<<ac.second<<")";
			std::cout<<std::endl;
			for(std::pair<long long,int> &ac:r2)
				std::cout<<" ("<<ac.first<<";"<<ac.second<<")";
			std::cout<<std::endl;

			tbl = read_table(dim);
		}

	} else {
		// Genero 'type' tableros pseudo aleatorios
		// Y comparo por sizes y cores entre todos
		// los algoritmos
		int sz=the_size;
		Generator gn=(argc>3)?Generator(seed):Generator();
		std::cout<<"Working with seed <"<<gn.get_seed()<<"> and size <"<<sz<<"X"<<sz<<">.\n\n";
		
		std::vector<std::vector<double>> sped(dist_algo,std::vector<double>(cores.size(),0.0));
		std::vector<int> ok(dist_algo,0);
		std::function<double(long long,long long)> a_sped=[](long long seq,long long paral){
			return double(seq)/double(paral);
		};

		for(int am=0;am<type;++am){
			//std::cout<<"doing the " << am << std::endl;
			Table tbl({sz,sz},gn.gen(sz*sz));
			for(int alg=0;alg<dist_algo;++alg){
				long long tm;int vl;std::tie(tm,vl)=ask_seq(alg,tbl);
				if(tm==-1ll)continue;
				++ok[alg];
				for(int cr=0;cr<int(cores.size());++cr){
					long long tm2;int vl2;std::tie(tm2,vl2)=ask_omp(alg,tbl,cores[cr]);
					if(tm2!=-1ll)assert(vl2==vl);
					else {std::cerr<<"XDXDXD fallo esto\n";continue;}
					sped[alg][cr]+=a_sped(tm,tm2);
				}
			}
		}
		for(int alg=0;alg<dist_algo;++alg)for(int cr=0;cr<int(cores.size());++cr){
			if(ok[alg])sped[alg][cr]/=double(ok[alg]);
		} 

		std::cout<<"Answer format [finished amount] <avg.speedup core1> ... <avg.speedup corei>"<<std::endl;
		std::cout<<"Alg order:\n1. BFS | 2. A*_1 | 3. A*_2 | <- SEQ"<<std::endl;
		std::cout<<"4. BFS | 5. A*_1 | 6. A*_2 | <- OMP"<<std::endl;

		for(int alg=0;alg<dist_algo;++alg){
			std::cout<<"["<<ok[alg]<<"]";
			for(int cr=0;cr<int(cores.size());++cr)std::cout<<" "<<sped[alg][cr];
			std::cout<<std::endl;
		}

		
	}

	return 0;
}