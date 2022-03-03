/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 13:48:52 by anadege           #+#    #+#             */
/*   Updated: 2022/03/03 22:18:38 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_ITERATOR_HPP
# define TREE_ITERATOR_HPP

#include <iterator>
#include "./iterators.hpp"
#include "./node.hpp"

namespace ft
{
	template <typename Type>
	class rb_tree_iterator
	{
		public:

			typedef Type																			iterator_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, Type>::iterator_category	iterator_category;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, Type>::value_type		value_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, Type>::difference_type	difference_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, Type>::pointer			pointer;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, Type>::reference			reference;
			typedef typename ft::node<Type>															node_type;

		protected:

			node_type*	node;

		public:

			// - Constructors
			rb_tree_iterator() : node(NULL) {}

			explicit rb_tree_iterator(const node_type* node) :
				node(static_cast<node_type*>(const_cast<node_type*>(node))) {}

			template <typename T>
			rb_tree_iterator(const ft::rb_tree_iterator<T>& x) : node(x.node) {}

			// - Base function
			node_type*	base() {
				return this->node;
			}

			node_type*	base() const {
				return this->node;
			}

			// - Assignment operator
			template <typename T>
			rb_tree_iterator& operator= (const rb_tree_iterator<T>& other)
			{
				this->node = other.node;
				return *this;
			}

			// - Operator*
			reference	operator* () const {
				return this->node->data;
			}

			// - Operator ->
			pointer	operator-> () const {
				return &(operator*());
			}

			// - Pre-increment iterator position modifier
			rb_tree_iterator&	operator++ () {
				if (!this->node) {
					return *this;
				}
				this->node = static_cast<node_type*>(increment_tree(this->node));
				return *this;
			}

			// - Post-increment iterator position modifier
			rb_tree_iterator	operator++ (int) {
				if (!this->node) {
					return *this;
				}
				rb_tree_iterator tmp = *this;
				this->node = static_cast<node_type*>(increment_tree(this->node));
				return tmp;
			}

			// - Pre-decrement iterator position modifier
			rb_tree_iterator&	operator-- () {
				if (!this->node) {
					return *this;
				}
				this->node = static_cast<node_type*>(decrement_tree(this->node));
				return *this;
			}

			// - Post-decrement iterator position modifier
			rb_tree_iterator	operator-- (int) {
				if (!this->node) {
					return *this;
				}
				rb_tree_iterator tmp = *this;
				this->node = static_cast<node_type*>(decrement_tree(this->node));
				return tmp;
			}
	};

	// Non member functions :
	// - Relationals operators
	template <typename T>
	bool	operator==(const ft::rb_tree_iterator<T>& lhs,
		const ft::rb_tree_iterator<T>& rhs)
	{
		return lhs.base() == rhs.base();
	};

	template <typename T>
	bool	operator!=(const ft::rb_tree_iterator<T>& lhs,
		const ft::rb_tree_iterator<T>& rhs)
	{
		return lhs.base() != rhs.base();
	};

	template <typename Type>
	class rb_tree_const_iterator
	{
		public:

			typedef const Type																		iterator_type;
			typedef rb_tree_iterator<const Type>													iterator;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, Type>::iterator_category	iterator_category;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, Type>::value_type		value_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, Type>::difference_type	difference_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, Type>::pointer			pointer;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, Type>::reference			reference;
			typedef typename ft::node<Type>															node_type;

		protected:

			node_type*	node;

		public:

			// - Constructors
			rb_tree_const_iterator() : node(NULL) {}

			explicit rb_tree_const_iterator(const node_type* node) :
				node(static_cast<node_type*>(const_cast<node_type*>(node))) {}

			template <typename T>
			rb_tree_const_iterator(const ft::rb_tree_const_iterator<T>& x) : node(x.node) {}

			template <typename T>
			rb_tree_const_iterator(const ft::rb_tree_iterator<T>& x) : node(x.base()) {}

			// - Base function
			node_type*	base() {
				return this->node;
			}

			node_type*	base() const {
				return this->node;
			}

			// - Assignment operator
			template <typename T>
			rb_tree_const_iterator& operator= (const rb_tree_const_iterator<T>& other)
			{
				this->node = other.node;
				return *this;
			}

			// - Operator*
			reference	operator* () const {
				return this->node->data;
			}

			// - Operator ->
			pointer	operator-> () const {
				return &(operator*());
			}

			// - Pre-increment iterator position modifier
			rb_tree_const_iterator&	operator++ () {
				if (!this->node) {
					return *this;
				}
				this->node = increment_tree(this->node);
				return *this;
			}

			// - Post-increment iterator position modifier
			rb_tree_const_iterator	operator++ (int) {
				if (!this->node) {
					return *this;
				}
				rb_tree_const_iterator tmp = *this;
				this->node = static_cast<node_type*>(increment_tree(this->node));
				return tmp;
			}

			// - Pre-decrement iterator position modifier
			rb_tree_const_iterator&	operator-- () {
				if (!this->node) {
					return *this;
				}
				this->node = static_cast<node_type*>(decrement_tree(this->node));
				return *this;
			}

			// - Post-decrement iterator position modifier
			rb_tree_const_iterator	operator-- (int) {
				if (!this->node) {
					return *this;
				}
				rb_tree_const_iterator tmp = *this;
				this->node = static_cast<node_type*>(decrement_tree(this->node));
				return tmp;
			}
	};

	// Non member functions :
	// - Relationals operators
	template <typename T>
	bool	operator==(const ft::rb_tree_const_iterator<T>& lhs,
		const ft::rb_tree_const_iterator<T>& rhs)
	{
		return lhs.base() == rhs.base();
	};

	template <typename T>
	bool	operator==(const ft::rb_tree_iterator<T>& lhs,
		const ft::rb_tree_const_iterator<T>& rhs)
	{
		return lhs.base() == rhs.base();
	};

	template <typename T>
	bool	operator==(const ft::rb_tree_const_iterator<T>& lhs,
		const ft::rb_tree_iterator<T>& rhs)
	{
		return lhs.base() == rhs.base();
	};

	template <typename T>
	bool	operator!=(const ft::rb_tree_const_iterator<T>& lhs,
		const ft::rb_tree_const_iterator<T>& rhs)
	{
		return lhs.base() != rhs.base();
	};

	template <typename T>
	bool	operator!=(const ft::rb_tree_iterator<T>& lhs,
		const ft::rb_tree_const_iterator<T>& rhs)
	{
		return lhs.base() != rhs.base();
	};

	template <typename T>
	bool	operator!=(const ft::rb_tree_const_iterator<T>& lhs,
		const ft::rb_tree_iterator<T>& rhs)
	{
		return lhs.base() != rhs.base();
	};
};

#endif
