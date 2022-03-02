#include "tests_utils.hpp"
#include "./map_subtests/constructors.cpp"
#include "./map_subtests/bounds.cpp"
#include "./map_subtests/comp.cpp"
#include "./map_subtests/empty.cpp"
#include "./map_subtests/erase.cpp"


#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define GREEN "\033[0;32m"
#define END "\033[0m"

template <template <class, class, class, class> class Map, template <class> class Comp, template <class, class> class Pair>
void	map_tests(bool benchmark, std::fstream& out) {
	map_constructor<Map, Comp, Pair>(benchmark, out);
	map_bounds<Map, Comp, Pair>(benchmark, out);
	map_comp<Map, Comp, Pair>(benchmark, out);
	map_empty<Map, Comp, Pair>(benchmark, out);
	map_erase<Map, Comp, Pair>(benchmark, out);
}

double	benchmark_ft_map() {
	std::fstream	null;
	time_t	timer_start;
	time_t	timer_end;

	time(&timer_start);
	for (int i = 0; i < 10000; i++) {
		map_tests<ft::map, ft::less, ft::pair>(true, null);
	}
	time(&timer_end);
	return difftime(timer_end, timer_start);
}

double	benchmark_std_map() {
	std::fstream	null;
	time_t	timer_start;
	time_t	timer_end;

	time(&timer_start);
	for (int i = 0; i < 10000; i++) {
		map_tests<std::map, std::less, std::pair>(true, null);
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

	map_tests<ft::map, ft::less, ft::pair>(false, ft_res);
	map_tests<std::map, std::less, std::pair>(false, std_res);

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

	if (std_time == 0 && ft_time != std_time) {
		std_time += 1;
	}

	if (ft_time > std_time * 20) {
		std::cout << "===> " << RED << "TIMEOUT !" << END << std::endl;
	} else {
		std::cout << "===> " << GREEN << "OK" << END << std::endl;
	}

	return 0;
}
