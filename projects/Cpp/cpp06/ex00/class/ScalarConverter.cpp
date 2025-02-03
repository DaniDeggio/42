/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:12:41 by dde-giov          #+#    #+#             */
/*   Updated: 2025/02/03 17:55:36 by dde-giov         ###   ########.fr       */
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
			double d = std::atof(literal.c_str());
			std::cout << "char: impossible" << std::endl;
			std::cout << "int: impossible" << std::endl;
			std::cout << "float: " << static_cast<float>(d) << 'f' << std::endl;
			std::cout << "double: " << d << std::endl;
			return;
		}
	}

	if (literal.length() == 1 && !std::isdigit(literal[0])) {
		char c = literal[0];
		if (std::isprint(c) == 0)
			std::cout << "char: Non displayable" << std::endl;
		else
			std::cout << "char: '" << c << "'" << std::endl;
		std::cout << "int: " << static_cast<int>(c) << std::endl;
		//std::cout << std::fixed << std::showpoint;
		std::cout << "float: " << static_cast<float>(c) << "f" << std::endl;
		std::cout << "double: " << static_cast<double>(c) << std::endl;
		return;
	}
	if (std::strchr(literal.c_str(), '.')) {

		if (literal[literal.length() - 1] == 'f') {
			float f = std::atof(literal.c_str());
			if (std::isprint(f) == 0)
				std::cout << "char: Non displayable" << std::endl;
			else
				std::cout << "char: '" << static_cast<char>(f) << "'" << std::endl;
			std::cout << "int: " << static_cast<int>(f) << std::endl;
            if (std::fmod(f, 1.0f) == 0.0f){
				std::cout << "float: " << f << ".0f" << std::endl;
				std::cout << "double: " << static_cast<double>(f) << ".0" << std::endl;
			} else {
				std::cout << std::setprecision(7) << "float: " << f << "f" << std::endl;
				std::cout << std::setprecision(15) << "double: " << static_cast<double>(f) << std::endl;
			}
			return;
		}
		double d = std::atof(literal.c_str());
		if (std::isprint(d) == 0)
			std::cout << "char: Non displayable" << std::endl;
		else
			std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;
		std::cout << "int: " << static_cast<int>(d) << std::endl;
		if (std::fmod(d, 1.0) == 0.0){
			std::cout << "float: " << static_cast<float>(d) << ".0f" << std::endl;
			std::cout << "double: " << d << ".0" << std::endl;
		} else {
			std::cout << std::setprecision(7) << "float: " << static_cast<float>(d) << "f" << std::endl;
			std::cout << std::setprecision(15) << "double: " << d << std::endl;
		}
		return;

	} else {
		int n = std::atoi(literal.c_str());
		if (std::isprint(n) == 0)
			std::cout << "char: Non displayable" << std::endl;
		else
			std::cout << "char: '" << static_cast<char>(n) << "'" << std::endl;
		std::cout << "int: " << n << std::endl;
		std::cout << "float: " << static_cast<float>(n) << ".0f" << std::endl;
		std::cout << "double: " << static_cast<double>(n) << ".0" << std::endl;
	}
}
