/*
Autor: Oscar Vargas Pabon
*/
#include "../map_pgm.h"
#include<functional>

pgmMap::pgmMap():width(0),height(0) {};
pgmMap::pgmMap(const std::vector<std::vector<int>> &omp,int omax_color):mp(omp),max_color(omax_color){
	this->height=omp.size();
	this->width=(omp.empty())?0:omp[0].size();
}
void pgmMap::read_from( FILE*fin ) {
		std::function<int()> read_int=[&fin](){
		int res=0; char t; bool blk=0,fnd=0;
		do {
			t=getc(fin);
			if( t=='\n' ) blk=0;
			else if(blk)continue;
			if('0'<=t&&t<='9'){
				res=res*10+ (t-'0');
				fnd=1;
			}
		} while( !fnd||(t!=' '&&t!='\n'&&t!='	'));
		return res;
	};
	this->width=read_int(); this->height=read_int();
	this->max_color=read_int();
	this->mp=std::vector<std::vector<int>>(this->height,std::vector<int>(this->width));
	for(std::vector<int>&rw:this->mp)for(int &act:rw)act=read_int();
}
void pgmMap::write_to(FILE*fout) {
  (void) fprintf(fout, "%d %d\n%d\n", this->width, this->height, this->max_color);
  for(const std::vector<int> &rw:this->mp)for(int vl:rw)fprintf(fout, "%d\n", vl);
}

pgmMap* pgmMap::apply_kernel( Kernel *krnl ) {
	pgmMap *blr = new pgmMap(this->mp,this->max_color);
	for(int i=0;i<this->height;++i)for(int j=0;j<this->width;++j) {
		krnl->init();
		for(int mx=-krnl->step;mx<=krnl->step;++mx)for(int my=-krnl->step;my<=krnl->step;++my){
			int ni=i+mx,nj=j+my;
			if(ni>=0&&nj>=0&&ni<this->height&&nj<this->width){
				krnl->add(mx+krnl->step,my+krnl->step,this->mp[ni][nj]);
			} else krnl->neut(mx+krnl->step,my+krnl->step);
		}
		blr->mp[i][j]=krnl->calculate();
	}
	return blr;
}