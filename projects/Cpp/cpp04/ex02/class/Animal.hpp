/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:01:32 by dde-giov          #+#    #+#             */
/*   Updated: 2024/09/19 16:27:32 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include <iostream>
#include <string>

class Animal {
    protected:
        std::string type;
    public:
        Animal();
        Animal(std::string type);
        virtual ~Animal();
        Animal(const Animal &src);
        Animal &operator=(const Animal &src);
        
        virtual void makeSound() const = 0;
        
        std::string getType() const;
};

#endif