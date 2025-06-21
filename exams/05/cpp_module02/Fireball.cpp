/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fireball.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:49:39 by dde-giov          #+#    #+#             */
/*   Updated: 2025/06/11 00:59:06 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fireball.hpp"

		Fireball::Fireball() : ASpell("Fireball", "burnt to a crisp") {
			//std::cout << name << ": This looks like another boring day." << std::endl;
		}

		Fireball::~Fireball() {
			//std::cout << name << ": My job here is done!" << std::endl;
		}
		
		Fireball *Fireball::clone() const {
			return new Fireball();
		}
		