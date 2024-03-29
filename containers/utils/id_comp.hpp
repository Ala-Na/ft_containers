/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_comp.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:27:59 by anadege           #+#    #+#             */
/*   Updated: 2022/03/04 22:46:55 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ID_COMP_HPP
# define ID_COMP_HPP

#include "./iterators.hpp"

namespace ft
{
	// ----------------------------
	// Implementation of enable_if
	// ----------------------------
	// It's a trait which will return a type T only if a given boolean condition
	// is true.
	// Otherwise, enable_if::type is not defined.

	template <bool Cond, class T = void>
	struct enable_if {};

	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	// ------------------------------
	// Implementation of is_integral
	// ------------------------------
	// It's a trait which identifies if T is an integral type.
	// It inherits from integral_constant class and returns either true_type
	// or false_type.
	// Only C++98 integrals types are taken into account here.

	template <typename T, T val>
	struct integral_constant {
		static const T							value = val;
		typedef T							value_type;
		typedef integral_constant<T, val>	type;

		operator value_type() {
			return val;
		}
	};

	typedef integral_constant<bool, true>	true_type;
	typedef integral_constant<bool, false>	false_type;

	// Implementation for differents integral or general types.
	template <class T>
	struct is_integral : public ft::false_type {};

	template <class T>
	struct is_integral<const T> : public is_integral<T> {};

	template <class T>
	struct is_integral<volatile const T> : public is_integral<T> {};

	template <class T>
	struct is_integral<volatile T> : public is_integral<T> {};

	template <>
	struct is_integral<unsigned char> : public ft::true_type {};

	template <>
	struct is_integral<unsigned short> : public ft::true_type {};

	template <>
	struct is_integral<unsigned int> : public ft::true_type {};

	template <>
	struct is_integral<unsigned long> : public ft::true_type {};

	template <>
	struct is_integral<signed char> : public ft::true_type {};

	template <>
	struct is_integral<short> : public ft::true_type {};

	template <>
	struct is_integral<int> : public ft::true_type {};

	template <>
	struct is_integral<long> : public ft::true_type {};

	template <>
	struct is_integral<char> : public ft::true_type {};

	template <>
	struct is_integral<bool> : public ft::true_type {};

	template <>
	struct is_integral<wchar_t> : public ft::true_type {};

	// ------------------------------------------
	// Implementation of equal function template
	// ------------------------------------------
	// It test if elements in two ranges are equal, using input iterators.

	// Equality equal template function, check if elements are equal with ==
	// operator.
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

	// Predicate equal template function, check if elements are equal with a
	// predicate function.
	template <class InputIt1, class InputIt2, class BinaryPredicate>
	bool	equal (InputIt1 first1, InputIt1 last1, InputIt2 first2,
	BinaryPredicate p)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!p(*first1, *first2))
			{
				return false;
			}
		}
		return true;
	};

	// ------------------------------------------------------------
	// Implementation of lexicographical_compare template function
	// ------------------------------------------------------------
	// Goal is to check if  an element InputIt1 is lexicographically less
	// than element InputIt2 inside the range first1, last1 and first2, last2.

	// Default template function, using operator < as comparator.
	template <class InputIt1, class InputIt2>
	bool	lexicographical_compare (InputIt1 first1, InputIt1 last1,
	InputIt2 first2, InputIt2 last2)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
		{
			if (*first1 < *first2)
				return true;
			else if (*first2 < *first1)
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	};

	// Custom template function, using a function comp to compare elements.
	template <class InputIt1, class InputIt2, class Compare>
	bool	lexicographical_compare(InputIt1 first1, InputIt1 last1,
	InputIt2 first2, InputIt2 last2, Compare comp)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
		{
			if (comp(*first1, *first2))
				return true;
			else if (comp(*first2, *first1))
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	};

	// --------------------------------------------
	// Implementation of binary_function structure
	// --------------------------------------------

	// Needed to reimplement less structure, needed by map
	template <typename Arg1, typename Arg2, typename Result>
	struct binary_function
	{
		typedef Arg1	first_argument_type;
		typedef Arg2	second_argument_type;
		typedef Result	result_type;
	};

	// ---------------------------------
	// Implementation of less structure
	// ---------------------------------

	// Needed by map.
	// It just contains a comparison function, using the < operator.
	template <typename Type>
	class less : public binary_function<Type, Type, bool>
	{
		public:
			bool	operator() (const Type& x, const Type& y) const {
				return x < y;
			}
	};


	// --------------------------------
	// Implementation of swap function
	// --------------------------------

	template <class T>
	void swap(T& a, T& b) {
		T	tmp = a;
		a = b;
		b = tmp;
	};
};

#endif
