#include <vector>
#include <iostream>
#include "vector.hpp"

int main()
{
	std::vector<int> second (4,100);
  	ft::vector<int> third (second.begin(), second.end());
	third[2] = 42;
	std::cout << "The contents of vector by range is:";
	for (std::vector<int>::iterator it = third.begin(); it != third.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}
