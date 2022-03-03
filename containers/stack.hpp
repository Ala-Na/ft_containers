/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:21:38 by anadege           #+#    #+#             */
/*   Updated: 2022/03/04 00:28:06 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include "./vector.hpp"
#include "./utils/iterators.hpp"
#include "./utils/id_comp.hpp"
#include "./utils/exceptions.hpp"

namespace ft
{
	template <class T, class Container = vector<T> >
	class stack
	{
		public:

			// ---------------------------
			// Members types definitions :
			// ---------------------------

			typedef T								value_type;
			typedef Container						container_type;
			typedef typename Container::size_type	size_type;

		protected:

			// -----------------
			// Member objects :
			// -----------------
			container_type	container;

		public:
			// -----------------
			// Member functions :
			// -----------------

			// - Constructor
			explicit	stack (const container_type& ctnr = container_type()) :
				container(ctnr) {}

			// - Empty function
			bool	empty () const {
				return this->container.empty();
			}

			// - Size function
			size_type	size () const {
				return this->container.size();
			}

			// - Top function
			value_type&	top () {
				return this->container.back();
			}

			value_type&	top () const {
				return this->container.back();
			}

			// - Push function
			void	push (const value_type& val) {
				this->container.push_back(val);
			}

			// - Pop function
			void	pop() {
				this->container.pop_back();
			}
			// Declarations of relationnals operators to access container
			template<typename Type, typename Cont>
			friend bool	operator== (const stack<Type, Cont>&, const stack<Type, Cont>&);

			template<typename Type, typename Cont>
			friend bool	operator< (const stack<Type, Cont>&, const stack<Type, Cont>&);

	};
	// ----------------------
	// Non member functions :
	// ----------------------

	// - Relational operators functions

	template <class T, class Container>
	bool	operator== (const stack<T, Container>& lhs,
		const stack<T, Container>& rhs)
	{
		return lhs.container == rhs.container;
	};

	template <class T, class Container>
	bool	operator!= (const stack<T, Container>& lhs,
		const stack<T, Container>& rhs)
	{
		return !(lhs == rhs);
	};

	template <class T, class Container>
	bool	operator< (const stack<T, Container>& lhs,
		const stack<T, Container>& rhs)
	{
		return lhs.container < rhs.container;
	};

	template <class T, class Container>
	bool	operator> (const stack<T, Container>& lhs,
		const stack<T, Container>& rhs)
	{
		return rhs < lhs;
	};

	template <class T, class Container>
	bool	operator<= (const stack<T, Container>& lhs,
		const stack<T, Container>& rhs)
	{
		return !(rhs < lhs);
	};

	template <class T, class Container>
	bool	operator>= (const stack<T, Container>& lhs,
		const stack<T, Container>& rhs)
	{
		return !(lhs < rhs);
	};
};

#endif
