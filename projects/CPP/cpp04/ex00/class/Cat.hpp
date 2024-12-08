/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:58:27 by dde-giov          #+#    #+#             */
/*   Updated: 2024/11/03 21:12:22 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

#include <iostream>
#include <string>

#include "Animal.hpp"

class Cat : public Animal {
    public:
        Cat(); // Default constructor
        ~Cat(); // Destructor
        Cat(const Cat &src); // Copy constructor
        Cat &operator=(const Cat &src); // Copy assignment operator
        
        void makeSound() const;
};

#endif