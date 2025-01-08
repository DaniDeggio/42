/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:01:23 by dde-giov          #+#    #+#             */
/*   Updated: 2024/09/11 20:22:25 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat() : WrongAnimal("WrongCat") {
    std::cout << "WrongCat constructor called" << std::endl;
}

WrongCat::~WrongCat() {
    std::cout << "WrongCat destructor called" << std::endl;
}

WrongCat::WrongCat(const WrongCat &src) : WrongAnimal("WrongCat") {
    *this = src;
    std::cout << "WrongCat copy constructor called" << std::endl;
}

WrongCat &WrongCat::operator=(const WrongCat &src) {
    if (this != &src)
        this->type = src.type;
    std::cout << "WrongCat assignation operator called" << std::endl;
    return *this;
}

void    WrongCat::makeSound() const {
    std::cout << "Miao Meow" << std::endl;
}
