#include "../tests_utils.hpp"

// Taken and adapted from mli42 ft_containers tester

template <class Map, template <class, class> class Pair>
void	ft_bound(Map &mp, const int &param, bool benchmark, std::fstream &out)
{
	typename Map::iterator ite = mp.end(), it[2];
	Pair<typename Map::iterator, typename Map::iterator> ft_range;

	int iter = 0;
	if (benchmark == false) {
		out << "-- [" << iter++ << "] --" << std::endl;
		out << "with key [" << param << "]:" << std::endl;
	}
	it[0] = mp.lower_bound(param); it[1] = mp.upper_bound(param);
	ft_range = mp.equal_range(param);
	if (benchmark == false) {
		out << "lower_bound: ";
		if (it[0] == ite) {
			out <<  "end()" << std::endl;
		} else {
			out << it[0]->first << " => " << it[0]->second << std::endl;
		}
		out << "upper_bound: ";
		if (it[1] == ite) {
			out <<  "end()" << std::endl;
		} else {
			out << it[1]->first << " => " << it[1]->second << std::endl;
		}
		out << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
	}
}

template <class Map, template <class, class> class Pair>
void	ft_const_bound(const Map &mp, const int &param, bool benchmark, std::fstream &out)
{
	typename Map::const_iterator ite = mp.end(), it[2];
	Pair<typename Map::const_iterator, typename Map::const_iterator> ft_range;

	int iter = 0;
	if (benchmark == false) {
		out << "-- [" << iter++ << "] (const) --" << std::endl;
		out << "with key [" << param << "]:" << std::endl;
	}
	it[0] = mp.lower_bound(param); it[1] = mp.upper_bound(param);
	ft_range = mp.equal_range(param);
	if (benchmark == false) {
		out << "lower_bound: ";
		if (it[0] == ite) {
			out <<  "end()" << std::endl;
		} else {
			out << it[0]->first << " => " << it[0]->second << std::endl;
		}
		out << "upper_bound: ";
		if (it[1] == ite) {
			out <<  "end()" << std::endl;
		} else {
			out << it[1]->first << " => " << it[1]->second << std::endl;
		}
		out << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
	}
}

template <template <class, class, class, class> class Map, template <class> class Comp, template <class, class> class Pair>
void	map_bounds(bool benchmark, std::fstream& out) {
	std::list<Pair<int, int> > lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(Pair<int,int>(i + 1, (i + 1) * 3));
	Map<int, int, Comp<int>, std::allocator<Pair<const int, int> > > mp(lst.begin(), lst.end());
	if (benchmark == false) {
		print_map("Map for bounds testing - 1: ", mp, out);
	}

	ft_const_bound<Map<int, int, Comp<int>, std::allocator<Pair<const int, int> > >, Pair>(mp, -10, benchmark, out);
	ft_const_bound<Map<int, int, Comp<int>, std::allocator<Pair<const int, int> > >, Pair>(mp, 1, benchmark, out);
	ft_const_bound<Map<int, int, Comp<int>, std::allocator<Pair<const int, int> > >, Pair>(mp, 5, benchmark, out);
	ft_const_bound<Map<int, int, Comp<int>, std::allocator<Pair<const int, int> > >, Pair>(mp, 10, benchmark, out);
	ft_const_bound<Map<int, int, Comp<int>, std::allocator<Pair<const int, int> > >, Pair>(mp, 50, benchmark, out);

	if (benchmark == false) {
		print_map("Map for bounds testing - 2: ", mp, out);
	}

	mp.lower_bound(3)->second = 404;
	mp.upper_bound(7)->second = 842;
	ft_bound<Map<int, int, Comp<int>, std::allocator<Pair<const int, int> > >, Pair>(mp, 5, benchmark, out);

	if (benchmark == false) {
		print_map("Map for bounds testing - 3: ", mp, out);
	}
};
