#include "tests_utils.hpp"
#include "./vector_subtests/constructors.cpp"
#include "./vector_subtests/assign.cpp"
#include "./vector_subtests/at.cpp"
#include "./vector_subtests/it.cpp"
#include "./vector_subtests/erase.cpp"
#include "./vector_subtests/insert.cpp"
#include "./vector_subtests/push_pop.cpp"
#include "./vector_subtests/relationnal_ope.cpp"
#include "./vector_subtests/rev_it.cpp"
#include "./vector_subtests/size.cpp"
#include "./vector_subtests/swap.cpp"

#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define GREEN "\033[0;32m"
#define END "\033[0m"

template <template <typename, typename> class Vector>
void	vector_tests(bool benchmark, std::fstream& out) {
	vector_constructor<Vector>(benchmark, out);
	vector_assign<Vector>(benchmark, out);
	vector_at<Vector>(benchmark, out);
	vector_it<Vector>(benchmark, out);
	vector_erase<Vector>(benchmark, out);
	vector_insert<Vector>(benchmark, out);
	vector_push_pop<Vector>(benchmark, out);
	vector_relationnal<Vector>(benchmark, out);
	vector_rev_it<Vector>(benchmark, out);
	vector_size<Vector>(benchmark, out);
	vector_swap<Vector>(benchmark, out);
}

double	benchmark_ft_vector() {
	std::fstream	null;
	clock_t	timer_start;
	clock_t	timer_end;

	timer_start = clock();
	for (int i = 0; i < 10000; i++) {
		vector_tests<ft::vector>(true, null);
	}
	timer_end = clock();
	double diff = (timer_end - timer_start);
	return diff;
}

double	benchmark_std_vector() {
	std::fstream	null;
	clock_t	timer_start;
	clock_t	timer_end;

	timer_start = clock();
	for (int i = 0; i < 10000; i++) {
		vector_tests<std::vector>(true, null);
	}
	timer_end = clock();
	double diff = (timer_end - timer_start);
	return diff;
}

int main() {
	struct stat st;
	std::fstream ft_res;
	std::fstream std_res;

	std::cout << YELLOW << "Testing ft::vector and comparing to std::vector" << END << std::endl;

	stat(".results", &st);
	if (!(st.st_mode & S_IFDIR) && mkdir(".results", 0777) == -1)  {
		std::cout << RED << "Error" << END << std::endl;
		return -1;
	}

	ft_res.open("./.results/ft_vector_res.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
	std_res.open("./.results/std_vector_res.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);

	if (ft_res.is_open() == false || std_res.is_open() == false) {
		std::cout << RED << "Error" << END << std::endl;
		return -1;
	}

	vector_tests<ft::vector>(false, ft_res);
	vector_tests<std::vector>(false, std_res);

	if (ft_res.tellg() != std_res.tellg()) {
		std::cout << "===> " << RED << "DIFF !" << END << std::endl;
		std::cout << "To check diff: 'diff .results/ft_vector_res.txt .results/std_vector_res.txt'" << std::endl;
		ft_res.close();
		std_res.close();
		return 0;
	}
	ft_res.seekg(0, ft_res.beg);
	std_res.seekg(0, std_res.beg);

	if (std::equal(std::istreambuf_iterator<char>(ft_res.rdbuf()),
		std::istreambuf_iterator<char>(), std::istreambuf_iterator<char>(std_res.rdbuf())) == false) {
		std::cout << "===> " << RED << "DIFF !" << END << std::endl;
		std::cout << "To check diff: 'diff .results/ft_vector_res.txt .results/std_vector_res.txt'" << std::endl;
	} else {
		std::cout << "===> " << GREEN << "OK" << END << std::endl;
	}

	ft_res.close();
	std_res.close();

	std::cout << YELLOW << "Benchmark testing" << END << std::endl;

	double ft_time = benchmark_ft_vector();
	double std_time = benchmark_std_vector();

	if (std_time == 0 && ft_time != std_time) {
		std_time += 1;
	}

	if (ft_time > std_time * 20) {
		std::cout << "===> " << RED << "TIMEOUT !" << END << std::endl;
	} else {
		std::cout << "===> " << GREEN << "OK" << END << std::endl;
	}

	std::cout << "[std_map: " << std_time / double(CLOCKS_PER_SEC) << " seconds.]" << std::endl;
	std::cout << "[ft_map: " << ft_time / double(CLOCKS_PER_SEC) << " seconds.]" << std::endl;

	return 0;
}
