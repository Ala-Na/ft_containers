#include <bits/stdc++.h>
#include "./tree_iterator.hpp"
#include "./iterators.hpp"

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
	ft::rb_tree<int, std::less<int>> demo;
	int info, input;
	menu();
	std::cin >> info;
	while(info != 6){
		switch (info){
			case 1: std::cout << "\nElement to be inserted -- ";
					std::cin >> input; demo.insert_value(input);
					break;

			case 2: std::cout << "\nElement to be searched -- ";
					std::cin >> input;
					if(demo.TreeSearch(input)) { std::cout << "Element found.\n"; }
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
					if(demo.TreeSearch(input)) { std::cout << "Element found.\n"; }
					demo.remove_node(demo.TreeSearch(input));
					break;

			default: std::cout << "Wrong Choice.\n";
			}
	std::cout << "\nAnything Else?";
	std::cin >> info;
		}
std::cout << "\nTerminating.... ";
return 0;
	}

