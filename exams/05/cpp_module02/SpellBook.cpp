/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SpellBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:27:44 by dde-giov          #+#    #+#             */
/*   Updated: 2025/06/11 01:59:02 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SpellBook.hpp"

		SpellBook::SpellBook() {
			// 
		}

		SpellBook::~SpellBook() {
			//
		}
	
		void SpellBook::learnSpell(ASpell *spell) {
			if (spell)
				spells.push_back(spell->clone());
		}

		void SpellBook::forgetSpell(std::string const &spellName) {
			std::vector<ASpell *>::iterator it = spells.begin();
			for (; it != spells.end(); ) {
				if ((*it)->getName() == spellName) {
					delete *it;
					it = spells.erase(it);
				}
			}
		}

		ASpell *SpellBook::createSpell(std::string const &spellName) const {
			std::vector<ASpell *>::const_iterator it = spells.begin();
			for (; it != spells.end(); ++it) {
				if ((*it)->getName() == spellName)
					return (*it)->clone();
			}
			return NULL;
		}
