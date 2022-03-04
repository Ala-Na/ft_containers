#include "../main_tests/tests_utils.hpp"

// Taken and adapted from mli42 ft_containers tester

template <class T1, class Map>
void	ft_find(Map mp, T1 const &k, bool benchmark, std::fstream& out)
{
	typename Map::iterator ret = mp.find(k);

	if (ret != mp.end() && benchmark == false)
		out << ret->first << " => " << ret->second << std::endl;
	else if (benchmark == false)
		out << "map::find(" << k << ") returned end()" << std::endl;
}

template <class T1, class Map>
void	ft_count(Map mp, T1 const &k, bool benchmark, std::fstream& out)
{
	if (benchmark == false)
		out << "map::count(" << k << ")\treturned [" << mp.count(k) << "]" << std::endl;
}

template <template <class, class, class, class> class Map, template <class> class Comp, template <class, class> class Pair>
void		map_find_count(bool benchmark, std::fstream& out)
{
	Map<int, std::string, Comp<int>, std::allocator<Pair<const int, std::string> > > mp;

	mp[42] = "fgzgxfn";
	mp[25] = "funny";
	mp[80] = "hey";
	mp[12] = "no";
	mp[27] = "bee";
	mp[90] = "8";
	if (benchmark == false) {
		print_map("Map for find:", mp, out);
	}

	if (benchmark == false) {
		out << "\t-- FIND --" << std::endl;
	}
	ft_find(mp, 12, benchmark, out);
	ft_find(mp, 3, benchmark, out);
	ft_find(mp, 35, benchmark, out);
	ft_find(mp, 90, benchmark, out);
	ft_find(mp, 100, benchmark, out);

	if (benchmark == false) {
		out << "\t-- COUNT --" << std::endl;
	}

	ft_count(mp, -3, benchmark, out);
	ft_count(mp, 12, benchmark, out);
	ft_count(mp, 3, benchmark, out);
	ft_count(mp, 35, benchmark, out);
	ft_count(mp, 90, benchmark, out);
	ft_count(mp, 100, benchmark, out);

	mp.find(27)->second = "newly inserted mapped_value";

	if (benchmark == false) {
		print_map("After some modifications:", mp, out);
	}
	Map<int, std::string, Comp<int>, std::allocator<Pair<const int, std::string> > > const c_map(mp.begin(), mp.end());
	if (benchmark == false) {
		out << "const map.find(" << 42 << ")->second: [" << c_map.find(42)->second << "]" << std::endl;
		out << "const map.count(" << 80 << "): [" << c_map.count(80) << "]" << std::endl;
	}
}
