#include "../main_tests/tests_utils.hpp"

// Taken and adapted from mli42 ft_containers tester

template <class Map>
void	cmp(const Map &lhs, const Map &rhs, bool benchmark, std::fstream& out)
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

template <template <class, class, class, class> class Map, template <class> class Comp, template <class, class> class Pair>
void	map_relationnal(bool benchmark, std::fstream& out)
{

	Map<char, int, Comp<char>, std::allocator<Pair<const char, int > > > mp1, mp2;

	mp1['a'] = 2; mp1['b'] = 3; mp1['c'] = 4; mp1['d'] = 5;
	mp2['a'] = 2; mp2['b'] = 3; mp2['c'] = 4; mp2['d'] = 5;

	cmp(mp1, mp1, benchmark, out);
	cmp(mp1, mp2, benchmark, out);

	mp2['e'] = 6; mp2['f'] = 7; mp2['h'] = 8; mp2['h'] = 9;

	cmp(mp1, mp2, benchmark, out);
	cmp(mp2, mp1, benchmark, out);

	(++(++mp1.begin()))->second = 42;

	cmp(mp1, mp2, benchmark, out);
	cmp(mp2, mp1, benchmark, out);

	mp1.swap(mp2);

	cmp(mp1, mp2, benchmark, out);
	cmp(mp2, mp1, benchmark, out);
}
