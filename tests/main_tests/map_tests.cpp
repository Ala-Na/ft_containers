#include "tests_utils.hpp"
#include "../map_subtests/constructors.cpp"
#include "../map_subtests/bounds.cpp"
#include "../map_subtests/comp.cpp"
#include "../map_subtests/empty.cpp"
#include "../map_subtests/erase.cpp"
#include "../map_subtests/find_count.cpp"
#include "../map_subtests/insert.cpp"
#include "../map_subtests/ite.cpp"
#include "../map_subtests/op_sqbr.cpp"
#include "../map_subtests/relationnal_ope.cpp"
#include "../map_subtests/rev_it.cpp"
#include "../map_subtests/swap.cpp"

#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define GREEN "\033[0;32m"
#define END "\033[0m"

template <template <class, class, class, class> class Map, template <class> class Comp, template <class, class> class Pair, template <typename, typename> class Vector>
void	map_tests(bool benchmark, std::fstream& out) {
	map_constructor<Map, Comp, Pair, Vector>(benchmark, out);
	map_bounds<Map, Comp, Pair, Vector>(benchmark, out);
	map_comp<Map, Comp, Pair>(benchmark, out);
	map_empty<Map, Comp, Pair, Vector>(benchmark, out);
	map_erase<Map, Comp, Pair, Vector>(benchmark, out);
	map_find_count<Map, Comp, Pair>(benchmark, out);
	map_insert<Map, Comp, Pair, Vector>(benchmark, out);
	map_ite<Map, Comp, Pair>(benchmark, out);
	map_op_sqbr<Map, Comp, Pair>(benchmark, out);
	map_relationnal<Map, Comp, Pair>(benchmark, out);
	map_rev_it<Map, Comp, Pair>(benchmark, out);
	map_swap<Map, Comp, Pair>(benchmark, out);
}

double	benchmark_ft_map() {
	std::fstream	null;
	clock_t	timer_start;
	clock_t	timer_end;

	timer_start = clock();
	for (int i = 0; i < 10000; i++) {
		map_tests<ft::map, ft::less, ft::pair, ft::vector>(true, null);
	}
	timer_end = clock();
	double diff = (timer_end - timer_start);
	return diff;
}

double	benchmark_std_map() {
	std::fstream	null;
	clock_t	timer_start;
	clock_t	timer_end;

	timer_start = clock();
	for (int i = 0; i < 10000; i++) {
		map_tests<std::map, std::less, std::pair, std::vector>(true, null);
	}
	timer_end = clock();
	double diff = (timer_end - timer_start);
	return diff;
}

int main() {
	struct stat st;
	std::fstream ft_res;
	std::fstream std_res;

	std::cout << YELLOW << "Testing ft::map and comparing to std::map" << END << std::endl;

	stat("../.results", &st);
	if (!(st.st_mode & S_IFDIR) && mkdir("../.results", 0777) == -1)  {
		std::cout << RED << "Error" << END << std::endl;
		return -1;
	}

	ft_res.open("../.results/ft_map_res.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
	std_res.open("../.results/std_map_res.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);

	if (ft_res.is_open() == false || std_res.is_open() == false) {
		std::cout << RED << "Error" << END << std::endl;
		return -1;
	}

	map_tests<ft::map, ft::less, ft::pair, ft::vector>(false, ft_res);
	map_tests<std::map, std::less, std::pair, std::vector>(false, std_res);

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

	if (ft_time > std_time * 20) {
		std::cout << "===> " << RED << "TIMEOUT !" << END << std::endl;
	} else {
		std::cout << "===> " << GREEN << "OK" << END << std::endl;
	}

	std::cout << "[std_map: " << std_time / double(CLOCKS_PER_SEC) << " seconds.]" << std::endl;
	std::cout << "[ft_map: " << ft_time / double(CLOCKS_PER_SEC) << " seconds.]" << std::endl;

	return 0;
}
