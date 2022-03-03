#include "../tests_utils.hpp"

// Taken and adapted from mli42 ft_containers tester

template <template <typename, typename> class Vector>
void	vector_push_pop(bool benchmark, std::fstream& out) {
	Vector<std::string, std::allocator<std::string> > vct(8);
	Vector<std::string, std::allocator<std::string> > vct2;
	typename Vector<std::string, std::allocator<std::string> >::iterator it = vct.begin();

	for (unsigned long int i = 0; i < vct.size(); ++i)
		it[i] = std::string((vct.size() - i), i + 65);

	if (benchmark == false) {
		print_vector("Vector for push/back:", vct, out);
		out << "push_back():\n" << std::endl;
	}

	vct.push_back("One long string");
	vct2.push_back("Another long string");

	if (benchmark == false) {
		print_vector("Vector for push/back:", vct, out);
		print_vector("Vector for push/back:", vct2, out);
	}

	vct.pop_back();
	vct2.pop_back();

	if (benchmark == false) {
		print_vector("Vector for push/back:", vct, out);
		print_vector("Vector for push/back:", vct2, out);
	}
}
