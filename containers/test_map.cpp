#include <cstdio>
#include "./map.hpp"
#include <map>

int main ()
{
	ft::map<char, int> mymap;
	mymap['a']=10;
	std::cout << "mymap['a'] is " << mymap['a'] << '\n';
	//first['b']=30;
	//first['c']=50;
	//first['d']=70;

	//std::map<char,int> second (first.begin(),first.end());

	//std::map<char,int> third (second);

	//std::map<char,int,classcomp> fourth;
}
