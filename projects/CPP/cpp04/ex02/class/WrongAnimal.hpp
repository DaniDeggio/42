/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:01:32 by dde-giov          #+#    #+#             */
/*   Updated: 2024/09/11 20:19:28 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

#include <iostream>
#include <string>

class WrongAnimal {
    protected:
        std::string type;
    public:
        WrongAnimal(std::string type); // Type constructor
    
        WrongAnimal(); // Default constructor
        ~WrongAnimal(); // Destructor
        WrongAnimal(const WrongAnimal &src); // Copy constructor
        WrongAnimal &operator=(const WrongAnimal &src); // Copy assignment operator
        
        void makeSound() const;
        
        std::string getType() const;
};

#endif