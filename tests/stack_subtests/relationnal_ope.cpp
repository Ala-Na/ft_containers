#include "../main_tests/tests_utils.hpp"

// Taken and adapted from mli42 ft_containers tester

template <class Stack>
void	cmp(const Stack &lhs, const Stack &rhs, bool benchmark, std::fstream& out)
{
	static int i = 0;

	if (benchmark == false) {
		out << "############### [" << i++ << "] ###############"  << std::endl;
		out << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
		out << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
		out << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
	} else {
		(void)(lhs == rhs);
		(void)(lhs != rhs);
		(void)(lhs < rhs);
		(void)(lhs <= rhs);
		(void)(lhs > rhs);
		(void)(lhs >= rhs);
	}
}
template <template <typename, typename> class Stack, template <typename, typename> class Vector>
void	stack_relationnal(bool benchmark, std::fstream &out) {

	typename Stack<int, Vector<int, std::allocator<int> > >::container_type	ctnr;

	ctnr.push_back(21);
	ctnr.push_back(42);
	ctnr.push_back(1337);
	ctnr.push_back(19);
	ctnr.push_back(0);
	ctnr.push_back(183792);

	Stack<int, Vector<int, std::allocator<int> > >	stck(ctnr);
	Stack<int, Vector<int, std::allocator<int> > >	stck2(ctnr);

	cmp(stck, stck, benchmark, out);
	cmp(stck, stck2, benchmark, out);

	stck2.push(60);
	stck2.push(61);
	stck2.push(62);

	cmp(stck, stck2, benchmark, out);
	cmp(stck2, stck, benchmark, out);

	stck.push(42);

	cmp(stck, stck2, benchmark, out);
	cmp(stck2, stck, benchmark, out);

	stck.push(100);

	cmp(stck, stck2, benchmark, out);
	cmp(stck2, stck, benchmark, out);

	typename Stack<int, std::list<int> >::container_type	ctnr2;

	ctnr2.push_back(21);
	ctnr2.push_back(42);
	ctnr2.push_back(1337);
	ctnr2.push_back(19);
	ctnr2.push_back(0);
	ctnr2.push_back(183792);

	Stack<int, std::list<int> >	stck3(ctnr2);
	Stack<int, std::list<int> >	stck4(ctnr2);

	cmp(stck3, stck3, benchmark, out);
	cmp(stck3, stck4, benchmark, out);

	stck4.push(60);
	stck4.push(61);
	stck4.push(62);

	cmp(stck3, stck4, benchmark, out);
	cmp(stck4, stck3, benchmark, out);

	stck3.push(42);

	cmp(stck3, stck4, benchmark, out);
	cmp(stck4, stck3, benchmark, out);

	stck3.push(100);

	cmp(stck3, stck4, benchmark, out);
	cmp(stck4, stck3, benchmark, out);
}
