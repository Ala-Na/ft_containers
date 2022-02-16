/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:11:55 by anadege           #+#    #+#             */
/*   Updated: 2022/02/16 18:28:21 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
# define TREE_HPP

#include <cstddef>
#include <memory>
#include "./iterators.hpp"
#include "./id_comp.hpp"
#include "./exceptions.hpp"
#include "./pair.hpp"

namespace ft
{

	// -----------------------------------
	// Enum for red-black tree node color
	// -----------------------------------

	enum rb_tree_color {
		red = false,
		black = true
	};

	template <typename Value>
	struct node {
		Value			data; // for map : pair of key/value
		node*			parent;
		node*			left_child;
		node*			right_child;
		rb_tree_color	color;

		node (Value& data) :
			data(data), parent(NULL), left_child(NULL), right_child(NULL), color(black)
		{}

		void	set_to_red () {
			this->color = red;
		}

		void	set_to_black () {
			this->color = black;
		}

		void	set_parent (node*& parent) {
			this->parent = parent;
		}

		void	set_left_child (node*& left_child) {
			this->left_child = left_child;
		}

		void	set_right_child (node*& right_child) {
			this->right_child = right_child;
		}

		void	unset_parent () {
			this->parent = NULL;
		}

		void	unset_left_child () {
			this->left_child = NULL;
		}

		void	unset_right_child () {
			this->right_child = NULL;
		}

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
			return (this->parent)->parent;
		}

		node*	get_right_uncle () {
			return (this->get_grandparent())->right_child;
		}

		node*	get_left_uncle () {
			return (this->get_grandparent())->left_child;
		}

		Value&	get_data () {
			return this->data;
		}

		rb_tree_color	get_color () {
			return this->color;
		}
	};

	template <typename Value, class Compare>
	class rb_tree {
		public:
			typedef Value	value_type;
			typedef Compare	compare_function;

		private:
			node*						root;
			std::size_t					node_count;
			compare_function			compare;

		public:
			// - Constructor
			rb_tree (compare_function compare) :
				root(NULL), node_count(0), compare(compare) {}

			// - Root getter
			node*	get_root () {
				return this->root;
			}

			// - Size function
			size_t	size () {
				return this->node_count;
			}

			// - Left rotate function
			void	left_rotate (node*& node) {
				node*	next_node = noleft();
				node->set_right_child(next_node->get_left_child());
				if (next_node->get_left_child() != NULL) {
					next_node->set_left_child(node);
				}
				next_node->set_parent(node->get_parent());
				if (node->get_parent() == NULL) {
					this->root = next_node;
				} else if (node == (node->get_parent())->get_left_child()) {
					(node->get_parent())->set_left_child(next_node);
				} else {
					(node->get_parent())->set_right_child(next_node);
				}
				next_node->set_left_child(node);
				node->set_parent(next_node);
			}

			// - Right rotate function
			void	right_rotate (node*& node) {
				node*	next_node = node->get_left_child();
				node->set_left_child(next_node->get_right_child());
				if (next_node->get_right_child() != NULL) {
					next_node->set_right_child(node);
				}
				next_node->set_parent(node->get_parent());
				if (node->get_parent() == NULL) {
					this->root = next_node;
				} else if (node == (node->get_parent())->get_right_child()) {
					(node->get_parent())->set_right_child(next_node);
				} else {
					(node->get_parent())->set_left_child(next_node);
				}
				next_node->set_right_child(node);
				node->set_parent(next_node);
			}

			// - Insert fixup function
			void	fix_tree(node*	new_node) {
				while ((new_node->get_parent())->get_color() == red) {
					if (new_node->get_parent() == new_node->get_left_uncle()) {
						node	*uncle_node = new_node->get_right_uncle();
						if (uncle_node->get_color() == red) {
							(new_node->get_parent())->set_to_black();
							uncle_node->set_to_black();
							(new_node->get_grandparent())->set_to_red();
							new_node = new_node->get_grandparent();
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
						node	*uncle_node = new_node->get_left_uncle();
						if (uncle_node->get_color() == red) {
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
			void	insert(value_type& data) {
				node*	new_node = node(data);
				node*	node_x = this->root;
				node*	node_y = NULL;
				while (node_x != NULL) {
					node_y = node_x;
					if (compare(new_node->get_data(), node_x->get_data())) { // new_node key < node_x key
						node_x = node_x->get_left_child();
					} else {
						node_x = node_x->get_right_child();
					}
				}
				new_node->set_parent(node_y);
				if (node_y == NULL) {
					this->root = new_node;
				} else if (compare(new_node->get_data(), node_y->get_data())) { // new_node key < node_y key
					node_y->set_left_child(new_node);
				} else {
					node_y->set_right_child(new_node);
				}
				new_node->set_to_red();
				this->fix_tree(new_node);
			}

			// - Minimum function
			node*	tree_minimum(node* x) {
				while (x->get_left_child() != NULL) {
					x = x->get_left_child();
				}
				return x;
			}

			// - Transplant function for deletion
			void	transplant(node* node_x, node* node_y) {
				if (node_x->get_parent() == NULL) {
					this->root = node_y;
				} else if (node_x == (node_x->get_parent())->get_left_child()) {
					(node_x->get_parent()->get_left_child()) = node_y;
				} else {
					(node_x->get_parent())->get_right_child() = node_y;
				}
				node_y->get_parent() = node_x->get_parent();
			}

			// - Delete function
			void	delete(node* to_del) {
				node*	track = to_del;
				rb_tree_color	track_color = track->get_color();
				if (to_del->get_left_child() == NULL) {
					node*	to_del_child = to_del->get_right_child();
					this->transplant(to_del, to_del->get_right_child());
				} else if (to_del->get_right_child() == NULL) {
					node*	to_del_child = to_del->get_left_child();
					this->transplant(to_del, to_del->get_left_child());
				} else {
					track = tree_minimum(to_del->get_right_child());
					track_color = track->get_color();
					node*	to_del_child = to_del->get_right_child();
					if (track->get_parent() == to_del) {
						to_del_child->get_parent() = track;
					} else {
						this->transplant(track, track->get_right_child());
						track->get_right_child() = to_del->get_right_child();
						(to_del->get_right_child())->get_parent() = track;
					}
					this->transplant(to_del, track);
					track->get_left_child() = to_del->get_left_child();
					(track->get_left_child())->get_parent() = track;
					if (to_del->get_color() == red) {
						track->set_to_red();
					} else {
						track->set_to_black();
					}
				}
				if (track_color == black)
					this->delete_fix(to_del_child);
					// TODO implement to_del_child
			}
	};




};

#endif
