/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:12:41 by dde-giov          #+#    #+#             */
/*   Updated: 2025/01/21 05:59:39 by dde-giov         ###   ########.fr       */
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
	try {
		char c = static_cast<char>(std::stoi(literal));
		std::cout << "char: '" << c << "'" << std::endl;
	} catch (std::exception &e) {
		std::cout << "char: impossible" << std::endl;
	}
	try {
		int i = static_cast<int>(std::stoi(literal));
		std::cout << "int: " << i << std::endl;
	} catch
	(std::exception &e) {
		std::cout << "int: impossible" << std::endl;
	}
	try {
		float f = static_cast<float>(std::stof(literal));
		std::cout << "float: " << f << "f" << std::endl;
	} catch (std::exception &e) {
		std::cout << "float: impossible" << std::endl;
	}
	try {
		double d = static_cast<double>(std::stod(literal));
		std::cout << "double: " << d << std::endl;
	} catch (std::exception &e) {
		std::cout << "double: impossible" << std::endl;
	}
}
