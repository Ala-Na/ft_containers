#include <vector>
#include <iostream>
#include "vector.hpp"

int main()
{
	// Test for range vector constructor
	std::vector<int> first (1, 42);
	printf("%li\n", first.capacity());
	std::vector<int> second (first);
	printf("%li %li\n", second.capacity(), second.size());
	second.assign(3, 100);
	printf("%li %li\n", second.capacity(), second.size());
	second.assign(2, 33);
	printf("%li %li\n", second.capacity(), second.size());
	ft::vector<int> *machin = new ft::vector<int> (4, 42);
  	ft::vector<int> third (second.begin(), second.end());
  	//ft::vector<int> truc ("a","a");
	//third[2] = 42;
	std::cout << "The contents of vector by range is:";
	for (std::vector<int>::iterator it = first.begin(); it != first.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	std::cout << "The contents of vector by range is:";
	for (std::vector<int>::iterator it = second.begin(); it != second.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	delete machin;
}

