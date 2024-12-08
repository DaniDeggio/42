/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:05:19 by dde-giov          #+#    #+#             */
/*   Updated: 2024/06/18 15:51:40 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void) {
	Zombie *horde = zombieHorde(5, "Zombie");

	for (int i = 0; i < 5; ++i) {
		horde[i].announce();
	}

	delete [] horde;
	return 0;
}
