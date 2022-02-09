/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:21:45 by anadege           #+#    #+#             */
/*   Updated: 2022/02/09 16:40:27 by anadege          ###   ########.fr       */
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

			// Members types definitions :
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

			//Parameters (choosen by me)
			allocator_type	alloc; //allocator object
			size_type		capacity; //max capacity of vector
			size_type		filled; //present number of element in vector
			T				*first_elem; //pointer to first element of vector

		public:
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
					this->alloc.construct(first_elem + i, val);
					this->filled++;
				}
			}

			// - Range constructor
			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
			const allocator_type &alloc = allocator_type()) :
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
				for (size_t i = 0; i < this->capacity; i++)
				{
					printf("new elem : %i\n", *first);
					this->alloc.construct(first_elem + i, *first);
					this->filled++;
					first++;
				}
			}

			
	};
};

#endif
