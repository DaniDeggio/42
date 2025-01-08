/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:10:36 by dde-giov          #+#    #+#             */
/*   Updated: 2024/10/24 20:03:44 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap(std::string name) : ClapTrap::ClapTrap(name){
	hitPoints = 100;
	energyPoints = 50;
	attackDamage = 20;
	std::cout << "ScavTrap constructor called" << std::endl;
}

ScavTrap::ScavTrap() : ClapTrap::ClapTrap(){
	hitPoints = 100;
	energyPoints = 50;
	attackDamage = 20;
	std::cout << "ScavTrap default constructor called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &src) : ClapTrap::ClapTrap(src.name){
	hitPoints = src.hitPoints;
	energyPoints = src.energyPoints;
	attackDamage = src.attackDamage;
	std::cout << "ScavTrap copy constructor called" << std::endl;
}

ScavTrap::~ScavTrap() {
	std::cout << "ScavTrap destructor called" << std::endl;
}
 
ScavTrap &ScavTrap::operator=(const ScavTrap &src) {
	std::cout << "ScavTrap assignation operator called" << std::endl;
	if (this != &src) {
		this->name = src.name;
		this->hitPoints = src.hitPoints;
		this->energyPoints = src.energyPoints;
		this->attackDamage = src.attackDamage;
	}
	return *this;
}

void ScavTrap::guardGate() {
    std::cout << "ScavTrap " << name << " has entered in Gate keeper mode!" << std::endl;
}

void ScavTrap::attack(const std::string &target) {
	if (hitPoints == 0) {
		std::cout << "ScavTrap " << name << " is dead and cannot attack!" << std::endl;
		return;
	}
	else if (energyPoints == 0) {
		std::cout << "ScavTrap " << name << " has no energy and cannot attack!" << std::endl;
		return;
	}
	energyPoints--;
	std::cout << "ScavTrap " << name << " attacks " << target << " causing " << attackDamage << " points of damage!" << std::endl;
}