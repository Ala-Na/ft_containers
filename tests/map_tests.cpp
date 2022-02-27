#include "tests_utils.hpp"

#if (NS == ft || NS == FT)
 #undef NS
 #define NS ft
 #include "../containers/map.hpp"
#else
 #undef NS
 #define NS std
 #include <map>
#endif

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
	bool operator() (const char& lhs, const char& rhs) const
	{return lhs>rhs;}
};

int	main() {

	NS::map<char,int> first;

	first['a']=10;
	first['b']=30;
	first['c']=50;
	first['d']=70;
	print_map("Example map:", first);

	NS::map<char,int> second (first.begin(),first.end());
	print_map("Iterator construct map:", second);

	NS::map<char,int> third (second);
	print_map("Copy constructor map:", third);

	NS::map<char,int,classcomp> fourth;
	fourth['a']=10;
	fourth['b']=30;
	fourth['c']=50;
	fourth['d']=70;
	print_map("Special compare class map:", fourth);

	bool(*fn_pt)(char,char) = fncomp;
	NS::map<char,int,bool(*)(char,char)> fifth (fn_pt);
	print_map("Pointer function compare map:", fifth);

	NS::map<char,int> copy;
	copy = first;
	print_map("Assignment operator test:", copy);

	return 0;
	}
