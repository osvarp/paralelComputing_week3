/*
Author:Oscar Vargas Pabon

OMP version. Tested with the 20X20 case
*/
#include"ecosystem_mod.h"
#include<omp.h>

void Eco::simulate_1_step(int iter){
	// constants and stuff
	const int n=grid.size(),m=grid[0].size();
	std::vector<std::vector<int>> &proc=attrib[0],&food=attrib[1];
	
	static const int IND_CONST=-1,SD_CONST=0;
	static const std::vector<std::vector<int>> mov={{-1,0},{0,1},{1,0},{0,-1}};
	
	std::vector<std::vector<std::vector<int>>> animal(n,std::vector<std::vector<int>>(m));
	std::vector<std::vector<bool>> vis(n,std::vector<bool>(m,0));
	
	// move rabbits
	std::vector<std::vector<std::vector<int>>> rab=animal;
	#pragma omp paralelize for
	for(int i=0;i<n;++i){
	#pragma omp paralelize for
	for(int j=0;j<m;++j)if(grid[i][j]==RABBIT){
		
		std::vector<int> pos; vis[i][j]=1;
		for(int mind=0;mind<int(mov.size());++mind){
			int ni=i+mov[mind][SD_CONST],nj=j+mov[mind][SD_CONST^1];
			
			// Note: possible ambiguity on the rules here if the 'unmoved offspring'
			if(ni>=0&&nj>=0&&ni<n&&nj<m&&grid[ni][nj]==NONE) pos.push_back(mind),vis[ni][nj]=1;
		}
		int mind=(pos.empty())?-1:pos[((i+j+iter+IND_CONST)%pos.size() +pos.size())%pos.size()];
		
		rab[i][j]={proc[i][j]+1,mind};
	}}
	
	#pragma omp paralelize for
	for(int i=0;i<n;++i){
	#pragma omp paralelize for
	for(int j=0;j<m;++j)if(vis[i][j]){
		vis[i][j]=0;
		if(!rab[i][j].empty()){
			std::vector<int> &a_rab=rab[i][j];
			int tproc=a_rab[0],mind=a_rab[1];
		
			if(mind==-1){proc[i][j]=tproc;continue;}//Stupid untold rule
		
			if(tproc>GEN_PROC_RABBITS)tproc=proc[i][j]=0;
			else grid[i][j]=proc[i][j]=NONE;
		}
		
		for(const std::vector<int> &mv:mov ){
			int ni=i+mv[SD_CONST],nj=j+mv[SD_CONST^1];
			if(ni<0||nj<0||ni>=n||nj>=m||rab[ni][nj].empty()||rab[ni][nj][1]==-1)continue;
			std::vector<int> &a_rab=rab[ni][nj];
			int tproc=a_rab[0],mind=a_rab[1];if(tproc>GEN_PROC_RABBITS)tproc=0;
			int nni=ni+mov[mind][SD_CONST],nnj=nj+mov[mind][SD_CONST^1];
			if(nni==i&&nnj==j){
				
				if(grid[i][j]==NONE)grid[i][j]=RABBIT,proc[i][j]=-1;
				if(proc[i][j] < tproc ) proc[i][j]=tproc;
			}
		}
	}}
	
	
	std::vector<std::vector<std::vector<int>>> &foxes=animal;// move foxes
	#pragma omp paralelize for
	for(int i=0;i<n;++i){
	#pragma omp paralelize for	
	for(int j=0;j<m;++j)if(grid[i][j]==FOX){
		int nproc=proc[i][j]+1,nfood=food[i][j]+1;
		
		std::vector<int> pos; bool eating=0; vis[i][j]=1;
		for(int mind=0;mind<int(mov.size());++mind){
			int ni=i+mov[mind][SD_CONST],nj=j+mov[mind][SD_CONST^1];
			
			// Note: possible ambiguity on the rules here if the 'unmoved offspring'
			if(ni>=0&&nj>=0&&ni<n&&nj<m&&grid[ni][nj]!=ROCK&&grid[ni][nj]!=FOX){
				vis[ni][nj]=1;
				if(grid[ni][nj]==RABBIT){
					if(!eating)pos={mind};
					else pos.push_back(mind);
					eating=1;
				}else if(!eating) pos.push_back(mind);
			}
		}
		int mind=(pos.empty())?-1:pos[((i+j+iter+IND_CONST)%pos.size() +pos.size())%pos.size()];
		if(eating)nfood=0; // posible ambiguity here if the fox 'dies before eating'
		
		
		foxes[i][j]={nproc,nfood,mind};
	}}
	
	#pragma omp paralelize for
	for(int i=0;i<n;++i){
	#pragma omp paralelize for
	for(int j=0;j<m;++j)if(vis[i][j]){
		vis[i][j]=0;
		if(!foxes[i][j].empty()){
			std::vector<int> &a_fox=foxes[i][j];
			int tproc=a_fox[0],tfood=a_fox[1],mind=a_fox[2];
			
			if(mind==-1&&tfood<GEN_FOOD_FOXES){proc[i][j]=tproc;food[i][j]=tfood;continue;}//Stupid untold rule
			
			if(tproc>GEN_PROC_FOXES&&tfood<GEN_FOOD_FOXES)tproc=proc[i][j]=food[i][j]=0;
			else grid[i][j]=proc[i][j]=food[i][j]=NONE;
			
			if(tfood>=GEN_FOOD_FOXES)continue;// possible ambiguity if it 'dies as it bears offspring'
		}
		
		for(const std::vector<int> &mv:mov ){
			int ni=i+mv[SD_CONST],nj=j+mv[SD_CONST^1];
			if(ni<0||nj<0||ni>=n||nj>=m||foxes[ni][nj].empty()||foxes[ni][nj][2]==-1)continue;
			
			std::vector<int> &a_fox=foxes[ni][nj];
			int tproc=a_fox[0],tfood=a_fox[1],mind=a_fox[2];if(tproc>GEN_PROC_FOXES)tproc=0;
			int nni=ni+mov[mind][SD_CONST],nnj=nj+mov[mind][SD_CONST^1];
			if(nni==i&&nnj==j&&tfood<GEN_FOOD_FOXES){
				if(grid[i][j]==NONE||grid[i][j]==RABBIT)grid[i][j]=FOX,proc[i][j]=food[i][j]=-1;
				if( proc[i][j] < tproc || (proc[i][j]==tproc &&food[i][j] > tfood ) ) proc[i][j]=tproc,food[i][j]=tfood;
			}
		}
	}}
}