/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Polymorph.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:49:39 by dde-giov          #+#    #+#             */
/*   Updated: 2025/06/11 00:59:23 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Polymorph.hpp"

		Polymorph::Polymorph() : ASpell("Polymorph", "turned into a critter") {
			//std::cout << name << ": This looks like another boring day." << std::endl;
		}

		Polymorph::~Polymorph() {
			//std::cout << name << ": My job here is done!" << std::endl;
		}
		
		Polymorph *Polymorph::clone() const {
			return new Polymorph();
		}
		