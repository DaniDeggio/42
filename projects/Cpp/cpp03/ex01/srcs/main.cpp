/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:18:01 by dde-giov          #+#    #+#             */
/*   Updated: 2024/10/24 20:06:26 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../class/ClapTrap.hpp"
#include "../class/ScavTrap.hpp"

int main() {
	ClapTrap claptrap("TestClap");
	ClapTrap claptrap2("TestClap2");
	std::cout << std::endl;

	ScavTrap scavtrap("TestScav");
	ScavTrap scavtrap2("TestScav2");
	std::cout << std::endl;

	for (int i = 0; i < 11; i++) {
		claptrap.attack("TestClap2");
	}
	std::cout << std::endl;

	claptrap2.takeDamage(42);
	claptrap2.attack("TestClap");
	std::cout << std::endl;

	claptrap.beRepaired(42);
	claptrap2.beRepaired(42);
	claptrap2.attack("TestClap");
	std::cout << std::endl;

	scavtrap2.attack("TestClap");
	claptrap.takeDamage(20);
	claptrap.attack("TestScav");
	scavtrap2.guardGate();
	std::cout << std::endl;
	return 0;
}
