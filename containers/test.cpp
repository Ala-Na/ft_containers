#include <vector>
#include <iostream>
#include "vector.hpp"

int main()
{
	// Test for range vector constructor
	std::vector<int> second (10, 42);
	second[1] = 1;
	second[2] = 2;
	second[9] = 100;
  	ft::vector<int> third (second.begin(), second.end());
  	ft::vector<int> truc ("a","a");
	//third[2] = 42;
	std::cout << "The contents of vector by range is:";
	for (std::vector<int>::iterator it = second.begin(); it != second.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}
