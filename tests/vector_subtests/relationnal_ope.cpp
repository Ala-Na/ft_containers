#include "../tests_utils.hpp"

// Taken and adapted from mli42 ft_containers tester

template <class Vector>
void	cmp(const Vector &lhs, const Vector &rhs, bool benchmark, std::fstream& out)
{
	static int i = 0;

	if (benchmark == false) {
		out << "############### [" << i++ << "] ###############"  << std::endl;
		out << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
		out << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
		out << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
	}
}

template <template <typename, typename> class Vector>
void	vector_relationnal(bool benchmark, std::fstream& out) {
	Vector<int, std::allocator<int> > vct1(4);
	Vector<int, std::allocator<int> > vct2(4);

	cmp(vct1, vct1, benchmark, out);
	cmp(vct1, vct2, benchmark, out);

	vct2.resize(10);

	cmp(vct1, vct2, benchmark, out);
	cmp(vct2, vct1, benchmark, out);

	vct1[2] = 42;

	cmp(vct1, vct2, benchmark, out);
	cmp(vct2, vct1, benchmark, out);

	vct1.swap(vct2);

	cmp(vct1, vct2, benchmark, out);
	cmp(vct2, vct1, benchmark, out);
}
