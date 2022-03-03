#include "tests_utils.hpp"
#include "./vector_subtests/constructors.cpp"

#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define GREEN "\033[0;32m"
#define END "\033[0m"

template <template <typename> class Vector>
void	vector_tests(bool benchmark, std::fstream& out) {
	vector_constructor<Vector>(benchmark, out);

}

double	benchmark_ft_vector() {
	std::fstream	null;
	time_t	timer_start;
	time_t	timer_end;

	time(&timer_start);
	for (int i = 0; i < 10000; i++) {
		vector_tests<ft::vector>(true, null);
	}
	time(&timer_end);
	double diff = difftime(timer_end, timer_start);
	std::cout << "ft_vector: " << diff << " seconds." << std::endl;
	return diff;
}

double	benchmark_std_map() {
	std::fstream	null;
	time_t	timer_start;
	time_t	timer_end;

	time(&timer_start);
	for (int i = 0; i < 10000; i++) {
		map_tests<std::vector>(true, null);
	}
	time(&timer_end);
	double diff = difftime(timer_end, timer_start);
	std::cout << "std_vector: " << diff << " seconds." << std::endl;
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

	map_tests<ft::vector>(false, ft_res);
	map_tests<std::vector>(false, std_res);

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

	return 0;
}
