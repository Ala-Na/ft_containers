/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:57:47 by anadege           #+#    #+#             */
/*   Updated: 2022/02/07 23:47:51 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORS_HPP
# define ITERATORS_HPP

// Librairy needed to use ptrdiff_t.
#include <cstddef>
// Librairy needed to use iterators tags
#include <iterator>

namespace ft
{
	// -----------------------------------
	// Implementation of iterator_traits
	// -----------------------------------

	// It's a trait class defining properties of iterators.
	// Some algorithms need to identify those properties to use the iterator
	// accordingly.

	// Definition for iterator_traits class template.
	template <class Iterator>
	struct iterator_traits {
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
	};

	// Partial specialization for pointer types. It use a random_access_iterator
	// by default.
	template <class T>
	struct iterator_traits<T*> {
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef T*								pointer;
		typedef T&								reference;
	};

	// Partial specialization for const pointer types. It use a
	// random_access_iterator by default.
	template <class T>
	struct iterator_traits<const T*> {
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef const T*						pointer;
		typedef const T&						reference;
	};

	// -----------------------------------
	// Implementation of reverse_iterator
	// -----------------------------------

	// It's a class template which adapt in order to reverse the direction of a
	// given iterator which need to be at least a bidirectionnal iterator.
	// Iterator is set as a random_acces_iterator by default as the partial
	// specialization for pointer types of iterator_traits is called.

	// Definition for reverse_iterator class template
	template <class Iterator>
	class reverse_iterator {

		protected:
			// Member objects :
			Iterator current;

		public:
			// Member types :
			typedef Iterator															iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;

			// Member functions :
			// - Default constructor
			reverse_iterator () : current() {}

			// - Initialization constructor
			explicit reverse_iterator (iterator_type it) : current(it) {}

			// - Copy constructor
			template <class Iter>
			reverse_iterator (const ft::reverse_iterator<Iter>& rev_it) :
			current(rev_it.base()) {}

			// - Base function (returns a copy of the base iterator)
			iterator_type	base () const
			{
				return current;
			}

			// - Dereference iterator function (returns pointer to the element
			// pointed by the iterator and decrease a copy of the base iterator)
			reference	operator* () const
			{
				Iterator	tmp = current;
				return *--tmp;
			}

			// - Dereference iterator function (returns pointer to the element
			// pointed by the iterator)
			pointer	operator-> () const
			{
				return &(operator*());
			}

			// - Pre-increment iterator position modifier
			reverse_iterator&	operator++ ()
			{
				--current;
				return *this;
			}

			// - Post-increment iterator position modifier
			reverse_iterator	operator++ (int)
			{
				reverse_iterator tmp = *this;
				--current;
				return tmp;
			}

			// - Pre-decrement iterator position modifier
			reverse_iterator&	operator-- ()
			{
				++current;
				return *this;
			}

			// - Post-decrement iterator position modifier
			reverse_iterator	operator-- (int)
			{
				reverse_iterator tmp = *this;
				++current;
				return tmp;
			}

			// - Addition operator
			reverse_iterator	operator+ (difference_type n) const
			{
				return reverse_iterator(base() - n);
			}

			// - Substraction operator
			reverse_iterator	operator- (difference_type n) const
			{
				return reverse_iterator(base() + n);
			}

			// - Advance iterator by n position modifier
			reverse_iterator&	operator+= (difference_type n)
			{
				current -= n;
				return *this;
			}

			// - Retrocede iterator by n position modifier
			reverse_iterator&	operator-= (difference_type n)
			{
				current += n;
				return *this;
			}

			// - Dereference iterator with offset at n position
			reference	operator[] (difference_type n) const
			{
				return *(base()[-n - 1]);
			}
	};

	// Non member functions :
	// - Relationals operators
	template <class Iterator1, class Iterator2>
	bool	operator==(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() == rhs.base();
	};

	template <class Iterator1, class Iterator2>
	bool	operator!=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() != rhs.base();
	};

	template <class Iterator1, class Iterator2>
	bool	operator<(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() < rhs.base();
	};

	template <class Iterator1, class Iterator2>
	bool	operator<=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() <= rhs.base();
	};

	template <class Iterator1, class Iterator2>
	bool	operator>(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() > rhs.base();
	};

	template <class Iterator1, class Iterator2>
	bool	operator>=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() >= rhs.base();
	};

	// - Addition and substraction operator overloads
	template <class Iterator>
	reverse_iterator<Iterator> operator+
	(typename reverse_iterator<Iterator>::difference_type n,
	const reverse_iterator<Iterator>& rev_it)
	{
		return reverse_iterator<Iterator>(rev_it.base() - n);
	};

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-
	(const reverse_iterator<Iterator>& lhs,
	const reverse_iterator<Iterator>& rhs)
	{
		return rhs.base() - lhs.base();
	};
};

#endif
