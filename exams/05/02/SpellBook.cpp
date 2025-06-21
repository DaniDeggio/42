
#include "SpellBook.hpp"

SpellBook::SpellBook(){}

SpellBook::~SpellBook(){
	std::vector<ASpell *>::iterator ite = this->spells.end();
	for (std::vector<ASpell *>::iterator it = this->spells.begin(); it != ite; ++it)
		delete *it;
	this->spells.clear();
}

void SpellBook::learnSpell(ASpell *spell){
	if(spell){
		std::vector<ASpell *>::iterator ite = this->spells.end();
		for (std::vector<ASpell *>::iterator it = this->spells.begin(); it != ite; ++it){
			if ((*it)->getName() == spell->getName())
				return;
		}
		this->spells.push_back(spell->clone());
	}
}

void SpellBook::forgetSpell(std::string const &spell){
	std::vector<ASpell *>::iterator ite = this->spells.end();
	for (std::vector<ASpell *>::iterator it = this->spells.begin(); it != ite; ++it){
		if ((*it)->getName() == spell){
			delete *it;
			it = this->spells.erase(it);
		}
	}
}

ASpell *SpellBook::createSpell(std::string const &spell){
	std::vector<ASpell *>::iterator ite = this->spells.end();
	for (std::vector<ASpell *>::iterator it = this->spells.begin(); it != ite; ++it){
		if ((*it)->getName() == spell)
			return ((*it)->clone());
	}
	return (NULL);
}
