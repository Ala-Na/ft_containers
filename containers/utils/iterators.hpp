/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:57:47 by anadege           #+#    #+#             */
/*   Updated: 2022/01/19 16:57:53 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// iterators_traits, reverse_iterator, enable_if, is_integral, equal/lexicographical com-
// pare, std : :pair, std : :make_pair, doivent être réimplémenté

#ifndef ITERATORS_HPP
# define ITERATORS_HPP

#include <cstddef>

namespace ft
{
	// Tags for iterators identifications, which are empty
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectionnal_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectionnal_iterator_tag {};

	template <class Iterator>
	struct iterator_traits {
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
	};

	template <class T>
	struct iterator_traits<T*> {
		typedef ft::random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef std::ptrdiff_t				difference_type;
		typedef T							*pointer;
		typedef T							&reference;
	};

	template <class T>
	struct iterator_traits<const T*> {
		typedef ft::random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef std::ptrdiff_t				difference_type;
		typedef T							*pointer;
		typedef T							&reference;
	};
}

#endif
