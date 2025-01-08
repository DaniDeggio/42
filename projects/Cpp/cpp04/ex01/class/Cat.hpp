/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:58:27 by dde-giov          #+#    #+#             */
/*   Updated: 2024/11/03 21:57:30 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

#include <iostream>
#include <string>

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal {
    private:
        Brain *brain;
    public:
        Cat();
        Cat(const Cat &src);
        Cat &operator=(const Cat &src);
        ~Cat();
        
        void makeSound() const;
        Brain *getBrain() const;
};

#endif