/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 20:50:20 by dde-giov          #+#    #+#             */
/*   Updated: 2024/10/13 17:00:37 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
# define HUMANA_HPP

#include <string>
#include <iostream>
#include "Weapon.hpp"

class HumanA{
	private:
		std::string	name;
		Weapon	 &gun;
        HumanA(void);

	public:
        HumanA(std::string	name, Weapon &gun);
		~HumanA();

		void	attack();
};

#endif
