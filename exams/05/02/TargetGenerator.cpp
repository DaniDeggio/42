
#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator(){}

TargetGenerator::~TargetGenerator(){
	std::vector<ATarget *>::iterator ite = this->targets.end();
	for (std::vector<ATarget *>::iterator it = this->targets.begin(); it != ite; ++it)
		delete *it;
	this->targets.clear();
}

void TargetGenerator::learnTargetType(ATarget *target){
	if(target){
		std::vector<ATarget *>::iterator ite = this->targets.end();
		for (std::vector<ATarget *>::iterator it = this->targets.begin(); it != ite; ++it){
			if ((*it)->getType() == target->getType())
				return;
		}
		this->targets.push_back(target->clone());
	}
}

void TargetGenerator::forgetTargetType(std::string const &target){
	std::vector<ATarget *>::iterator ite = this->targets.end();
	for (std::vector<ATarget *>::iterator it = this->targets.begin(); it != ite; ++it){
		if ((*it)->getType() == target){
			delete *it;
			it = this->targets.erase(it);
		}
	}
}

ATarget *TargetGenerator::createTarget(std::string const &target){
	std::vector<ATarget *>::iterator ite = this->targets.end();
	for (std::vector<ATarget *>::iterator it = this->targets.begin(); it != ite; ++it){
		if ((*it)->getType() == target)
			return ((*it)->clone());
	}
	return (NULL);
}
