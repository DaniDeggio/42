/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASpell.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:17:30 by dde-giov          #+#    #+#             */
/*   Updated: 2025/06/11 01:39:04 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ASpell.hpp"

		ASpell::ASpell(std::string const &name, std::string const &effects) : name(name), effects(effects){
			//std::cout << name << ": This looks like another boring day." << std::endl;
		}

		ASpell::~ASpell() {
			//std::cout << name << ": My job here is done!" << std::endl;
		}
		
		std::string const &ASpell::getName() const {
			return name;
		}
		
		std::string const &ASpell::getEffects() const {
			return effects;
		}

		void ASpell::lunchSpell(const ATarget &target) const {
			target.getHitBySpell(*this);
		}