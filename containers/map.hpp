/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:21:47 by anadege           #+#    #+#             */
/*   Updated: 2022/02/23 17:34:18 by anadege          ###   ########.fr       */
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

		protected:

			typedef rb_tree<key_type, value_type, key_compare, allocator_type::template rebind<value_type>::other,
							ft::use_first<ft::pair<const Key, T>>>	tree_type;

		public:
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

			// -----------------
			// Member objects :
			// -----------------
			tree_type			tree;

		public:

			// ---------------------------
			// --- VALUE COMPARE CLASS ---
			// ---------------------------

			// Class needed to define return value of value_comp function.
			// Value compare inherite from binary_function in cpp source code.
			// Here, member definitions of binary_function are made inside
			// value_compare class.

			class value_compare :
				public ft::binary_function<value_type, value_type, bool>
			{
				protected :
					friend class	map<Key, T, Compare, Alloc>;
					Compare			comp;

					value_compare(Compare c) : comp(c) {}

				public:
					bool operator() (const value_type& x, const value_type& y) const {
						return comp(x.first, y.first);
					}
			}

			// -----------------
			// Member functions :
			// -----------------

			// --------------------
			// --- CONSTRUCTORS ---
			// --------------------

			// - Default constructor
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
				tree(comp, alloc)
			{}

			// - Range consructor
			template <class InputIterator>
			map (InputIterator first, InputIterator last,
			const key_compare& comp= key_compare(),
			const allocator_type& alloc = allocator_type(),
			typename std::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) :
				tree(comp, alloc)
			{
				if (is_valid_input_iterator(first) == false) {
					throw InvalidIteratorTypeException();
				}
				this->insert(first, last);
			}

			// - Copy constructor
			map (const map& other) :
				tree(other.tree)
			{}

			// ------------------
			// --- DESTRUCTOR ---
			// ------------------

			~map () {
				this->clean();
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
				return this->insert(ft::make_pair(k, mapped_type()))->get_data().second;
			};

			// -----------------
			// --- MODIFIERS ---
			// -----------------

			// - Insert single element function
			ft::pair<iterator, bool>	insert (const value_type& val) {
				tree_type::node_type*	node = this->tree.seek_node(val);
				bool		is_inserted = false;
				if (node == NULL) {
					node = this->tree.insert_value(val);
					is_inserted = true;
				}
				return ft::make_pair(iterator(node), is_inserted);
			}

			// - Insert with hint
			iterator	insert (iterator position, const value_type& val) {
				(void)position;
				return iterator(this->tree.insert_value(val));
			}

			// - Insert range of iterators
			template <class InputIterator>
			void	insert (InputIterator first, InputIterator last) {
				if (is_valid_input_iterator(first) == false) {
					throw InvalidIteratorTypeException();
				} else if (first == last) {
					return;
				}
				for (; first != last; first++) {
					this->tree.insert_value(*first);
				}
			}

			// - Erase function for element at position iterator
			void	erase (iterator position) {
				this->tree.remove_node(static_cast<tree_type::node_type*>(position));
			}

			// - Erase function for element witk k key.
			size_type	erase (const key_type& k) {
				return this->tree.remove_node(k);
			}

			void	erase (iterator first, iterator last) {
				for (; first != last; first++) {
					this->tree.remove_node(static_cast<tree_type::node_type*>(first));
				}
			}

			void	swap (map &other) {
				if (*this == other) {
					return ;
				}
				tree_type	tmp = other.tree;
				other.tree = this->tree;
				this->tree = tmp;
			}

			void	clear () {
				this->tree.delete_tree();
			}

			// -----------------
			// --- OBSERVERS ---
			// -----------------

			key_compare	key_comp () const {
				return key_compare();
			}

			value_compare	value_comp() const {
				return value_compare(keycompare());
			}

			// ------------------
			// --- OPERATIONS ---
			// ------------------

			iterator	find (const key_type& k) {
				tree_type::node_type*	found = this->tree.seek_node(k);
				if (found == NULL)	{
					return this->end();
				}
				return iterator(found);
			}

			const_iterator	find (const key_type& k) const {
				tree_type::node_type*	found = this->tree.seek_node(k);
				if (found == NULL)	{
					return this->end();
				}
				return iterator(found);
			}

			size_type	count (const key_type& k) {
					return (this->tree.seek_node(k) == NULL ? 0 : 1);
			}

			iterator	lower_bound (const key_type& k) {
				return iterator(this->tree.lower_bound(k));
			}

			const_iterator	lower_bound (const key_type& k) const {
				return const_iterator(this->tree.lower_bound(k));
			}

			iterator	upper_bound (const key_type& k) {
				return iterator(this->tree.upper_bound(k));
			}

			const_iterator	upper_bound (const key_type& k) const {
				return const_iterator(this->tree.upper_bound(k));
			}
	};

};

#endif
