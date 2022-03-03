#include "../tests_utils.hpp"

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

template <template <typename, typename> class Stack, template <typename, typename> class Vector>
void	stack_constructor(bool benchmark, std::fstream &out) {
	std::deque<int> mydeque (3,100);
	Vector<int, std::allocator<int> > myvector (2,200);

	Stack<int, Vector<int, std::allocator<int> > > first;
	Stack<int, std::deque<int> > second (mydeque);

	Stack<int, Vector<int, std::allocator<int> > > third;
	Stack<int, Vector<int, std::allocator<int> > > fourth (myvector);

	if (benchmark == false) {
		out << "size of first: " << first.size() << '\n';
		out << "size of second: " << second.size() << '\n';
		out << "size of third: " << third.size() << '\n';
		out << "size of fourth: " << fourth.size() << '\n';
		print_stack("Stack:", first, out);
		print_stack("Stack:", second, out);
		print_stack("Stack:", third, out);
		print_stack("Stack:", fourth, out);
	}

	// Taken and adapted from mli42 ft_containers tester
	Stack<foo<int>, Vector<foo<int>, std::allocator<foo<int> > > > stck;

	if (benchmark == false) {
		out << "empty: " << stck.empty() << std::endl;
		out << "size: " << stck.size() << std::endl;
	}

	stck.push(41);
	stck.push(29);
	stck.push(10);
	stck.push(42);
	if (benchmark == false) {
		out << "Added some elements" << std::endl;
		out << "empty: " << stck.empty() << std::endl;
		print_stack("Stack:", stck, out);
	}

	typename Stack<foo<int>, Vector<foo<int>, std::allocator<foo<int> > > >::container_type	ctnr;

	ctnr.push_back(21);
	ctnr.push_back(42);
	ctnr.push_back(1337);
	ctnr.push_back(19);
	ctnr.push_back(0);
	ctnr.push_back(183792);

	Stack<foo<int>, Vector<foo<int>, std::allocator<foo<int> > > > stck2(ctnr);

	if (benchmark == false) {
		out << "empty: " << stck2.empty() << std::endl;
		out << "size: " << stck2.size() << std::endl;
	}

	stck2.push(1);
	stck2.push(2);
	stck2.push(3);
	stck2.push(4);
	stck2.push(5);
	stck2.push(6);

	if (benchmark == false) {
		out << "Added some elements" << std::endl;
		out << "empty: " << stck2.empty() << std::endl;
		print_stack("Stack:", stck2, out);
	}

	typename Stack<foo<int>, Vector<foo<int>, std::allocator<foo<int> > > >::container_type	ctnr3;

	ctnr3.push_back(21);
	ctnr3.push_back(42);
	ctnr3.push_back(1337);
	ctnr3.push_back(19);
	ctnr3.push_back(0);
	ctnr3.push_back(183792);

	Stack<foo<int>, Vector<foo<int>, std::allocator<foo<int> > > > stck3(ctnr3);

	if (benchmark == false) {
		out << "empty: " << stck3.empty() << std::endl;
		out << "size: " << stck3.size() << std::endl;
	}

	stck3.push(1);
	stck3.push(2);
	stck3.push(3);
	stck3.push(4);
	stck3.push(5);
	stck3.push(6);

	if (benchmark == false) {
		out << "Added some elements" << std::endl;
		out << "empty: " << stck3.empty() << std::endl;
		print_stack("Stack:", stck3, out);
	}
}
