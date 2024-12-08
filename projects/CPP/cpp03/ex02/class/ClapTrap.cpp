/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:57:16 by dde-giov          #+#    #+#             */
/*   Updated: 2024/10/24 18:26:22 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(std::string name) : name(name), hitPoints(10), energyPoints(10), attackDamage(0) {
	std::cout << "ClapTrap constructor called" << std::endl;
}

ClapTrap::ClapTrap() : name("ClapTrap"), hitPoints(10), energyPoints(10), attackDamage(0) {
	std::cout << "ClapTrap constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &src) : name(src.name), hitPoints(src.hitPoints), energyPoints(src.energyPoints), attackDamage(src.attackDamage) {
	std::cout << "ClapTrap copy constructor called" << std::endl;
}

ClapTrap::~ClapTrap() {
	std::cout << "ClapTrap destructor called" << std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &src) {
	std::cout << "ClapTrap assignation operator called" << std::endl;
	if (this != &src) {
		this->name = src.name;
		this->hitPoints = src.hitPoints;
		this->energyPoints = src.energyPoints;
		this->attackDamage = src.attackDamage;
	}
	return *this;
}

void ClapTrap::attack(const std::string &target) {
	if (this->hitPoints <= 0) {
		std::cout << "ClapTrap " << this->name << " is dead and cannot attack!" << std::endl;
		return;
	}
	else if (this->energyPoints <= 0) {
		std::cout << "ClapTrap " << this->name << " has no energy and cannot attack!" << std::endl;
		return;
	}
	this->energyPoints -= 1;
	std::cout << "ClapTrap " << this->name << " attacks " << target << " causing " << this->attackDamage << " points of damage!" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount) {
	this->hitPoints -= amount;
	std::cout << "ClapTrap " << this->name << " takes " << amount << " points of damage!" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount) {
	if (this->hitPoints <= 0) {
		std::cout << "ClapTrap " << this->name << " is dead and cannot be repaired!" << std::endl;
		return;
	}
	else if (this->energyPoints <= 0) {
		std::cout << "ClapTrap " << this->name << " has no energy and cannot be repaired!" << std::endl;
		return;
	}
	this->energyPoints -= 1;
	this->hitPoints += amount;
	std::cout << "ClapTrap " << this->name << " is repaired by " << amount << " points!" << std::endl;
}
