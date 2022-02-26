#ifndef TESTS_UTILS_HPP
# define TESTS_UTILS_HPP

#include <iostream>
#include <string>

template <typename Tvecstack>
void	print_vector_or_stack (std::string comment, const Tvecstack& vecstack)
{
	std::cout << "------------------ " << std::endl;
	std::cout << comment << std::endl;
	std::cout << "Size: " << vecstack.size() << std::endl << std::endl;
	typename Tvecstack::const_iterator	start = vecstack.begin();
	typename Tvecstack::const_iterator	stop = vecstack.end();
	for (; start != stop; start++) {
		std::cout << *start << std::endl;
	}
	std::cout << std::endl;
};

template <typename Tmap>
void	print_map (std::string comment, const Tmap& map)
{
	std::cout << "------------------ " << std::endl;
	std::cout << comment << std::endl << std::endl;
	std::cout << "Size: " << map.size() << std::endl;
	typename Tmap::const_iterator	start = map.begin();
	typename Tmap::const_iterator	stop = map.end();
	for (; start != stop; start++) {
		std::cout << start->first << " => " << start->second << std::endl;
	}
};

#endif
