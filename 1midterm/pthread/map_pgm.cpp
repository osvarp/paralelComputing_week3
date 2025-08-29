/*
Autor: Oscar Vargas Pabon
*/
#include "../map_pgm.h"
#include<functional>
#include<pthread.h>

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


// APPLY KERNEL STUFF
struct tdata{ std::vector<std::vector<int>> *ori,*blur; Kernel*krnl; int l,r,u,d; };
void*worker_apply_kernel(void *arg){
	tdata *dat=(tdata*)arg;
	Kernel *krnl=new Kernel; *krnl=*dat->krnl;
	for(int i=dat->u;i<dat->d;++i)for(int j=dat->l;j<dat->r;++j){
		krnl->init();
		for(int mx=-krnl->step;mx<=krnl->step;++mx)for(int my=-krnl->step;my<=krnl->step;++my){
			int ni=i+mx,nj=j+my;
			if(ni>=0&&nj>=0&&ni<int((*dat->ori).size())&&nj<int((*dat->ori)[ni].size())) {
				krnl->add(mx+krnl->step,my+krnl->step,(*dat->ori)[ni][nj]);
			} else krnl->neut(mx+krnl->step,my+krnl->step);
		}
		(*dat->blur)[i][j]=krnl->calculate();

	}

	delete krnl; pthread_exit(NULL);
}


pgmMap* pgmMap::apply_kernel( Kernel *krnl ) {
	pgmMap *blr = new pgmMap(this->mp,this->max_color);
	std::vector<std::vector<pthread_t>> pth(2,std::vector<pthread_t>(2));
	std::vector<std::vector<tdata>> pdt(2,std::vector<tdata>(2));
	int wmd=this->width/2,hmd=this->height/2;
	for(int i=0;i<2;++i)for(int j=0;j<2;++j){
		pdt[i][j]={&this->mp,&blr->mp,krnl,(j)?wmd:0,(j)?this->width:wmd,(i)?hmd:0,(i)?this->height:hmd};
		pthread_create(&pth[i][j],NULL,worker_apply_kernel,(void*)&pdt[i][j]);
	}
	for(int i=0;i<2;++i)for(int j=0;j<2;++j)pthread_join(pth[i][j],NULL);
	return blr;
}
