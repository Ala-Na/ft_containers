/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:21:45 by anadege           #+#    #+#             */
/*   Updated: 2022/02/11 17:06:58 by anadege          ###   ########.fr       */
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
				for (size_type i = 0; i < this->capacity; i++)
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
				for (size_type i = 0; i < this->capacity; i++, first++)
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
				for (size_type i = 0; i < x->filled; i++)
				{
					this->alloc.construct(this->first_elem + i, x[i]);
					this->filled++;
				}
			}

			// --- DESTRUCTOR ---
			~vector ()
			{
				value_type*	elem = first_elem;
				for (size_type i = 0; i < this->filled; i++)
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
				for (size_type i = 0; i < this->filled; i++)
				{
					this->alloc.destroy(elem);
					elem++;
				}
				this->filled = 0;
				this->alloc.deallocate(this->first_elem, this->capacity);
				this->first_elem = NULL;
				this->first_elem = this->alloc.allocate(other->capacity);
				for (size_type i = 0; i < other->filled; i++)
				{
					this->alloc.construct(this->first_elem + i, other[i]);
					this->filled++;
				}
				return *this;
			}

			// --- ALLOCATOR ---

			// Returns the allocator object of vector
			allocator_type	get_allocator() const
			{
				return this->alloc;
			}


			// --- ITERATORS ---

			// - Begin functions

			// Returns iterator to first element.
			iterator	begin()
			{
				return static_cast<iterator>(this->first_elem);
			}

			// Returns constant iterator to first element.
			const_iterator	begin() const
			{
				return static_cast<const_iterator>(this->first_elem);
			}

			// - End functions

			// Returns iterator to last element.
			iterator	end()
			{
				return static_cast<iterator>(this->first_elem + this->filled);
			}

			// Returns constant iterator to last element.
			const_iterator	end() const
			{
				return static_cast<const_iterator>(this->first_elem + this->filled);
			}

			// - Reverse begin functions

			// Returns reverse iterator, starting from last element.
			reverse_iterator	rbegin()
			{
				return static_cast<reverse_iterator>(this->end());
			}

			// Returns constant reverse iterator, starting from last element.
			const_reverse_iterator	rbegin() const
			{
				return static_cast<const_reverse_iterator>(this->end());
			}

			// - Reverse end functions

			// Returns reverse iterator, starting from first element.
			reverse_iterator	rend()
			{
				return static_cast<reverse_iterator>(this->begin());
			}

			// Returns constant reverse iterator, starting from first element.
			const_reverse_iterator	rend() const
			{
				return static_cast<const_reverse_iterator>(this->begin());
			}

			// --- CAPACITY ---

			// - Size function

			// Returns number of elements already present.
			size_type	size() const
			{
				return this->filled;
			}

			// - Maximum size function

			// Returns the capacity of the allocator object, not the current
			// capacity of the vector.
			size_type	max_size () const
			{
				return this->alloc.max_size();
			}

			// - Resize function

			// Resize the container to size n.
			// Behaviour is different depending of previous size.
			// If n is lesser, the rest is deleted.
			// If n is greater, elements of value val are inserted after the
			// original content.
			// Reallocation can be made if capacity is exceeded.
			void	resize (size_type n, value_type val = value_type())
			{
				if (n > this->max_size())
					throw MaxSizeExceeded();
				else if (n > this->capacity)
					this->reserve(n);
				if (n > this->filled)
					for (; this->filled < n; this->filled++)
						this->alloc.construct(this->first_elem[this->filled], val);
				else if (n < this->filled)
					for (; this->filled != n; this->filled--)
						this->alloc.destroy(this->first_elem[this->filled - 1]);
			}

			// - Capacity function

			// Returns size of allocated storage capacity, which can be equal
			// or greater than size.
			size_type	capacity () const
			{
				return this->capacity;
			}

			// - Empty function

			// Boolean returning true when size is 0.
			bool	empty () const
			{
				return (this->filled == 0 ? true : false);
			}

			// - Reserve function

			// Change the capacity to contains at least n elements.
			// Reallocation only occurs if n is greater than current capacity.
			void	reserve (size_type n)
			{
				if (n <= this->capacity)
					return ;
				else if (n > this->max_size())
					throw MaxSizeExceeded();
				T*	new_first_elem = alloc.allocate(n);
				for (size_type i = 0; i < this->filled; i++)
				{
					this->alloc.construct(new_first_elem + i,
						this->first_elem[i]);
					this->alloc.destroy(this->first_elem[i]);
				}
				this->alloc.deallocate(this->first_elem, this->capacity);
				this->capacity = n;
				this->first_elem = new_first_elem;
			}

			// --- MODIFIERS ---

			// - Fill assign function

			// Replace the contents with count copies of value value.
			// Capacity is modified only if count is superior to it.
			void	assign (size_type count, const T& value)
			{
				// TODO replace by clear
				for (size_type i = 0; i < this->filled; i++)
					this->alloc.destroy(first_elem[i]);
				this->filled = 0;
				this->first_elem = NULL;
				if (count > this->capacity)
				{
					this->alloc.deallocate(this->first_elem, this->capacity);
					this->capacity = count;
					this->first elem = this->alloc.allocate(this->capacity);
				}
				for (size_type i = 0; i < count; i++)
				{
					this->alloc.construct(this->first_elem + i, value);
					this->filled++;
				}
			}

			// - Range assign function

			// Replace the contents with copies of those in the range first-last
			// . May cause a reallocation if distance between first and last
			// exceed capacity.
			template <class InputIt>
			void	assign (InputIt first, InputIt last)
			{
				size_type	count;
				// TODO replace with clear
				for (size_type i = 0; i < this->filled; i++)
					this->alloc.destroy(first_elem[i]);
				this->filled = 0;
				this->first_elem = NULL;
				if (is_valid_input_iterator(first) == false)
					throw InvalidIteratorTypeException();
				if (first == last)
					return ;
				count = std::distance(first, last);
				if (count > alloc.max_size())
					throw MaxSizeExceeded();
				if (count > this->capacity)
				{
					this->alloc.deallocate(this->first_elem, this->capacity);
					this->capacity = count;
					this->first elem = this->alloc.allocate(this->capacity);
				}
				for (size_type i = 0; i < count; i++, first++)
				{
					this->alloc.construct(this->first_elem + i, *first);
					this->filled++;
				}
			}

			// - Push back function

			// Add an element at the end. May cause a reallocation if capacity
			// is exceeded.
			void	push_back (const value_type& val)
			{
				if (this->filled == this->capacity)
				{
					size_type	new_capacity;
					this->capacity == 0 ? new_capacity = 1
						: new_capacity = this->capacity * 2;
					T*	new_first_elem;
					new_first_elem = this->alloc.allocate(new_capacity);
					for (size_type i = 0; i < this->filled; i++)
						this->alloc.construct(new_first_elem + i,
							this->first_elem[i]);
					for (size_type i = 0; i < this->filled; i++)
						this->alloc.destroy(this->first_elem + i);
					this->alloc.deallocate(this->first_elem);
					this->first_elem = new_first_elem;
					this->capacity = new_capacity;
				}
				this->alloc.construct(this->first_elem + this->filled, val);
				this->filled++;
			}

			// - Pop back function

			// Function to delete last element
			void	pop_back()
			{
				if (this->filled == 0)
					return;
				this->alloc.destroy(this->first_elem + this->filled);
				this->filled--;
			}

			// - Single element insert function

			// Insert element before the given position. May cause reallocation
			// if capacity is exceeded.
			iterator	insert (iterator position, const value_type& val)
			{
				size_type	pos;
				pos = std::distance(this->first_elem, position);
				//TODO continue
			}



	};
};

#endif
