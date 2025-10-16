/*
Fecha: 10/10/2025
Autor: Oscar Vargas Pabon

Algoritmos para la act3
*/
#include"table.h"
#include<set>
#include<vector>
#include<utility>
#include<array>
#include<assert.h>
#include<tuple>
#include<omp.h>

int omp_bfs(const Table &strt,int number_of_threads){
	omp_set_num_threads(number_of_threads);

	Table obj;
	{
		std::array<int,2> bnd=strt.get_bnd();
		std::vector<int> ptmp(bnd[0]*bnd[1]);
		for(int i=0;i<int(ptmp.size());++i)ptmp[i]=i;
		obj=Table(bnd,ptmp);
	}
	if(obj==strt)return 0;

	std::set<std::vector<int>> us={strt.get_p()};
	std::vector<Table> act={strt},nxt;

	omp_lock_t set_lock;
    omp_init_lock(&set_lock);

	int cst=0;bool found=0;
	while(!act.empty()&&!found){
		nxt.clear();
		#pragma omp parallel shared(us,nxt,found)
		{
			#pragma omp parallel for
		//for(const Table &ac:act)
		for(int i=0;i<int(act.size());++i){
			Table &ac=act[i];
			if(!found)for(const std::array<int,2> &mv:mov)if(!found){
			Table neo=ac.move(mv);
			if(!us.count(neo.get_p())){
				
				omp_set_lock(&set_lock);
				us.insert(neo.get_p()); nxt.push_back(neo);
				omp_unset_lock(&set_lock);

				if(neo==obj) found=1;
			}
		}}}
		//for(const Table &ac:act)us.erase(ac.get_p());

		++cst; std::swap(nxt,act);
	}

	return (found)?cst:-1;
}

int omp_aStar_1(const Table &strt,int number_of_threads){
	omp_set_num_threads(number_of_threads);

	std::array<int,2> bnd=strt.get_bnd();
	Table obj;
	{
		std::vector<int> ptmp(bnd[0]*bnd[1]);
		for(int i=0;i<int(ptmp.size());++i)ptmp[i]=i;
		obj=Table(bnd,ptmp);
	}
	if(obj==strt)return 0;

	std::set<std::vector<int>> us={strt.get_p()};
	int tope = bnd[0]*bnd[1]+11;
	std::vector<std::vector<std::pair<Table,int>>> pq(tope);
	pq[0]={{strt,0}};

	omp_lock_t set_lock;
    omp_init_lock(&set_lock);

	int am=1,found=-1,ind=0;
	while(am&&found==-1){
		std::vector<std::pair<Table,int>> eq_lev;

		#pragma omp parallel shared(us,eq_lev,pq)
		{
			#pragma omp parallel for
		//for(std::pair<Table,int> &r_ac:pq[ind%tope])
		for(int i=0;i<int(pq[ind%tope].size());++i){
			std::pair<Table,int> &r_ac=pq[ind%tope][i];
			if(found==-1){
			Table &ac=r_ac.first;int a_cst=r_ac.second;
			for(const std::array<int,2> &mv:mov)if(found==-1){
				Table neo=ac.move(mv);
				int n_cst=a_cst+1,over_cst=(bnd[0]*bnd[1]-neo.get_stat()-1);
				{std::array<int,2> init=neo.get_init();if(init[0]==bnd[0]-1&&init[1]==bnd[1]-1)++over_cst;}

				assert(n_cst+over_cst-a_cst<tope);
				assert(n_cst+over_cst>=ind);

				if(!us.count(neo.get_p())){
					#pragma omp atomic
					++am;

					omp_set_lock(&set_lock);
					us.insert(neo.get_p());
					
					if(n_cst+over_cst==ind)eq_lev.push_back({neo,n_cst});
					else pq[(n_cst+over_cst)%tope].push_back({neo,n_cst});
					omp_unset_lock(&set_lock);

					if(neo==obj)found=n_cst;
				}
			}
		}}}
		am-=pq[ind%tope].size();
		//for(const std::pair<Table,int> r_ac:pq[ind%tope])us.erase(r_ac.first.get_p());
		pq[ind%tope].clear();
		if(eq_lev.empty())++ind;
		else swap(pq[ind%tope],eq_lev);
	}

	return found;
}

int omp_aStar_2(const Table &strt,int number_of_threads){
	omp_set_num_threads(number_of_threads);

	std::array<int,2> bnd=strt.get_bnd();
	Table obj;
	{
		std::vector<int> ptmp(bnd[0]*bnd[1]);
		for(int i=0;i<int(ptmp.size());++i)ptmp[i]=i;
		obj=Table(bnd,ptmp);
	}
	if(obj==strt)return 0;

	std::set<std::vector<int>> us={strt.get_p()};
	int tope = bnd[0]*bnd[1]*(bnd[0]+bnd[1])+11;
	std::vector<std::vector<std::pair<Table,int>>> pq(tope);
	pq[0]={{strt,0}};

	omp_lock_t set_lock;
    omp_init_lock(&set_lock);

	int am=1,found=-1,ind=0;
	while(am&&found==-1){
		std::vector<std::pair<Table,int>> eq_lev;
		#pragma omp parallel shared(us,eq_lev,pq)
		{
			#pragma omp parallel for
		//for(std::pair<Table,int> &r_ac:pq[ind%tope])
		for(int i=0;i<int(pq[ind%tope].size());++i){
			std::pair<Table,int> &r_ac=pq[ind%tope][i];
			if(found==-1){
			Table &ac=r_ac.first;int a_cst=r_ac.second;
			for(const std::array<int,2> &mv:mov)if(found==-1){
				Table neo=ac.move(mv);
				int n_cst=a_cst+1,over_cst=neo.get_sm_dst();
				over_cst-=Table::manh_dst(neo.get_init(),{bnd[0]-1,bnd[1]-1});

				//std::cout << n_cst<<"_"<<over_cst<<"____"<<a_cst<<"<->"<<ind<<std::endl;
				assert(n_cst+over_cst-a_cst<tope);
				assert(n_cst+over_cst>=ind);

				if(!us.count(neo.get_p())){
					#pragma omp atomic
					++am;

					omp_set_lock(&set_lock);
					us.insert(neo.get_p());
					
					if(n_cst+over_cst==ind)eq_lev.push_back({neo,n_cst});
					else pq[(n_cst+over_cst)%tope].push_back({neo,n_cst});
					omp_unset_lock(&set_lock);

					if(neo==obj)found=n_cst;
				}
			}
		}}}
		am-=pq[ind%tope].size();
		//for(const std::pair<Table,int> r_ac:pq[ind%tope])us.erase(r_ac.first.get_p());
		pq[ind%tope].clear();
		if(eq_lev.empty())++ind;
		else swap(pq[ind%tope],eq_lev);
	}

	return found;
}
