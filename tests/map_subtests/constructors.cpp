#include "../tests_utils.hpp"
#include <map>
#include "../../containers/map.hpp"
#include <fstream>
#include <cstddef>

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
}
