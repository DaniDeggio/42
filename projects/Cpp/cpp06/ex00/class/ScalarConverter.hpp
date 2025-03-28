/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 05:17:39 by dde-giov          #+#    #+#             */
/*   Updated: 2025/01/21 05:53:48 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctype.h>
#include <iomanip>
#include <cmath>
#include <limits>
#include <climits>
#include <cerrno>

class ScalarConverter {
	private:	
		ScalarConverter(void);
		ScalarConverter(ScalarConverter const &src);
		ScalarConverter &operator=(ScalarConverter const &src);
		~ScalarConverter();

	public:
		static void convert(std::string literal);
}; 

#endif