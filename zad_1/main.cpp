#include <iostream>
#include <algorithm>
#include <vector>

typedef std::vector <int> configuration; 

uint32_t calculate_cmax(std::vector <std::vector<int>> data){
	uint32_t cmax=0; 
	std::vector<std::vector<int>> time;
	time.push_back({data[0][0], 0}); 
	for(int i=1; i<data.size(); ++i){
		time.push_back({time[i-1][0]+data[i][0],0}); 
	}
	for(int j=1; j<data[0].size()-1; ++j){
		time[0][j]=time[0][j-1]+data[0][j]; 
		for(int i=1; i<data.size(); ++i){
			time[i][j]=data[i][j]+(time[i][j-1]>time[i-1][j]?time[i][j-1]:time[i-1][j]); 
		}
		cmax = time[data.size()-1][j]; 
	}
	return cmax; 
}

void add_indexes_to_jobs(std::vector <std::vector<int>> * data){
	for(int i=0; i<data->size(); ++i){
		(*data)[i].push_back(i+1); 
	}
}

void find_solution_by_permutation(std::vector <std::vector<int>> data){
	do {
		std::cout << calculate_cmax(data) << std::endl; 
	} while(std::next_permutation(data.begin(),data.end())); 
}

configuration get_current_configuration(std::vector <std::vector<int>> data){
	configuration tmp; 
	for(int i=0; i<data.size(); ++i){
		tmp.push_back(data[i][data[0].size()-1]); 
	}
	return tmp;
}

void print_current_configuration(std::vector <std::vector<int>> data){
	std::cout << "Current configuration: " << std::endl; 
	for(int i=0; i<data.size(); ++i){
		std::cout << data[i][data[0].size()-1] << " "; 
	}
	std::cout << std::endl; 
}

void print_current_configuration(configuration con){
	std::cout << "Current configuration: " << std::endl; 
	for(int i=0; i<con.size(); ++i){
		std::cout << con[i] << " "; 
	}
	std::cout << std::endl; 
}

int main(int argc, char **argv) {
	std::vector <std::vector<int>> data; 
	// data.push_back({4,5}); 
	// data.push_back({4,1}); 
	// data.push_back({10,4}); 
	// data.push_back({6,10}); 
	// data.push_back({2,3}); 

	// data.push_back({5,2}); 
	// data.push_back({5,1}); 
	// data.push_back({6,2}); 
	// data.push_back({4,3}); 
	// data.push_back({2,6});
	// data.push_back({1,7});

	data.push_back({4,5,1}); 
	data.push_back({4,1,1}); 
	data.push_back({10,4,1}); 
	data.push_back({6,10,1}); 
	data.push_back({2,3,1}); 
	data.push_back({6,10,1}); 
	add_indexes_to_jobs(&data);
	do {
		std::cout << calculate_cmax(data) << std::endl; 
	} while(std::next_permutation(data.begin(),data.end())); 
	return 0; 
}