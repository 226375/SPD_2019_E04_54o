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
int find_solution_by_shrage(jobs data); 
int find_solution_by_shrage_pmtn(jobs data); 
configuration get_current_configuration(jobs data);
void print_current_configuration(jobs data);
void print_current_configuration(configuration con);



int main(int argc, char **argv) {
	jobs data; 
	read_jobs_data(&data); 
	add_indexes_to_jobs(&data);
	std::cout << "Cmax1: " << find_solution_by_shrage(data) << std::endl; 
	std::cout << "Cmax2: " << find_solution_by_shrage_pmtn(data) << std::endl; 
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

int find_solution_by_shrage(jobs data){
	jobs N = data; 
	jobs G; 
	int t=0, Cmax=0; 
	std::sort(N.begin(), N.end(), [](const job& a, const job& b){return a[0]<b[0];}); 
	while(N.size() != 0 || G.size() != 0){
		while(N.size() != 0 && N[0][0] <= t){
			G.push_back(N[0]); 
			N.erase(N.begin()); 
		}
		if(G.size() == 0){
			t = N[0][0]; 
		} else {
			int tmp_max=0, max_i=0;
			for(int i=0; i<G.size(); ++i){
				if(tmp_max < G[i][2]){
					tmp_max = G[i][2]; 
					max_i = i; 
				}
			}
			job tmp_job= G[max_i]; 
			G.erase(G.begin()+max_i); 
			t += tmp_job[1]; 
			Cmax = std::max(Cmax, t+tmp_job[2]); 
		}
	}
	return Cmax; 
}

int find_solution_by_shrage_pmtn(jobs data){
	jobs N = data; 
	jobs G; 
	int t=0, Cmax=0; 
	job l; 
	l.push_back(0); 
	l.push_back(0);
	l.push_back(INT_MAX); 

	std::sort(N.begin(), N.end(), [](const job& a, const job& b){return a[0]<b[0];}); 
	while(N.size() != 0 || G.size() != 0){
		while(N.size() != 0 && N[0][0] <= t){
			job tmp = N[0]; 
			G.push_back(N[0]); 
			N.erase(N.begin()); 
			if(tmp[2]>l[2]){
				l[1] = t - tmp[0]; 
				t = tmp[0]; 
				if(l[1]>0){
					G.push_back(l); 
				}
			}
		}
		if(G.size() == 0){
			t = N[0][0]; 
		} else {
			int tmp_max=0, max_i=0;
			for(int i=0; i<G.size(); ++i){
				if(tmp_max < G[i][2]){
					tmp_max = G[i][2]; 
					max_i = i; 
				}
			}
			job tmp_job= G[max_i]; 
			G.erase(G.begin()+max_i); 
			t += tmp_job[1]; 
			Cmax = std::max(Cmax, t+tmp_job[2]); 
			l = tmp_job; 
		}
	}

	return Cmax; 
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
