/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:01:29 by dde-giov          #+#    #+#             */
/*   Updated: 2024/11/03 22:47:58 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"


Dog::Dog() : Animal("Dog") {
    brain = new Brain();
    std::cout << "Dog constructor called" << std::endl;
}

Dog::Dog(const Dog &src) : Animal("Dog") {
    brain = new Brain(*src.brain);
    std::cout << "Dog copy constructor called" << std::endl;
}

Dog &Dog::operator=(const Dog &src) {
    if (this != &src) {
        Animal::operator=(src);
        delete brain;
        brain = new Brain(*src.brain);
    }
    std::cout << "Dog assignation operator called" << std::endl;
    return *this;
}

Dog::~Dog() {
    delete brain;
    std::cout << "Dog destructor called" << std::endl;
}

void    Dog::makeSound() const {
    std::cout << "BAU Bau" << std::endl;
}

Brain *Dog::getBrain() const {
    return brain;
}