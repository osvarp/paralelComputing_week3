/*
Fecha: 10/10/2025
Autor: Oscar Vargas Pabon

Algoritmos para la act2
*/
#include"table.h"
#include<set>
#include<vector>
#include<utility>
#include<array>
#include<assert.h>
#include<tuple>

const std::vector<std::array<int,2>> mov={{-1,0},{1,0},{0,-1},{0,1}};

int bfs(const Table &strt){
	Table obj;
	{
		std::array<int,2> bnd=strt.get_bnd();
		std::vector<int> ptmp(bnd[0]*bnd[1]);
		for(int i=0;i<int(ptmp.size());++i)ptmp[i]=i;
		obj=Table(bnd,ptmp);
	}
	if(obj==strt)return 0;

	std::set<Table> us={strt};
	std::vector<Table> act={strt},nxt;
	int cst=0;bool found=0;
	while(!act.empty()&&!found){
		nxt.clear();
		for(const Table &ac:act)if(!found)for(const std::array<int,2> &mv:mov)if(!found){
			Table neo=ac.move(mv);
			if(!us.count(neo)){
				us.insert(neo);nxt.push_back(neo);
				if(neo==obj)found=1;
			}
		}

		++cst; std::swap(nxt,act);
	}

	return (found)?cst:-1;
}

int aStar_1(const Table &strt){
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

	int am=1,found=-1,ind=0;
	while(am&&found==-1){
		std::vector<std::pair<Table,int>> eq_lev;
		for(std::pair<Table,int> &r_ac:pq[ind%tope])if(found==-1){
			Table &ac=r_ac.first;int a_cst=r_ac.second;
			for(const std::array<int,2> &mv:mov)if(found==-1){
				Table neo=ac.move(mv);
				int n_cst=a_cst+1,over_cst=(bnd[0]*bnd[1]-neo.get_stat()-1);
				{std::array<int,2> init=neo.get_init();if(init[0]==bnd[0]-1&&init[1]==bnd[1]-1)++over_cst;}

				assert(n_cst+over_cst-a_cst<tope);
				assert(n_cst+over_cst>=ind);

				if(!us.count(neo.get_p())){
					us.insert(neo.get_p());++am;
					
					if(n_cst+over_cst==ind)eq_lev.push_back({neo,n_cst});
					else pq[(n_cst+over_cst)%tope].push_back({neo,n_cst});

					if(neo==obj)found=n_cst;
				}
			}
		}
		am-=pq[ind%tope].size();
		pq[ind%tope].clear();
		if(eq_lev.empty())++ind;
		else swap(pq[ind%tope],eq_lev);
	}

	return found;
}

int aStar_2(const Table &strt){
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

	int am=1,found=-1,ind=0;
	while(am&&found==-1){
		std::vector<std::pair<Table,int>> eq_lev;
		for(std::pair<Table,int> &r_ac:pq[ind%tope])if(found==-1){
			Table &ac=r_ac.first;int a_cst=r_ac.second;
			for(const std::array<int,2> &mv:mov)if(found==-1){
				Table neo=ac.move(mv);
				int n_cst=a_cst+1,over_cst=neo.get_sm_dst();
				over_cst-=Table::manh_dst(neo.get_init(),{bnd[0]-1,bnd[1]-1});

				//std::cout << n_cst<<"_"<<over_cst<<"____"<<a_cst<<"<->"<<ind<<std::endl;
				assert(n_cst+over_cst-a_cst<tope);
				assert(n_cst+over_cst>=ind);

				if(!us.count(neo.get_p())){
					us.insert(neo.get_p());++am;
					
					if(n_cst+over_cst==ind)eq_lev.push_back({neo,n_cst});
					else pq[(n_cst+over_cst)%tope].push_back({neo,n_cst});

					if(neo==obj)found=n_cst;
				}
			}
		}
		am-=pq[ind%tope].size();
		pq[ind%tope].clear();
		if(eq_lev.empty())++ind;
		else swap(pq[ind%tope],eq_lev);
	}

	return found;
}