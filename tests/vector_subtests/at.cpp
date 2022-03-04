#include "../main_tests/tests_utils.hpp"

// Taken and adapted from mli42 ft_containers tester

template <template <typename, typename> class Vector>
void	vector_at(bool benchmark, std::fstream& out) {
	Vector<int, std::allocator<int> > vct(7);

	for (unsigned long int i = 0; i < vct.size(); ++i)
	{
		vct.at(i) = (vct.size() - i) * 3;
		if (benchmark == false) {
			out << "vct.at(): " << vct.at(i) << " | ";
			out << "vct[]: " << vct[i] << std::endl;
		}
	}
	if (benchmark == false) {
		print_vector("Vector for at:", vct, out);
	}

	Vector<int, std::allocator<int> > const vct_c(vct);

	if (benchmark == false) {
		out << "front(): " << vct.front() << " " << vct_c.front() << std::endl;
		out << "back(): " << vct.back() << " " <<  vct_c.back() << std::endl;
	} else {
		vct.front();
		vct.back();
		vct_c.front();
		vct_c.back();
	}

	try {
		vct.at(10) = 42;
	}
	catch (std::exception &e) {
		if (benchmark == false) {
			out << "Out of range exception (message may differ from ft and std)" << std::endl;
		}
	}

	Vector<int, std::allocator<int> > vct2(7);

	for (unsigned long int i = 0; i < vct2.size(); ++i)
	{
		vct2.at(i) = (vct2.size() - i) * 3;
		if (benchmark == false) {
			out << "vct2[]: " << vct2[i] << std::endl;
		}
	}
	if (benchmark == false) {
		print_vector("Vector for 2nd at:", vct2, out);
	}

	Vector<int, std::allocator<int> > const vct_c2(vct2);

	if (benchmark == false) {
		out << "front(): " << vct2.front() << " " << vct_c2.front() << std::endl;
		out << "back(): " << vct2.back() << " " <<  vct_c2.back() << std::endl;
	} else {
		vct2.front();
		vct2.back();
		vct_c2.front();
		vct_c2.back();
	}

	if (benchmark == false) {
		for (unsigned long int i = 0; i < vct_c2.size(); ++i)
			out << "vct_c2.at(): " << vct_c2.at(i) << std::endl;
		try {
			out << vct_c2.at(10) << std::endl;
		}
		catch (std::exception &e) {
			out << "Catch exception: Out of range (messages may differ from std and ft)" << std::endl;
		}
		print_vector("Vector constant:", vct_c2, out);
	} else {
		for (unsigned long int i = 0; i < vct_c2.size(); ++i)
			vct_c2.at(i);
		try {
			out << vct_c2.at(10) << std::endl;
		}
		catch (std::exception &e) {
			return ;
		}
	}
}
