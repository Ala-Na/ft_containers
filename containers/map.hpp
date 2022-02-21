/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:21:47 by anadege           #+#    #+#             */
/*   Updated: 2022/02/21 21:46:30 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include <functional>
#include <cstddef>
#include <memory>
#include "./utils/exceptions.hpp"
#include "./utils/pair.hpp"
#include "./utils/id_comp.hpp"
#include "./utils/iterators.hpp"
#include "./utils/tree.hpp"
#include "./utils/tree_iterator.hpp"

namespace ft
{
	template <class Key, class T, class Compare = less<Key>, class Alloc = std::allocator<pair<const Key, T>>>
	class map
	{
		public:

			// ---------------------------
			// Members types definitions :
			// ---------------------------

			typedef Key														key_type;
			typedef T														mapped_type;
			typedef ft::pair<const Key, T>									value_type;
			typedef Compare													key_compare;
			typedef Alloc													allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_point					const_pointer;
			typedef ft::rb_tree<value_type, key_compare>::iterator			iterator;
			typedef ft::rb_tree<value_type, key_compare>::const_iterator	const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const iterator>					const_reverse_iterator;
			typedef typename std::ptrdiff_t									difference_type;
			typedef typename std::size_t									size_type;

		protected:

			// -----------------
			// Member objects :
			// -----------------
			key_compare							compare_function;
			allocator_type						alloc;
			ft::rb_tree<value_type, Compare>*	tree;

		public:

			// -----------------
			// Member functions :
			// -----------------

			// --------------------
			// --- CONSTRUCTORS ---
			// --------------------

			// - Default constructor
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
				compare_function(comp), alloc(alloc) {}

			// - Range consructor
			template <class InputIterator>
			map (InputIterator first, InputIterator last,
			const key_compare& comp= key_compare(),
			const allocator_type& alloc = allocator_type(),
			typename std::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) :
				compare_function(comp), alloc(alloc), tree(NULL) {
				if (is_valid_input_iterator(first) == false) {
					throw InvalidIteratorTypeException();
				}
				if (first == last) {
					this->tree = NULL;
					return ;
				//TODO continue by copying tree into new one
				}
			}

			// - Copy constructor
			map (const map& other) :
				compare_function(other.compare_function), alloc(other.alloc) {
					//TODO continue by copying tree into new one
			}

			// ------------------
			// --- DESTRUCTOR ---
			// ------------------

			~map () {
				//TODO deallocate memory
			}

			// --------------------------
			// -- ASSIGNMENT OPERATOR ---
			// --------------------------

			map&	operator= (const map& other) {
				//TODO deallocate memory and reallocate copying other tree
			}

	};

};

#endif
