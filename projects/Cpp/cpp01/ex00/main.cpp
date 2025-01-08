/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:05:19 by dde-giov          #+#    #+#             */
/*   Updated: 2024/06/18 15:10:58 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void) {
	Zombie  *z1 = newZombie("Zombie1");
	Zombie  *z2 = newZombie("Zombie2");
	Zombie  *z3 = newZombie("Zombie3");

	z1->announce();
	z2->announce();
	z3->announce();
	randomChump("Zombie4");
	randomChump("Zombie5");

	delete z1;
	delete z2;
	delete z3;

	return (0);
}
