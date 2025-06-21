/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fwoosh.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:49:39 by dde-giov          #+#    #+#             */
/*   Updated: 2025/06/11 00:39:43 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fwoosh.hpp"

		Fwoosh::Fwoosh() : ASpell("Fwoosh", "fwooshed") {
			//std::cout << name << ": This looks like another boring day." << std::endl;
		}

		Fwoosh::~Fwoosh() {
			//std::cout << name << ": My job here is done!" << std::endl;
		}
		
		Fwoosh *Fwoosh::clone() const {
			return new Fwoosh();
		}
		