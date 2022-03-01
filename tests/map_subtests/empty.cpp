#include "../tests_utils.hpp"

// Taken and adapted from mli42 ft_containers tester

template <class T>
void	is_empty(T const &mp, bool benchmark, std::fstream& out)
{
	if (benchmark == false) {
		out << "is_empty: " << mp.empty() << std::endl;
	} else {
		mp.empty();
	}
}

template <template <class, class, class, class> class Map, template <class> class Comp, template <class, class> class Pair>
void	map_empty(bool benchmark, std::fstream& out)
{
	std::list<Pair<char, int> > lst;
	unsigned int lst_size = 7;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(Pair<char, int>('a' + i, lst_size - i));

	Map<char, int, Comp<char>, std::allocator<Pair<const char, int> > > mp(lst.begin(), lst.end()), mp2;
	typename Map<char, int, Comp<char>, std::allocator<Pair<const char, int> > >::iterator it;

	lst.clear();
	is_empty(mp, benchmark, out);
	if (benchmark == false) {
		print_map("Map for empty testing - 1:", mp, out);
	}

	is_empty(mp2, benchmark, out);
	mp2 = mp;
	is_empty(mp2, benchmark, out);

	it = mp.begin();
	for (unsigned long int i = 3; i < mp.size(); ++i)
		it++->second = i * 7;

	print_map("Map for empty testing - 2:", mp, out);
	print_map("Map for empty testing - 3:", mp2, out);

	mp2.clear();
	is_empty(mp2, benchmark, out);
	print_map("Map for empty testing - 4:", mp2, out);
}
