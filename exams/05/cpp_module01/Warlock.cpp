/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:27:44 by dde-giov          #+#    #+#             */
/*   Updated: 2025/06/11 00:28:38 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Warlock.hpp"

		Warlock::Warlock(std::string const &name, std::string const &title) : name(name), title(title){
			std::cout << name << ": This looks like another boring day." << std::endl;
		}

		Warlock::~Warlock() {
			std::cout << name << ": My job here is done!" << std::endl;
		}
		
		std::string const &Warlock::getName() const {
			return name;
		}
		
		std::string const &Warlock::getTitle() const {
			return title;
		}

		void Warlock::setTitle(std::string const &title) {
			this->title = title;
		}

		void Warlock::introduce() const {
			std::cout << name << ": I am " << name << ", " << title << "!" << std::endl;
		}
		
		void Warlock::learnSpell(ASpell *spell) {
			if (spell)
				spells.push_back(spell->clone());
		}

		void Warlock::forgetSpell(std::string const &spellName) {
			// c++ 98
			std::vector<ASpell *>::iterator it = spells.begin();
			for (; it != spells.end(); ) {
				if ((*it)->getName() == spellName) {
					delete *it;
					it = spells.erase(it);
				}
			}
		}

		void Warlock::launchSpell(std::string const &spellName, ATarget &target) const {
			std::vector<ASpell *>::const_iterator it = spells.begin();
			for (; it != spells.end(); ++it) {
				if ((*it)->getName() == spellName) {
					(*it)->lunchSpell(target);
					return;
				}
			}
		}