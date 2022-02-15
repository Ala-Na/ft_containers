#include <vector>
#include <iostream>
#include "vector.hpp"

int main()
{
	// Test for range vector constructor
	std::vector<int> first(3, 2);
	printf("%li\n", first.capacity());
	printf("%li\n", *(first.erase(first.begin(), first.begin())));
	for (std::vector<int>::iterator it = first.erase(first.begin(), first.begin()); it != first.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	printf("%li\n", *first.erase(first.begin()));
	std::vector<int> second (first);
	printf("%li %li\n", second.capacity(), second.size());
	second.assign(26, 100);
	//second.insert(second.begin(), -1, 2);
	printf("%li %li\n", second.capacity(), second.size());
	printf("%li\n", *(second.insert(second.begin() + 6, 56)));
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
	third = *machin;
	for (rev_it = third.rbegin(); rev_it != third.rend(); ++rev_it)
		std::cout << ' ' << *rev_it;
	std::cout << '\n';
	third.assign(12, 9);
	ft::vector<int>::iterator it2 = third.begin();
	printf("%i\n", *(third.insert(third.begin() + 4, 42)));
	for (it = third.begin(); it != third.end(); ++it)
		std::cout << ' ' << *it;
	printf("\n");
	third.insert(third.begin() + 1, 3, 42);
	third.insert(third.begin(), third.begin(), third.end());
	//third.insert(third.begin() + 1, -3, 42);
	for (it = third.begin(); it != third.end(); ++it)
		std::cout << ' ' << *it;
	printf("\n");
	printf("%li %li\n", third.capacity(), third.size());
	ft::vector<int> ty(5, 2);
	printf("%li\n", *(ty.erase(ty.begin(), ty.begin() + 2)));
	ty.swap(third);
	for (ft::vector<int>::iterator it = ty.erase(ty.begin()); it != ty.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	delete machin;
}

