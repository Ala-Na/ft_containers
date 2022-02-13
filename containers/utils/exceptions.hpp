/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:42:46 by anadege           #+#    #+#             */
/*   Updated: 2022/02/13 15:37:58 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

#include <exception>

namespace ft
{
	struct InvalidIteratorTypeException : public std::exception
	{
		const char*	what () const throw ()
		{
			return "Iterator type is invalid.";
		}
	};

	struct MaxSizeExceededException : public std::exception
	{
		const char*	what () const throw ()
		{
			return "Container max size is or will be exceeded.";
		}
	};

	struct OutOfRangeException : public std::exception
	{
		const char*	what () const throw ()
		{
			return "Element is out of container's range.";
		}
	};

};

#endif
