
#include "Warlock.hpp"

Warlock::Warlock(std::string const &name, std::string const &title) : name(name), title(title){
	std::cout << this->name << ": What a boring day\n";
}

Warlock::~Warlock(){
	std::vector<ASpell *>::iterator ite = this->spells.end();
	for (std::vector<ASpell *>::iterator it = this->spells.begin(); it != ite; ++it)
		delete *it;
	this->spells.clear();
	std::cout << this->name << ": My job here is done!\n";

}

std::string const &Warlock::getName() const{
	return(this->name);
}

std::string const &Warlock::getTitle() const{
	return(this->title);

}

void Warlock::setTitle(std::string const &ttl){
	this->title = ttl;
}

void Warlock::introduce() const{
	std::cout << this->name << ": My name is " << this->name << ", " << this->title << "!\n";
}

void Warlock::learnSpell(ASpell *spell){
	if(spell){
		std::vector<ASpell *>::iterator ite = this->spells.end();
		for (std::vector<ASpell *>::iterator it = this->spells.begin(); it != ite; ++it){
			if ((*it)->getName() == spell->getName())
				return;
		}
		this->spells.push_back(spell->clone());
	}
}

void Warlock::forgetSpell(std::string const &spell){
	std::vector<ASpell *>::iterator ite = this->spells.end();
	for (std::vector<ASpell *>::iterator it = this->spells.begin(); it != ite; ++it){
		if ((*it)->getName() == spell){
			delete *it;
			it = this->spells.erase(it);
		}
	}
}

void Warlock::launchSpell(std::string const &spell, ATarget const &target){
	std::vector<ASpell *>::iterator ite = this->spells.end();
	for (std::vector<ASpell *>::iterator it = this->spells.begin(); it != ite; ++it){
		if ((*it)->getName() == spell){
			(*it)->launch(target);
			return;
		}
	}
}
