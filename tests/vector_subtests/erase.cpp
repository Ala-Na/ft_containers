#include "../main_tests/tests_utils.hpp"

// Taken and adapted from mli42 ft_containers tester

template <class Vector>
void	checkErase(Vector const &vct, typename Vector::const_iterator const &it, bool benchmark, std::fstream& out)
{
	static int i = 0;
	if (benchmark == false) {
		out << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
		print_vector("Vector erase:",vct, out);
	} else {
		it - vct.begin();
	}
}

template <template <typename, typename> class Vector>
void	vector_erase(bool benchmark, std::fstream& out) {

	Vector<std::string, std::allocator<std::string> > vct(10);

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = std::string((vct.size() - i), i + 65);
	if (benchmark == false) {
		print_vector("Vector erase:",vct, out);
	}

	checkErase(vct, vct.erase(vct.begin() + 2), benchmark, out);

	checkErase(vct, vct.erase(vct.begin()), benchmark, out);
	checkErase(vct, vct.erase(vct.end() - 1), benchmark, out);

	checkErase(vct, vct.erase(vct.begin(), vct.begin() + 3), benchmark, out);
	checkErase(vct, vct.erase(vct.end() - 3, vct.end() - 1), benchmark, out);

	vct.push_back("Hello");
	vct.push_back("Hi there");
	if (benchmark == false) {
		print_vector("Vector erase:",vct, out);
	}
	checkErase(vct, vct.erase(vct.end() - 3, vct.end()), benchmark, out);

	vct.push_back("ONE");
	vct.push_back("TWO");
	vct.push_back("THREE");
	vct.push_back("FOUR");
	if (benchmark == false) {
		print_vector("Vector erase:",vct, out);
	}
	checkErase(vct, vct.erase(vct.begin(), vct.end()), benchmark, out);
}

