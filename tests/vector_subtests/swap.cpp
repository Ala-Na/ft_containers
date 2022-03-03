#include "../tests_utils.hpp"

// Taken and adapted from mli42 ft_containers tester

template <template <typename, typename> class Vector>
void	vector_swap(bool benchmark, std::fstream& out) {
	Vector<int, std::allocator<int> > foo(3, 15);
	Vector<int, std::allocator<int> > bar(5, 42);

	typename Vector<int, std::allocator<int> >::const_iterator it_foo = foo.begin();
	typename Vector<int, std::allocator<int> >::const_iterator it_bar = bar.begin();

	if (benchmark == false) {
		out << "BEFORE SWAP" << std::endl;

		out << "foo contains:" << std::endl;
		print_vector("Vector for swap:", foo, out);
		out << "bar contains:" << std::endl;
		print_vector("Vector for swap:", bar, out);
	}

	foo.swap(bar);

	if (benchmark == false) {
		out << "AFTER SWAP" << std::endl;

		out << "foo contains:" << std::endl;
		print_vector("Vector for swap:", foo, out);
		out << "bar contains:" << std::endl;
		print_vector("Vector for swap:", bar, out);

		out << "Iterator validity:" << std::endl;
		out << (it_foo == bar.begin()) << std::endl;
		out << (it_bar == foo.begin()) << std::endl;
	}
}
