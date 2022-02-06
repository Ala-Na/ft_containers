/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:57:47 by anadege           #+#    #+#             */
/*   Updated: 2022/02/06 19:18:01 by anadege          ###   ########.fr       */
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

	// Definitions for iterator_traits
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
		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef T*								pointer;
		typedef T&								reference;
	};

	template <class T>
	struct iterator_traits<const T*> {
		typedef ft::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef const T*						pointer;
		typedef const T&						reference;
	};

	// Definition for reverse_iterator
	template <class Iterator>
	class reverse_iterator {

		protected:
			// Member objects
			Iterator current;

		public:
			// Member types
			Iterator															iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;

			// Reverse_iterator constructors
			// Default constructor
			reverse_iterator () : current() {};
			// Initialization constructor
			explicit reverse_iterator (iterator_type it) : current(it) {};
			// Copy constructor
			template <class Iter>
			reverse_iterator (const ft::reverse_iterator<Iter>& rev_it) : current(rev_it.base()) {};

			// Member functions

			iterator_type	base () const { return current; };

			reference	operator* () const
			{
				Iterator	tmp = current;
				return *--tmp;
			};

			pointer	operator-> () const
			{
				return &(operator*());
			};

			reverse_iterator&	operator++ ()
			{
				--current;
				return *this;
			};

			reverse_iterator	operator++ (int)
			{
				reverse_iterator tmp = *this;
				--current;
				return tmp;
			};

			reverse_iterator&	operator-- ()
			{
				++current;
				return *this;
			};

			reverse_iterator	operator-- (int)
			{
				reverse_iterator tmp = *this;
				++current;
				return tmp;
			};

			reverse_iterator	operator+ (difference_type n) const
			{
				return (reverse_iterator(base() - n);
			};

			reverse_iterator	operator- (difference_type n) const
			{
				return (reverse_iterator(base() + n);
			};

			reverse_iterator&	operator+= (difference_type n)
			{
				current -= n;
				return *this;
			};

			reverse_iterator&	operator-= (difference_type n)
			{
				current += n;
				return *this;
			};

			reference	operator[] (difference_type n) const
			{
				return *(base()[-n - 1]);
			};
	};

	// Non member functions for reverse_iterator
	template <class Iterator1, class Iterator2>
	bool	operator==(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() == rhs.base();
	};

	template <class Iterator1, class Iterator2>
	bool	operator!=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() != rhs.base());
	};

	template <class Iterator1, class Iterator2>
	bool	operator<(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() < rhs.base());
	};

	template <class Iterator1, class Iterator2>
	bool	operator<=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() <= rhs.base());
	};

	template <class Iterator1, class Iterator2>
	bool	operator>(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() > rhs.base());
	};

	template <class Iterator1, class Iterator2>
	bool	operator>=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() >= rhs.base());
	};

	// enable_if reimplementation
	template <bool Cond, class T = void>
	struct enable_if {};

	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	// is_integral reimplementation
	// quick simple implementation of integral_constant to define true_type and false_type
	template <typename T, bool val>
	struct integral_constant
	{
		typedef T			value_type;
		static const bool	value = val;
	};

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	// Implementation made only for C++98 suported types
	template <class T>
	struct is_integral : public false_type {};

	template <class T>
	struct is_integral<const T> : public is_integral<T> {};

	template <class T>
	struct is_integral<volatile const T> : public is_integral<T> {};

	template <class T>
	struct is_integral<volatile T> : public is_integral<T> {};

	template <class T>
	struct is_integral<unsigned char> : public true_type {};

	template <class T>
	struct is_integral<unsigned short> : public true_type {};

	template <class T>
	struct is_integral<unsigned int> : public true_type {};

	template <class T>
	struct is_integral<unsigned long> : public true_type {};

	template <class T>
	struct is_integral<signed char> : public true_type {};

	template <class T>
	struct is_integral<short> : public true_type {};

	template <class T>
	struct is_integral<int> : public true_type {};

	template <class T>
	struct is_integral<long> : public true_type {};

	template <class T>
	struct is_integral<char> : public true_type {};

	template <class T>
	struct is_integral<bool> : public true_type {};

	template <class T>
	struct is_integral<wchar_t> : public true_type {};

	// equal compare implementation
	template <class InputIt1, class InputIt2>
	bool	equal (InputIt1 first1, InputIt1 last1, InputIt2  first2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!(*first1 == *first2))
				return false;
		}
		return true;
	};

	template <class InputIt1, class InputIt2, class BinaryPredicate>
	bool	equal (InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p);
	{
		for (; first1 != last1; ++first1, ++first2) {
			if (!p(*first1, *first2)) {
				return false;
			}
		}
		return true;
	};

	// lexicographical_compare implementation
	template <class InputIt1, class InputIt2>
	bool	lexicographical_compare (InputIt1 )

};

#endif
