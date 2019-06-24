#include <iostream>
#include <algorithm>
#include <vector>

typedef std::vector <int> configuration; 
typedef std::vector <std::vector<int>> jobs; 

void read_jobs_data(jobs * data); 
void add_indexes_to_jobs(jobs * data);
void print_jobs_data(jobs* data); 
void convert_machines_no(jobs* data); 
uint32_t calculate_cmax(jobs data); 
void find_solution_by_permutation(jobs data);
void find_solution_by_johnsons_alghoritm(jobs data); 
configuration get_current_configuration(jobs data);
void print_current_configuration(jobs data);
void print_current_configuration(configuration con);



int main(int argc, char **argv) {
	jobs data; 
	read_jobs_data(&data); 
	add_indexes_to_jobs(&data);
	//find_solution_by_permutation(data); 
	find_solution_by_johnsons_alghoritm(data); 
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

void convert_machines_no(jobs* data){
	if((*data)[0].size()-1==3){
		jobs tmp; 
		for(int i=0; i<data->size(); ++i){
			std::vector<int> tmp_job; 
			tmp_job.push_back((*data)[i][0]+(*data)[i][1]); 
			tmp_job.push_back((*data)[i][1]+(*data)[i][2]); 
			tmp_job.push_back((*data)[i][3]); 
			tmp.push_back(tmp_job); 
		}
		*data=tmp; 
	} else {
		std::cout << "Wrong size for convertion" << std::endl; 
		return; 
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

configuration johnsons_for_two_machines(jobs data){
	jobs tmp; 
	for(int i=0; i<data.size(); ++i){
		std::vector<int> tmp_job; 
		tmp.push_back(tmp_job); 
	}
	int front_iterator=0, end_iterator=tmp.size()-1; 

	do {
		int min_i=0, min_j=0, min=data[0][0]; 
		for(int i=0; i<data.size(); ++i){
			for(int j=0; j<data[i].size()-1; ++j){
				if(data[i][j]<min){
					min = data[i][j]; 
					min_i = i; 
					min_j = j; 
				}
			}
		}
		if(min_j==1){
			tmp[end_iterator] = data[min_i]; 
			--end_iterator; 
		} else if(min_j==0){
			tmp[front_iterator] = data[min_i]; 
			++front_iterator; 
		} else {
			std::cout << "Error occured!!!" << std::endl; 
		}
		data.erase(data.begin()+min_i); 
	} while (end_iterator-front_iterator >= 0); 
	return get_current_configuration(tmp); 
}

void find_solution_by_johnsons_alghoritm(jobs data){
	if(data[0].size()-1==3){
		jobs tmp_data = data; 
		jobs ordered_data; 
		convert_machines_no(&tmp_data);
		configuration out_config= johnsons_for_two_machines(tmp_data); 
		for(int i=0; i<out_config.size(); ++i){
			for(int j=0; j<data.size(); ++j){
				if(data[j][data[j].size()-1] == out_config[i]){
					ordered_data.push_back(data[j]); 
				}
			}

		}
		std::cout << "Solution by Johnsons alghoritm: " << std::endl; 
		std::cout << "Cmax: " << calculate_cmax(ordered_data) << std::endl; 
		print_current_configuration(out_config); 
	} else if (data[0].size()-1==2){
		std::cout << "Solution by Johnsons alghoritm: " << std::endl; 
		std::cout << "Cmax: " << calculate_cmax(data) << std::endl; 
		print_current_configuration(johnsons_for_two_machines(data)); 
	} else {
		std::cout << "Wrong size for Johnsons alghoritm" << std::endl; 
		return; 
	}

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
