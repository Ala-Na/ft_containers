/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:11:55 by anadege           #+#    #+#             */
/*   Updated: 2022/02/22 13:38:53 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
# define TREE_HPP

#include <cstddef>
#include <memory>
#include <cstdio> //TODO delete, test purpose only
#include <iostream> // TODO delete, test purpose only
#include "./tree_iterator.hpp" // include node.hpp
#include "./iterators.hpp"
#include "./id_comp.hpp"
#include "./exceptions.hpp"
#include "./pair.hpp"

namespace ft
{
	// ---------------------------------
	// Red-black tree class and methods
	// ---------------------------------

	// Here, value represent a pair for map
	template <typename Value, class Compare = ft::less<Value>, typename Allocator = std::allocator<node<Value>>>
	class rb_tree {

		public:

			typedef Value									value_type;
			typedef Allocator								allocator_type;
			typedef Compare									compare_function;
			typedef ft::node<Value>							node_type;
			typedef std::size_t								size_type;
			typedef std::ptrdiff_t							difference_type;
			typedef value_type&								reference;
			typedef const value_type&						const_reference;
			typedef value_type*								pointer;
			typedef const value_type*						const_pointer;
			typedef ft::rb_tree_iterator<value_type>		iterator;
			typedef ft::rb_tree_iterator<const value_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const iterator>	const_reverse_iterator;

		private:
			node_type*			root;
			size_type			node_count;
			compare_function	comp;
			allocator_type		alloc;

		public:

			// --------------------
			// --- CONSTRUCTORS ---
			// --------------------

			// - Default constructor
			rb_tree (const compare_function& comp = compare_function(), const allocator_type &alloc = allocator_type()) :
				root(NULL), node_count(0), comp(comp), alloc(alloc) {}

			// - Compare specification constructor
			rb_tree (compare_function comp, const allocator_type &alloc = allocator_type()) :
				root(NULL), node_count(0), comp(comp), alloc(alloc) {}

			// - Range constructor
			template <typename InputIterator>
			rb_tree (InputIterator first, InputIterator last, const compare_function& comp = compare_function(), const allocator_type &alloc = allocator_type()) :
				root(NULL), node_count(0), comp(comp), alloc(alloc)
			{
				if (is_valid_input_iterator(first) == false) {
					throw InvalidIteratorTypeException();
				}
				if (first == last) {
					this->first_elem = NULL;
					return ;
				}
				for (; first != last; ++first)
					this->insert(*first);
			}

			// - Copy constructor
			rb_tree (const rb_tree& other, const allocator_type &alloc = allocator_type()) :
				alloc(alloc), root(other.root), node_count(other.root_count), comp(other.comp) {}

			// ------------------
			// --- DESTRUCTOR ---
			// ------------------

			~rb_tree () {
				delete_tree(this->root);
			}

			// ---------------------------
			// --- ASSIGNMENT OPERATOR ---
			// ---------------------------

			rb_tree&	operator= (cons this type& other) {
				if (this == &other) {
					return *this;
				}
				delete_tree(this->root);
				this->comp = other.comp;
				this->node_count = other.node_count;
				this->alloc = other.alloc;
				iterator	first = other.begin();
				iterator	last = other.last();
				for (; first != last; first++) {
					this->insert(*first);
				}
				return *this;
			}

			// ---------------
			// --- GETTERS ---
			// ---------------

			// - Root getter
			node_type*	get_root () {
				return this->root;
			}

			// - Size function / get size_count function
			size_t	size () {
				return this->node_count;
			}

			// - Allocator getter
			allocator_type&	get_allocator() {
				return this->alloc;
			}

			compare_function&	get_compare_function() {
				return this->comp;
			}

			// ----------------------
			// --- BOOLEAN STATES ---
			// ----------------------

			// - Empty function
			bool	empty() {
				return (this->node_count == 0);
			}

			// -----------------
			// --- ITERATORS ---
			// -----------------

			// - Begin functions (returns iterator to smallest element)

			// Non constant begin function
			iterator begin () {
				return iterator(static_cast<node_type*>(tree_minimum(this->root)));
			}

			// Constant begin function
			const_iterator begin() const {
				return const_iterator(static_cast<node_type*>(const_cast<node_type*>(tree_minimum(this->root))));
			}

			// - End functions (returns iterator to biggest element)

			// Non constant end function
			iterator end () {
				return iterator(static_cast<node_type*>(tree_maximum(this->root)));
			}

			// Constant end function
			const_iterator end() const {
				return const_iterator(static_cast<node_type*>(const_cast<node_type*>(tree_maximum(this->root))));
			}

			// - Reverse begin functions

			// Returns reverse iterator, starting from last element.
			reverse_iterator	rbegin() {
				return static_cast<reverse_iterator>(this->end());
			}

			// Returns constant reverse iterator, starting from last element.
			const_reverse_iterator	rbegin() const {
				return static_cast<const_reverse_iterator>(this->end());
			}

			// - Reverse end functions

			// Returns reverse iterator, starting from first element.
			reverse_iterator	rend() {
				return static_cast<reverse_iterator>(this->begin());
			}

			// Returns constant reverse iterator, starting from first element.
			const_reverse_iterator	rend() const {
				return static_cast<const_reverse_iterator>(this->begin());
			}

			// --------------
			// --- MEMORY ---
			// --------------

			// - Function to create and allocate memory for a new node of data
			// value.
			node_type*	create_node(value_type data) {
				node_type*	new_node = this->alloc.allocate(1);
				node_type	filler(data);
				alloc.construct(new_node, filler);
				return new_node;
			}

			node_type*	create_node(node_type* other) {
				node_type*	new_node = this->alloc.allocate(1);
				node_type	filler(other);
				alloc.construct(new_node, filler);
				return new_node;
			}

			void	delete_node(node_type* to_delete) {
				this->alloc.destroy(to_delete);
				this->alloc.deallocate(to_delete, 1);
			}

			void	delete_tree(node_type* curr_root) {
				while (curr_root) {
					delete_tree(curr_root->get_right_child());
					node_type* left_child = curr_root->get_left_child();
					delete_node(curr_root);
					curr_root = left_child;
				}
			}

			// ---------------------------
			// --- ROTATIONS FUNCTIONS ---
			// ---------------------------

			// - Left rotate function, used to exchange two nodes in insertion
			// and deletion.
			void	left_rotate (node_type* node) {
				node_type*	next_node = node->get_right_child();
				node->set_right_child(next_node->get_left_child());
				if (next_node->get_left_child() != NULL) {
					next_node->set_left_child(node);
				}
				next_node->set_parent(node->get_parent());
				if (node == this->root) {
					this->root = next_node;
				} else if (node->is_left_child() == true) {
					(node->get_parent())->set_left_child(next_node);
				} else {
					(node->get_parent())->set_right_child(next_node);
				}
				next_node->set_left_child(node);
				node->set_parent(next_node);
			}

			// - Right rotate function, used to exchange two nodes in insertion
			// and deletion.
			void	right_rotate (node_type* node) {
				node_type*	next_node = node->get_left_child();
				node->set_left_child(next_node->get_right_child());
				if (next_node->get_right_child() != NULL) {
					next_node->get_right_child()->set_parent(node);
				}
				next_node->set_parent(node->get_parent());
				if (node == this->root) {
					this->root = next_node;
				} else if (node->is_right_child() == true) {
					(node->get_parent())->set_right_child(next_node);
				} else {
					(node->get_parent())->set_left_child(next_node);
				}
				next_node->set_right_child(node);
				node->set_parent(next_node);
			}

			// --------------
			// --- SEARCH ---
			// --------------

			// - Function to seek a node of node_value data. Return pointer to
			// corresponding node.
			node_type* seek_node(value_type node_value) {
				node_type* tmp = this->root;
				if(!tmp) {
					return NULL;
				}
				while(tmp) {
					if (tmp->get_data() == node_value) {
						return tmp;
					} else if (this->comp(node_value, tmp->get_data())) {
						tmp = tmp->get_left_child();
					} else {
						tmp = tmp->get_right_child();
					}
				}
				return NULL;
			}

			// -----------------
			// --- INSERTION ---
			// -----------------

			// - Function to fix colors and order inside tree after insertion
			// of new_node.
			void	fix_tree(node_type*	new_node) {
				node_type*	uncle_node;
				while (new_node->get_parent() && (new_node->get_parent())->get_color() == red) {
					if (new_node->get_parent() == new_node->get_left_uncle()) {
						uncle_node = new_node->get_right_uncle();
						if (uncle_node && uncle_node->get_color() == red) {
							(new_node->get_parent())->set_to_black();
							uncle_node->set_to_black();
							(new_node->get_grandparent())->set_to_red();
							new_node = new_node->get_grandparent();
							return;
						} else {
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
			void	insert_value(value_type data) {
				node_type*	new_node = create_node(data);
				node_type*	node_x = this->root;
				node_type*	node_y = NULL;
				while (node_x != NULL) {
					node_y = node_x;
					if (this->comp(data, node_x->get_data())) { // new_node key < node_x key
						node_x = node_x->get_left_child();
					} else {
						node_x = node_x->get_right_child();
					}
				}
				new_node->set_parent(node_y);
				if (node_y == NULL) {
					this->root = new_node;
				} else if (this->comp(new_node->get_data(), node_y->get_data())) { // new_node key < node_y key
					node_y->set_left_child(new_node);
				} else {
					node_y->set_right_child(new_node);
				}
				new_node->set_to_red();
				this->fix_tree(new_node);
				this->node_count += 1;
				std::cout << "Element inserted\n";
			}

			// ----------------
			// --- DELETION ---
			// ----------------

			// - Node deletion function
			void	remove_node(node_type* node) {
				node_type*&	root_track = this->root;
				node_type*	min = tree_minimum(this->root);
				node_type*	max = tree_maximum(this->root);
				node_type*	child = NULL;
				node_type*	child_parent = NULL;
				node_type*	successor = node;
				if (successor->get_left_child() == NULL) {
					child = node->get_right_child();
				} else if (successor->get_right_child() == NULL) {
					child = node->get_left_child();
				} else {
					successor = successor->get_right_child();
					while (successor->get_left_child()) {
						successor = successor->get_left_child();
					}
					child = successor->get_right_child();
				}
				if (successor == node) {
					child_parent = successor->get_parent();
					if (child != NULL) {
						child->set_parent(successor->get_parent());
					}
					if (node == root_track) {
						root_track = child;
					} else {
						if (node == node->get_parent()->get_left_child()) {
							node->get_parent()->set_left_child(child);
						} else {
							node->get_parent()->set_right_child(child);
						}
					}
					if (node == min) {
						if (node->get_right_child() && child) {
							min = tree_minimum(child);
						} else {
							min = node->get_parent();
						}
					}
					if (node == max) {
						if (node->get_left_child() && child) {
							max = tree_maximum(child);
						} else {
							max = node->get_parent();
						}
					}
				} else {
					node->get_left_child()->set_parent(successor);
					successor->set_left_child(node->get_left_child());
					if (successor == node->get_right_child()) {
						child_parent = successor;
					} else {
						child_parent = successor->get_parent();
						if (child) {
							child->set_parent(child_parent);
						}
						child_parent->set_left_child(child);
						successor->set_right_child(node->get_right_child());
						node->get_right_child()->set_parent(successor);
					}
					if (node == root_track) {
						root_track = successor;
						this->root = root_track;
					} else if (node == node->get_parent()->get_left_child()) {
						node->get_parent()->set_left_child(successor);
					} else {
						node->get_parent()->set_right_child(successor);
					}
					successor->set_parent(node->get_parent());
					ft::swap(successor->get_color(), node->get_color());
				}
				if (node->get_color() == black) {
					while (child != root_track && (child == NULL || child->get_color() == black)) {
						if (child == child_parent->get_left_child()) {
							node_type*	tmp = child_parent->get_right_child();
							if (tmp->get_color() == red) {
								tmp->set_to_black();
								child_parent->set_to_red();
								left_rotate(child_parent);
								root_track = this->root;
								tmp = child_parent->get_right_child();
							}
							if ((tmp->get_left_child() == NULL || tmp->get_left_child()->get_color() == black)
							&& (tmp->get_right_child() ==  NULL || tmp->get_right_child()->get_color() == black)) {
								tmp->set_to_red();
								child = child_parent;
								child_parent = child_parent->get_parent();
							} else {
								if ((tmp->get_right_child() == NULL || tmp->get_right_child()->get_color() == black)) {
									tmp->get_left_child()->set_to_black();
									tmp->set_to_red();
									right_rotate(tmp);
									root_track = this->root;
									tmp = child_parent->get_right_child();
								}
								tmp->set_color(child_parent->get_color());
								child_parent->set_to_black();
								if (tmp->get_right_child()) {
									tmp->get_right_child()->set_to_black();
								}
								left_rotate(child_parent);
								root_track = this->root;
								break;
							}
						}
						else {
							node_type*	tmp = child_parent->get_left_child();
							if (tmp->get_color() == red) {
								tmp->set_to_black();
								child_parent->set_to_red();
								right_rotate(child_parent);
								root_track = this->root;
								tmp = child_parent->get_left_child();
							}
							if ((tmp->get_left_child() == NULL || tmp->get_left_child()->get_color() ==  black)
							&& (tmp->get_right_child() ==  NULL || tmp->get_right_child()->get_color() == black)) {
								tmp->set_to_red();
								child = child_parent;
								child_parent = child_parent->get_parent();
							} else {
								if ((tmp->get_left_child() == NULL || tmp->get_left_child()->get_color() == black)) {
									tmp->get_right_child()->set_to_black();
									tmp->set_to_red();
									left_rotate(tmp);
									root_track = this->root;
									tmp = child_parent->get_left_child();
								}
								tmp->set_color(child_parent->get_color());
								child_parent->set_to_black();
								if (tmp->get_left_child()) {
									tmp->get_left_child()->set_to_black();
								}
								right_rotate(child_parent);
								root_track = this->root;
								break;
							}
						}
					}
					if (child) {
						child->set_to_black();
					}
				}
				delete_node(node);
				this->node_count -= 1;
			}

			// TODO DELETE FOLLOWING
			void PreorderTraversal(node_type* temp) {
				if(!temp){
					std::cout << "--> end branch |";
					return; }
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
