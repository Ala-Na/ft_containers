#include "../tests_utils.hpp"

// Taken and adapted from mli42 ft_containers tester

template <typename T>
class foo {
	public:
		typedef T	value_type;

		foo(void) : value(), _verbose(false) { };
		foo(value_type src, const bool verbose = false) : value(src), _verbose(verbose) { };
		foo(foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose) { };
		~foo(void) { if (this->_verbose) std::cout << "~foo::foo()" << std::endl; };
		void m(void) { std::cout << "foo::m called [" << this->value << "]" << std::endl; };
		void m(void) const { std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
		foo &operator=(value_type src) { this->value = src; return *this; };
		foo &operator=(foo const &src) {
			if (this->_verbose || src._verbose)
				std::cout << "foo::operator=(foo) CALLED" << std::endl;
			this->value = src.value;
			return *this;
		};
		value_type	getValue(void) const { return this->value; };
		void		switchVerbose(void) { this->_verbose = !(this->_verbose); };

		operator value_type(void) const {
			return value_type(this->value);
		}
	private:
		value_type	value;
		bool		_verbose;
};


template <typename Ite_1, typename Ite_2>
void ft_eq_ope(const Ite_1 &first, const Ite_2 &second, bool benchmark, std::fstream& out, const bool redo = 1)
{
	if (benchmark == false) {
		out << (first < second) << std::endl;
		out << (first <= second) << std::endl;
		out << (first > second) << std::endl;
		out << (first >= second) << std::endl;
	} else {
		first < second;
		first <= second;
		first > second;
		first >= second;
	}
	if (redo)
		ft_eq_ope(second, first, benchmark, out, 0);
}

template <class Vector>
void	prepost_incdec(Vector &vct, bool benchmark, std::fstream& out)
{
	typename Vector::iterator it = vct.begin();
	typename Vector::iterator it_tmp;

	if (benchmark == false)
		out << "Pre inc" << std::endl;
	it_tmp = ++it;
	if (benchmark == false)
		out << *it_tmp << " | " << *it << std::endl;

	if (benchmark == false)
		out << "Pre dec" << std::endl;
	it_tmp = --it;
	if (benchmark == false)
		out << *it_tmp << " | " << *it << std::endl;

	if (benchmark == false)
		out << "Post inc" << std::endl;
	it_tmp = it++;
	if (benchmark == false)
		out << *it_tmp << " | " << *it << std::endl;

	if (benchmark == false)
		out << "Post dec" << std::endl;
	it_tmp = it--;
	if (benchmark == false) {
		out << *it_tmp << " | " << *it << std::endl;
		out << "###############################################" << std::endl;
	}
}

template <template <typename, typename> class Vector>
void	vector_it(bool benchmark, std::fstream& out) {
	std::list<int> lst;
	std::list<int>::iterator lst_it;
	for (int i = 1; i < 5; ++i)
		lst.push_back(i * 3);

	Vector<int, std::allocator<int> > vct(lst.begin(), lst.end());
	if (benchmark == false) {
		print_vector("Vector for it - 1:", vct, out);
	}

	lst_it = lst.begin();
	for (int i = 1; lst_it != lst.end(); ++i)
		*lst_it++ = i * 5;
	vct.assign(lst.begin(), lst.end());
	if (benchmark == false) {
		print_vector("Vector for it - 2:", vct, out);
	}

	vct.insert(vct.end(), lst.rbegin(), lst.rend());
	if (benchmark == false) {
		print_vector("Vector for it - 3:", vct, out);
	}

	const int size = 5;
	Vector<int, std::allocator<int> > vct2(size);
	typename Vector<int, std::allocator<int> >::iterator it = vct2.begin();
	typename Vector<int, std::allocator<int> >::const_iterator ite = vct2.begin();

	for (int i = 0; i < size; ++i)
		it[i] = (size - i) * 5;
	prepost_incdec(vct2, benchmark, out);

	it = it + 5;
	it = 1 + it;
	it = it - 4;
	if (benchmark == false) {
		out << *(it += 2) << std::endl;
		out << *(it -= 1) << std::endl;
	} else {
		it += 2;
		it -= 1;
	}

	*(it -= 2) = 42;
	*(it += 2) = 21;

	if (benchmark == false) {
		out << "const_ite +=: " << *(ite += 2) << std::endl;
		out << "const_ite -=: " << *(ite -= 2) << std::endl;

		out << "(it == const_it): " << (ite == it) << std::endl;
		out << "(const_ite - it): " << (ite - it) << std::endl;
		out << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;

		print_vector("Vector in ite at end:", vct2, out);
	} else {
		ite += 2;
		ite -= 2;
		ite == it;
		ite - 1;
		ite + 3 == it;
	}

	const int size3 = 5;
	Vector<foo<int>, std::allocator<foo<int> > > vct3(size3);
	typename Vector<foo<int>, std::allocator<foo<int> > >::iterator it3(vct3.begin());
	typename Vector<foo<int>, std::allocator<foo<int> > >::const_iterator ite3(vct3.end());

	for (int i = 1; it3 != ite3; ++i)
		*it3++ = i;
	if (benchmark == false)
		print_vector("Vector for iterator 3:", vct3, out);

	it3 = vct3.begin();
	ite3 = vct3.begin();

	if (benchmark == false) {
		out << *(++ite3) << std::endl;
		out << *(ite3++) << std::endl;
		out << *ite3++ << std::endl;
		out << *++ite3 << std::endl;

		out << it3->getValue() << std::endl;
		out << ite3->getValue() << std::endl;

		out << *(++it3) << std::endl;
		out << *(it3++) << std::endl;
		out << *it3++ << std::endl;
		out << *++it3 << std::endl;

		out << *(--ite3) << std::endl;
		out << *(ite3--) << std::endl;
		out << *--ite3 << std::endl;
		out << *ite3-- << std::endl;

		out << (*it3).getValue() << std::endl;
		out << (*ite3).getValue() << std::endl;

		out << *(--it3) << std::endl;
		out << *(it3--) << std::endl;
		out << *it3-- << std::endl;
		out << *--it3 << std::endl;
	}

	const int size4 = 5;
	Vector<foo<int>, std::allocator<foo<int> > > vct4(size4);
	typename Vector<foo<int>, std::allocator<foo<int> > >::iterator it_0(vct4.begin());
	typename Vector<foo<int>, std::allocator<foo<int> > >::iterator it_1(vct4.end());
	typename Vector<foo<int>, std::allocator<foo<int> > >::iterator it_mid;

	typename Vector<foo<int>, std::allocator<foo<int> > >::const_iterator cit_0 = vct4.begin();
	typename Vector<foo<int>, std::allocator<foo<int> > >::const_iterator cit_1;
	typename Vector<foo<int>, std::allocator<foo<int> > >::const_iterator cit_mid;

	for (int i = size; it_0 != it_1; --i)
		*it_0++ = i;
	if (benchmark == false) {
		print_vector("Vector for equal operator iterator:", vct4, out);
	}
	it_0 = vct4.begin();
	cit_1 = vct4.end();
	it_mid = it_0 + 3;
	cit_mid = it_0 + 3; cit_mid = cit_0 + 3; cit_mid = it_mid;

	if (benchmark == false) {
		out << std::boolalpha;
		out << ((it_0 + 3 == cit_0 + 3) && (cit_0 + 3 == it_mid)) << std::endl;
		out << "\t\tft_eq_ope:" << std::endl;
	} else {
		it_0 + 3 == cit_0 + 3;
		cit_0 + 3 == it_mid;
	}
	// regular it
	ft_eq_ope(it_0 + 3, it_mid, benchmark, out);
	ft_eq_ope(it_0, it_1, benchmark, out);
	ft_eq_ope(it_1 - 3, it_mid, benchmark, out);
	// const it
	ft_eq_ope(cit_0 + 3, cit_mid, benchmark, out);
	ft_eq_ope(cit_0, cit_1, benchmark, out);
	ft_eq_ope(cit_1 - 3, cit_mid, benchmark, out);
	// both it
	ft_eq_ope(it_0 + 3, cit_mid, benchmark, out);
	ft_eq_ope(it_mid, cit_0 + 3, benchmark, out);
	ft_eq_ope(it_0, cit_1, benchmark, out);
	ft_eq_ope(it_1, cit_0, benchmark, out);
	ft_eq_ope(it_1 - 3, cit_mid, benchmark, out);
	ft_eq_ope(it_mid, cit_1 - 3, benchmark, out);

	const int size5 = 5;
	Vector<int, std::allocator<int> > vct5(size5);
	Vector<int, std::allocator<int> > const vct6(size5);
	typename Vector<int, std::allocator<int> >::iterator it5 = vct5.begin();
	typename Vector<int, std::allocator<int> >::const_iterator ite5 = vct5.begin();

	for (int i = 0; i < size5; ++i)
		it5[i] = i;

	(void)ite5;
	// UNCOMMENT TO CHECK, BUT GIVE COMPILATION ERROR
	//*ite5 = 42;
	//*ite5[1] = 42;
	//typename Vector<int, std::allocator<int> >::iterator it6 = vct6.begin();
}
