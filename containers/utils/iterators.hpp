/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:57:47 by anadege           #+#    #+#             */
/*   Updated: 2022/02/09 15:54:42 by anadege          ###   ########.fr       */
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
				return this->current;
			}

			// - Assignment operator
			template <class U>
			reverse_iterator& operator= (const reverse_iterator<U>& other)
			{
				current = other.base();
				return *this;
			}

			// - Dereference iterator function (returns pointer to the element
			// pointed by the iterator and decrease a copy of the base iterator)
			reference	operator* () const
			{
				Iterator	tmp = this->current;
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
				--(this->current);
				return *this;
			}

			// - Post-increment iterator position modifier
			reverse_iterator	operator++ (int)
			{
				reverse_iterator tmp = *this;
				--(this->current);
				return tmp;
			}

			// - Pre-decrement iterator position modifier
			reverse_iterator&	operator-- ()
			{
				++(this->current);
				return *this;
			}

			// - Post-decrement iterator position modifier
			reverse_iterator	operator-- (int)
			{
				reverse_iterator tmp = *this;
				++(this->current);
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
				this->current -= n;
				return *this;
			}

			// - Retrocede iterator by n position modifier
			reverse_iterator&	operator-= (difference_type n)
			{
				this->current += n;
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

	// -----------------------------------------
	// Implementation of random_access_iterator
	// -----------------------------------------

	// It's a bidirectionnal iterator which can be used to access elements at an
	// abritrary offset position.
	template <class Iterator>
	class random_access_iterator {

		protected:
			// Member objects :
			Iterator*	current;

		public:
			// Member types :
			typedef Iterator													iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;

			// Member functions :
			// - Default constructor
			random_access_iterator () : current() {}

			// - Initialization constructor
			explicit random_access_iterator (iterator_type* it) : current(it) {}

			// - Copy constructor
			template <class Iter>
			random_access_iterator (const ft::random_access_iterator<Iter>& it) :
			current(it.base()) {}

			// - Base function (returns a copy of the base iterator)
			Iterator*	base () const
			{
				return this->current;
			}

			// - Assignment operator
			template <class U>
			random_access_iterator& operator= (const reverse_iterator<U>& other)
			{
				this->current = other.base();
				return *this;
			}

			// - Dereference iterator function (returns pointer to the element
			// pointed by the iterator and decrease a copy of the base iterator)
			reference	operator* () const
			{
				return *(this->current);
			}

			// - Dereference iterator function (returns pointer to the element
			// pointed by the iterator)
			pointer	operator-> () const
			{
				return &(operator*());
			}

			// - Pre-increment iterator position modifier
			random_access_iterator&	operator++ ()
			{
				++(this->current);
				return *this;
			}

			// - Post-increment iterator position modifier
			random_access_iterator	operator++ (int)
			{
				random_access_iterator tmp = *this;
				++(this->current);
				return tmp;
			}

			// - Pre-decrement iterator position modifier
			random_access_iterator&	operator-- ()
			{
				--(this->current);
				return *this;
			}

			// - Post-decrement iterator position modifier
			random_access_iterator	operator-- (int)
			{
				random_access_iterator tmp = *this;
				--(this->current);
				return tmp;
			}

			// - Addition operator
			random_access_iterator	operator+ (difference_type n) const
			{
				return random_access_iterator(base() + n);
			}

			// - Substraction operator
			random_access_iterator	operator- (difference_type n) const
			{
				return random_access_iterator(base() - n);
			}

			// - Advance iterator by n position modifier
			random_access_iterator&	operator+= (difference_type n)
			{
				this->current += n;
				return *this;
			}

			// - Retrocede iterator by n position modifier
			random_access_iterator&	operator-= (difference_type n)
			{
				this->current -= n;
				return *this;
			}

			// - Dereference iterator with offset at n position
			reference	operator[] (difference_type n) const
			{
				return *(base()[n - 1]);
			}
	};

	// Non member functions :
	// - Relationals operators
	template <class Iterator1, class Iterator2>
	bool	operator==(const ft::random_access_iterator<Iterator1>& lhs, const ft::random_access_iterator<Iterator2>& rhs)
	{
		return lhs.base() == rhs.base();
	};

	template <class Iterator1, class Iterator2>
	bool	operator!=(const ft::random_access_iterator<Iterator1>& lhs, const ft::random_access_iterator<Iterator2>& rhs)
	{
		return lhs.base() != rhs.base();
	};

	template <class Iterator1, class Iterator2>
	bool	operator<(const ft::random_access_iterator<Iterator1>& lhs, const ft::random_access_iterator<Iterator2>& rhs)
	{
		return lhs.base() < rhs.base();
	};

	template <class Iterator1, class Iterator2>
	bool	operator<=(const ft::random_access_iterator<Iterator1>& lhs, const ft::random_access_iterator<Iterator2>& rhs)
	{
		return lhs.base() <= rhs.base();
	};

	template <class Iterator1, class Iterator2>
	bool	operator>(const ft::random_access_iterator<Iterator1>& lhs, const ft::random_access_iterator<Iterator2>& rhs)
	{
		return lhs.base() > rhs.base();
	};

	template <class Iterator1, class Iterator2>
	bool	operator>=(const ft::random_access_iterator<Iterator1>& lhs, const ft::random_access_iterator<Iterator2>& rhs)
	{
		return lhs.base() >= rhs.base();
	};

	// - Addition and substraction operator overloads
	template <class Iterator>
	random_access_iterator<Iterator> operator+
	(typename random_access_iterator<Iterator>::difference_type n,
	const random_access_iterator<Iterator>& it)
	{
		return random_access_iterator<Iterator>(it.base() + n);
	};

	template <class Iterator>
	typename random_access_iterator<Iterator>::difference_type operator-
	(const random_access_iterator<Iterator>& lhs,
	const random_access_iterator<Iterator>& rhs)
	{
		return lhs.base() - rhs.base();
	};

	// -------------------------------------------
	// Home made is_valid_input_iterator function
	// -------------------------------------------

	// Function to check if an iterator is a valid input iterator (including
	// forward, bidirectionnal and random access iterator).
	// It's quite ugly and use typeid.
	// Another solution could be to create template struct/class which returns a
	// true/false type depending of the iterator_tag.

	// Or templated functions for each kind of valid input iterator_tag.

	// Example from stackoverflow :
	//	template <typename Iterator>
	//	void FooImpl(Iterator first, Iterator last, std::random_access_iterator_tag) {
	//	}
	//
	//	template <typename Iterator>
	//	void Foo(Iterator first, Iterator last) {
	//		typedef typename std::iterator_traits<Iterator>::iterator_category category;
	//		return FooImpl(first, last, category());
	//	}

	// Another solution would be to reimplement is_base_of (CPP20) in order to
	// verify InputIterator type inside a specialized class template.

	// Either of those solutions need a lot of lines. But maybe they're quicker
	// to use than multiple typeid checks.

	template <class Iterator>
	bool	is_valid_input_iterator(Iterator it)
	{
		const std::type_info&	it_cat = typeid(typename \
			ft::iterator_traits<Iterator>::iterator_category);
		if (it_cat != typeid(std::input_iterator_tag)
			&& it_cat != typeid(std::forward_iterator_tag)
			&& it_cat != typeid(std::bidirectional_iterator_tag)
			&& it_cat != typeid(std::random_access_iterator_tag))
			return false;
		return true;
	};
};

#endif
