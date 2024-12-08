/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 21:06:38 by dde-giov          #+#    #+#             */
/*   Updated: 2024/10/21 18:55:06 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "HumanB.hpp"

HumanB::HumanB(std::string name) : name(name), gun(NULL) {
	return ;	
}

HumanB::~HumanB(void) {
	return ;
}

void	HumanB::attack(void) {
	std::cout << this->name << " attacks with their " << this->gun->getType() << std::endl;
}

void    HumanB::setWeapon(Weapon &gun){
    this->gun = &gun;
}
