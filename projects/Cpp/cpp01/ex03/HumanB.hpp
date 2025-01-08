/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 20:50:20 by dde-giov          #+#    #+#             */
/*   Updated: 2024/10/13 17:00:31 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
# define HUMANB_HPP

#include <string>
#include <iostream>
#include "Weapon.hpp"

class HumanB{
	private:
		std::string	name;
		Weapon	*gun;

	public:
		HumanB(std::string	name);
		~HumanB();

		void	attack();
		void    setWeapon(Weapon &gun);
};

#endif