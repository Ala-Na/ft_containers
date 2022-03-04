#ifndef TESTS_UTILS_HPP
# define TESTS_UTILS_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <stack>
#include "../../containers/map.hpp"
#include "../../containers/vector.hpp"
#include "../../containers/stack.hpp"
#include <list>
#include <fstream>
#include <sys/stat.h>
#include <cstddef>
#include <string>
#include <bits/stdc++.h>
#include <deque>

template <typename Tvec>
void	print_vector (std::string comment, const Tvec& vec, std::fstream& out)
{
	out << "------------------ " << std::endl;
	out << comment << std::endl;
	out << "Size: " << vec.size() << std::endl << std::endl;
	out << "Capacity: " << (vec.size() <= vec.capacity() ? "OK" : "KO") << std::endl;
	typename Tvec::const_iterator	start = vec.begin();
	typename Tvec::const_iterator	stop = vec.end();
	for (; start != stop; start++) {
		out << *start << std::endl;
	}
	out << std::endl;
};

template <typename Tstack>
void	print_stack (std::string comment, Tstack& stack, std::fstream& out)
{
	out << "------------------ " << std::endl;
	out << comment << std::endl;
	out << "Size: " << stack.size() << std::endl << std::endl;
	while (stack.size() != 0) {
		out << stack.top() << std::endl;
		stack.pop();
	}
	out << std::endl;
};

template <typename Tmap>
void	print_map (std::string comment, const Tmap& map, std::fstream& out)
{
	out << "------------------ " << std::endl;
	out << comment << std::endl << std::endl;
	out << "Size: " << map.size() << std::endl;
	typename Tmap::const_iterator	start = map.begin();
	typename Tmap::const_iterator	stop = map.end();
	for (; start != stop; start++) {
		out << start->first << " => " << start->second << std::endl;
	}
};

#endif
