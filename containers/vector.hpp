/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:21:45 by anadege           #+#    #+#             */
/*   Updated: 2022/01/18 17:14:25 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

namespace ft
{
    template <class T, class Alloc = allocator<T> >
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
                

            explicit vector (const allocator_type& alloc = allocator_type())
    };
};

#endif
