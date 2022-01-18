/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:21:45 by anadege           #+#    #+#             */
/*   Updated: 2022/01/18 17:50:57 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

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
    template <class T, class Alloc = std::allocator<T> >
    class vector
    {
        public:

            // Members types
            typedef T           value_type;
            typedef T*          pointer;
            typedef T&          reference;
            typedef const T*    const_pointer;
            typedef const T&    const_reference;
            typedef size_t      size_type;
            typedef ptdrdiff_t  difference_type;

            // Constructors
            explicit vector (const allocator_type& alloc = allocator_type())
    };
};

#endif
