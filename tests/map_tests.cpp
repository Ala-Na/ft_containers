#include "tests_utils.hpp"
#include <map>
#include "../containers/map.hpp"
#include <fstream>
#include <sys/stat.h>
#include <cstddef>


#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define GREEN "\033[0;32m"
#define END "\033[0m"

bool fncomp (char lhs, char rhs) {return lhs<rhs;};

struct classcomp {
	bool operator() (const char& lhs, const char& rhs) const
	{return lhs>rhs;}
};


template <template <class, class, class, class> class Map, template <class> class Comp, template <class, class> class Pair>
void	map_constructor(bool benchmark, std::fstream &out) {

	Map<char,int, Comp<char>, std::allocator<Pair<const char,int> > > first;

	first['a']=10;
	first['b']=30;
	first['c']=50;
	first['d']=70;
	if (benchmark == false) {
		print_map("Example map:", first, out);
	}

	Map<char,int, Comp<char>, std::allocator<Pair<const char,int> > > second (first.begin(),first.end());
	if (benchmark == false) {
		print_map("Iterator construct map:", second, out);
	}

	Map<char,int, Comp<char>, std::allocator<Pair<const char,int> > > third (second);
	if (benchmark == false) {
		print_map("Copy constructor map:", third, out);
	}

	Map<char, int, classcomp, std::allocator<Pair<const char,int> > > fourth;
	fourth['a']=10;
	fourth['b']=30;
	fourth['c']=50;
	fourth['d']=70;
	if (benchmark == false) {
		print_map("Special compare class map:", fourth, out);
	}

	bool(*fn_pt)(char,char) = fncomp;
	Map<char,int,bool(*)(char,char), std::allocator<Pair<const char,int> > > fifth (fn_pt);
	if (benchmark == false) {
		print_map("Pointer function compare map:", fifth, out);
	}

	Map<char,int, Comp<char>, std::allocator<Pair<const char,int> > > copy;
	copy = first;
	if (benchmark == false) {
		print_map("Assignment operator test:", copy, out);
	}
}

double	benchmark_ft_map() {
	std::fstream	null;
	time_t	timer_start;
	time_t	timer_end;

	time(&timer_start);
	for (int i = 0; i < 1000; i++) {
		map_constructor<ft::map, ft::less, ft::pair>(true, null);
	}
	time(&timer_end);
	return difftime(timer_end, timer_start);
}

double	benchmark_std_map() {
	std::fstream	null;
	time_t	timer_start;
	time_t	timer_end;

	time(&timer_start);
	for (int i = 0; i < 1000; i++) {
		map_constructor<std::map, std::less, std::pair>(true, null);
	}
	time(&timer_end);
	return difftime(timer_end, timer_start);
}

int main() {
	struct stat st;
	std::fstream ft_res;
	std::fstream std_res;

	std::cout << YELLOW << "Testing ft::map and comparing to std::map" << END << std::endl;

	stat(".results", &st);
	if (!(st.st_mode & S_IFDIR) && mkdir(".results", 0777) == -1)  {
		std::cout << RED << "Error" << END << std::endl;
		return -1;
	}

	ft_res.open("./.results/ft_map_res.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
	std_res.open("./.results/std_map_res.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);

	if (ft_res.is_open() == false || std_res.is_open() == false) {
		std::cout << RED << "Error" << END << std::endl;
		return -1;
	}

	map_constructor<ft::map, ft::less, ft::pair>(true, ft_res);
	map_constructor<std::map, std::less, std::pair>(true, std_res);

	if (ft_res.tellg() != std_res.tellg()) {
		std::cout << "===> " << RED << "DIFF !" << END << std::endl;
		std::cout << "To check diff: 'diff .results/ft_map_res.txt .results/std_map_res.txt'" << std::endl;
		ft_res.close();
		std_res.close();
		return 0;
	}
	ft_res.seekg(0, ft_res.beg);
	std_res.seekg(0, std_res.beg);

	if (std::equal(std::istreambuf_iterator<char>(ft_res.rdbuf()),
		std::istreambuf_iterator<char>(), std::istreambuf_iterator<char>(std_res.rdbuf())) == false) {
		std::cout << "===> " << RED << "DIFF !" << END << std::endl;
		std::cout << "To check diff: 'diff .results/ft_map_res.txt .results/std_map_res.txt'" << std::endl;
	} else {
		std::cout << "===> " << GREEN << "OK" << END << std::endl;
	}

	ft_res.close();
	std_res.close();

	std::cout << YELLOW << "Benchmark testing" << END << std::endl;

	double ft_time = benchmark_ft_map();
	double std_time = benchmark_std_map();

	std::cout << "Std: " << std_time << " | " << "Ft: " << ft_time << std::endl;
	if (ft_time > std_time * 20) {
		std::cout << "===> " << RED << "TIMEOUT !" << END << std::endl;
	} else {
		std::cout << "===> " << GREEN << "OK" << END << std::endl;
	}

	return 0;
}
