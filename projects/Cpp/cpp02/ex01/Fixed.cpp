/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:26:22 by dde-giov          #+#    #+#             */
/*   Updated: 2024/07/04 19:54:07 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed(void): fx_value(0) {
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &fx) {
	std::cout << "Copy constructor called" << std::endl;
	*this = fx;
}

Fixed::Fixed(const int value): fx_value(value << this->fract) {
	std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(const float value): fx_value(roundf(value * (1 << this->fract))) {
	std::cout << "Float constructor called" << std::endl;
}

Fixed &Fixed::operator=(const Fixed &fx) {
	std::cout << "Assignation operator called" << std::endl;
	if (this != &fx)
		this->fx_value = fx.getRawBits();
	return *this;
}

Fixed::~Fixed(void) {
	std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits( void ) const {
	std::cout << "getRawBits member function called" << std::endl;
	return this->fx_value;
}

void Fixed::setRawBits( int const raw ) {
	std::cout << "setRawBits member function called" << std::endl;
	this->fx_value = raw;
}

float Fixed::toFloat( void ) const {
	return static_cast<float>(this->fx_value) / (1 << this->fract);
}

int	Fixed::toInt( void ) const {
	return this->fx_value >> this->fract;
}

std::ostream & operator<<(std::ostream &out, const Fixed &fx) {
	out << fx.toFloat();
	return out;
}
