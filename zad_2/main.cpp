#include <iostream>
#include <algorithm>
#include <vector>

typedef std::vector <int> configuration; 
typedef std::vector <std::vector<int>> jobs; 

void read_jobs_data(jobs * data); 
void add_indexes_to_jobs(jobs * data);
void print_jobs_data(jobs* data); 
uint32_t calculate_cmax(jobs data); 
void find_solution_by_neh_alghoritm(jobs data); 
configuration get_current_configuration(jobs data);
void print_current_configuration(jobs data);
void print_current_configuration(configuration con);



int main(int argc, char **argv) {
	jobs data; 
	read_jobs_data(&data); 
	add_indexes_to_jobs(&data);
	find_solution_by_neh_alghoritm(data); 
	return 0; 
}


void read_jobs_data(jobs * data){
	int x, a, b; 
	std::cin >> a >> b;
	for(int i=0; i<a; ++i){
		std::vector<int> tmp; 
		for(int j=0; j<b; ++j){
			std::cin >> x; 
			tmp.push_back(x); 
		}
		data->push_back(tmp); 
	}
}

void add_indexes_to_jobs(jobs * data){
	for(int i=0; i<data->size(); ++i){
		(*data)[i].push_back(i+1); 
	}
}

void print_jobs_data(jobs* data){
	for(int i=0; i<data->size(); ++i){
		for(int j=0; j<(*data)[i].size()-1; ++j){
			std::cout << (*data)[i][j] << " "; 
		}
		std::cout << std::endl; 
	}
}

uint32_t calculate_cmax(jobs data){
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

void find_solution_by_neh_alghoritm(jobs data){
	//SUM time on all machines
	jobs sum_data; 
	for(int i=0; i<data.size(); ++i){
		int sum=0; 
		for(int j=0; j<data[i].size()-1; ++j){
			sum += data[i][j]; 
		}
		std::vector<int> tmp; 
		tmp.push_back(sum); 
		tmp.push_back(data[i][data[i].size()-1]); 
		sum_data.push_back(tmp); 
	}

	//sort data
	jobs sorted_sum_data; 
	do {
		int max = sum_data[0][0], max_i=0;
		for(int i=0; i<sum_data.size(); ++i){
			if(max<sum_data[i][0]){
				max=sum_data[i][0]; 
				max_i=i; 
			}
		} 
		sorted_sum_data.push_back(sum_data[max_i]); 
		sum_data.erase(sum_data.begin()+max_i); 
	} while(sum_data.size()>0); 
	
}

configuration get_current_configuration(jobs data){
	configuration tmp; 
	for(int i=0; i<data.size(); ++i){
		tmp.push_back(data[i][data[i].size()-1]); 
	}
	return tmp;
}

void print_current_configuration(jobs data){
	std::cout << "Current configuration: " << std::endl; 
	for(int i=0; i<data.size(); ++i){
		std::cout << data[i][data[i].size()-1] << " "; 
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
