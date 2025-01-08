/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:01:23 by dde-giov          #+#    #+#             */
/*   Updated: 2024/11/03 21:54:52 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() : Animal("Cat") {
    std::cout << "Cat constructor called" << std::endl;
}

Cat::Cat(const Cat &src) : Animal("Cat") {
    *this = src;
    std::cout << "Cat copy constructor called" << std::endl;
}

Cat::~Cat() {
    std::cout << "Cat destructor called" << std::endl;
}

Cat &Cat::operator=(const Cat &src) {
    if (this != &src)
        this->type = src.type;
    std::cout << "Cat assignation operator called" << std::endl;
    return *this;
}

void    Cat::makeSound() const {
    std::cout << "Miao Miao" << std::endl;
}
