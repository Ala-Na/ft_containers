/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:11:55 by anadege           #+#    #+#             */
/*   Updated: 2022/02/17 17:47:19 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
# define TREE_HPP

#include <cstddef>
#include <memory>
#include <cstdio> //TODO delete, test purpose only
#include <iostream> // TODO delete, test purpose only
#include "./iterators.hpp"
#include "./id_comp.hpp"
#include "./exceptions.hpp"
#include "./pair.hpp"
#include "./tree_iterator.hpp"

namespace ft
{

	// -----------------------------------
	// Enum for red-black tree node color
	// -----------------------------------

	enum rb_tree_color {
		red = false,
		black = true
	};

	// ----------------------------------
	// Node structure for red-black tree
	// ----------------------------------

	template <typename Value>
	struct node {
		Value			data; // for map : pair of key/value
		node*			parent;
		node*			left_child;
		node*			right_child;
		rb_tree_color	color;

		// - Constructor
		node (Value& data) :
			data(data), parent(NULL), left_child(NULL), right_child(NULL), color(black)
		{}

		node&	operator* () const {
			return *this;
		}

		node*	operator-> () const {
			return &(operator*());
		}

		// - Setters

		void	set_to_red () {
			this->color = red;
		}

		void	set_to_black () {
			this->color = black;
		}

		void	set_parent (node* parent) {
			this->parent = parent;
		}

		void	set_left_child (node* left_child) {
			this->left_child = left_child;
		}

		void	set_right_child (node* right_child) {
			this->right_child = right_child;
		}

		// - Unsetters

		void	unset_parent () {
			this->parent = NULL;
		}

		void	unset_left_child () {
			this->left_child = NULL;
		}

		void	unset_right_child () {
			this->right_child = NULL;
		}

		// - Getters
		node*	get_parent () {
			return this->parent;
		}

		node*	get_left_child () {
			return this->left_child;
		}

		node*	get_right_child () {
			return this->right_child;
		}

		node*	get_grandparent () {
			if (!this->parent)
				return NULL;
			return (this->parent)->parent;
		}

		node*	get_right_uncle () {
			if (!this->get_parent() || !this->get_grandparent())
				return NULL;
			return (this->get_grandparent())->right_child;
		}

		node*	get_left_uncle () {
			if (!this->get_parent() || !this->get_grandparent())
				return NULL;
			return (this->get_grandparent())->left_child;
		}

		Value&	get_data () {
			return this->data;
		}

		rb_tree_color	get_color () {
			return this->color;
		}

		// - Position checkers
		bool	is_right_child() {
			return ((this->get_parent() != NULL)
				&& ((this->get_parent())->get_right_child() != NULL)
				&& (this == (this->get_parent())->get_right_child()));
		}

		bool	is_left_child() {
			return ((this->get_parent() != NULL)
				&& ((this->get_parent())->get_left_child() != NULL)
				&& (this == (this->get_parent())->get_left_child()));
		}
	};

	template <typename T>
	ft::node<T>*	increment_tree(const ft::node<T>* node) {
		ft::node<T>*(tmp_node);
		if (node->get_right_child() != NULL) {
			node = node->get_right_child();
			while (node->get_left_child() != NULL) {
				node = node->get_left_child();
			}
		} else {
			tmp_node = node->get_parent();
			while (node == tmp_node->get_right_node() != NULL) {
				node = tmp_node;
				tmp_node = tmp_node->get_parent();
			}
			if (node->get_right_child() != tmp_node) {
				node = tmp_node;
			}
		}
		return node;
	};

	template <typename T>
	ft::node<T>*	decrement_tree(const ft::node<T>* node) {
		ft::node<T>*	tmp_node;
		if ((node->get_grandparent() == node) && (node->get_color() == red)) {
			return node->get_right_node();
		} else if (node->get_left_child() != NULL) {
			tmp_node = node->get_left_child();
			while(tmp_node->get_right_child() != NULL) {
				tmp_node = tmp_node->get_right_child();
			}
			return tmp_node;
		}
		tmp_node = node->get_parent();
		while (node == tmp_node->get_left_child()) {
			node = tmp_node;
			tmp_node = tmp_node->get_parent();
		}
		return tmp_node;
	};

	// - Minimum function
	template <typename T>
	ft::node<T>*	tree_minimum(ft::node<T>* current) {
		while (current->get_left_child() != NULL) {
			current = current->get_left_child();
		}
		return current;
	};

	// - Maximum function
	template <typename T>
	ft::node<T>*	tree_maximum(ft::node<T>* current) {
		while (current->get_right_child() != NULL) {
			current = current->get_right_child();
		}
		return current;
	};

	// ---------------------------------
	// Red-black tree class and methods
	// ---------------------------------


	// Here, value represent a pair for map
	template <typename Value, class Compare = ft::less<Value>>//, typename Allocator>
	class rb_tree {

		public:

			typedef Value										value_type;
			//typedef Allocator									allocator_type;
			typedef Compare										compare_function;
			typedef ft::node<Value>								node_type;
			typedef std::size_t									size_type;
			typedef std::ptrdiff_t								difference_type;
			typedef value_type&									reference;
			typedef const value_type&							const_reference;
			typedef value_type*									pointer;
			typedef const value_type*							const_pointer;
			//typedef ft::rb_tree_iterator<value_type>	iterator;


		private:
			node_type*			root;
			size_type			node_count;
			compare_function	compare;
			//allocator_type		alloc;

		public:
			// - Constructors
			rb_tree () : root(NULL), node_count(0) {}

			rb_tree (compare_function compare) :
				root(NULL), node_count(0), compare(compare) {}

			rb_tree(const rb_tree& other) :
				root(other.root), node_count(other.root_count), compare(other.compare) {}

			// - Root getter
			node_type*	get_root () {
				return this->root;
			}

			// - Size function
			size_t	size () {
				return this->node_count;
			}

			// - Empty function
			bool	empty() {
				return (this->node_count == 0);
			}




			// --------------------------------------------------------
			// Functions for RBTree algorithm (insert, delete, rotate)
			// --------------------------------------------------------

			// - Left rotate function
			void	left_rotate (node_type* node) {
				node_type*	next_node = node->get_right_child();
				node->set_right_child(next_node->get_left_child());
				if (next_node->get_left_child() != NULL) {
					next_node->set_left_child(node);
				}
				next_node->set_parent(node->get_parent());
				if (node->get_parent() == NULL) {
					this->root = next_node;
				} else if (node->is_left_child() == true) {
					(node->get_parent())->set_left_child(next_node);
				} else {
					(node->get_parent())->set_right_child(next_node);
				}
				next_node->set_left_child(node);
				node->set_parent(next_node);
			}

			// - Right rotate function
			void	right_rotate (node_type* node) {
				node_type*	next_node = node->get_left_child();
				node->set_left_child(next_node->get_right_child());
				if (next_node->get_right_child() != NULL) {
					next_node->set_right_child(node);
				}
				next_node->set_parent(node->get_parent());
				if (node->get_parent() == NULL) {
					this->root = next_node;
				} else if (node->is_right_child() == true) {
					(node->get_parent())->set_right_child(next_node);
				} else {
					(node->get_parent())->set_left_child(next_node);
				}
				next_node->set_right_child(node);
				node->set_parent(next_node);
			}

			// - Insert fixup function
			void	fix_tree(node_type*	new_node) {
				node_type*	uncle_node;
				while (new_node->get_parent() && (new_node->get_parent())->get_color() == red) {
					std::cout << "In while\n";
					if (new_node->get_parent() == new_node->get_left_uncle()) {
						std::cout << "case1\n";
						uncle_node = new_node->get_right_uncle();
						if (uncle_node && uncle_node->get_color() == red) {
							std::cout << "subcase1\n";
							(new_node->get_parent())->set_to_black();
							uncle_node->set_to_black();
							(new_node->get_grandparent())->set_to_red();
							new_node = new_node->get_grandparent();
							std::cout << new_node->get_data() << std::endl;
						} else {
							std::cout << "subcase2\n";
							if (new_node == (new_node->get_parent())->get_right_child()) {
								new_node = new_node->get_parent();
								this->left_rotate(new_node);
							}
							(new_node->get_parent())->set_to_black();
							(new_node->get_grandparent())->set_to_red();
							this->right_rotate(new_node->get_grandparent());
						}
					}
					else {
						std::cout << "case2\n";
						uncle_node = new_node->get_left_uncle();
						if (uncle_node && uncle_node->get_color() == red) {
							(new_node->get_parent())->set_to_black();
							uncle_node->set_to_black();
							(new_node->get_grandparent())->set_to_red();
							new_node = new_node->get_grandparent();
						} else {
							if (new_node == (new_node->get_parent())->get_left_child()) {
								new_node = new_node->get_parent();
								this->right_rotate(new_node);
							}
							(new_node->get_parent())->set_to_black();
							(new_node->get_grandparent())->set_to_red();
							this->left_rotate(new_node->get_grandparent());
						}
					}
				}
				(this->root)->set_to_black();
			}

			// - Insert node function
			void	insert_value(value_type& data) {
				node_type	new_node = node<value_type>(data);
				node_type*	node_x = this->root;
				node_type*	node_y = NULL;
				while (node_x != NULL) {
					node_y = node_x;
					if (compare(new_node.get_data(), node_x->get_data())) { // new_node key < node_x key
						node_x = node_x->get_left_child();
					} else {
						node_x = node_x->get_right_child();
					}
				}
				new_node.set_parent(node_y);
				if (node_y == NULL) {
					this->root = &new_node;
				} else if (compare(new_node.get_data(), node_y->get_data())) { // new_node key < node_y key
					node_y->set_left_child(&new_node);
				} else {
					node_y->set_right_child(&new_node);
				}
				new_node.set_to_red();
				this->fix_tree(&new_node);
				this->node_count += 1;
				std::cout << "Element inserted\n";
			}

			// - Transplant function for deletion
			void	transplant(node_type* node_x, node_type* node_y) {
				if (node_x->get_parent() == NULL) {
					this->root = node_y;
				} else if (node_x == (node_x->get_parent())->get_left_child()) {
					(node_x->get_parent())->set_left_child(node_y);
				} else {
					(node_x->get_parent())->set_right_child(node_y);
				}
				node_y->set_parent(node_x->get_parent());
			}

			void	fix_delete(node_type* to_fix) {
				node_type*	sibling;
				while (to_fix != NULL and to_fix->get_color() == black) {
					if (to_fix == (to_fix->get_parent())->get_left_child()) {
						sibling = (to_fix->get_parent())->get_right_child();
						if (sibling->get_color() == red) {
							sibling->set_to_black();
							(to_fix->get_parent())->set_to_red();
							this->left_rotate(to_fix->get_parent());
							sibling = (to_fix->get_parent())->get_right_child();
						}
						if ((sibling->get_left_child())->get_color() == black
							&& (sibling->get_right_child())->get_color() == black) {
								sibling->set_to_red();
								to_fix = to_fix->get_parent();
						} else {
							if ((sibling->get_right_child())->get_color() == black) {
								(sibling->get_left_child())->set_to_black();
								sibling->set_to_red();
								this->right_rotate(sibling);
								sibling = (to_fix->get_parent())->get_right_child();
							}
							if ((to_fix->get_parent())->get_color() == red) {
								sibling->set_to_red();
							} else {
								sibling->set_to_black();
							}
							(to_fix->get_parent())->set_to_black();
							(sibling->get_right_child())->set_to_black();
							this->left_rotate(to_fix->get_parent());
							to_fix = this->root;
						}
					} else {
						sibling = (to_fix->get_parent())->get_left_child();
						if (sibling->get_color() == red) {
							sibling->set_to_black();
							(to_fix->get_parent())->set_to_red();
							this->right_rotate(to_fix->get_parent());
							sibling = (to_fix->get_parent())->get_left_child();
						}
						if ((sibling->get_right_child())->get_color() == black
							&& (sibling->get_left_child())->get_color() == black) {
								sibling->set_to_red();
								to_fix = to_fix->get_parent();
						} else {
							if ((sibling->get_left_child())->get_color() == black) {
								(sibling->get_right_child())->set_to_black();
								sibling->set_to_red();
								this->left_rotate(sibling);
								sibling = (to_fix->get_parent())->get_left_child();
							}
							if ((to_fix->get_parent())->get_color() == red) {
								sibling->set_to_red();
							} else {
								sibling->set_to_black();
							}
							(to_fix->get_parent())->set_to_black();
							(sibling->get_left_child())->set_to_black();
							this->right_rotate(to_fix->get_parent());
							to_fix = this->root;
						}
					}
				}
				to_fix->set_to_black();
			}

			// - Delete function
			void	remove_node(node_type* to_del) {
				node_type*	track = to_del;
				node_type*	to_del_child;
				rb_tree_color	track_color = track->get_color();
				if (to_del->get_left_child() == NULL) {
					to_del_child = to_del->get_right_child();
					this->transplant(to_del, to_del->get_right_child());
				} else if (to_del->get_right_child() == NULL) {
					to_del_child = to_del->get_left_child();
					this->transplant(to_del, to_del->get_left_child());
				} else {
					track = tree_minimum(to_del->get_right_child());
					track_color = track->get_color();
					to_del_child = to_del->get_right_child();
					if (track->get_parent() == to_del) {
						to_del_child->set_parent(track);
					} else {
						this->transplant(track, track->get_right_child());
						track->set_right_child(to_del->get_right_child());
						(to_del->get_right_child())->set_parent(track);
					}
					this->transplant(to_del, track);
					track->set_left_child(to_del->get_left_child());
					(track->get_left_child())->set_parent(track);
					if (to_del->get_color() == red) {
						track->set_to_red();
					} else {
						track->set_to_black();
					}
				}
				if (track_color == black)
					this->fix_delete(to_del_child);
				this->node_count -= 1;
				printf("Element deleted\n");
			}

			// TODO DELETE FOLLOWING
			node_type* TreeSearch(int stuff) {
			node<value_type>* temp = this->get_root();
			if(temp == nullptr) { return nullptr; }

			while(temp) {
				if(stuff == temp->data){ return temp; }
				else if(compare(stuff, temp->get_data())){ temp = temp->get_left_child(); }
				else { temp = temp->get_right_child(); }
			}
			return nullptr;
			}


			void PreorderTraversal(node_type* temp) {
				if(!temp){ return; }
				std::cout << "--> " << temp->data << "<" << temp->get_color() << ">";
				PreorderTraversal(temp->get_left_child());
				PreorderTraversal(temp->get_right_child());
			}

			void PostorderTraversal(node_type* temp) {
				if(!temp){ return; }
				PostorderTraversal(temp->get_left_child());
				PostorderTraversal(temp->get_right_child());
				std::cout << "--> " << temp->get_data() << "<" << temp->get_color() << ">";
			}
	};
};

#endif
