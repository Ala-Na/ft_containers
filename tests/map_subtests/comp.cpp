//Taken and adapted from mli42 ft_containers tester

#include "../main_tests/tests_utils.hpp"

template <class Map, typename const_it>
void	ft_comp(const Map &mp, const const_it &it1, const const_it &it2, bool benchmark, std::fstream& out)
{
	bool res[2];

	int i = 0;
	if (benchmark == false) {
		out << "\t-- [" << ++i << "] --" << std::endl;
	}
	res[0] = mp.key_comp()(it1->first, it2->first);
	res[1] = mp.value_comp()(*it1, *it2);
	if (benchmark == false) {
		out << "with [" << it1->first << " and " << it2->first << "]: ";
		out << "key_comp: " << res[0] << " | " << "value_comp: " << res[1] << std::endl;
	}
}

template <template <class, class, class, class> class Map, template <class> class Comp, template <class, class> class Pair>
void	map_comp(bool benchmark, std::fstream &out)
{
	Map<char, float, Comp<char>, std::allocator<Pair<const char, float> > >	mp;

	mp['a'] = 2.3;
	mp['b'] = 1.4;
	mp['c'] = 0.3;
	mp['d'] = 4.2;
	if (benchmark == false) {
		print_map("Map for comparison - 1:", mp, out);
	}

	for (typename Map<char, float, Comp<char>, std::allocator<Pair<const char, float> > >::const_iterator it1 = mp.begin(); it1 != mp.end(); ++it1) {
		for (typename Map<char, float, Comp<char>, std::allocator<Pair<const char, float> > >::const_iterator it2 = mp.begin(); it2 != mp.end(); ++it2) {
			ft_comp<Map<char, float, Comp<char>, std::allocator<Pair<const char, float> > >, typename Map<char, float, Comp<char>, std::allocator<Pair<const char, float> > >::const_iterator >(mp, it1, it2, benchmark, out);
		}
	}
	if (benchmark == false) {
		print_map("Map for comparison - 2:", mp, out);
	}
}
