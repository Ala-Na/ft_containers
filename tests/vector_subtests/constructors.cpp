#include "../tests_utils.hpp"

template <template <typename, typename> class Vector>
void	vector_constructor(bool benchmark, std::fstream& out) {
	Vector<int, std::allocator<int> > first;

	if (benchmark == false) {
		print_vector("Empty constructor vector:", first, out);
		out << first.max_size() << std::endl;
	}

	Vector<int, std ::allocator<int> > second (4,100);

	if (benchmark == false) {
		print_vector("Fill constructor vector:", second, out);
		out << second.max_size() << std::endl;
	}

	Vector<int, std ::allocator<int> > third (second.begin(),second.end());

	if (benchmark == false) {
		print_vector("Range constructor vector:", third, out);
		out << third.max_size() << std::endl;
	}

	Vector<int, std ::allocator<int> > fourth (third);

	if (benchmark == false) {
		print_vector("Copy constructor vector:", fourth, out);
		out << fourth.max_size() << std::endl;
	}

	int myints[] = {16,2,77,29};
	Vector<int, std ::allocator<int> > fifth (myints, myints + sizeof(myints) / sizeof(int) );

	if (benchmark == false) {
		print_vector("Another iterator constructor vector from array:", fifth, out);
		out << fifth.max_size() << std::endl;
	}

	// Taken and adapted from mli42 ft_containers tester

	Vector<int, std ::allocator<int> > vct(5);
	typename Vector<int, std ::allocator<int> >::iterator it = vct.begin(), ite = vct.end();

	if (benchmark == false) {
		out << "len: " << (ite - it) << std::endl;
	}
	for (; it != ite; ++it)
		*it = (ite - it);

	it = vct.begin();
	Vector<int, std ::allocator<int> > vct_range(it, --(--ite));
	for (int i = 0; it != ite; ++it)
		*it = ++i * 5;

	it = vct.begin();
	Vector<int, std ::allocator<int> > vct_copy(vct);
	for (int i = 0; it != ite; ++it)
		*it = ++i * 7;
	vct_copy.push_back(42);
	vct_copy.push_back(21);

	if (benchmark == false) {
		out << "\t-- PART ONE --" << std::endl;
		print_vector("Original:", vct, out);
		print_vector("Range:", vct_range, out);
		print_vector("Copy:", vct_copy, out);
	}

	vct = vct_copy;
	vct_copy = vct_range;
	vct_range.clear();

	if (benchmark == false) {
		out << "\t-- PART TWO --" << std::endl;
		print_vector("Original:", vct, out);
		print_vector("Range:", vct_range, out);
		print_vector("Copy:", vct_copy, out);
	}
}
