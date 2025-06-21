#include "ASpell.hpp"

	ASpell::ASpell() : name(), effects(){
	}

	ASpell::ASpell(std::string const &name, std::string const &effects) : name(name), effects(effects){
	}

	ASpell::ASpell(ASpell const &src) : name(src.name), effects(src.effects){
	}

	ASpell &ASpell::operator=(ASpell const &src){
		if (this != &src)
			this->name = src.name;
			this->effects = src.effects;
		return (*this);
	}

	ASpell::~ASpell(){
	}
	
	std::string const &ASpell::getName() const{
		return(this->name);
	}

	std::string const &ASpell::getEffects() const{
		return(this->effects);
	}

	void ASpell::launch(ATarget const &target) const{
		target.getHitBySpell(*this);
	}
