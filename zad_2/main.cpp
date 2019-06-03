#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

typedef std::vector <int> configuration; 
typedef std::vector <int> job; 
typedef std::vector <std::vector<int>> jobs; 

void read_jobs_data(jobs * data); 
void add_indexes_to_jobs(jobs * data);
void print_jobs_data(jobs* data); 
uint32_t calculate_cmax(jobs data); 
void find_solution_by_permutation(jobs data); 
void find_solution_by_neh_alghoritm(jobs data); 
configuration get_current_configuration(jobs data);
void print_current_configuration(jobs data);
void print_current_configuration(configuration con);



int main(int argc, char **argv) {
	jobs data; 
	read_jobs_data(&data); 
	add_indexes_to_jobs(&data);
	//find_solution_by_permutation(data); 
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
	std::vector<uint32_t> time;

	//create place for every job
	for(int i=0; i<data[0].size()-1; ++i){
		int x=0; 
		time.push_back(x); 
	}

	for(int i=0; i<data.size(); ++i){
		for(int j=0; j<data[i].size()-1; ++j){
			if(j==0){
				time[j] += data[i][j]; 
			} else {
				time[j] = std::max(time[j-1], time[j]) + data[i][j]; 
				//std::cout << "Iter_i: " << i << " Iter_j: " << j << " Time: " << time[j] << std::endl; 
			}
		}
	}

	cmax = time[time.size()-1]; 
	return cmax; 
}

void find_solution_by_permutation(jobs data){
	configuration tmp; 
	uint32_t cmax_min = calculate_cmax(data); 
	std::sort(data.begin(),data.end()); 
	do {
		if(cmax_min>calculate_cmax(data)){
			cmax_min = calculate_cmax(data); 
			tmp = get_current_configuration(data); 
		}
	} while(std::next_permutation(data.begin(), data.end())); 
	std::cout << "Solution by permutation: " << std::endl; 
	std::cout << "Cmax: " << cmax_min << std::endl; 
	print_current_configuration(tmp); 
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

	jobs neh_data; 
	do {
		job tmp_job=data[sorted_sum_data[0][1]-1]; 
		int min_i=0, CmaxMin=INT_MAX; 
		for(int i=0; i<neh_data.size()+1; ++i){
			jobs neh_data_copy = neh_data; 
			neh_data_copy.insert(neh_data_copy.begin()+i, tmp_job); 
			calculate_cmax(neh_data_copy); 
			if(CmaxMin > calculate_cmax(neh_data_copy)){
				CmaxMin=calculate_cmax(neh_data_copy); 
				min_i=i; 
			}
		}
		neh_data.insert(neh_data.begin()+min_i, tmp_job); 
		sorted_sum_data.erase(sorted_sum_data.begin()); 
	} while(sorted_sum_data.size()>0); 

	//print_jobs_data(&neh_data); 
	std::cout << "Solution by neh: " << std::endl; 
	std::cout << "Cmax: " << calculate_cmax(neh_data) << std::endl; 
	print_current_configuration(neh_data); 
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
