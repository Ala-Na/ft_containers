#include "../tests_utils.hpp"

// Taken and adapted from mli42 ft_containers tester

template <template <class, class, class, class> class Map, template <class> class Comp, template <class, class> class Pair>
void	map_swap(bool benchmark, std::fstream& out)
{
	std::list<Pair<char, int> > lst;

	unsigned int lst_size = 7;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(Pair<char, int>('a' + i, lst_size - i));
	Map<char, int, Comp<char>, std::allocator<Pair<const char, int > > > foo(lst.begin(), lst.end());

	lst.clear(); lst_size = 4;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(Pair<char, int>('z' - i, i * 5));
	Map<char, int, Comp<char>, std::allocator<Pair<const char, int > > > bar(lst.begin(), lst.end());

	typename Map<char, int, Comp<char>, std::allocator<Pair<const char, int > > >::const_iterator it_foo = foo.begin();
	typename Map<char, int, Comp<char>, std::allocator<Pair<const char, int > > >::const_iterator it_bar = bar.begin();

	if (benchmark == false) {
		print_map("Before swap foo map:", foo, out);
		print_map("Before swap foo map:", bar, out);
	}

	foo.swap(bar);

	if (benchmark == false) {
		print_map("After swap foo map:", foo, out);
		print_map("After swap foo map:", bar, out);
		out << "Iterator validity:" << std::endl;
		out << (it_foo == bar.begin() ? "true" : "false") << std::endl;
		out << (it_bar == foo.begin() ? "true" : "false") << std::endl;
	}
}
