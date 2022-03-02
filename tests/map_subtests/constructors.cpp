#include "../tests_utils.hpp"

bool fncomp (char lhs, char rhs) {return lhs<rhs;};

struct classcomp {
	bool operator() (const char& lhs, const char& rhs) const
	{return lhs>rhs;}
};


template <template <class, class, class, class> class Map, template <class> class Comp, template <class, class> class Pair>
void	map_constructor(bool benchmark, std::fstream &out) {

	Map<char,int, Comp<char>, std::allocator<Pair<const char,int> > > first;

	first['a']=10;
	first['b']=30;
	first['c']=50;
	first['d']=70;
	if (benchmark == false) {
		print_map("Example map:", first, out);
	}

	Map<char,int, Comp<char>, std::allocator<Pair<const char,int> > > second (first.begin(),first.end());
	if (benchmark == false) {
		print_map("Iterator construct map:", second, out);
	}

	Map<char,int, Comp<char>, std::allocator<Pair<const char,int> > > third (second);
	if (benchmark == false) {
		print_map("Copy constructor map:", third, out);
	}

	Map<char, int, classcomp, std::allocator<Pair<const char,int> > > fourth;
	fourth['a']=10;
	fourth['b']=30;
	fourth['c']=50;
	fourth['d']=70;
	if (benchmark == false) {
		print_map("Special compare class map:", fourth, out);
	}

	bool(*fn_pt)(char,char) = fncomp;
	Map<char,int,bool(*)(char,char), std::allocator<Pair<const char,int> > > fifth (fn_pt);
	if (benchmark == false) {
		print_map("Pointer function compare map:", fifth, out);
	}

	Map<char,int, Comp<char>, std::allocator<Pair<const char,int> > > copy;
	copy = first;
	if (benchmark == false) {
		print_map("Assignment operator test:", copy, out);
	}

	// Taken and adapted from mli42 ft_containers tester

	std::list<Pair<const int, int> > lst;
	unsigned int lst_size = 7;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(Pair<const int, int>(lst_size - i, i));
	Map<int, int, Comp<int>, std::allocator<Pair<const int, int> > > mp(lst.begin(), lst.end());
	typename Map<int, int, Comp<int>, std::allocator<Pair<const int, int> > >::iterator it =mp.begin(), ite = mp.end();

	Map<int, int, Comp<int>, std::allocator<Pair<const int, int> > > mp_range(it, --(--ite));
	for (int i = 0; it != ite; ++it)
		it->second = ++i * 5;

	it = mp.begin(); ite = --(--mp.end());
	Map<int, int, Comp<int>, std::allocator<Pair<const int, int> > > mp_copy(mp);
	for (int i = 0; it != ite; ++it)
		it->second = ++i * 7;

	if (benchmark == false) {
		print_map("Original:", mp, out);
		print_map("Range constructor:", mp_range, out);
		print_map("Copy:", mp_copy, out);
	}

	mp = mp_copy;
	mp_copy = mp_range;
	mp_range.clear();

	if (benchmark == false) {
		out << "\nAfter modifications\n" << std::endl;
		print_map("Original:", mp, out);
		print_map("Range constructor:", mp_range, out);
		print_map("Copy:", mp_copy, out);
	}

	// Tricky construct from mli42
	std::list<Pair<int, std::string> > lst2;
	typename std::list<Pair<int, std::string> >::iterator itlst;

	lst2.push_back(Pair<int, std::string>(42, "lol"));
	lst2.push_back(Pair<int, std::string>(50, "mdr"));
	lst2.push_back(Pair<int, std::string>(35, "funny"));
	lst2.push_back(Pair<int, std::string>(45, "bunny"));
	lst2.push_back(Pair<int, std::string>(21, "fizz"));
	lst2.push_back(Pair<int, std::string>(35, "this key is already inside"));
	lst2.push_back(Pair<int, std::string>(55, "fuzzy"));
	lst2.push_back(Pair<int, std::string>(38, "buzz"));
	lst2.push_back(Pair<int, std::string>(55, "inside too"));

	if (benchmark == false) {
		out << "List contains: " << lst2.size() << " elements." << std::endl;
		for (itlst = lst2.begin(); itlst != lst2.end(); ++itlst)
			out << itlst->first << " => " << itlst->second << std::endl;
		out << "---------------------------------------------" << std::endl;
	}

	Map<int, std::string, Comp<int>, std::allocator<Pair<const int, std::string> > > mplst(lst2.begin(), lst2.end());
	lst2.clear();

	if (benchmark == false) {
		print_map("Mplst:", mplst, out);
	}


}
