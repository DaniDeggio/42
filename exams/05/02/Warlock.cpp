
#include "Warlock.hpp"

Warlock::Warlock(std::string const &name, std::string const &title) : name(name), title(title){
	std::cout << this->name << ": What a boring day\n";
}

Warlock::~Warlock(){
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
	this->spells.learnSpell(spell);
}

void Warlock::forgetSpell(std::string const &spell){
	this->spells.forgetSpell(spell);
}

void Warlock::launchSpell(std::string const &spell, ATarget const &target){
	ASpell *spl = this->spells.createSpell(spell);
	if (spl) {
		spl->launch(target);
	}
}
