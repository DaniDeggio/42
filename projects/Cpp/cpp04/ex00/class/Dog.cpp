/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:01:29 by dde-giov          #+#    #+#             */
/*   Updated: 2024/11/03 21:54:55 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"


Dog::Dog() : Animal("Dog") {
    std::cout << "Dog constructor called" << std::endl;
}

Dog::~Dog() {
    std::cout << "Dog destructor called" << std::endl;
}

Dog::Dog(const Dog &src) : Animal("Dog") {
    *this = src;
    std::cout << "Dog copy constructor called" << std::endl;
}

Dog &Dog::operator=(const Dog &src) {
    if (this != &src)
        this->type = src.type;
    std::cout << "Dog assignation operator called" << std::endl;
    return *this;
}

void    Dog::makeSound() const {
    std::cout << "BAU Bau" << std::endl;
}

