/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 22:11:57 by anadege           #+#    #+#             */
/*   Updated: 2022/02/23 22:09:02 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

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
		node<Value>*	parent;
		node<Value>*	left_child;
		node<Value>*	right_child;
		rb_tree_color	color;

		// - Constructors
		node () :
			data(), parent(NULL), left_child(NULL), right_child(NULL), color(black)
		{}


		node (Value& data) :
			data(data), parent(NULL), left_child(NULL), right_child(NULL), color(black)
		{}

		node (node*& other) :
			data(other->data), parent(other->parent), left_child(other->left_child), right_child(other->right_child), color(other->color)
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

		void	set_color (rb_tree_color rob) {
			this->color = rob;
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

		rb_tree_color&	get_color () {
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
	ft::node<T>*	increment_tree(ft::node<T>* node) {
		ft::node<T>*(tmp_node);
		if (node->get_right_child() != NULL) {
			node = node->get_right_child();
			while (node->get_left_child() != NULL) {
				node = node->get_left_child();
			}
		} else {
			tmp_node = node->get_parent();
			while (tmp_node && node == tmp_node->get_right_child()) {
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
	ft::node<T>*	decrement_tree(ft::node<T>* node) {
		ft::node<T>*	tmp_node;
		if (node->get_left_child() != NULL) {
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
		while (current && current->get_left_child() != NULL) {
			current = current->get_left_child();
		}
		return current;
	};

	// - Maximum function
	template <typename T>
	ft::node<T>*	tree_maximum(ft::node<T>* current) {
		while (current && current->get_right_child() != NULL) {
			current = current->get_right_child();
		}
		return current;
	};
};

#endif
