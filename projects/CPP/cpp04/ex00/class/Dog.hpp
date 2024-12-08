/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:11:44 by dde-giov          #+#    #+#             */
/*   Updated: 2024/11/03 21:12:16 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

#include <iostream>
#include <string>

#include "Animal.hpp"

class Dog : public Animal {
    public:
        Dog(); // Default constructor
        ~Dog(); // Destructor
        Dog(const Dog &src); // Copy constructor
        Dog &operator=(const Dog &src); // Copy assignment operator
        
        void makeSound() const;
};

#endif