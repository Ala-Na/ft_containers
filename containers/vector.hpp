/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:21:45 by anadege           #+#    #+#             */
/*   Updated: 2022/02/07 23:42:33 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <cstddef>
#include <memory>
#include <iterator>
#include "./utils/iterators.hpp"
#include "./utils/id_comp.hpp"

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
			typedef std::random_access_iterator<value_type>			iterator;
			typedef std::random_access_iterator<const value_type>	const_iterator;
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
				value_type *array = this->alloc.allocate(this->capacity);
				for (size_t i = 0; i < this->capacity; i++)
				{
					this->alloc.construct(array + i, val);
					this->filled++;
				}
				this->first_elem = array;
			}

			// - Range constructor
			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
			const allocator_type &alloc = allocator_type()) :
				alloc(alloc), capacity(0), filled(0)
			{
				// need to check that ft::iterator_traits<InputIterator>::iterator_category
				// is std::input_iterator_tag
				// if not, std::abort()
			}

	};
};

#endif
