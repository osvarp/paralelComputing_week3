/*
Autor: Oscar Vargas Pabon
*/
#include "../map_ppm.h"
#include<functional>

ppmMap::ppmMap():width(0),height(0) {};
void ppmMap::read_from( FILE*fin ) {
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

	std::vector<std::vector<std::vector<int>>> all_lay(3,std::vector<std::vector<int>>(this->height,std::vector<int>(this->width)));
	for(int i=0;i<this->height;++i)for(int j=0;j<this->width;++j)for(int k=0;k<3;++k)all_lay[k][i][j]=read_int();
	for(int i=0;i<3;++i)this->mp[i]=pgmMap(all_lay[i],this->max_color);
}
void ppmMap::write_to(FILE*fout) {
  (void) fprintf(fout, "%d %d\n%d\n", this->width, this->height, this->max_color);
  for(int i=0;i<this->height;++i)for(int j=0;j<this->width;++j)for(int k=0;k<3;++k)fprintf(fout, "%d\n", this->mp[k].mp[i][j]);
}
ppmMap* ppmMap::apply_kernel( Kernel *krnl ) {
	ppmMap *blr = new ppmMap;	*blr=*this;
	for(int i=0;i<3;++i)blr->mp[i]= *this->mp[i].apply_kernel(krnl);
	return blr;
}