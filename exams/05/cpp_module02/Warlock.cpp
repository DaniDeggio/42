/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:27:44 by dde-giov          #+#    #+#             */
/*   Updated: 2025/06/11 01:58:13 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Warlock.hpp"

		Warlock::Warlock(std::string const &name, std::string const &title) : name(name), title(title){
			SpellBook *spellBook = new SpellBook();
			this->spellBook = spellBook;
			std::cout << name << ": This looks like another boring day." << std::endl;
		}

		Warlock::~Warlock() {
			delete spellBook;
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
				spellBook->learnSpell(spell);
		}

		void Warlock::forgetSpell(std::string const &spellName) {
			spellBook->forgetSpell(spellName);
		}

		void Warlock::launchSpell(std::string const &spellName, ATarget &target) const {
			ASpell *spell = spellBook->createSpell(spellName);

			if (spell) {
				spell->lunchSpell(target);
				delete spell;
			}
		}