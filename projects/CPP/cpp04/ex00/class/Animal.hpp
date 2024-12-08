/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:01:32 by dde-giov          #+#    #+#             */
/*   Updated: 2024/11/03 21:12:52 by dde-giov         ###   ########.fr       */
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
		Animal(std::string type); // Type constructor

		Animal(); // Default constructor
		virtual ~Animal(); // Destructor
		Animal(const Animal &src); // Copy constructor
		Animal &operator=(const Animal &src); // Copy assignment operator
		
		virtual void makeSound() const;
		std::string getType() const;
};

#endif