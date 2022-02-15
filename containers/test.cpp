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
	ft::vector<int> third (1, 42);
	ft::vector<int> *machin = new ft::vector<int> (4, 42);
	//std::vector<int> third (second.begin(), second.end());
  	ft::vector<int> truc ("a","a");
	ft::vector<int> lol(third);
	//third[2] = 42;
	std::cout << "The contents of vector by range is:";
	for (std::vector<int>::iterator it = first.begin(); it != first.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	std::cout << "The contents of vector by range is:";
	for (std::vector<int>::iterator it = second.begin(); it != second.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	printf("dis: %li\n", std::distance(first.begin(), first.begin()));
	ft::vector<int>::iterator it;
	ft::vector<int>::reverse_iterator rev_it;
	for (it = third.begin(); it != third.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	for (rev_it = third.rbegin(); rev_it != third.rend(); ++rev_it)
		std::cout << ' ' << *rev_it;
	std::cout << '\n';
	//for (ft::vector<int>::iterator it = lol.begin(); it != lol.end(); ++it)
	//	std::cout << ' ' << *it;
	//std::cout << '\n';
	delete machin;
}

