/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:21:45 by anadege           #+#    #+#             */
/*   Updated: 2022/01/19 14:49:06 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <cstddef>
#include <memory>

//Must use ft as namespace
//Containers must be called as ft::<containers>
//Only C++98
//Must use std::allocator
//Must implement system of iterator if present in container
//STD lib is authorized
//STL containers are forbidden
//no need to code vector<bool>
//pile must use vector container as subjacent container


//TODO random_access_iterator_tag and inclue corresponding .hpp
//TODO Same with reverse iterator
//TODO Same with iterator_traits

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:

			// Members types definitions
			typedef T													value_type;
			typedef Alloc												allocator_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef ft::random_access_iterator<value_type>				iterator;
			typedef ft::random_access_iterator<const value_type>		const_iterator;
			typedef ft::reverse_iterator<iterator>						reverse_iterator;
			typedef ft::reverse_iterator<const iterator>				const_reverse_iterator;
			typedef typename std::ptrdiff_t								difference_type;
			typedef typename std::size_t								size_type;

		private:

			//Parameters (choosen by me)
			allocator_type	alloc; //allocator object
			size_type		capacity; //max capacity of vector
			size_type		filled; //present number of element in vector
			T				*first_elem; //pointer to first element of vector

		public:
			// Constructors
			explicit vector (const allocator_type &alloc = allocator_type()) :
				alloc(alloc),
				capacity(0),
				filled(0),
				first_elem(NULL)
			{};
	};
};

#endif
