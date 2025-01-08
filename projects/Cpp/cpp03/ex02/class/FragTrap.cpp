/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:10:36 by dde-giov          #+#    #+#             */
/*   Updated: 2024/10/24 20:04:44 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap(std::string name) : ClapTrap::ClapTrap(name){
	hitPoints = 100;
	energyPoints = 100;
	attackDamage = 30;
	std::cout << "FragTrap constructor called" << std::endl;
}

FragTrap::FragTrap() : ClapTrap::ClapTrap(){
	hitPoints = 100;
	energyPoints = 100;
	attackDamage = 30;
	std::cout << "FragTrap default constructor called" << std::endl;
}

FragTrap::FragTrap(const FragTrap &src) : ClapTrap::ClapTrap(src.name){
	hitPoints = src.hitPoints;
	energyPoints = src.energyPoints;
	attackDamage = src.attackDamage;
	std::cout << "FragTrap copy constructor called" << std::endl;
}

FragTrap::~FragTrap() {
	std::cout << "FragTrap destructor called" << std::endl;
}

FragTrap &FragTrap::operator=(const FragTrap &src) {
	std::cout << "FragTrap assignation operator called" << std::endl;
	if (this != &src) {
		this->name = src.name;
		this->hitPoints = src.hitPoints;
		this->energyPoints = src.energyPoints;
		this->attackDamage = src.attackDamage;
	}
	return *this;
}

void FragTrap::highFivesGuys() {
	std::cout << "FragTrap " << name << " high fives guys!" << std::endl;
}