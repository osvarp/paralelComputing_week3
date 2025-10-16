#include "plate.h"
#include <omp.h>

std::vector<std::vector<double>> simul( int n, int m, std::array<int,2> init ){
	const double neut=0,src=1,EPS=0.1;
	std::vector<std::vector<double>> plt(n,std::vector<double>(m,neut)),neo(n,std::vector<double>(m));
	plt[init[0]][init[1]]=src;
	
	bool conv=0;
	while(!conv){
		conv=1;
		#pragma omp parallel
		{
			#pragma omp for
		for(int i=0;i<n;++i){
			#pragma omp parallel
			{
				#pragma omp for
			for(int j=0;j<m;++j){
				double inc=neut;
				
				for(const std::array<int,2> &mv:mov){
					int ni=i+mv[0],nj=j+mv[1];
					if(ni>=0&&nj>=0&&ni<n&&nj<m)inc+=plt[ni][nj];
					else inc+=neut;
				}
				neo[i][j]= (4*plt[i][j]+inc)/8;
				
				#pragma omp atomic
				conv=conv&& abs(plt[i][j]-inc/4)<=EPS;
			}
			}
		}
		}
		neo[init[0]][init[1]]=src;
		swap(plt,neo);
	}
	return plt;
}