/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:12:41 by dde-giov          #+#    #+#             */
/*   Updated: 2025/02/05 04:30:57 by dde-giov         ###   ########.fr       */
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
	errno = 0; // Reset di errno prima di ogni conversione
	char *end;

	for (int i = 0; i < 8; i++) {
		if (literal == pseudo[i]) {
            double d = std::strtod(literal.c_str(), &end);
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
            float f = std::strtof(literal.c_str(), &end);
			if (errno == ERANGE || *end != 'f') {
                std::cout << "Conversione in float fuori range o non valida" << std::endl;
                return;
			}
			if (static_cast<int>(f) < 33 || static_cast<int>(f) > 126)
				std::cout << "char: Non displayable" << std::endl;
			else
				std::cout << "char: '" << static_cast<char>(f) << "'" << std::endl;
			if (static_cast<long>(f) > INT_MAX || static_cast<long>(f) < INT_MIN)
				std::cout << "int: impossible" << std::endl;
			else
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

        double d = std::strtod(literal.c_str(), &end);
		if (errno == ERANGE || *end != '\0') {
            std::cout << "Conversione in double fuori range o non valida" << std::endl;
            return;
        }
		if (static_cast<int>(d) < 33 || static_cast<int>(d) > 126)
			std::cout << "char: Non displayable" << std::endl;
		else
			std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;
		if (static_cast<long>(d) > INT_MAX || static_cast<long>(d) < INT_MIN)
			std::cout << "int: impossible" << std::endl;
		else
			std::cout << "int: " << static_cast<int>(d) << std::endl;
		if (std::fmod(d, 1.0) == 0.0){
        	if (d > std::numeric_limits<float>::max() || d < std::numeric_limits<float>::min())
				std::cout << "float: impossible" << std::endl;
			else
				std::cout << "float: " << static_cast<float>(d) << ".0f" << std::endl;
			std::cout << "double: " << d << ".0" << std::endl;
		} else {
			if (d > std::numeric_limits<float>::max() || d < std::numeric_limits<float>::min())
				std::cout << "float: impossible" << std::endl;
			else
				std::cout << std::setprecision(7) << "float: " << static_cast<float>(d) << "f" << std::endl;
			std::cout << std::setprecision(15) << "double: " << d << std::endl;
		}
		return;

	} else {
		long nl = std::strtol(literal.c_str(), &end, 10);
        if (errno == ERANGE || *end != '\0' || nl < INT_MIN || nl > INT_MAX) {
            std::cout << "Conversione in int fuori range o non valida" << std::endl;
            return;
        }
		
		int n = std::atoi(literal.c_str());
		if (n < 33 || n > 126)
			std::cout << "char: Non displayable" << std::endl;
		else
			std::cout << "char: '" << static_cast<char>(n) << "'" << std::endl;
		std::cout << "int: " << n << std::endl;
		if (n > std::numeric_limits<float>::max() || n < std::numeric_limits<float>::min())
			std::cout << "float: impossible" << std::endl;
		else
			std::cout << "float: " << static_cast<float>(n) << ".0f" << std::endl;
		if (n > std::numeric_limits<float>::max() || n < std::numeric_limits<float>::min())
			std::cout << "double: impossible" << std::endl;
		else
			std::cout << "double: " << static_cast<double>(n) << ".0" << std::endl;
	}
}
