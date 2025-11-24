/*
Author: Oscar Vargas Pabon

Input/Output
*/
#include"ecosystem_mod.h"

#include<cassert>
#include<fstream>

// const std::string sim_file="file_sim.txt", log_file="file_log.txt";
// const std::string sim_file, log_file;
// const std::string sim_file, log_file="log_file.txt";

// const std::string sim_file="lin_sim.txt",log_file="lin_log.txt";
// const std::string sim_file="omp_sim.txt",log_file="omp_log.txt";
// const std::string sim_file="loc_sim.txt",log_file="loc_log.txt";
const std::string sim_file="nlc_sim.txt",log_file="nlc_log.txt";


int main(int argc, char *argv[]){
	int GEN_PROC_RABBITS,GEN_PROC_FOXES,GEN_FOOD_FOXES,N_GEN,R,C;
	std::cin>>GEN_PROC_RABBITS>>GEN_PROC_FOXES>>GEN_FOOD_FOXES>>N_GEN>>R>>C;
	Eco mod(R,C,GEN_PROC_RABBITS,GEN_PROC_FOXES,GEN_FOOD_FOXES);
	// reading stuff
	int n;std::cin>>n;++n;assert(n>0);while(--n){
		std::string tp;int x,y;std::cin>>tp>>x>>y;
		mod.place(tp,x,y);
	}
	// doing stuff
	const int off=1; std::ofstream sim_out,log_out; // setting the streams to the files
	std::streambuf* original_cout_buffer = std::cout.rdbuf(),*original_cerr_buffer=std::cerr.rdbuf();
	
	if(!sim_file.empty()) sim_out=std::ofstream(sim_file), std::cout.rdbuf(sim_out.rdbuf());
	if(!log_file.empty()) log_out=std::ofstream(log_file), std::cerr.rdbuf(log_out.rdbuf());
	
	auto take_time=[&](){return std::chrono::high_resolution_clock::now();};
	auto get_durat=[&](const auto start){ return std::chrono::duration_cast<std::chrono::milliseconds>(take_time() - start).count();};
	auto start_time=take_time();
	mod.simulate(N_GEN); // execute
	auto tot_time=get_durat(start_time);
	
	// to reset the streams
	if(!sim_file.empty()) std::cout.rdbuf(original_cout_buffer), sim_out.flush(), sim_out.close();
	if(!log_file.empty()) std::cerr.rdbuf(original_cerr_buffer), log_out.flush(), log_out.close();
	
	// Now printing the last state of the program
	std::cerr << "Total time(counting I/O stuff) " << tot_time << '\n';
	
	std::cout << GEN_PROC_RABBITS << ' ' << GEN_PROC_FOXES << ' ' << GEN_FOOD_FOXES;
	std::cout << " 0 " << R << ' ' << C << ' '; // already known information
	
	std::vector<std::vector<int>> elem;
	for(int i=0;i<R;++i)for(int j=0;j<C;++j)for(int eid:{ROCK,RABBIT,FOX})if(mod.grid[i][j]==eid){
		elem.push_back({i,j,eid});
	}
	
	std::cout << elem.size() << '\n'; // print elements
	for(const std::vector<int> &ac:elem) std::cout << ievent[ac[2]] << ' ' << ac[0] << ' ' << ac[1] << '\n';
	
	return 0;
}