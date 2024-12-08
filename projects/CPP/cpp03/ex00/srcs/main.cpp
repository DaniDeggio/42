/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:18:01 by dde-giov          #+#    #+#             */
/*   Updated: 2024/09/11 19:46:50 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../class/ClapTrap.hpp"

int main() {
	ClapTrap claptrap("TestClap");
	ClapTrap claptrap2("TestClap2");

	for (int i = 0; i < 11; i++) {
		claptrap.attack("TestClap2");
	}
	claptrap2.takeDamage(42);
	claptrap2.attack("TestClap");
	claptrap.beRepaired(42);
	claptrap2.beRepaired(42);
	claptrap2.attack("TestClap");
	return 0;
}
