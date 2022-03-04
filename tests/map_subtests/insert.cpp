#include "../tests_utils.hpp"

// Taken and adapted from mli42 ft_containers tester

template <template <typename, typename> class Pair, typename Map>
void	ft_insert(Map &mp, Pair<int, std::string> param, bool benchmark, std::fstream& out)
{
	Pair<typename Map::iterator, bool> tmp;

	int iter = 0;
	if (benchmark == false) {
		out << "\t-- [" << iter++ << "] --" << std::endl;
	}
	tmp = mp.insert(param);
	if (benchmark == false) {
		out << "insert return: " << tmp.first->first << tmp.first->second << std::endl;
		out << "Created new node: " << tmp.second << std::endl;
		print_map("After insert:", mp, out);
	}
}

template <typename Map, typename U, template <typename, typename> class Pair>
void	ft_insert(Map &mp, U param, Pair<int, std::string> param2, bool benchmark, std::fstream& out)
{
	typename Map::iterator tmp;

	int iter = 0;
	if (benchmark == false) {
		out << "\t-- [" << iter++ << "] --" << std::endl;
	}
	tmp = mp.insert(param, param2);
	if (benchmark == false) {
		out << "insert return: " << tmp->first << " & " << tmp->second << std::endl;
		print_map("After insert:", mp, out);
	}
}


template <typename Map, typename Pair>
void	ft_insert(Map &mp, Pair param, Pair param2, bool benchmark, std::fstream& out)
{
	int iter = 0;
	if (benchmark == false) {
		out << "\t-- [" << iter++ << "] --" << std::endl;
	}
	mp.insert(param, param2);
	if (benchmark == false) {
		print_map("After insert:", mp, out);
	}
}

template <template <class, class, class, class> class Map, template <class> class Comp, template <class, class> class Pair, template <typename, typename> class Vector>
void	map_insert(bool benchmark, std::fstream& out)
{
	// Insert from mli42

	Map<int, std::string, Comp<int>, std::allocator<Pair<const int, std::string> > > mp, mp2;

	ft_insert(mp, Pair<int, std::string>(42, "lol"), benchmark, out);
	ft_insert(mp, Pair<int, std::string>(42, "mdr"), benchmark, out);

	ft_insert(mp, Pair<int, std::string>(50, "mdr"), benchmark, out);
	ft_insert(mp, Pair<int, std::string>(35, "funny"), benchmark, out);

	ft_insert(mp, Pair<int, std::string>(45, "bunny"), benchmark, out);
	ft_insert(mp, Pair<int, std::string>(21, "fizz"), benchmark, out);
	ft_insert(mp, Pair<int, std::string>(38, "buzz"), benchmark, out);

	ft_insert(mp, mp.begin(), Pair<int, std::string>(55, "fuzzy"), benchmark, out);

	ft_insert(mp2, mp2.begin(), Pair<int, std::string>(1337, "beauty"), benchmark, out);
	ft_insert(mp2, mp2.end(), Pair<int, std::string>(1000, "Hello"), benchmark, out);
	ft_insert(mp2, mp2.end(), Pair<int, std::string>(1500, "World"), benchmark, out);

	// Insert2 from mli42
	Vector<Pair<int, std::string>, std::allocator<Pair<int, std::string> > > lst;
	typename Vector<Pair<int, std::string>, std::allocator<Pair<int, std::string> > >::iterator itlst;

	lst.push_back(Pair<int, std::string>(42, "lol"));

	lst.push_back(Pair<int, std::string>(50, "mdr"));
	lst.push_back(Pair<int, std::string>(35, "funny"));

	lst.push_back(Pair<int, std::string>(45, "bunny"));
	lst.push_back(Pair<int, std::string>(21, "fizz"));
	lst.push_back(Pair<int, std::string>(38, "buzz"));
	lst.push_back(Pair<int, std::string>(55, "fuzzy"));

	if (benchmark == false) {
		out << "List contains:" << std::endl;
		for (itlst = lst.begin(); itlst != lst.end(); ++itlst)
			out << itlst->first << " => " << itlst->second << std::endl;
	}

	Map<int, std::string, Comp<int>, std::allocator<Pair<const int, std::string> > > mp3;
	ft_insert(mp, lst.begin(), lst.end(), benchmark, out);

	lst.clear();

	lst.push_back(Pair<int, std::string>(87, "hey"));
	lst.push_back(Pair<int, std::string>(47, "eqweqweq"));
	lst.push_back(Pair<int, std::string>(35, "this key is already inside"));
	lst.push_back(Pair<int, std::string>(23, "but not that one"));
	lst.push_back(Pair<int, std::string>(1, "surprising isnt it?"));
	lst.push_back(Pair<int, std::string>(100, "is it enough??"));
	lst.push_back(Pair<int, std::string>(55, "inside map too"));

	if (benchmark == false) {
		out << "List contains:" << std::endl;
		for (itlst = lst.begin(); itlst != lst.end(); ++itlst)
			out << itlst->first << " => " << itlst->second << std::endl;
	}

	ft_insert(mp3, lst.begin(), lst.begin(), benchmark, out);
	ft_insert(mp3, lst.begin(), lst.end(), benchmark, out);
}
