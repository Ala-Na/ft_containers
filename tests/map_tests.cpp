#include <cstdio>

#ifndef NS
 #define NS std
 #include <map>
#else
 #define NS ft
 #include "../containers/map.hpp"
#endif

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
	bool operator() (const char& lhs, const char& rhs) const
	{return lhs<rhs;}
};



int	main() {

	NS::map<char,int> first;

	first['a']=10;
	first['b']=30;
	first['c']=50;
	first['d']=70;

	for (NS::map<char, int>::iterator it = first.begin(); it != first.end(); it++) {
		std::cout << (*it).first << " => " << (*it).second << std::endl;
	}

	NS::map<char,int> second (first.begin(),first.end());

	for (NS::map<char, int>::iterator it = second.begin(); it != second.end(); it++) {
		std::cout << (*it).first << " => " << (*it).second << std::endl;
	}

	NS::map<char,int> third (second);

	for (NS::map<char, int>::iterator it = third.begin(); it != third.end(); it++) {
		std::cout << (*it).first << " => " << (*it).second << std::endl;
	}

	NS::map<char,int,classcomp> fourth;                 // class as Compare

	for (NS::map<char, int>::iterator it = fourth.begin(); it != fourth.end(); it++) {
		std::cout << (*it).first << " => " << (*it).second << std::endl;
	}

	bool(*fn_pt)(char,char) = fncomp;
	NS::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare

	for (NS::map<char, int>::iterator it = fifth.begin(); it != fifth.end(); it++) {
		std::cout << (*it).first << " => " << (*it).second << std::endl;
	}

	NS::map<char,int> copy;
	copy = first;
	std::cout << "size of original: " << first.size() << std::endl;
	std::cout << "size of copy: " << copy.size() << std::endl;

	for (NS::map<char, int>::iterator it = copy.begin(); it != copy.end(); it++) {
		std::cout << it->first << " => " << it->second << std::endl;
	}

	return 0;
	}
