#include "../main_tests/tests_utils.hpp"

// Taken and adapted from mli42 ft_containers tester

template <class Vector>
void	is_empty(Vector const &vct, bool benchmark, std::fstream& out) {
	if (benchmark == false)
		out << "is_empty: " << vct.empty() << std::endl;
}

template <template <typename, typename> class Vector>
void	vector_size(bool benchmark, std::fstream& out) {
	const int start_size = 7;
	Vector<int, std::allocator<int> > vct(start_size, 20);
	Vector<int, std::allocator<int> > vct2;
	typename Vector<int, std::allocator<int> >::iterator it = vct.begin();

	for (int i = 2; i < start_size; ++i)
		it[i] = (start_size - i) * 3;
	if (benchmark == false)
		print_vector("Vector for size:", vct, out);

	vct.resize(10, 42);
	if (benchmark == false)
		print_vector("Vector for size:", vct, out);

	vct.resize(18, 43);
	if (benchmark == false)
		print_vector("Vector for size:", vct, out);
	vct.resize(10);
	if (benchmark == false)
		print_vector("Vector for size:", vct, out);
	vct.resize(23, 44);
	if (benchmark == false)
		print_vector("Vector for size:", vct, out);
	vct.resize(5);
	if (benchmark == false)
		print_vector("Vector for size:", vct, out);
	vct.reserve(5);
	vct.reserve(3);
	if (benchmark == false)
		print_vector("Vector for size:", vct, out);
	vct.resize(87);
	vct.resize(5);
	if (benchmark == false)
		print_vector("Vector for size:", vct, out);

	is_empty(vct2, benchmark, out);
	vct2 = vct;
	is_empty(vct2, benchmark, out);
	vct.reserve(vct.capacity() + 1);
	if (benchmark == false)
		print_vector("Vector for size:", vct, out);
	if (benchmark == false)
		print_vector("Vector for size:", vct2, out);

	vct2.resize(0);
	is_empty(vct2, benchmark, out);
	if (benchmark == false)
		print_vector("Vector for size:", vct2, out);
}
