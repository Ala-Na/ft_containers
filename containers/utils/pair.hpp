/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:15:01 by anadege           #+#    #+#             */
/*   Updated: 2022/02/22 23:02:29 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	// ---------------------------------------------
	// Implementation of pair structure and methods
	// ---------------------------------------------

	template <class T1, class T2>
	struct pair
	{
		// Member types :
		typedef T1	first_type;
		typedef T2 second_type;

		// Member objects :
		T1	first;
		T2	second;

		// Member functions :
		// - Default constructor
		pair () : first(), second() {}

		// - Copy constructor
		template <class U, class V>
		pair (const pair <U, V>& pr) : first(pr.first), second(pr.second) {}

		// - Initialization constructor
		pair (const T1& a, const T2& b) : first(a), second(b) {}

		// - Assignment operator
		pair&	operator= (const pair& pr)
		{
			first = pr.first;
			second = pr.second;
			return *this;
		}
	};

	// Non member functions :
	// - Function make_pair
	template <class T1, class T2>
	pair<T1, T2>	make_pair (T1 x, T2 y)
	{
		return (pair <T1, T2>(x, y));
	};

	// - Relationals operators
	template <class T1, class T2>
	bool	operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first == rhs.first) && (lhs.second == rhs.second);
	};

	template <class T1, class T2>
	bool	operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(lhs == rhs);
	};

	template <class T1, class T2>
	bool	operator< (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return lhs.first < rhs.first || (!(rhs.first < lhs.first)
			&& lhs.second < rhs.second);
	};

	template <class T1, class T2>
	bool	operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(rhs < lhs);
	};

	template <class T1, class T2>
	bool	operator> (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return rhs < lhs;
	};

	template <class T1, class T2>
	bool	operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(lhs < rhs);
	};

	// - Use first structure for use of key during comparisons in map.
	template <typename Pair>
	struct use_first {
		typedef typename	Pair::first_type result_type;

		const result_type&	operator() (const Pair& x) const {
			return x.first;
		}
	};
};

#endif
