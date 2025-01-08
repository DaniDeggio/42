/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:01:16 by dde-giov          #+#    #+#             */
/*   Updated: 2024/11/03 21:54:46 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal() : type("Animal") {
    std::cout << "Animal default constructor called" << std::endl;
}

Animal::Animal(std::string type) : type(type) {
    std::cout << "Animal constructor called" << std::endl;
}

Animal::~Animal() {
    std::cout << "Animal destructor called" << std::endl;
}

Animal::Animal(const Animal &src) {
    *this = src;
    std::cout << "Animal copy constructor called" << std::endl;
}

Animal &Animal::operator=(const Animal &src) {
    if (this != &src)
        this->type = src.type;
    std::cout << "Animal assignation operator called" << std::endl;
    return *this;
}

std::string Animal::getType() const {
    return this->type;
}

void Animal::makeSound() const {
    std::cout << "Animal sound" << std::endl;
}
