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
	
	// move rabbits
	std::vector<std::vector<int>> rab;
	#pragma omp paralelize for
	for(int i=0;i<n;++i){
	#pragma omp paralelize for
	for(int j=0;j<m;++j)if(grid[i][j]==RABBIT){
			
		std::vector<int> pos;
		for(int mind=0;mind<int(mov.size());++mind){
			int ni=i+mov[mind][SD_CONST],nj=j+mov[mind][SD_CONST^1];
			
			// Note: possible ambiguity on the rules here if the 'unmoved offspring'
			if(ni>=0&&nj>=0&&ni<n&&nj<m&&grid[ni][nj]==NONE) pos.push_back(mind);
		}
		int mind=(pos.empty())?-1:pos[((i+j+iter+IND_CONST)%pos.size() +pos.size())%pos.size()];
		
		#pragma omp critical
		rab.push_back({i,j,proc[i][j]+1,mind});
	}}
	
	#pragma omp paralelize for
	for(const std::vector<int> &a_rab:rab){
		int i=a_rab[0],j=a_rab[1],tproc=a_rab[2],mind=a_rab[3];
		
		if(mind==-1){proc[i][j]=tproc;continue;}//Stupid untold rule
		
		if(tproc>GEN_PROC_RABBITS)tproc=proc[i][j]=0;
		else grid[i][j]=proc[i][j]=NONE;
		
		int ni=i+mov[mind][SD_CONST],nj=j+mov[mind][SD_CONST^1];
		
		#pragma omp critical
		{ // there are surely better ways to ensure paralelism here
		if(grid[ni][nj]==NONE)grid[ni][nj]=RABBIT,proc[ni][nj]=-1;
		if(proc[ni][nj] < tproc ) proc[ni][nj]=tproc;
		}
	}
	
	std::vector<std::vector<int>> foxes; // move foxes
	#pragma omp paralelize for
	for(int i=0;i<n;++i){
	#pragma omp paralelize for	
	for(int j=0;j<m;++j)if(grid[i][j]==FOX){
		int nproc=proc[i][j]+1,nfood=food[i][j]+1;
		
		std::vector<int> pos; bool eating=0;
		for(int mind=0;mind<int(mov.size());++mind){
			int ni=i+mov[mind][SD_CONST],nj=j+mov[mind][SD_CONST^1];
			
			// Note: possible ambiguity on the rules here if the 'unmoved offspring'
			if(ni>=0&&nj>=0&&ni<n&&nj<m&&grid[ni][nj]!=ROCK&&grid[ni][nj]!=FOX){
				if(grid[ni][nj]==RABBIT){
					if(!eating)pos={mind};
					else pos.push_back(mind);
					eating=1;
				}else if(!eating) pos.push_back(mind);
			}
		}
		int mind=(pos.empty())?-1:pos[((i+j+iter+IND_CONST)%pos.size() +pos.size())%pos.size()];
		if(eating)nfood=0; // posible ambiguity here if the fox 'dies before eating'
		
		#pragma omp critical
		foxes.push_back({i,j,nproc,nfood,mind});
	}}
	
	#pragma omp paralelize for
	for(const std::vector<int> &a_fox:foxes){
		int i=a_fox[0],j=a_fox[1],tproc=a_fox[2],tfood=a_fox[3],mind=a_fox[4];
		
		if(mind==-1&&tfood<GEN_FOOD_FOXES){proc[i][j]=tproc;food[i][j]=tfood;continue;}//Stupid untold rule
		
		if(tproc>GEN_PROC_FOXES&&tfood<GEN_FOOD_FOXES)tproc=proc[i][j]=food[i][j]=0;
		else grid[i][j]=proc[i][j]=food[i][j]=NONE;
		
		if(tfood>=GEN_FOOD_FOXES)continue;// possible ambiguity if it 'dies as it bears offspring'
		
		int ni=i+mov[mind][SD_CONST],nj=j+mov[mind][SD_CONST^1];
		
		#pragma omp critical
		{ // there are surely better ways to ensure paralelism here
		if(grid[ni][nj]==NONE||grid[ni][nj]==RABBIT)grid[ni][nj]=FOX,proc[ni][nj]=food[ni][nj]=-1;
		if( proc[ni][nj] < tproc || (proc[ni][nj]==tproc &&food[ni][nj] > tfood ) ) proc[ni][nj]=tproc,food[ni][nj]=tfood;
		}
		
	}
}