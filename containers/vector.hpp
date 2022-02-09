/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:21:45 by anadege           #+#    #+#             */
/*   Updated: 2022/02/09 18:15:21 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <cstddef>
#include <memory>
#include <iterator>
#include <cstdio> //TODO delete, only for tests
#include "./utils/iterators.hpp"
#include "./utils/id_comp.hpp"
#include "./utils/exceptions.hpp"

//Must use ft as namespace
//Containers must be called as ft::<containers>
//Only C++98
//Must use std::allocator
//Must implement system of iterator if present in container
//STD lib is authorized
//STL containers are forbidden
//no need to code vector<bool>
//pile must use vector container as subjacent container

namespace ft
{
	template <class T, class Alloc = std::allocator<T>>
	class vector
	{
		public:

			// ---------------------------
			// Members types definitions :
			// ---------------------------

			typedef T												value_type;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef ft::random_access_iterator<value_type>			iterator;
			typedef ft::random_access_iterator<const value_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const iterator>			const_reverse_iterator;
			typedef typename std::ptrdiff_t							difference_type;
			typedef typename std::size_t							size_type;

		private:

			// -----------------
			// Member objects :
			// -----------------

			allocator_type	alloc; //allocator object
			size_type		capacity; //max capacity of vector
			size_type		filled; //present number of element in vector
			T*				first_elem; //pointer to first element of vector

		public:

			// -----------------
			// Member functions :
			// -----------------

			// --- CONSTRUCTORS ---

			// - Default constructor
			explicit vector (const allocator_type &alloc = allocator_type()) :
				alloc(alloc), capacity(0), filled(0), first_elem(NULL) {}

			// - Fill constructor
			explicit vector (size_type n, const value_type &val = value_type(),
			const allocator_type &alloc = allocator_type()) :
				alloc(alloc), capacity(n), filled(0)
			{
				this->first_elem = this->alloc.allocate(this->capacity);
				for (size_t i = 0; i < this->capacity; i++)
				{
					this->alloc.construct(this->first_elem + i, val);
					this->filled++;
				}
			}

			// - Range constructor (enable_if is use to differenciate from
			// fill constructor)
			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
			const allocator_type &alloc = allocator_type(),
			typename std::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) :
				alloc(alloc), capacity(0), filled(0)
			{
				if (is_valid_input_iterator(first) == false)
					throw InvalidIteratorTypeException();
				if (first == last)
				{
					this->first_elem = NULL;
					return ;
				}
				if ((this->capacity = std::distance(first, last)) > alloc.max_size())
					throw MaxSizeExceeded();
				this->first_elem = this->alloc.allocate(this->capacity);
				for (size_t i = 0; i < this->capacity; i++, first++)
				{
					this->alloc.construct(this->first_elem + i, *first);
					this->filled++;
				}
			}

			// - Copy constructor (deep)
			vector (const vector& x) :
				alloc(x.alloc), capacity(x.capacity), filled (0)
			{
				this->first_elem = this->alloc.allocate(this->capacity);
				for (size_t i = 0; i < x->filled; i++)
				{
					this->alloc.construct(this->first_elem + i, x[i]);
					this->filled++;
				}
			}

			// --- DESTRUCTOR ---
			~vector ()
			{
				value_type*	elem = first_elem;
				for (size_t i = 0; i < this->filled; i++)
				{
					this->alloc.destroy(elem);
					elem++;
				}
				this->alloc.deallocate(this->first_elem, this->capacity);
			}

			// -- ASSIGNMENT OPERATOR ---
			// TODO cut function when clear and insert functions are made
			vector&	operator= (const vector& other)
			{
				value_type*	elem = first_elem;
				for (size_t i = 0; i < this->filled; i++)
				{
					this->alloc.destroy(elem);
					elem++;
				}
				this->filled = 0;
				this->alloc.deallocate(this->first_elem, this->capacity);
				this->first_elem = NULL;
				this->first_elem = this->alloc.allocate(other->capacity);
				for (size_t i = 0; i < x->filled; i++)
				{
					this->alloc.construct(this->first_elem + i, x[i]);
					this->filled++;
				}
				return *this;
			}

			// --- ALLOCATOR ---
			allocator_type	get_allocator() const
			{

			}


	};
};

#endif
