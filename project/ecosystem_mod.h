/*
Author:Oscar Vargas Pabon

I implemented everything except for Eco::simulate_1_step, as this is the code to be
	rewritten once I start parallelizing stuff
*/
#ifndef ECOSYSTEM_MOD_H
#define ECOSYSTEM_MOD_H

#include<vector>
#include<map>
#include<stdexcept>
#include<iostream>

#include<iostream>

#include<chrono>
#include<functional>

const int RABBIT=0,FOX=1,ROCK=2,NONE=3;
const std::map<std::string,int> event={ {"ROCK",ROCK},{"RABBIT",RABBIT},{"FOX",FOX},{"NONE",NONE} };
const std::vector<std::string> ievent={"RABBIT","FOX","ROCK","NONE"};
const std::vector<char> image={'R','F','*',' '};
const std::vector<int> attribute={1,2|1,0,0}; const int N_ATTRIB=2; // 1->procreation ; 2 -> food ;
// const std::vector<std::string> attribute_name={"PROC","FOOD"}; // not needed

class Eco{
private:
	void simulate_1_step(int iter); // the one my parallelism will overwrite
public:
	
	int GEN_PROC_RABBITS,GEN_PROC_FOXES,GEN_FOOD_FOXES;
	std::vector<std::vector<int>> grid;
	std::vector<std::vector<std::vector<int>>> attrib;
	
	Eco()=default; // constructor world
	Eco(int R,int C,int GEN_PROC_RABBITS,int GEN_PROC_FOXES,int GEN_FOOD_FOXES):
	GEN_PROC_RABBITS(GEN_PROC_RABBITS),GEN_PROC_FOXES(GEN_PROC_FOXES),GEN_FOOD_FOXES(GEN_FOOD_FOXES){
		grid=std::vector<std::vector<int>>(R,std::vector<int>(C,NONE));
		attrib=std::vector<std::vector<std::vector<int>>>(N_ATTRIB,grid);
	} // this input is a little hardcoded, but what can I do???
	
	void place( const std::string&tp,int x,int y ){
		// sets grid[x][y] to the element described in tp
		//note: I assume x,y are 0 indexed
		if(event.count(tp)) {
			grid[x][y]=event.find(tp)->second;
			for(int i=0;i<N_ATTRIB;++i)if(attribute[grid[x][y]]>>i&1){
				attrib[i][x][y]=0;
			}
		} else throw std::invalid_argument("Type of element |"+tp+"| not recognized (TYPO?)");
	}
	
	void pretty_print()const{
		// prints the grid real pretty
		auto line_print=[&](){
			if(grid.empty())return;
			for(int j=0;j<=N_ATTRIB;++j){
				if(j==1)std::cout << "  ";
				for(int i=-2;i<int(grid[0].size());++i)std::cout << '-';
				if(j<N_ATTRIB)std::cout << ' ';
			}
			std::cout << '\n';
			// std::cout.flush();
		}; line_print();
		
		for(int i=0;i<int(grid.size());++i){
			std::cout << '|'; // the grid
			for(int j=0;j<int(grid[i].size());++j)
				std::cout<<image[grid[i][j]];
			std::cout<<"|  "; // now the attributes
			for(int at=0;at<N_ATTRIB;++at){
				std::cout << " |";
				for(int j=0;j<int(attrib[at][i].size());++j){
					if(attribute[grid[i][j]]>>at&1)
						std::cout << attrib[at][i][j];
					else std::cout << image[grid[i][j]];
				}
				std::cout << "|";
			}
			std::cout << '\n';
		} line_print();
	}
	
	void simulate(int n_gen){
		// simulates n_gen steps of the ecosystem and outputs the generations and the statistics
		// note it 'damages' the data (it may not be possible to go back to previous states
		//                                     of the ecosystem once simulated)
		
		// to take time::: powered by chrono and functional
		auto take_time=[&](){return std::chrono::high_resolution_clock::now();};
		auto get_durat=[&](const auto start){ return std::chrono::duration_cast<std::chrono::milliseconds>(take_time() - start).count();};
		
		auto total = get_durat(take_time());
		
		for(int iter=0;iter<=n_gen;++iter){
			const auto in_tm=take_time();
			if(iter)simulate_1_step(iter); // xd
			const auto milisec=get_durat(in_tm);
			total+=milisec;
			
			std::vector<int> freq(ievent.size(),0);
			for(int i=0;i<int(grid.size());++i)for(int j=0;j<int(grid[i].size());++j){
				++freq[grid[i][j]];
			}
			
			// log writing
			std::cerr << "Iteration " << iter << "\n";
			if(iter)std::cerr << "Time "<< milisec << "\n";
			else std::cerr << "Time -1\n";
			for(int i=0;i<int(ievent.size());++i)
				std::cerr << "FrequencyElement " << freq[i] << " " << ievent[i] << "\n";
			std::cerr << '\n';
			
			// output grid
			std::cout << "Generation " << iter << '\n';
			pretty_print();
			std::cout << '\n'; // its pretty this way
		}
		std::cerr << "TotalTime " << total << '\n';
		std::cerr << "\nRemember the iteration index is 0-indexed and\nthe time is given in miliseconds\n";
	}
	
};



#endif // ECOSYSTEM_MOD_H