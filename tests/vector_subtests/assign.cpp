#include "../tests_utils.hpp"

// Taken and adapted from mli42 ft_containers tester

template <template <typename, typename> class Vector>
void	vector_assign(bool benchmark, std::fstream& out)
{
	Vector<int, std::allocator<int> > vct(7);
	Vector<int, std::allocator<int> > vct_two(4);
	Vector<int, std::allocator<int> > vct_three;
	Vector<int, std::allocator<int> > vct_four;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	for (unsigned long int i = 0; i < vct_two.size(); ++i)
		vct_two[i] = (vct_two.size() - i) * 5;
	if (benchmark == false) {
		print_vector("Vector 1 for assign:", vct, out);
		print_vector("Vector 2 for assign:", vct_two, out);
	}

	vct_three.assign(vct.begin(), vct.end());
	vct.assign(vct_two.begin(), vct_two.end());
	vct_two.assign(2, 42);
	vct_four.assign(4, 21);

	if (benchmark == false) {
		out << "\t### After assign(): ###" << std::endl;

		print_vector("Vector 1 after assign:", vct, out);
		print_vector("Vector 2 after assign:", vct_two, out);
		print_vector("Vector 3 after assign:", vct_three, out);
		print_vector("Vector 4 after assign:", vct_four, out);
	}

	vct_four.assign(6, 84);
	if (benchmark == false) {
		print_vector("Vector 4 after 2nd assign:", vct_four, out);
		out << "\t### assign() on enough capacity and low size: ###" << std::endl;
	}

	vct.assign(5, 53);
	vct_two.assign(vct_three.begin(), vct_three.begin() + 3);

	if (benchmark == false) {
		print_vector("Vector 1 after finals assign:", vct, out);
		print_vector("Vector 2 after finals assign:", vct_two, out);
	}
}
