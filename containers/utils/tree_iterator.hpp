/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 13:48:52 by anadege           #+#    #+#             */
/*   Updated: 2022/02/21 22:11:16 by anadege          ###   ########.fr       */
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
			typedef ft::node<Type>																	node_type;

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
				this->node = static_cast<node_type*>(increment_tree(this->node));
				return *this;
			}

			// - Post-increment iterator position modifier
			rb_tree_iterator	operator++ (int) {
				rb_tree_iterator tmp = *this;
				this->node = static_cast<node_type*>(increment_tree(this->node));
				return tmp;
			}

			// - Pre-decrement iterator position modifier
			rb_tree_iterator&	operator-- () {
				this->node = static_cast<node_type*>(decrement_tree(this->node));
				return *this;
			}

			// - Post-decrement iterator position modifier
			rb_tree_iterator	operator-- (int) {
				rb_tree_iterator tmp = *this;
				this->node = static_cast<node_type*>(decrement_tree(this->node));
				return tmp;
			}
	};

	// Non member functions :
	// - Relationals operators
	template <typename T1, typename T2>
	bool	operator==(const ft::rb_tree_iterator<T1>& lhs,
		const ft::rb_tree_iterator<T2>& rhs)
	{
		return lhs.base() == rhs.base();
	};

	template <typename T1, typename T2>
	bool	operator!=(const ft::rb_tree_iterator<T1>& lhs,
		const ft::rb_tree_iterator<T2>& rhs)
	{
		return lhs.base() != rhs.base();
	};
};

#endif
