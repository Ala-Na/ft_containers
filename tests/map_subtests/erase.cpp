#include "../tests_utils.hpp"

// Taken and adapted from mli42 ft_containers tester

template <typename Map, typename U>
void	ft_erase(Map &mp, U param, bool benchmark, std::fstream& out)
{
	int iter = 0;
	if (benchmark == false) {
		out << "-- [" << iter++ << "] --" << std::endl;
	}
	mp.erase(param);
	if (benchmark == false) {
		print_map("After erase:", mp, out);
	}
}

template <typename Map, typename U, typename V>
void	ft_erase(Map &mp, U param, V param2, bool benchmark, std::fstream& out)
{
	int iter = 0;
	if (benchmark == false) {
		out << "-- [" << iter++ << "] --" << std::endl;
	}
	mp.erase(param, param2);
	if (benchmark == false) {
		print_map("After erase:", mp, out);
	}
}

template <template <class, class, class, class> class Map, template <class> class Comp, template <class, class> class Pair>
void	map_erase(bool benchmark, std::fstream& out)
{
	std::list<Pair<int, std::string> > lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(Pair<int, std::string>(i, std::string((lst_size - i), i + 65)));
	Map<int, std::string, Comp<int>, std::allocator<Pair<const int, std::string> > > mp(lst.begin(), lst.end());
	if (benchmark == false) {
		print_map("Map for erase testing:", mp, out);
	}

	//ft_erase(mp, ++mp.begin(), benchmark, out);

	//ft_erase(mp, mp.begin(), benchmark, out);
	//ft_erase(mp, --mp.end(), benchmark, out);

	std::cout << "ERASE\n";
	ft_erase(mp, mp.begin(), ++(++(++mp.begin())), benchmark, out);
	//ft_erase(mp, --(--(--mp.end())), --mp.end(), benchmark, out);

	//mp[10] = "Hello";
	//mp[11] = "Hi there";
	//if (benchmark == false) {
	//	print_map("Map after some erasing:", mp, out);
	//}
	//ft_erase(mp, --(--(--mp.end())), mp.end(), benchmark, out);

	//mp[12] = "ONE";
	//mp[13] = "TWO";
	//mp[14] = "THREE";
	//mp[15] = "FOUR";
	//if (benchmark == false) {
	//	print_map("Map after some adding:", mp, out);
	//}
	//ft_erase(mp, mp.begin(), mp.end(), benchmark, out);
	//if (benchmark == false) {
	//	print_map("Map after complete erasing:", mp, out);
	//}
}
