/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:42:46 by anadege           #+#    #+#             */
/*   Updated: 2022/02/09 16:12:49 by anadege          ###   ########.fr       */
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

	struct MaxSizeExceeded : public std::exception
	{
		const char*	what () const throw ()
		{
			return "Container max size is exceeded.";
		}
	};

};

#endif
