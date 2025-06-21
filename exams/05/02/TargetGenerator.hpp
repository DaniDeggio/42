#ifndef TARGETGENERATOR_HPP
# define TARGETGENERATOR_HPP

#include <string>
#include <iostream>
#include <vector>

#include "ATarget.hpp"

class ATarget;

class TargetGenerator{
	private:

		std::vector<ATarget *> targets;
	
		TargetGenerator(TargetGenerator const &src);
		TargetGenerator &operator=(TargetGenerator const &src);
	public:

		TargetGenerator();
		~TargetGenerator();
		
		void learnTargetType(ATarget *target);
		void forgetTargetType(std::string const &target);
		ATarget *createTarget(std::string const &target);
};

#endif