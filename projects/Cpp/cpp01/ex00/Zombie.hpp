/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 02:32:42 by dde-giov          #+#    #+#             */
/*   Updated: 2024/10/13 16:52:25 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <iostream>
#include <string>

class Zombie {
	private:
		std::string name;

	public:
		Zombie(std::string name);
		~Zombie(void);

		void    announce(void);
};

Zombie  *newZombie(std::string name);
void    randomChump(std::string name);

#endif