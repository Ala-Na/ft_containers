/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:21:47 by anadege           #+#    #+#             */
/*   Updated: 2022/02/22 22:59:19 by anadege          ###   ########.fr       */
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
	template <class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<pair<const Key, T>>>
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
			typedef tree_type::iterator										iterator;
			typedef tree_type::const_iterator								const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const iterator>					const_reverse_iterator;
			typedef typename std::ptrdiff_t									difference_type;
			typedef typename std::size_t									size_type;

		protected:

			typedef rb_tree<key_type, value_type, key_compare, allocator_type::template rebind<value_type>::other,
							ft::use_first<ft::pair<const Key, T>>>	tree_type;

			// -----------------
			// Member objects :
			// -----------------
			key_compare			comp;
			allocator_type		alloc;
			tree_type			tree;

		public:

			// -----------------
			// Member functions :
			// -----------------

			// --------------------
			// --- CONSTRUCTORS ---
			// --------------------

			// - Default constructor
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
				comp(comp), alloc(alloc), tree()
			{}

			// - Range consructor
			template <class InputIterator>
			map (InputIterator first, InputIterator last,
			const key_compare& comp= key_compare(),
			const allocator_type& alloc = allocator_type(),
			typename std::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) :
				comp(comp), alloc(alloc), tree()
			{
				if (is_valid_input_iterator(first) == false) {
					throw InvalidIteratorTypeException();
				}
				if (first == last) {
					this->tree = NULL;
					return ;
				}
				for(; first != last; first++)
					this->insert(*first);
			}

			// - Copy constructor
			map (const map& other) :
				comp(other.compare_function), alloc(other.alloc), tree()
			{
				if (other.empty() == true)
					return ;
				for (iterator it = other.begin(); it != other.end(); ++it) {
					this->insert(*it);
				}
			}

			// ------------------
			// --- DESTRUCTOR ---
			// ------------------

			~map () {
				tree.delete_tree();
				// TODO deallocate all memory
			}

			// --------------------------
			// -- ASSIGNMENT OPERATOR ---
			// --------------------------

			map&	operator= (const map& other) {
				//TODO deallocate memory and reallocate copying other tree
			}

			// -----------------
			// --- ALLOCATOR ---
			// -----------------

			allocator_type	get_allocator () const {
				return this->alloc;
			}

			// -----------------
			// --- ITERATORS ---
			// -----------------

			iterator	begin () {
				return iterator(this->tree.begin());
			}

			const_iterator	begin () const {
				return const_iterator(this->tree.begin());
			}

			iterator	end () {
				return iterator(this->tree.end());
			}

			const_iterator	end () const {
				return const_iterator(this->tree.end());
			}

			iterator	rbegin () {
				return iterator(this->tree.rbegin());
			}

			const_iterator	rbegin () const {
				return const_iterator(this->tree.rbegin());
			}

			iterator	rend () {
				return iterator(this->tree.rend());
			}

			const_iterator	rend () const {
				return const_iterator(this->tree.rend());
			}

			// ----------------
			// --- CAPACITY ---
			// ----------------

			bool	empty() const {
				return this->tree.empty();
			}

			size_type	size() const {
				return this->tree.size();
			}

			size_type	max_size() const {
				return this->tree.max_size();
			}

			// ----------------------
			// --- ELEMENT ACCESS ---
			// ----------------------

			mapped_type&	operator[] (const key_type& k) {
				// TODO first check if key is already present an return *found.second
				// TODO else : insert value
				return (*((this->insert(make_pair(k,mapped_type()))).first)).second;
			};

			// -----------------
			// --- MODIFIERS ---
			// -----------------

			// - Insert single element function
			ft::pair<iterator, bool>	insert (const value_type& val) {
				node_type*	node = tree.seek_node(val.first);
				if (node != NULL)
					return make_pair(static_cast<iterator>(node), false);
				tree.insert_value(val);
			}
	};

};

#endif
