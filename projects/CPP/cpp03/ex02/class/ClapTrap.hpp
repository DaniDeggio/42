/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:51:22 by dde-giov          #+#    #+#             */
/*   Updated: 2024/10/24 19:52:19 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

#include <iostream>
#include <string>

class ClapTrap
{
	protected:
		std::string name;
		int hitPoints;
		int energyPoints;
		int attackDamage;
		
	public:
		ClapTrap(std::string name);
		ClapTrap(); // Default constructor
		ClapTrap(const ClapTrap &src); // Copy constructor
		virtual ~ClapTrap();
		ClapTrap &operator=(const ClapTrap &src); // Assignment operator

		virtual void attack(const std::string &target);
		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);
};

#endif
