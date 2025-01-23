/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:12:41 by dde-giov          #+#    #+#             */
/*   Updated: 2025/01/23 17:38:40 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter(void) {
}

ScalarConverter::ScalarConverter(ScalarConverter const &src) {
	(void)src;
}

ScalarConverter &ScalarConverter::operator=(ScalarConverter const &src) {
	(void)src;
	return *this;
}

ScalarConverter::~ScalarConverter(void) {
}

void ScalarConverter::convert(std::string literal) {
	std::string pseudo[8] = {"inff", "+inff", "-inff", "nanf", "inf", "+inf", "-inf", "nan"};

	for (int i = 0; i < 8; i++) {
		if (literal == pseudo[i]) {
			float f = std::atof(literal.c_str());
			std::cout << "char: impossible" << std::endl;
			std::cout << "int: impossible" << std::endl;
			std::cout << "float: " << f << "f" << std::endl;
			std::cout << "double: " << static_cast<double>(f) << std::endl;
			return;
		}
	}
// 	try {
// 		int i = std::atoi(literal.c_str());
// 		if (i < 32 || i > 126 || i == 127)
// 			throw std::exception();
// 		char c = static_cast<char>(std::atoi(literal.c_str()));
// 		std::cout << "char: '" << c << "'" << std::endl;
// 	} catch (std::exception &e) {
// 		std::cout << "char: impossible" << std::endl;
// 	}
	
// 	try {
// 		int i = static_cast<int>(std::atoi(literal.c_str()));
// 		std::cout << "int: " << i << std::endl;
// 	} catch
// 	(std::exception &e) {
// 		std::cout << "int: impossible" << std::endl;
// 	}
// 	try {
// 		float f = static_cast<float>(std::atof(literal.c_str()));
// 		std::cout << "float: " << f << "f" << std::endl;
// 	} catch (std::exception &e) {
// 		std::cout << "float: impossible" << std::endl;
// 	}
// 	try {
// 		double d = static_cast<double>(std::atof(literal.c_str()));
// 		std::cout << "double: " << d << std::endl;
// 	} catch (std::exception &e) {
// 		std::cout << "double: impossible" << std::endl;
// 	}
}
