#include "tests_utils.hpp"
#include "../stack_subtests/constructors.cpp"
#include "../stack_subtests/relationnal_ope.cpp"

#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define GREEN "\033[0;32m"
#define END "\033[0m"

template <template <typename, typename> class Stack, template <typename, typename> class Vector>
void	stack_tests(bool benchmark, std::fstream& out) {
	stack_constructor<Stack, Vector>(benchmark, out);
	stack_relationnal<Stack, Vector>(benchmark, out);

}

double	benchmark_ft_stack() {
	std::fstream	null;
	clock_t	timer_start;
	clock_t	timer_end;

	timer_start = clock();
	for (int i = 0; i < 10000; i++) {
		stack_tests<ft::stack, ft::vector>(true, null);
	}
	timer_end = clock();
	double diff = (timer_end - timer_start);
	return diff;
}

double	benchmark_std_stack() {
	std::fstream	null;
	clock_t	timer_start;
	clock_t	timer_end;

	timer_start = clock();
	for (int i = 0; i < 10000; i++) {
		stack_tests<std::stack, std::vector>(true, null);
	}
	timer_end = clock();
	double diff = (timer_end - timer_start);
	return diff;
}

int main() {
	struct stat st;
	std::fstream ft_res;
	std::fstream std_res;

	std::cout << YELLOW << "Testing ft::stack and comparing to std::stack" << END << std::endl;

	stat("../.results", &st);
	if (!(st.st_mode & S_IFDIR) && mkdir("../.results", 0777) == -1)  {
		std::cout << RED << "Error" << END << std::endl;
		return -1;
	}

	ft_res.open("../.results/ft_stack_res.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
	std_res.open("../.results/std_stack_res.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);

	if (ft_res.is_open() == false || std_res.is_open() == false) {
		std::cout << RED << "Error" << END << std::endl;
		return -1;
	}

	stack_tests<ft::stack, ft::vector>(false, ft_res);
	stack_tests<std::stack, std::vector>(false, std_res);

	if (ft_res.tellg() != std_res.tellg()) {
		std::cout << "===> " << RED << "DIFF !" << END << std::endl;
		std::cout << "To check diff: 'diff .results/ft_stack_res.txt .results/std_stack_res.txt'" << std::endl;
		ft_res.close();
		std_res.close();
		return 0;
	}
	ft_res.seekg(0, ft_res.beg);
	std_res.seekg(0, std_res.beg);

	if (std::equal(std::istreambuf_iterator<char>(ft_res.rdbuf()),
		std::istreambuf_iterator<char>(), std::istreambuf_iterator<char>(std_res.rdbuf())) == false) {
		std::cout << "===> " << RED << "DIFF !" << END << std::endl;
		std::cout << "To check diff: 'diff .results/ft_stack_res.txt .results/std_stack_res.txt'" << std::endl;
	} else {
		std::cout << "===> " << GREEN << "OK" << END << std::endl;
	}

	ft_res.close();
	std_res.close();

	std::cout << YELLOW << "Benchmark testing" << END << std::endl;

	double ft_time = benchmark_ft_stack();
	double std_time = benchmark_std_stack();

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
