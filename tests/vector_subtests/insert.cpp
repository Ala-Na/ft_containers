#include "../tests_utils.hpp"

// Taken and adapted from mli42 ft_containers tester

template <template <typename, typename> class Vector>
void	vector_insert(bool benchmark, std::fstream& out) {
	Vector<int, std::allocator<int> > vct(10);
	Vector<int, std::allocator<int> > vct2;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	if (benchmark == false)
		print_vector("Vector for insert 1:", vct, out);

	vct2.insert(vct2.end(), 42);
	vct2.insert(vct2.begin(), 2, 21);
	if (benchmark == false)
		print_vector("Vector for insert 2:", vct2, out);

	vct2.insert(vct2.end() - 2, 42);
	if (benchmark == false)
		print_vector("Vector for insert 2:", vct2, out);

	vct2.insert(vct2.end(), 2, 84);
	if (benchmark == false)
		print_vector("Vector for insert 2:", vct2, out);

	vct2.resize(4);
	if (benchmark == false)
		print_vector("Vector for insert 2:", vct2, out);

	vct2.insert(vct2.begin() + 2, vct.begin(), vct.end());
	vct.clear();
	if (benchmark == false)
		print_vector("Vector for insert 2:", vct2, out);

	if (benchmark == false)
		print_vector("Vector for insert 1:", vct, out);

	Vector<int, std::allocator<int> > vct3(5);
	Vector<int, std::allocator<int> > vct4;
	const int cut = 3;

	for (unsigned long int i = 0; i < vct3.size(); ++i)
		vct3[i] = (vct3.size() - i) * 7;
	if (benchmark == false)
		print_vector("Vector for insert 3:", vct3, out);

	vct4.insert(vct4.begin(), vct3.begin(), vct3.begin() + cut);
	if (benchmark == false)
		print_vector("Vector for insert 4:", vct4, out);
	vct4.insert(vct4.begin(), vct3.begin() + cut, vct3.end());
	if (benchmark == false)
		print_vector("Vector for insert 4:", vct4, out);
	vct4.insert(vct4.end(), vct3.begin(), vct3.begin() + cut);
	if (benchmark == false) {
		print_vector("Vector for insert 4:", vct4, out);

		out << "insert return:" << std::endl;

		out << *vct4.insert(vct4.end(), 42) << std::endl;
		out << *vct4.insert(vct4.begin() + 5, 84) << std::endl;
		out << "----------------------------------------" << std::endl;

		print_vector("Vector for insert:", vct4, out);
	} else {
		vct4.insert(vct4.end(), 42);
		vct4.insert(vct4.begin() + 5, 84);
	}
}
