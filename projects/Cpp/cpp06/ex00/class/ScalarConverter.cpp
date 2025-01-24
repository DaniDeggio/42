/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:12:41 by dde-giov          #+#    #+#             */
/*   Updated: 2025/01/24 18:35:45 by dde-giov         ###   ########.fr       */
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
	char c;
	int n = 0;
	float f = 0.0f;
	double d = 0.0;

	for (int i = 0; i < 8; i++) {
		if (literal == pseudo[i]) {
			d = std::atof(literal.c_str());
			std::cout << "char: impossible" << std::endl;
			std::cout << "int: impossible" << std::endl;
			std::cout << "float: " << static_cast<float>(d) << 'f' << std::endl;
			std::cout << "double: " << d << std::endl;
			return;
		}
	}

	if (literal.length() == 1 && !std::isdigit(literal[0])) {
		c = literal[0];
		if (c < 32 || c > 126 || c == 127)
			std::cout << "char: Non displayable" << std::endl;
		else
			std::cout << "char: '" << c << "'" << std::endl;
		std::cout << "int: " << static_cast<int>(c) << std::endl;
		std::cout << "float: " << static_cast<float>(c) << 'f' << std::endl;
		std::cout << "double: " << static_cast<double>(c) << std::endl;
		return;
	}
	n = std::atoi(literal.c_str());
	if (std::strchr(literal.c_str(), '.')){

		if (literal[literal.length() - 1] == 'f'){
			f = static_cast<float>(std::atof(literal.c_str()));
			if (n < 32 || n > 126 || n == 127)
				std::cout << "char: Non displayable" << std::endl;
			else
				std::cout << "char: '" << static_cast<char>(f) << "'" << std::endl;
			std::cout << "int: " << static_cast<int>(f) << std::endl;
			std::cout << "float: " << f << 'f' << std::endl;
			std::cout << "double: " << static_cast<double>(f) << std::endl;
			return;
		}
		d = std::atof(literal.c_str());
		if (n < 32 || n > 126 || n == 127)
			std::cout << "char: Non displayable" << std::endl;
		else
			std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;
		std::cout << "int: " << static_cast<int>(d) << std::endl;
		std::cout << "float: " << static_cast<float>(d) << 'f' << std::endl;
		std::cout << "double: " << d << std::endl;
			return;
		
	} else {
		if (n < 32 || n > 126 || n == 127)
			std::cout << "char: Non displayable" << std::endl;
		else
			std::cout << "char: '" << static_cast<char>(n) << "'" << std::endl;
		std::cout << "int: " << n << std::endl;
		std::cout << "float: " << static_cast<float>(n) << 'f' << std::endl;
		std::cout << "double: " << static_cast<double>(n) << std::endl;
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
