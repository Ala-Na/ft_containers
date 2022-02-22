#include <bits/stdc++.h>
#include "./tree.hpp"
#include <map>

void menu(){
		std::cout << "\n__________________________________________";
		std::cout << "\n\n  --HEIGHT BALANCED BINARY SEARCH TREE--";
		std::cout << "\n          --(Red-Black-Tree)--";
		std::cout << "\n__________________________________________";
		std::cout << "\n\n1. Insert elements into the tree.";
		std::cout << "\n2. Search for an element.";
		std::cout << "\n3. PRE-ORDER Tree-Walk.";
		std::cout << "\n4. POST-ORDER Tree-Walk.";
		std::cout << "\n5. Remove an element from the tree.";
		std::cout << "\n6. Exit.";
		std::cout << "\n__________________________________________";
		std::cout << "\nYour Choice -- ";
}

int main(){
	ft::rb_tree<int, ft::pair<int, int>, std::less<int>, std::allocator<int>, ft::use_first<ft::pair<int, int>>> demo;
	demo.insert_value(ft::make_pair(2, 2));
	demo.insert_value(ft::make_pair(1, 1));
	demo.insert_value(ft::make_pair(6, 6));
	demo.insert_value(ft::make_pair(3, 3));
	demo.insert_value(ft::make_pair(4, 4));
	demo.insert_value(ft::make_pair(10, 10));
	std::map<char,int> first;

	first['a']=10;
	first['b']=30;
	first['c']=50;
	first['d']=70;
	first['a']=15;
	first.insert(std::pair<char, int>('d', 150));
	for (std::map<char,int>::iterator itt = first.begin(); itt != first.end(); ++itt)
		std::cout << itt->first << ' ' << itt->second << std::endl;
	std::map<char,int>::iterator it = (first.end());
	std::cout << it->first << std::endl;
	for (ft::rb_tree<int, ft::pair<int, int>, std::less<int>, std::allocator<int>, ft::use_first<ft::pair<int, int>>>::reverse_iterator itt = demo.rbegin(); itt != demo.rend(); ++itt)
		std::cout << itt->first << std::endl;
	int info, input;
	menu();
	std::cin >> info;
	while(info != 6){
		switch (info){
			case 1: std::cout << "\nElement to be inserted -- ";
					std::cin >> input; demo.insert_value(ft::make_pair(input, input));
					break;

			case 2: std::cout << "\nElement to be searched -- ";
					std::cin >> input;
					if(demo.seek_node(input)) { std::cout << "Element found.\n"; }
					else { std::cout << "Element not found.\n"; }
					break;

			case 3: std::cout << "Pre-Order Tree Walk ";
					demo.PreorderTraversal(demo.get_root());
					std::cout << std::endl;
					break;

			case 4: std::cout << "Post-Order Tree Walk ";
					demo.PostorderTraversal(demo.get_root());
					std::cout << std::endl;
					break;

			case 5: std::cout << "\nElement to be deleted? -- ";
					std::cin >> input;
					if(demo.seek_node(input)) { std::cout << "Element found.\n";
					demo.remove_node(demo.seek_node(input)); }
					break;

			default: std::cout << "Wrong Choice.\n";
			}
	std::cout << "\nAnything Else?";
	std::cin >> info;
		}
std::cout << "\nTerminating.... ";
return 0;
	}

