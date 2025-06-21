#ifndef SPELLBOOK_HPP
# define SPELLBOOK_HPP

#include <string>
#include <iostream>
#include <vector>

#include "ASpell.hpp"

class ASpell;

class SpellBook{
	private:

		std::vector<ASpell *> spells;
	
		SpellBook(SpellBook const &src);
		SpellBook &operator=(SpellBook const &src);
	public:

		SpellBook();
		~SpellBook();
		
		void learnSpell(ASpell *spell);
		void forgetSpell(std::string const &spell);
		ASpell *createSpell(std::string const &spell);
};

#endif