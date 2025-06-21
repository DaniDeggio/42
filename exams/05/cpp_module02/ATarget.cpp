/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ATarget.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:39:34 by dde-giov          #+#    #+#             */
/*   Updated: 2025/06/11 00:38:31 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATarget.hpp"

		ATarget::ATarget(std::string const &type) : type(type) {
			//std::cout << name << ": This looks like another boring day." << std::endl;
		}

		ATarget::~ATarget() {
			//std::cout << name << ": My job here is done!" << std::endl;
		}
		
		std::string const &ATarget::getType() const {
			return type;
		}

		void ATarget::getHitBySpell(const ASpell &spell) const {
			std::cout << type << " has been " << spell.getEffects() << "!" << std::endl;
		}